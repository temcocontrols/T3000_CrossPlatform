namespace T3000.Forms
{
    partial class HolidaysForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ProgramsForm));
            this.saveButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.clearSelectedRowButton = new System.Windows.Forms.Button();
            this.view = new T3000.Controls.Improved.TDataGridView();
            this.NumberColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.StatusColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.AutoManualColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.SizeColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.RunStatusColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.LabelColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CodeColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            ((System.ComponentModel.ISupportInitialize)(this.view)).BeginInit();
            this.SuspendLayout();
            // 
            // saveButton
            // 
            resources.ApplyResources(this.saveButton, "saveButton");
            this.saveButton.Name = "saveButton";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.Save);
            // 
            // cancelButton
            // 
            resources.ApplyResources(this.cancelButton, "cancelButton");
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.Cancel);
            // 
            // clearSelectedRowButton
            // 
            resources.ApplyResources(this.clearSelectedRowButton, "clearSelectedRowButton");
            this.clearSelectedRowButton.Name = "clearSelectedRowButton";
            this.clearSelectedRowButton.UseVisualStyleBackColor = true;
            this.clearSelectedRowButton.Click += new System.EventHandler(this.ClearSelectedRow);
            // 
            // view
            // 
            this.view.AllowUserToAddRows = false;
            this.view.AllowUserToDeleteRows = false;
            resources.ApplyResources(this.view, "view");
            this.view.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.view.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.view.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.NumberColumn,
            this.DescriptionColumn,
            this.StatusColumn,
            this.AutoManualColumn,
            this.SizeColumn,
            this.RunStatusColumn,
            this.LabelColumn,
            this.CodeColumn});
            this.view.MultiSelect = false;
            this.view.Name = "view";
            this.view.ValidationArguments = ((System.Collections.Generic.Dictionary<string, object[]>)(resources.GetObject("view.ValidationArguments")));
            this.view.ValidationHandles = ((System.Collections.Generic.Dictionary<string, System.Func<System.Windows.Forms.DataGridViewCell, object[], bool>>)(resources.GetObject("view.ValidationHandles")));
            // 
            // NumberColumn
            // 
            this.NumberColumn.FillWeight = 55F;
            resources.ApplyResources(this.NumberColumn, "NumberColumn");
            this.NumberColumn.Name = "NumberColumn";
            this.NumberColumn.ReadOnly = true;
            // 
            // DescriptionColumn
            // 
            this.DescriptionColumn.FillWeight = 150F;
            resources.ApplyResources(this.DescriptionColumn, "DescriptionColumn");
            this.DescriptionColumn.Name = "DescriptionColumn";
            // 
            // StatusColumn
            // 
            resources.ApplyResources(this.StatusColumn, "StatusColumn");
            this.StatusColumn.Name = "StatusColumn";
            // 
            // AutoManualColumn
            // 
            resources.ApplyResources(this.AutoManualColumn, "AutoManualColumn");
            this.AutoManualColumn.Name = "AutoManualColumn";
            // 
            // SizeColumn
            // 
            resources.ApplyResources(this.SizeColumn, "SizeColumn");
            this.SizeColumn.Name = "SizeColumn";
            // 
            // RunStatusColumn
            // 
            resources.ApplyResources(this.RunStatusColumn, "RunStatusColumn");
            this.RunStatusColumn.Name = "RunStatusColumn";
            this.RunStatusColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // LabelColumn
            // 
            resources.ApplyResources(this.LabelColumn, "LabelColumn");
            this.LabelColumn.Name = "LabelColumn";
            // 
            // CodeColumn
            // 
            resources.ApplyResources(this.CodeColumn, "CodeColumn");
            this.CodeColumn.Name = "CodeColumn";
            this.CodeColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.CodeColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // ProgramsForm
            // 
            this.AcceptButton = this.saveButton;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.Controls.Add(this.clearSelectedRowButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.view);
            this.Name = "ProgramsForm";
            ((System.ComponentModel.ISupportInitialize)(this.view)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private T3000.Controls.Improved.TDataGridView view;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button clearSelectedRowButton;
        private System.Windows.Forms.DataGridViewTextBoxColumn NumberColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn DescriptionColumn;
        private System.Windows.Forms.DataGridViewButtonColumn StatusColumn;
        private System.Windows.Forms.DataGridViewButtonColumn AutoManualColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn SizeColumn;
        private System.Windows.Forms.DataGridViewButtonColumn RunStatusColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn LabelColumn;
        private System.Windows.Forms.DataGridViewButtonColumn CodeColumn;
    }
}

