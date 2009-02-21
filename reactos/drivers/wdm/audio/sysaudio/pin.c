/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS Kernel Streaming
 * FILE:            drivers/wdm/audio/sysaudio/deviface.c
 * PURPOSE:         System Audio graph builder
 * PROGRAMMER:      Johannes Anderwald
 */

#include <ntifs.h>
#include <ntddk.h>
#include <portcls.h>
#include <ks.h>
#include <ksmedia.h>
#include <math.h>
#define YDEBUG
#include <debug.h>
#include "sysaudio.h"

NTSTATUS
NTAPI
Pin_fnDeviceIoControl(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    PDISPATCH_CONTEXT Context;
    PKSOBJECT_CREATE_ITEM CreateItem;
    NTSTATUS Status;
    ULONG BytesReturned;
    PIO_STACK_LOCATION IoStack;

    DPRINT1("Pin_fnDeviceIoControl called DeviceObject %p Irp %p\n", DeviceObject);

    /* access the create item */
    CreateItem = KSCREATE_ITEM_IRP_STORAGE(Irp);
    Context = (PDISPATCH_CONTEXT)CreateItem->Context;

    IoStack = IoGetCurrentIrpStackLocation(Irp);

    Status = KsSynchronousIoControlDevice(Context->FileObject, KernelMode, IoStack->Parameters.DeviceIoControl.IoControlCode,
                                          IoStack->Parameters.DeviceIoControl.Type3InputBuffer,
                                          IoStack->Parameters.DeviceIoControl.InputBufferLength,
                                          Irp->UserBuffer,
                                          IoStack->Parameters.DeviceIoControl.OutputBufferLength,
                                          &BytesReturned);

    DPRINT1("Status %x\n", Status);

    Irp->IoStatus.Information = BytesReturned;
    Irp->IoStatus.Status = Status;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Status;
}

NTSTATUS
NTAPI
Pin_fnRead(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    DPRINT1("Pin_fnRead called DeviceObject %p Irp %p\n", DeviceObject);

    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
PinWriteCompletionRoutine(
    IN PDEVICE_OBJECT  DeviceObject,
    IN PIRP  Irp,
    IN PVOID  Context)
{
    PIRP CIrp = (PIRP)Context;

    CIrp->IoStatus.Status = STATUS_SUCCESS;
    CIrp->IoStatus.Information = 0;
    IoCompleteRequest(CIrp, IO_NO_INCREMENT);
    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
Pin_fnWrite(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    PDISPATCH_CONTEXT Context;
    PKSOBJECT_CREATE_ITEM CreateItem;
    PIO_STACK_LOCATION IoStack;
    ULONG BytesReturned;
    NTSTATUS Status;

    DPRINT1("Pin_fnWrite called DeviceObject %p Irp %p\n", DeviceObject);

   /* access the create item */
    CreateItem = KSCREATE_ITEM_IRP_STORAGE(Irp);
    Context = (PDISPATCH_CONTEXT)CreateItem->Context;

    IoStack = IoGetCurrentIrpStackLocation(Irp);

    Status = KsSynchronousIoControlDevice(Context->FileObject, KernelMode, IOCTL_KS_WRITE_STREAM,
                                          IoStack->Parameters.DeviceIoControl.Type3InputBuffer,
                                          IoStack->Parameters.DeviceIoControl.InputBufferLength,
                                          Irp->UserBuffer,
                                          IoStack->Parameters.DeviceIoControl.OutputBufferLength,
                                          &BytesReturned);

    Irp->IoStatus.Information = BytesReturned;
    Irp->IoStatus.Status = Status;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    return Status;
}

NTSTATUS
NTAPI
Pin_fnFlush(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    DPRINT1("Pin_fnFlush called DeviceObject %p Irp %p\n", DeviceObject);

    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
Pin_fnClose(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    DPRINT1("Pin_fnClose called DeviceObject %p Irp %p\n", DeviceObject);


    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
Pin_fnQuerySecurity(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    DPRINT1("Pin_fnQuerySecurity called DeviceObject %p Irp %p\n", DeviceObject);


    return STATUS_SUCCESS;
}

NTSTATUS
NTAPI
Pin_fnSetSecurity(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{

    DPRINT1("Pin_fnSetSecurity called DeviceObject %p Irp %p\n", DeviceObject);

    return STATUS_SUCCESS;
}

BOOLEAN
NTAPI
Pin_fnFastDeviceIoControl(
    PFILE_OBJECT FileObject,
    BOOLEAN Wait,
    PVOID InputBuffer,
    ULONG InputBufferLength,
    PVOID OutputBuffer,
    ULONG OutputBufferLength,
    ULONG IoControlCode,
    PIO_STATUS_BLOCK IoStatus,
    PDEVICE_OBJECT DeviceObject)
{
    DPRINT1("Pin_fnFastDeviceIoControl called DeviceObject %p Irp %p\n", DeviceObject);


    return FALSE;
}


BOOLEAN
NTAPI
Pin_fnFastRead(
    PFILE_OBJECT FileObject,
    PLARGE_INTEGER FileOffset,
    ULONG Length,
    BOOLEAN Wait,
    ULONG LockKey,
    PVOID Buffer,
    PIO_STATUS_BLOCK IoStatus,
    PDEVICE_OBJECT DeviceObject)
{
    DPRINT1("Pin_fnFastRead called DeviceObject %p Irp %p\n", DeviceObject);

    return FALSE;

}

BOOLEAN
NTAPI
Pin_fnFastWrite(
    PFILE_OBJECT FileObject,
    PLARGE_INTEGER FileOffset,
    ULONG Length,
    BOOLEAN Wait,
    ULONG LockKey,
    PVOID Buffer,
    PIO_STATUS_BLOCK IoStatus,
    PDEVICE_OBJECT DeviceObject)
{
    DPRINT1("Pin_fnFastWrite called DeviceObject %p Irp %p\n", DeviceObject);

    return FALSE;
}

static KSDISPATCH_TABLE PinTable =
{
    Pin_fnDeviceIoControl,
    Pin_fnRead,
    Pin_fnWrite,
    Pin_fnFlush,
    Pin_fnClose,
    Pin_fnQuerySecurity,
    Pin_fnSetSecurity,
    Pin_fnFastDeviceIoControl,
    Pin_fnFastRead,
    Pin_fnFastWrite,
};

NTSTATUS
CreateDispatcher(
    IN PIRP Irp,
    IN HANDLE Handle,
    IN PFILE_OBJECT FileObject)
{
    PKSOBJECT_CREATE_ITEM CreateItem;
    NTSTATUS Status;
    KSOBJECT_HEADER ObjectHeader;
    PDISPATCH_CONTEXT Context;

    /* allocate create item */
    CreateItem = ExAllocatePool(NonPagedPool, sizeof(KSOBJECT_CREATE_ITEM));
    if (!CreateItem)
        return STATUS_INSUFFICIENT_RESOURCES;

    Context = ExAllocatePool(NonPagedPool, sizeof(DISPATCH_CONTEXT));
    if (!Context)
    {
        ExFreePool(CreateItem);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    Context->Handle = Handle;
    Context->FileObject = FileObject;


     CreateItem->Context = (PVOID)Context;

    /* allocate object header */
    Status = KsAllocateObjectHeader(&ObjectHeader, 1, CreateItem, Irp, &PinTable);
    return Status;
}
