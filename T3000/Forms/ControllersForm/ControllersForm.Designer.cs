namespace T3000.Forms
{
    partial class ControllersForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ControllersForm));
            this.saveButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.clearSelectedRowButton = new System.Windows.Forms.Button();
            this.view = new T3000.Controls.TView();
            this.NumberColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.InputColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.UnitsColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.AutoManualColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.OutputColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SetPointColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SetValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SetPointUnitsColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ActionColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.PropColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.IntColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.TimeColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.Der = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.BiasColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
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
            this.InputColumn,
            this.ValueColumn,
            this.UnitsColumn,
            this.AutoManualColumn,
            this.OutputColumn,
            this.SetPointColumn,
            this.SetValueColumn,
            this.SetPointUnitsColumn,
            this.ActionColumn,
            this.PropColumn,
            this.IntColumn,
            this.TimeColumn,
            this.Der,
            this.BiasColumn});
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
            // InputColumn
            // 
            resources.ApplyResources(this.InputColumn, "InputColumn");
            this.InputColumn.Name = "InputColumn";
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
            // AutoManualColumn
            // 
            resources.ApplyResources(this.AutoManualColumn, "AutoManualColumn");
            this.AutoManualColumn.Name = "AutoManualColumn";
            this.AutoManualColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // OutputColumn
            // 
            resources.ApplyResources(this.OutputColumn, "OutputColumn");
            this.OutputColumn.Name = "OutputColumn";
            // 
            // SetPointColumn
            // 
            resources.ApplyResources(this.SetPointColumn, "SetPointColumn");
            this.SetPointColumn.Name = "SetPointColumn";
            // 
            // SetValueColumn
            // 
            resources.ApplyResources(this.SetValueColumn, "SetValueColumn");
            this.SetValueColumn.Name = "SetValueColumn";
            // 
            // SetPointUnitsColumn
            // 
            resources.ApplyResources(this.SetPointUnitsColumn, "SetPointUnitsColumn");
            this.SetPointUnitsColumn.Name = "SetPointUnitsColumn";
            // 
            // ActionColumn
            // 
            resources.ApplyResources(this.ActionColumn, "ActionColumn");
            this.ActionColumn.Name = "ActionColumn";
            this.ActionColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.ActionColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // PropColumn
            // 
            resources.ApplyResources(this.PropColumn, "PropColumn");
            this.PropColumn.Name = "PropColumn";
            // 
            // IntColumn
            // 
            resources.ApplyResources(this.IntColumn, "IntColumn");
            this.IntColumn.Name = "IntColumn";
            // 
            // TimeColumn
            // 
            resources.ApplyResources(this.TimeColumn, "TimeColumn");
            this.TimeColumn.Name = "TimeColumn";
            this.TimeColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.TimeColumn.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // Der
            // 
            resources.ApplyResources(this.Der, "Der");
            this.Der.Name = "Der";
            // 
            // BiasColumn
            // 
            resources.ApplyResources(this.BiasColumn, "BiasColumn");
            this.BiasColumn.Name = "BiasColumn";
            // 
            // ControllersForm
            // 
            this.AcceptButton = this.saveButton;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.Controls.Add(this.clearSelectedRowButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.view);
            this.Name = "ControllersForm";
            ((System.ComponentModel.ISupportInitialize)(this.view)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private T3000.Controls.TView view;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button clearSelectedRowButton;
        private System.Windows.Forms.DataGridViewTextBoxColumn NumberColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn InputColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn ValueColumn;
        private System.Windows.Forms.DataGridViewButtonColumn UnitsColumn;
        private System.Windows.Forms.DataGridViewButtonColumn AutoManualColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn OutputColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn SetPointColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn SetValueColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn SetPointUnitsColumn;
        private System.Windows.Forms.DataGridViewButtonColumn ActionColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn PropColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn IntColumn;
        private System.Windows.Forms.DataGridViewButtonColumn TimeColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn Der;
        private System.Windows.Forms.DataGridViewTextBoxColumn BiasColumn;
    }
}

