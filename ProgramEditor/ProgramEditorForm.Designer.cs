namespace T3000.Forms
{
    partial class ProgramEditorForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ProgramEditorForm));
            this.saveButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.editTextBox = new FastColoredTextBoxNS.IronyFCTB();
            this.autocompleteMenu = new FastColoredTextBoxNS.AutocompleteMenu(this.editTextBox);
            this.tsTopMenu = new System.Windows.Forms.ToolStrip();
            this.cmdSend = new System.Windows.Forms.ToolStripButton();
            this.cmdClear = new System.Windows.Forms.ToolStripButton();
            this.cmdLoad = new System.Windows.Forms.ToolStripButton();
            this.cmdSave = new System.Windows.Forms.ToolStripButton();
            this.cmdRefresh = new System.Windows.Forms.ToolStripButton();
            this.cmdSettings = new System.Windows.Forms.ToolStripButton();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.txtSyntaxErrors = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.editTextBox)).BeginInit();
            this.tsTopMenu.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // saveButton
            // 
            this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.saveButton.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.saveButton.Location = new System.Drawing.Point(403, 3);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(82, 32);
            this.saveButton.TabIndex = 5;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.Save);
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.cancelButton.Location = new System.Drawing.Point(491, 3);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(82, 32);
            this.cancelButton.TabIndex = 6;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.Cancel);
            // 
            // editTextBox
            // 
            this.editTextBox.AutoCompleteBracketsList = new char[] {
        '(',
        ')',
        '{',
        '}',
        '[',
        ']',
        '\"',
        '\"',
        '\'',
        '\''};
            this.editTextBox.AutoScrollMinSize = new System.Drawing.Size(27, 14);
            this.editTextBox.BackBrush = null;
            this.editTextBox.CharHeight = 14;
            this.editTextBox.CharWidth = 8;
            this.editTextBox.Cursor = System.Windows.Forms.Cursors.IBeam;
            this.editTextBox.DisabledColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))), ((int)(((byte)(180)))));
            this.editTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.editTextBox.IsReplaceMode = false;
            this.editTextBox.Location = new System.Drawing.Point(3, 28);
            this.editTextBox.Name = "editTextBox";
            this.editTextBox.Paddings = new System.Windows.Forms.Padding(0);
            this.editTextBox.SelectionColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(255)))));
            this.editTextBox.ServiceColors = ((FastColoredTextBoxNS.ServiceColors)(resources.GetObject("editTextBox.ServiceColors")));
            this.editTextBox.Size = new System.Drawing.Size(576, 230);
            this.editTextBox.TabIndex = 7;
            this.editTextBox.Zoom = 100;
            // 
            // autocompleteMenu
            // 
            this.autocompleteMenu.AllowTabKey = false;
            this.autocompleteMenu.AlwaysShowTooltip = false;
            this.autocompleteMenu.AppearInterval = 500;
            this.autocompleteMenu.AutoClose = false;
            this.autocompleteMenu.AutoSize = false;
            this.autocompleteMenu.BackColor = System.Drawing.Color.White;
            this.autocompleteMenu.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.Flow;
            this.autocompleteMenu.MaxTooltipSize = new System.Drawing.Size(0, 0);
            this.autocompleteMenu.MinFragmentLength = 1;
            this.autocompleteMenu.Name = "autocompleteMenu";
            this.autocompleteMenu.Padding = new System.Windows.Forms.Padding(0);
            this.autocompleteMenu.SearchPattern = "[\\w\\.]";
            this.autocompleteMenu.Size = new System.Drawing.Size(154, 154);
            this.autocompleteMenu.ToolTipDuration = 3000;
            // 
            // tsTopMenu
            // 
            this.tsTopMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.cmdSend,
            this.cmdClear,
            this.cmdLoad,
            this.cmdSave,
            this.cmdRefresh,
            this.cmdSettings});
            this.tsTopMenu.Location = new System.Drawing.Point(0, 0);
            this.tsTopMenu.Name = "tsTopMenu";
            this.tsTopMenu.Size = new System.Drawing.Size(582, 25);
            this.tsTopMenu.TabIndex = 8;
            this.tsTopMenu.Text = "toolStrip1";
            // 
            // cmdSend
            // 
            this.cmdSend.Image = ((System.Drawing.Image)(resources.GetObject("cmdSend.Image")));
            this.cmdSend.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cmdSend.Name = "cmdSend";
            this.cmdSend.Size = new System.Drawing.Size(76, 22);
            this.cmdSend.Text = "Send (F2)";
            // 
            // cmdClear
            // 
            this.cmdClear.Image = ((System.Drawing.Image)(resources.GetObject("cmdClear.Image")));
            this.cmdClear.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cmdClear.Name = "cmdClear";
            this.cmdClear.Size = new System.Drawing.Size(77, 22);
            this.cmdClear.Text = "Clear (F3)";
            this.cmdClear.Click += new System.EventHandler(this.cmdClear_Click);
            // 
            // cmdLoad
            // 
            this.cmdLoad.Image = ((System.Drawing.Image)(resources.GetObject("cmdLoad.Image")));
            this.cmdLoad.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cmdLoad.Name = "cmdLoad";
            this.cmdLoad.Size = new System.Drawing.Size(97, 22);
            this.cmdLoad.Text = "Load File (F7)";
            // 
            // cmdSave
            // 
            this.cmdSave.Image = ((System.Drawing.Image)(resources.GetObject("cmdSave.Image")));
            this.cmdSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cmdSave.Name = "cmdSave";
            this.cmdSave.Size = new System.Drawing.Size(95, 22);
            this.cmdSave.Text = "Save File (F6)";
            // 
            // cmdRefresh
            // 
            this.cmdRefresh.Image = ((System.Drawing.Image)(resources.GetObject("cmdRefresh.Image")));
            this.cmdRefresh.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cmdRefresh.Name = "cmdRefresh";
            this.cmdRefresh.Size = new System.Drawing.Size(89, 22);
            this.cmdRefresh.Text = "Refresh (F8)";
            // 
            // cmdSettings
            // 
            this.cmdSettings.Image = ((System.Drawing.Image)(resources.GetObject("cmdSettings.Image")));
            this.cmdSettings.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cmdSettings.Name = "cmdSettings";
            this.cmdSettings.Size = new System.Drawing.Size(69, 22);
            this.cmdSettings.Text = "Settings";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.tsTopMenu, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.editTextBox, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.flowLayoutPanel1, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.txtSyntaxErrors, 0, 2);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 78.66666F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 21.33333F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 40F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(582, 366);
            this.tableLayoutPanel1.TabIndex = 9;
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.cancelButton);
            this.flowLayoutPanel1.Controls.Add(this.saveButton);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel1.FlowDirection = System.Windows.Forms.FlowDirection.RightToLeft;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(3, 328);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(576, 35);
            this.flowLayoutPanel1.TabIndex = 9;
            // 
            // txtSyntaxErrors
            // 
            this.txtSyntaxErrors.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtSyntaxErrors.Location = new System.Drawing.Point(3, 264);
            this.txtSyntaxErrors.Multiline = true;
            this.txtSyntaxErrors.Name = "txtSyntaxErrors";
            this.txtSyntaxErrors.ReadOnly = true;
            this.txtSyntaxErrors.Size = new System.Drawing.Size(576, 58);
            this.txtSyntaxErrors.TabIndex = 10;
            // 
            // ProgramEditorForm
            // 
            this.AcceptButton = this.saveButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(582, 366);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "ProgramEditorForm";
            this.Text = "Edit code:";
            ((System.ComponentModel.ISupportInitialize)(this.editTextBox)).EndInit();
            this.tsTopMenu.ResumeLayout(false);
            this.tsTopMenu.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button cancelButton;
        private FastColoredTextBoxNS.IronyFCTB editTextBox;
        private FastColoredTextBoxNS.AutocompleteMenu autocompleteMenu;
        private System.Windows.Forms.ToolStrip tsTopMenu;
        private System.Windows.Forms.ToolStripButton cmdSend;
        private System.Windows.Forms.ToolStripButton cmdClear;
        private System.Windows.Forms.ToolStripButton cmdLoad;
        private System.Windows.Forms.ToolStripButton cmdSave;
        private System.Windows.Forms.ToolStripButton cmdRefresh;
        private System.Windows.Forms.ToolStripButton cmdSettings;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.TextBox txtSyntaxErrors;
    }
}