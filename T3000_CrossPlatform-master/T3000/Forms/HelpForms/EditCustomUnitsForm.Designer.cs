namespace T3000.Forms
{
    partial class EditCustomUnitsForm
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
            this.saveButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.analogView = new T3000.Controls.TView();
            this.AnalogNumberColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.NameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.digitalView = new T3000.Controls.TView();
            this.NumberColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.OffNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.OnNameColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DirectColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            ((System.ComponentModel.ISupportInitialize)(this.analogView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.digitalView)).BeginInit();
            this.SuspendLayout();
            // 
            // saveButton
            // 
            this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.saveButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.saveButton.Location = new System.Drawing.Point(229, 237);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(137, 23);
            this.saveButton.TabIndex = 2;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.Save);
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(372, 237);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(115, 23);
            this.cancelButton.TabIndex = 3;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.Cancel);
            // 
            // analogView
            // 
            this.analogView.AllowUserToAddRows = false;
            this.analogView.AllowUserToDeleteRows = false;
            this.analogView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.analogView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.AnalogNumberColumn,
            this.NameColumn});
            this.analogView.Location = new System.Drawing.Point(12, 10);
            this.analogView.Name = "analogView";
            this.analogView.Size = new System.Drawing.Size(205, 220);
            this.analogView.TabIndex = 8;
            // 
            // AnalogNumberColumn
            // 
            this.AnalogNumberColumn.FillWeight = 20F;
            this.AnalogNumberColumn.HeaderText = "N";
            this.AnalogNumberColumn.Name = "AnalogNumberColumn";
            this.AnalogNumberColumn.ReadOnly = true;
            this.AnalogNumberColumn.Width = 20;
            // 
            // NameColumn
            // 
            this.NameColumn.HeaderText = "Name";
            this.NameColumn.Name = "NameColumn";
            this.NameColumn.Width = 140;
            // 
            // digitalView
            // 
            this.digitalView.AllowUserToAddRows = false;
            this.digitalView.AllowUserToDeleteRows = false;
            this.digitalView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.digitalView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.NumberColumn,
            this.OffNameColumn,
            this.OnNameColumn,
            this.DirectColumn});
            this.digitalView.Location = new System.Drawing.Point(223, 10);
            this.digitalView.Name = "digitalView";
            this.digitalView.Size = new System.Drawing.Size(264, 220);
            this.digitalView.TabIndex = 7;
            // 
            // NumberColumn
            // 
            this.NumberColumn.FillWeight = 20F;
            this.NumberColumn.HeaderText = "N";
            this.NumberColumn.Name = "NumberColumn";
            this.NumberColumn.ReadOnly = true;
            this.NumberColumn.Width = 20;
            // 
            // OffNameColumn
            // 
            this.OffNameColumn.HeaderText = "OffName";
            this.OffNameColumn.Name = "OffNameColumn";
            this.OffNameColumn.Width = 80;
            // 
            // OnNameColumn
            // 
            this.OnNameColumn.HeaderText = "OnName";
            this.OnNameColumn.Name = "OnNameColumn";
            this.OnNameColumn.Width = 80;
            // 
            // DirectColumn
            // 
            this.DirectColumn.HeaderText = "Direct";
            this.DirectColumn.Name = "DirectColumn";
            this.DirectColumn.Width = 40;
            // 
            // EditCustomUnitsForm
            // 
            this.AcceptButton = this.saveButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(499, 272);
            this.Controls.Add(this.analogView);
            this.Controls.Add(this.digitalView);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Name = "EditCustomUnitsForm";
            this.Text = "Change custom unit:";
            ((System.ComponentModel.ISupportInitialize)(this.analogView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.digitalView)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button cancelButton;
        private Controls.TView digitalView;
        private System.Windows.Forms.DataGridViewTextBoxColumn NumberColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn OffNameColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn OnNameColumn;
        private System.Windows.Forms.DataGridViewButtonColumn DirectColumn;
        private Controls.TView analogView;
        private System.Windows.Forms.DataGridViewTextBoxColumn AnalogNumberColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn NameColumn;
    }
}