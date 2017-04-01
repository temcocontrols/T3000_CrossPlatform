namespace T3000.Forms
{
    partial class InputsForm
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
            this.prgView = new System.Windows.Forms.DataGridView();
            this.saveButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.clearSelectedRowButton = new System.Windows.Forms.Button();
            this.NumberColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.AutoManualColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.ValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.UnitsColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.LabelColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.prgView)).BeginInit();
            this.SuspendLayout();
            // 
            // prgView
            // 
            this.prgView.AllowUserToAddRows = false;
            this.prgView.AllowUserToDeleteRows = false;
            resources.ApplyResources(this.prgView, "prgView");
            this.prgView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.prgView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.prgView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.NumberColumn,
            this.DescriptionColumn,
            this.AutoManualColumn,
            this.ValueColumn,
            this.UnitsColumn,
            this.LabelColumn});
            this.prgView.MultiSelect = false;
            this.prgView.Name = "prgView";
            this.prgView.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.prgView_CellContentClick);
            this.prgView.CellValidating += new System.Windows.Forms.DataGridViewCellValidatingEventHandler(this.prgView_CellValidating);
            this.prgView.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.prgView_CellValueChanged);
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
            this.clearSelectedRowButton.Click += new System.EventHandler(this.clearSelectedRowButton_Click);
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
            this.Controls.Add(this.prgView);
            this.Name = "VariablesForm";
            ((System.ComponentModel.ISupportInitialize)(this.prgView)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView prgView;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button clearSelectedRowButton;
        private System.Windows.Forms.DataGridViewTextBoxColumn NumberColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn DescriptionColumn;
        private System.Windows.Forms.DataGridViewButtonColumn AutoManualColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn ValueColumn;
        private System.Windows.Forms.DataGridViewButtonColumn UnitsColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn LabelColumn;
    }
}

