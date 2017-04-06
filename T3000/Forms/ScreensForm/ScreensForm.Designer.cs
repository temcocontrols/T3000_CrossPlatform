namespace T3000.Forms
{
    partial class ScreensForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ScreensForm));
            this.view = new T3000.Controls.Improved.TDataGridView();
            this.saveButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.clearSelectedRowButton = new System.Windows.Forms.Button();
            this.NumberColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.LabelColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.PictureColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.ModeColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.RefreshColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.view)).BeginInit();
            this.SuspendLayout();
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
            this.LabelColumn,
            this.PictureColumn,
            this.ModeColumn,
            this.RefreshColumn});
            this.view.MultiSelect = false;
            this.view.Name = "view";
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
            // LabelColumn
            // 
            resources.ApplyResources(this.LabelColumn, "LabelColumn");
            this.LabelColumn.Name = "LabelColumn";
            // 
            // PictureColumn
            // 
            resources.ApplyResources(this.PictureColumn, "PictureColumn");
            this.PictureColumn.Name = "PictureColumn";
            // 
            // ModeColumn
            // 
            resources.ApplyResources(this.ModeColumn, "ModeColumn");
            this.ModeColumn.Name = "ModeColumn";
            this.ModeColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // RefreshColumn
            // 
            resources.ApplyResources(this.RefreshColumn, "RefreshColumn");
            this.RefreshColumn.Name = "RefreshColumn";
            // 
            // ScreensForm
            // 
            this.AcceptButton = this.saveButton;
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.Controls.Add(this.clearSelectedRowButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.view);
            this.Name = "ScreensForm";
            this.Icon = global::T3000.Properties.Resources.GraphicsIcon;
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
        private System.Windows.Forms.DataGridViewTextBoxColumn LabelColumn;
        private System.Windows.Forms.DataGridViewButtonColumn PictureColumn;
        private System.Windows.Forms.DataGridViewButtonColumn ModeColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn RefreshColumn;
    }
}

