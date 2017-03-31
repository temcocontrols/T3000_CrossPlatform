﻿namespace T3000
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
            this.prgView = new System.Windows.Forms.DataGridView();
            this.saveButton = new System.Windows.Forms.Button();
            this.NumberColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.AutoManualColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.ValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.UnitsColumn = new System.Windows.Forms.DataGridViewComboBoxColumn();
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
            this.prgView.CellContextMenuStripChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.prgView_CellContextMenuStripChanged);
            this.prgView.CellStateChanged += new System.Windows.Forms.DataGridViewCellStateChangedEventHandler(this.prgView_CellStateChanged);
            this.prgView.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.prgView_CellValueChanged);
            this.prgView.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.prgView_PreviewKeyDown);
            // 
            // saveButton
            // 
            resources.ApplyResources(this.saveButton, "saveButton");
            this.saveButton.Name = "saveButton";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.Save);
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
            // 
            // LabelColumn
            // 
            resources.ApplyResources(this.LabelColumn, "LabelColumn");
            this.LabelColumn.Name = "LabelColumn";
            // 
            // VariablesForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.prgView);
            this.Name = "VariablesForm";
            ((System.ComponentModel.ISupportInitialize)(this.prgView)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView prgView;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.DataGridViewTextBoxColumn NumberColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn DescriptionColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn AutoManualColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn ValueColumn;
        private System.Windows.Forms.DataGridViewComboBoxColumn UnitsColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn LabelColumn;
    }
}
