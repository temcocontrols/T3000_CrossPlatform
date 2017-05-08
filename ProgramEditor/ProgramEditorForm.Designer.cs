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
            ((System.ComponentModel.ISupportInitialize)(this.editTextBox)).BeginInit();
            this.SuspendLayout();
            // 
            // saveButton
            // 
            this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.saveButton.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.saveButton.Location = new System.Drawing.Point(296, 327);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(145, 32);
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
            this.cancelButton.Location = new System.Drawing.Point(447, 327);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(133, 32);
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
            this.editTextBox.Font = new System.Drawing.Font("Courier New", 9.75F);
            this.editTextBox.IsReplaceMode = false;
            this.editTextBox.Location = new System.Drawing.Point(12, 12);
            this.editTextBox.Name = "editTextBox";
            this.editTextBox.Paddings = new System.Windows.Forms.Padding(0);
            this.editTextBox.SelectionColor = System.Drawing.Color.FromArgb(((int)(((byte)(60)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(255)))));
            this.editTextBox.ServiceColors = ((FastColoredTextBoxNS.ServiceColors)(resources.GetObject("editTextBox.ServiceColors")));
            this.editTextBox.Size = new System.Drawing.Size(560, 309);
            this.editTextBox.TabIndex = 7;
            this.editTextBox.Zoom = 100;
            // 
            // autocompleteMenu
            // 
            this.autocompleteMenu.AllowTabKey = false;
            this.autocompleteMenu.AppearInterval = 500;
            this.autocompleteMenu.AutoClose = false;
            this.autocompleteMenu.AutoSize = false;
            this.autocompleteMenu.BackColor = System.Drawing.Color.White;
            this.autocompleteMenu.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.Flow;
            this.autocompleteMenu.MinFragmentLength = 1;
            this.autocompleteMenu.Name = "autocompleteMenu";
            this.autocompleteMenu.Padding = new System.Windows.Forms.Padding(0);
            this.autocompleteMenu.SearchPattern = "[\\w\\.]";
            this.autocompleteMenu.Size = new System.Drawing.Size(154, 154);
            this.autocompleteMenu.ToolTipDuration = 3000;
            // 
            // ProgramEditorForm
            // 
            this.AcceptButton = this.saveButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(584, 361);
            this.Controls.Add(this.editTextBox);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Name = "ProgramEditorForm";
            this.Text = "Edit code:";
            ((System.ComponentModel.ISupportInitialize)(this.editTextBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button cancelButton;
        private FastColoredTextBoxNS.IronyFCTB editTextBox;
        private FastColoredTextBoxNS.AutocompleteMenu autocompleteMenu;
    }
}