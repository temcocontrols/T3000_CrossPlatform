namespace T3000.Forms
{
    partial class VariablesForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(VariablesForm));
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            this.saveButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.clearSelectedRowButton = new System.Windows.Forms.Button();
            this.view = new T3000.Controls.TView();
            this.NumberColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.AutoManualColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.ValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.UnitsColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.RangeColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.StatusColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.LabelColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.view)).BeginInit();
            this.SuspendLayout();
            // 
            // saveButton
            // 
            resources.ApplyResources(this.saveButton, "saveButton");
            this.saveButton.DialogResult = System.Windows.Forms.DialogResult.OK;
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
            this.AutoManualColumn,
            this.ValueColumn,
            this.UnitsColumn,
            this.StatusColumn,
            this.LabelColumn,
            this.RangeColumn});
            this.view.MultiSelect = false;
            this.view.Name = "view";
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
            // AutoManualColumn
            // 
            resources.ApplyResources(this.AutoManualColumn, "AutoManualColumn");
            this.AutoManualColumn.Name = "AutoManualColumn";
            this.AutoManualColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // ValueColumn
            // 
            resources.ApplyResources(this.ValueColumn, "ValueColumn");
            this.ValueColumn.Name = "ValueColumn";
            // 
            // UnitsColumn
            // 
            resources.ApplyResources(this.UnitsColumn, "UnitsColumn");
            this.UnitsColumn.Name = "UnitsColumn";
            this.UnitsColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // RangeColumn
            // 
            resources.ApplyResources(this.RangeColumn, "RangeColumn");
            this.RangeColumn.Name = "RangeColumn";
            // 
            // StatusColumn
            // 
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.ButtonFace;
            dataGridViewCellStyle1.ForeColor = System.Drawing.Color.Red;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.ButtonHighlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.ControlText;
            this.StatusColumn.DefaultCellStyle = dataGridViewCellStyle1;
            this.StatusColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            resources.ApplyResources(this.StatusColumn, "StatusColumn");
            this.StatusColumn.Name = "StatusColumn";
            this.StatusColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.StatusColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // LabelColumn
            // 
            resources.ApplyResources(this.LabelColumn, "LabelColumn");
            this.LabelColumn.Name = "LabelColumn";
            // 
            // VariablesForm
            // 
            this.AcceptButton = this.saveButton;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.Controls.Add(this.clearSelectedRowButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.view);
            this.Icon = global::T3000.Properties.Resources.VariablesIcon;
            this.Name = "VariablesForm";
            ((System.ComponentModel.ISupportInitialize)(this.view)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private T3000.Controls.TView view;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button clearSelectedRowButton;
        private System.Windows.Forms.DataGridViewTextBoxColumn NumberColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn DescriptionColumn;
        private System.Windows.Forms.DataGridViewButtonColumn AutoManualColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn ValueColumn;
        private System.Windows.Forms.DataGridViewButtonColumn UnitsColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn RangeColumn;
        private System.Windows.Forms.DataGridViewButtonColumn StatusColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn LabelColumn;
    }
}

