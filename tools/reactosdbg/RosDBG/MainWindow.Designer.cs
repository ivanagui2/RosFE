﻿namespace RosDBG
{
    partial class MainWindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openSourceFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addSymbolFileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.symbolDirectoryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.connectSerialToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.connectPipeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.connectTCPIPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pasteToInteractionToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.memoryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.debugToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.continueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.bugcheckToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.breakToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.stepToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.breakHereToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.breakpointClipboardToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.followListToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.windowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.NewWindowItem = new System.Windows.Forms.ToolStripMenuItem();
            this.detachCurrentTabToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeCurrentTabToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.WorkTabs = new System.Windows.Forms.TabControl();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.RunStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.IsSplitterFixed = true;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.menuStrip1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.splitContainer2);
            this.splitContainer1.Size = new System.Drawing.Size(529, 416);
            this.splitContainer1.SplitterDistance = 26;
            this.splitContainer1.TabIndex = 0;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem,
            this.debugToolStripMenuItem,
            this.windowToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(529, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openSourceFileToolStripMenuItem,
            this.addSymbolFileToolStripMenuItem,
            this.symbolDirectoryToolStripMenuItem,
            this.connectSerialToolStripMenuItem,
            this.connectPipeToolStripMenuItem,
            this.connectTCPIPToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openSourceFileToolStripMenuItem
            // 
            this.openSourceFileToolStripMenuItem.Name = "openSourceFileToolStripMenuItem";
            this.openSourceFileToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.openSourceFileToolStripMenuItem.Text = "Open Source File ...";
            // 
            // addSymbolFileToolStripMenuItem
            // 
            this.addSymbolFileToolStripMenuItem.Name = "addSymbolFileToolStripMenuItem";
            this.addSymbolFileToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.addSymbolFileToolStripMenuItem.Text = "Add Symbol File ...";
            // 
            // symbolDirectoryToolStripMenuItem
            // 
            this.symbolDirectoryToolStripMenuItem.Name = "symbolDirectoryToolStripMenuItem";
            this.symbolDirectoryToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.symbolDirectoryToolStripMenuItem.Text = "Symbol Path ...";
            // 
            // connectSerialToolStripMenuItem
            // 
            this.connectSerialToolStripMenuItem.Name = "connectSerialToolStripMenuItem";
            this.connectSerialToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.connectSerialToolStripMenuItem.Text = "Connect Serial ...";
            // 
            // connectPipeToolStripMenuItem
            // 
            this.connectPipeToolStripMenuItem.Name = "connectPipeToolStripMenuItem";
            this.connectPipeToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.connectPipeToolStripMenuItem.Text = "Connect Pipe ...";
            // 
            // connectTCPIPToolStripMenuItem
            // 
            this.connectTCPIPToolStripMenuItem.Name = "connectTCPIPToolStripMenuItem";
            this.connectTCPIPToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.connectTCPIPToolStripMenuItem.Text = "Connect TCP/IP ...";
            this.connectTCPIPToolStripMenuItem.Click += new System.EventHandler(this.connectTCPIPToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(175, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // editToolStripMenuItem
            // 
            this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyToolStripMenuItem,
            this.pasteToInteractionToolStripMenuItem,
            this.memoryToolStripMenuItem});
            this.editToolStripMenuItem.Name = "editToolStripMenuItem";
            this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
            this.editToolStripMenuItem.Text = "Edit";
            // 
            // copyToolStripMenuItem
            // 
            this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
            this.copyToolStripMenuItem.Size = new System.Drawing.Size(187, 22);
            this.copyToolStripMenuItem.Text = "Copy";
            // 
            // pasteToInteractionToolStripMenuItem
            // 
            this.pasteToInteractionToolStripMenuItem.Name = "pasteToInteractionToolStripMenuItem";
            this.pasteToInteractionToolStripMenuItem.Size = new System.Drawing.Size(187, 22);
            this.pasteToInteractionToolStripMenuItem.Text = "Paste to Interaction";
            // 
            // memoryToolStripMenuItem
            // 
            this.memoryToolStripMenuItem.Name = "memoryToolStripMenuItem";
            this.memoryToolStripMenuItem.Size = new System.Drawing.Size(187, 22);
            this.memoryToolStripMenuItem.Text = "Memory at Clipboard";
            // 
            // debugToolStripMenuItem
            // 
            this.debugToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.continueToolStripMenuItem,
            this.bugcheckToolStripMenuItem,
            this.breakToolStripMenuItem,
            this.stepToolStripMenuItem,
            this.breakHereToolStripMenuItem,
            this.breakpointClipboardToolStripMenuItem,
            this.followListToolStripMenuItem});
            this.debugToolStripMenuItem.Name = "debugToolStripMenuItem";
            this.debugToolStripMenuItem.Size = new System.Drawing.Size(54, 20);
            this.debugToolStripMenuItem.Text = "Debug";
            // 
            // continueToolStripMenuItem
            // 
            this.continueToolStripMenuItem.Name = "continueToolStripMenuItem";
            this.continueToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.continueToolStripMenuItem.Text = "Continue";
            this.continueToolStripMenuItem.Click += new System.EventHandler(this.continueToolStripMenuItem_Click);
            // 
            // bugcheckToolStripMenuItem
            // 
            this.bugcheckToolStripMenuItem.Name = "bugcheckToolStripMenuItem";
            this.bugcheckToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.bugcheckToolStripMenuItem.Text = "Bugcheck";
            // 
            // breakToolStripMenuItem
            // 
            this.breakToolStripMenuItem.Name = "breakToolStripMenuItem";
            this.breakToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.breakToolStripMenuItem.Text = "Break";
            this.breakToolStripMenuItem.Click += new System.EventHandler(this.breakToolStripMenuItem_Click);
            // 
            // stepToolStripMenuItem
            // 
            this.stepToolStripMenuItem.Name = "stepToolStripMenuItem";
            this.stepToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.stepToolStripMenuItem.Text = "Step";
            this.stepToolStripMenuItem.Click += new System.EventHandler(this.stepToolStripMenuItem_Click);
            // 
            // breakHereToolStripMenuItem
            // 
            this.breakHereToolStripMenuItem.Name = "breakHereToolStripMenuItem";
            this.breakHereToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.breakHereToolStripMenuItem.Text = "Breakpoint Here";
            // 
            // breakpointClipboardToolStripMenuItem
            // 
            this.breakpointClipboardToolStripMenuItem.Name = "breakpointClipboardToolStripMenuItem";
            this.breakpointClipboardToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.breakpointClipboardToolStripMenuItem.Text = "Breakpoint Clipboard";
            // 
            // followListToolStripMenuItem
            // 
            this.followListToolStripMenuItem.Name = "followListToolStripMenuItem";
            this.followListToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.followListToolStripMenuItem.Text = "Follow List";
            // 
            // windowToolStripMenuItem
            // 
            this.windowToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NewWindowItem,
            this.detachCurrentTabToolStripMenuItem,
            this.closeCurrentTabToolStripMenuItem});
            this.windowToolStripMenuItem.Name = "windowToolStripMenuItem";
            this.windowToolStripMenuItem.Size = new System.Drawing.Size(63, 20);
            this.windowToolStripMenuItem.Text = "Window";
            // 
            // NewWindowItem
            // 
            this.NewWindowItem.Name = "NewWindowItem";
            this.NewWindowItem.Size = new System.Drawing.Size(177, 22);
            this.NewWindowItem.Text = "New";
            // 
            // detachCurrentTabToolStripMenuItem
            // 
            this.detachCurrentTabToolStripMenuItem.Name = "detachCurrentTabToolStripMenuItem";
            this.detachCurrentTabToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.detachCurrentTabToolStripMenuItem.Text = "Detach Current Tab";
            this.detachCurrentTabToolStripMenuItem.Click += new System.EventHandler(this.detachCurrentTabToolStripMenuItem_Click);
            // 
            // closeCurrentTabToolStripMenuItem
            // 
            this.closeCurrentTabToolStripMenuItem.Name = "closeCurrentTabToolStripMenuItem";
            this.closeCurrentTabToolStripMenuItem.Size = new System.Drawing.Size(177, 22);
            this.closeCurrentTabToolStripMenuItem.Text = "Close Current Tab";
            this.closeCurrentTabToolStripMenuItem.Click += new System.EventHandler(this.closeCurrentTabToolStripMenuItem_Click);
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer2.IsSplitterFixed = true;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.WorkTabs);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.statusStrip1);
            this.splitContainer2.Size = new System.Drawing.Size(529, 386);
            this.splitContainer2.SplitterDistance = 357;
            this.splitContainer2.TabIndex = 0;
            // 
            // WorkTabs
            // 
            this.WorkTabs.Dock = System.Windows.Forms.DockStyle.Fill;
            this.WorkTabs.Location = new System.Drawing.Point(0, 0);
            this.WorkTabs.Name = "WorkTabs";
            this.WorkTabs.SelectedIndex = 0;
            this.WorkTabs.Size = new System.Drawing.Size(529, 357);
            this.WorkTabs.TabIndex = 1;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.RunStatus});
            this.statusStrip1.Location = new System.Drawing.Point(0, 3);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(529, 22);
            this.statusStrip1.TabIndex = 0;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // RunStatus
            // 
            this.RunStatus.Name = "RunStatus";
            this.RunStatus.Size = new System.Drawing.Size(0, 17);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(529, 416);
            this.Controls.Add(this.splitContainer1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainWindow";
            this.Text = "ReactOS Debug Shell";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            this.splitContainer2.Panel2.PerformLayout();
            this.splitContainer2.ResumeLayout(false);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem debugToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem windowToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem NewWindowItem;
        private System.Windows.Forms.ToolStripMenuItem detachCurrentTabToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeCurrentTabToolStripMenuItem;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.TabControl WorkTabs;
        private System.Windows.Forms.ToolStripMenuItem continueToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem bugcheckToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openSourceFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addSymbolFileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem symbolDirectoryToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem connectSerialToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem connectPipeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem connectTCPIPToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem stepToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem breakHereToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem breakpointClipboardToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem followListToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pasteToInteractionToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem memoryToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem breakToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel RunStatus;

    }
}

