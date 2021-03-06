/*
 *  ReactOS kernel
 *  Copyright (C) 2002, 2014 ReactOS Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * COPYRIGHT:        See COPYING in the top level directory
 * PROJECT:          ReactOS kernel
 * FILE:             drivers/filesystem/ntfs/fcb.c
 * PURPOSE:          NTFS filesystem driver
 * PROGRAMMERS:      Eric Kohl
 *                   Pierre Schweitzer (pierre@reactos.org)
 *                   Hervé Poussineau (hpoussin@reactos.org)
 */

/* INCLUDES *****************************************************************/

#include "ntfs.h"

#define NDEBUG
#include <debug.h>

/* MACROS *******************************************************************/

#define TAG_FCB 'BCFI'

/* FUNCTIONS ****************************************************************/

static
PWCHAR
NtfsGetNextPathElement(PWCHAR FileName)
{
    if (*FileName == L'\0')
    {
        return NULL;
    }

    while (*FileName != L'\0' && *FileName != L'\\')
    {
        FileName++;
    }

    return FileName;
}


static
VOID
NtfsWSubString(PWCHAR pTarget,
               const PWCHAR pSource,
               size_t pLength)
{
    wcsncpy(pTarget, pSource, pLength);
    pTarget[pLength] = L'\0';
}


PNTFS_FCB
NtfsCreateFCB(PCWSTR FileName,
              PNTFS_VCB Vcb)
{
    PNTFS_FCB Fcb;

    ASSERT(Vcb);
    ASSERT(Vcb->Identifier.Type == NTFS_TYPE_VCB);

    Fcb = ExAllocatePoolWithTag(NonPagedPool, sizeof(NTFS_FCB), TAG_FCB);
    RtlZeroMemory(Fcb, sizeof(NTFS_FCB));

    Fcb->Identifier.Type = NTFS_TYPE_FCB;
    Fcb->Identifier.Size = sizeof(NTFS_TYPE_FCB);

    Fcb->Vcb = Vcb;

    if (FileName)
    {
        wcscpy(Fcb->PathName, FileName);
        if (wcsrchr(Fcb->PathName, '\\') != 0)
        {
            Fcb->ObjectName = wcsrchr(Fcb->PathName, '\\');
        }
        else
        {
            Fcb->ObjectName = Fcb->PathName;
        }
    }

    ExInitializeResourceLite(&Fcb->MainResource);

    Fcb->RFCB.Resource = &(Fcb->MainResource);

    return Fcb;
}


VOID
NtfsDestroyFCB(PNTFS_FCB Fcb)
{
    ASSERT(Fcb);
    ASSERT(Fcb->Identifier.Type == NTFS_TYPE_FCB);

    ExDeleteResourceLite(&Fcb->MainResource);

    ExFreePool(Fcb);
}


BOOLEAN
NtfsFCBIsDirectory(PNTFS_FCB Fcb)
{
    return ((Fcb->Entry.FileAttributes & NTFS_FILE_TYPE_DIRECTORY) == NTFS_FILE_TYPE_DIRECTORY);
}


BOOLEAN
NtfsFCBIsRoot(PNTFS_FCB Fcb)
{
    return (wcscmp(Fcb->PathName, L"\\") == 0);
}


VOID
NtfsGrabFCB(PNTFS_VCB Vcb,
            PNTFS_FCB Fcb)
{
    KIRQL oldIrql;

    DPRINT("grabbing FCB at %p: %S, refCount:%d\n",
           Fcb,
           Fcb->PathName,
           Fcb->RefCount);

    KeAcquireSpinLock(&Vcb->FcbListLock, &oldIrql);
    Fcb->RefCount++;
    KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
}


VOID
NtfsReleaseFCB(PNTFS_VCB Vcb,
               PNTFS_FCB Fcb)
{
    KIRQL oldIrql;

    DPRINT("releasing FCB at %p: %S, refCount:%d\n",
           Fcb,
           Fcb->PathName,
           Fcb->RefCount);

    KeAcquireSpinLock(&Vcb->FcbListLock, &oldIrql);
    Fcb->RefCount--;
    if (Fcb->RefCount <= 0 && !NtfsFCBIsDirectory(Fcb))
    {
        RemoveEntryList(&Fcb->FcbListEntry);
        KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
        CcUninitializeCacheMap(Fcb->FileObject, NULL, NULL);
        NtfsDestroyFCB(Fcb);
    }
    else
    {
        KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
    }
}


VOID
NtfsAddFCBToTable(PNTFS_VCB Vcb,
                  PNTFS_FCB Fcb)
{
    KIRQL oldIrql;

    KeAcquireSpinLock(&Vcb->FcbListLock, &oldIrql);
    Fcb->Vcb = Vcb;
    InsertTailList(&Vcb->FcbListHead, &Fcb->FcbListEntry);
    KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
}


PNTFS_FCB
NtfsGrabFCBFromTable(PNTFS_VCB Vcb,
                     PCWSTR FileName)
{
    KIRQL oldIrql;
    PNTFS_FCB Fcb;
    PLIST_ENTRY current_entry;

    KeAcquireSpinLock(&Vcb->FcbListLock, &oldIrql);

    if (FileName == NULL || *FileName == 0)
    {
        DPRINT("Return FCB for stream file object\n");
        Fcb = Vcb->StreamFileObject->FsContext;
        Fcb->RefCount++;
        KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
        return Fcb;
    }

    current_entry = Vcb->FcbListHead.Flink;
    while (current_entry != &Vcb->FcbListHead)
    {
        Fcb = CONTAINING_RECORD(current_entry, NTFS_FCB, FcbListEntry);

        DPRINT("Comparing '%S' and '%S'\n", FileName, Fcb->PathName);
        if (_wcsicmp(FileName, Fcb->PathName) == 0)
        {
            Fcb->RefCount++;
            KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
            return Fcb;
        }

        //FIXME: need to compare against short name in FCB here

        current_entry = current_entry->Flink;
    }

    KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);

    return NULL;
}


NTSTATUS
NtfsFCBInitializeCache(PNTFS_VCB Vcb,
                       PNTFS_FCB Fcb)
{
    PFILE_OBJECT FileObject;
    NTSTATUS Status;
    PNTFS_CCB newCCB;

    FileObject = IoCreateStreamFileObject(NULL, Vcb->StorageDevice);

    newCCB = ExAllocatePoolWithTag(NonPagedPool, sizeof(NTFS_CCB), TAG_CCB);
    if (newCCB == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlZeroMemory(newCCB, sizeof(NTFS_CCB));

    newCCB->Identifier.Type = NTFS_TYPE_CCB;
    newCCB->Identifier.Size = sizeof(NTFS_TYPE_CCB);

    FileObject->SectionObjectPointer = &Fcb->SectionObjectPointers;
    FileObject->FsContext = Fcb;
    FileObject->FsContext2 = newCCB;
    newCCB->PtrFileObject = FileObject;
    Fcb->FileObject = FileObject;
    Fcb->Vcb = Vcb;

    Status = STATUS_SUCCESS;
    CcInitializeCacheMap(FileObject,
                         (PCC_FILE_SIZES)(&Fcb->RFCB.AllocationSize),
                         FALSE,
                         &(NtfsGlobalData->CacheMgrCallbacks),
                         Fcb);

    ObDereferenceObject(FileObject);
    Fcb->Flags |= FCB_CACHE_INITIALIZED;

    return Status;
}


PNTFS_FCB
NtfsMakeRootFCB(PNTFS_VCB Vcb)
{
    PNTFS_FCB Fcb;
    PFILE_RECORD_HEADER MftRecord;
    PFILENAME_ATTRIBUTE FileName;

    MftRecord = ExAllocatePoolWithTag(NonPagedPool,
                                      Vcb->NtfsInfo.BytesPerFileRecord,
                                      TAG_NTFS);
    if (MftRecord == NULL)
    {
        return NULL;
    }

    if (!NT_SUCCESS(ReadFileRecord(Vcb, NTFS_FILE_ROOT, MftRecord)))
    {
        ExFreePoolWithTag(MftRecord, TAG_NTFS);
        return NULL;
    }

    FileName = GetFileNameFromRecord(MftRecord, NTFS_FILE_NAME_WIN32);
    if (!FileName)
    {
        ExFreePoolWithTag(MftRecord, TAG_NTFS);
        return NULL;
    }

    Fcb = NtfsCreateFCB(L"\\", Vcb);
    if (!Fcb)
    {
        ExFreePoolWithTag(MftRecord, TAG_NTFS);
        return NULL;
    }

    memcpy(&Fcb->Entry, FileName, FIELD_OFFSET(FILENAME_ATTRIBUTE, NameLength));
    Fcb->Entry.NameType = FileName->NameType;
    Fcb->Entry.NameLength = 0;
    Fcb->Entry.Name[0] = UNICODE_NULL;
    Fcb->RefCount = 1;
    Fcb->DirIndex = 0;
    Fcb->RFCB.FileSize.QuadPart = FileName->DataSize;
    Fcb->RFCB.ValidDataLength.QuadPart = FileName->DataSize;
    Fcb->RFCB.AllocationSize.QuadPart = FileName->AllocatedSize;
    Fcb->MFTIndex = NTFS_FILE_ROOT;

    NtfsFCBInitializeCache(Vcb, Fcb);
    NtfsAddFCBToTable(Vcb, Fcb);
    NtfsGrabFCB(Vcb, Fcb);

    ExFreePoolWithTag(MftRecord, TAG_NTFS);

    return Fcb;
}


PNTFS_FCB
NtfsOpenRootFCB(PNTFS_VCB Vcb)
{
    PNTFS_FCB Fcb;

    Fcb = NtfsGrabFCBFromTable(Vcb, L"\\");
    if (Fcb == NULL)
    {
        Fcb = NtfsMakeRootFCB(Vcb);
    }

    return Fcb;
}


#if 0
static VOID
NtfsGetDirEntryName(PDEVICE_EXTENSION DeviceExt,
		    PDIR_RECORD Record,
		    PWSTR Name)
/*
 * FUNCTION: Retrieves the file name, be it in short or long file name format
 */
{
  if (Record->FileIdLength == 1 && Record->FileId[0] == 0)
    {
      wcscpy(Name, L".");
    }
  else if (Record->FileIdLength == 1 && Record->FileId[0] == 1)
    {
      wcscpy(Name, L"..");
    }
  else
    {
      if (DeviceExt->CdInfo.JolietLevel == 0)
	{
	  ULONG i;

	  for (i = 0; i < Record->FileIdLength && Record->FileId[i] != ';'; i++)
	    Name[i] = (WCHAR)Record->FileId[i];
	  Name[i] = 0;
	}
      else
	{
	  NtfsSwapString(Name, Record->FileId, Record->FileIdLength);
	}
    }

  DPRINT("Name '%S'\n", Name);
}
#endif


NTSTATUS
NtfsMakeFCBFromDirEntry(PNTFS_VCB Vcb,
			PNTFS_FCB DirectoryFCB,
			PUNICODE_STRING Name,
			PFILE_RECORD_HEADER Record,
                        ULONGLONG MFTIndex,
			PNTFS_FCB * fileFCB)
{
    WCHAR pathName[MAX_PATH];
    PFILENAME_ATTRIBUTE FileName;
    PNTFS_FCB rcFCB;

    DPRINT1("NtfsMakeFCBFromDirEntry(%p, %p, %wZ, %p, %p)\n", Vcb, DirectoryFCB, Name, Record, fileFCB);

    FileName = GetFileNameFromRecord(Record, NTFS_FILE_NAME_WIN32);
    if (!FileName)
    {
        return STATUS_OBJECT_NAME_NOT_FOUND; // Not sure that's the best here
    }

    if (Name->Buffer[0] != 0 && wcslen(DirectoryFCB->PathName) +
        sizeof(WCHAR) + Name->Length / sizeof(WCHAR) > MAX_PATH)
    {
        return STATUS_OBJECT_NAME_INVALID;
    }

    wcscpy(pathName, DirectoryFCB->PathName);
    if (!NtfsFCBIsRoot(DirectoryFCB))
    {
        wcscat(pathName, L"\\");
    }
    wcscat(pathName, Name->Buffer);

    rcFCB = NtfsCreateFCB(pathName, Vcb);
    if (!rcFCB)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    memcpy(&rcFCB->Entry, FileName, FIELD_OFFSET(FILENAME_ATTRIBUTE, NameLength));
    rcFCB->Entry.NameType = FileName->NameType;
    rcFCB->RFCB.FileSize.QuadPart = FileName->DataSize;
    rcFCB->RFCB.ValidDataLength.QuadPart = FileName->DataSize;
    rcFCB->RFCB.AllocationSize.QuadPart = FileName->AllocatedSize;

    NtfsFCBInitializeCache(Vcb, rcFCB);
    rcFCB->RefCount = 1;
    rcFCB->MFTIndex = MFTIndex;
    NtfsAddFCBToTable(Vcb, rcFCB);
    *fileFCB = rcFCB;

    return STATUS_SUCCESS;
}


NTSTATUS
NtfsAttachFCBToFileObject(PNTFS_VCB Vcb,
                          PNTFS_FCB Fcb,
                          PFILE_OBJECT FileObject)
{
    PNTFS_CCB newCCB;

    newCCB = ExAllocatePoolWithTag(NonPagedPool, sizeof(NTFS_CCB), TAG_CCB);
    if (newCCB == NULL)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlZeroMemory(newCCB, sizeof(NTFS_CCB));

    newCCB->Identifier.Type = NTFS_TYPE_CCB;
    newCCB->Identifier.Size = sizeof(NTFS_TYPE_CCB);

    FileObject->SectionObjectPointer = &Fcb->SectionObjectPointers;
    FileObject->FsContext = Fcb;
    FileObject->FsContext2 = newCCB;
    newCCB->PtrFileObject = FileObject;
    Fcb->Vcb = Vcb;

    if (!(Fcb->Flags & FCB_CACHE_INITIALIZED))
    {
        CcInitializeCacheMap(FileObject,
                             (PCC_FILE_SIZES)(&Fcb->RFCB.AllocationSize),
                             FALSE,
                             NULL,
                             NULL);

        Fcb->Flags |= FCB_CACHE_INITIALIZED;
    }

    //DPRINT("file open: fcb:%x file size: %d\n", Fcb, Fcb->Entry.DataLengthL);

    return STATUS_SUCCESS;
}


static NTSTATUS
NtfsDirFindFile(PNTFS_VCB Vcb,
                PNTFS_FCB DirectoryFcb,
                PWSTR FileToFind,
                PNTFS_FCB *FoundFCB)
{
    NTSTATUS Status;
    ULONGLONG CurrentDir;
    UNICODE_STRING File;
    PFILE_RECORD_HEADER FileRecord;
    PNTFS_ATTR_CONTEXT DataContext;
    ULONGLONG MFTIndex;

    DPRINT1("NtfsDirFindFile(%p, %p, %S, %p)\n", Vcb, DirectoryFcb, FileToFind, FoundFCB);

    *FoundFCB = NULL;
    RtlInitUnicodeString(&File, FileToFind);
    CurrentDir = DirectoryFcb->MFTIndex;

    Status = NtfsLookupFileAt(Vcb, &File, &FileRecord, &DataContext, &MFTIndex, CurrentDir);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    Status = NtfsMakeFCBFromDirEntry(Vcb, DirectoryFcb, &File, FileRecord, MFTIndex, FoundFCB);
    ExFreePoolWithTag(FileRecord, TAG_NTFS);

    return Status;
}


NTSTATUS
NtfsGetFCBForFile(PNTFS_VCB Vcb,
                  PNTFS_FCB *pParentFCB,
                  PNTFS_FCB *pFCB,
                  const PWSTR pFileName)
{
    NTSTATUS Status;
    WCHAR pathName [MAX_PATH];
    WCHAR elementName [MAX_PATH];
    PWCHAR currentElement;
    PNTFS_FCB FCB;
    PNTFS_FCB parentFCB;

    DPRINT("NtfsGetFCBForFile(%p, %p, %p, '%S')\n",
           Vcb,
           pParentFCB,
           pFCB,
           pFileName);

    /* Dummy code */
//  FCB = NtfsOpenRootFCB(Vcb);
//  *pFCB = FCB;
//  *pParentFCB = NULL;

#if 1
    /* Trivial case, open of the root directory on volume */
    if (pFileName [0] == L'\0' || wcscmp(pFileName, L"\\") == 0)
    {
        DPRINT("returning root FCB\n");

        FCB = NtfsOpenRootFCB(Vcb);
        *pFCB = FCB;
        *pParentFCB = NULL;

        return (FCB != NULL) ? STATUS_SUCCESS : STATUS_OBJECT_PATH_NOT_FOUND;
    }
    else
    {
        currentElement = pFileName + 1;
        wcscpy (pathName, L"\\");
        FCB = NtfsOpenRootFCB (Vcb);
    }

    parentFCB = NULL;

    /* Parse filename and check each path element for existance and access */
    while (NtfsGetNextPathElement(currentElement) != 0)
    {
        /* Skip blank directory levels */
        if ((NtfsGetNextPathElement(currentElement) - currentElement) == 0)
        {
            currentElement++;
            continue;
        }

        DPRINT("Parsing, currentElement:%S\n", currentElement);
        DPRINT("  parentFCB:%p FCB:%p\n", parentFCB, FCB);

        /* Descend to next directory level */
        if (parentFCB)
        {
            NtfsReleaseFCB(Vcb, parentFCB);
            parentFCB = NULL;
        }

        /* fail if element in FCB is not a directory */
        if (!NtfsFCBIsDirectory(FCB))
        {
            DPRINT("Element in requested path is not a directory\n");

            NtfsReleaseFCB(Vcb, FCB);
            FCB = 0;
            *pParentFCB = NULL;
            *pFCB = NULL;

            return STATUS_OBJECT_PATH_NOT_FOUND;
        }

        parentFCB = FCB;

        /* Extract next directory level into dirName */
        NtfsWSubString(pathName,
                       pFileName,
                       NtfsGetNextPathElement(currentElement) - pFileName);
        DPRINT("  pathName:%S\n", pathName);

        FCB = NtfsGrabFCBFromTable(Vcb, pathName);
        if (FCB == NULL)
        {
            NtfsWSubString(elementName,
                           currentElement,
                           NtfsGetNextPathElement(currentElement) - currentElement);
            DPRINT("  elementName:%S\n", elementName);

            Status = NtfsDirFindFile(Vcb, parentFCB, elementName, &FCB);
            if (Status == STATUS_OBJECT_NAME_NOT_FOUND)
            {
                *pParentFCB = parentFCB;
                *pFCB = NULL;
                currentElement = NtfsGetNextPathElement(currentElement);
                if (*currentElement == L'\0' || NtfsGetNextPathElement(currentElement + 1) == 0)
                {
                    return STATUS_OBJECT_NAME_NOT_FOUND;
                }
                else
                {
                    return STATUS_OBJECT_PATH_NOT_FOUND;
                }
            }
            else if (!NT_SUCCESS(Status))
            {
                NtfsReleaseFCB(Vcb, parentFCB);
                *pParentFCB = NULL;
                *pFCB = NULL;

                return Status;
            }
        }

        currentElement = NtfsGetNextPathElement(currentElement);
    }

    *pParentFCB = parentFCB;
    *pFCB = FCB;
#endif

    return STATUS_SUCCESS;
}

/* EOF */
