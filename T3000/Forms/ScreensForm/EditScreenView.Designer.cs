namespace T3000.Forms
{
    partial class EditScreenView
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
            this.view = new T3000.Controls.TView();
            this.LabelColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DescriptionColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ValueColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.AutoManualColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.HighLimitColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.LowLimitColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.DisplayColorColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.HighColorColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.LowColorColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            this.DisplayColumn = new System.Windows.Forms.DataGridViewButtonColumn();
            ((System.ComponentModel.ISupportInitialize)(this.view)).BeginInit();
            this.SuspendLayout();
            // 
            // view
            // 
            this.view.AllowUserToAddRows = false;
            this.view.AllowUserToDeleteRows = false;
            this.view.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.view.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.view.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.view.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.LabelColumn,
            this.DescriptionColumn,
            this.ValueColumn,
            this.AutoManualColumn,
            this.HighLimitColumn,
            this.LowLimitColumn,
            this.DisplayColorColumn,
            this.HighColorColumn,
            this.LowColorColumn,
            this.DisplayColumn});
            this.view.Location = new System.Drawing.Point(12, 12);
            this.view.MultiSelect = false;
            this.view.Name = "view";
            this.view.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.view.Size = new System.Drawing.Size(875, 57);
            this.view.TabIndex = 1;
            // 
            // LabelColumn
            // 
            this.LabelColumn.HeaderText = "Label";
            this.LabelColumn.Name = "LabelColumn";
            // 
            // DescriptionColumn
            // 
            this.DescriptionColumn.FillWeight = 150F;
            this.DescriptionColumn.HeaderText = "Description";
            this.DescriptionColumn.Name = "DescriptionColumn";
            // 
            // ValueColumn
            // 
            this.ValueColumn.HeaderText = "Value";
            this.ValueColumn.Name = "ValueColumn";
            // 
            // AutoManualColumn
            // 
            this.AutoManualColumn.HeaderText = "A/M";
            this.AutoManualColumn.Name = "AutoManualColumn";
            this.AutoManualColumn.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // HighLimitColumn
            // 
            this.HighLimitColumn.HeaderText = "HighLimit";
            this.HighLimitColumn.Name = "HighLimitColumn";
            // 
            // LowLimitColumn
            // 
            this.LowLimitColumn.HeaderText = "LowLimit";
            this.LowLimitColumn.Name = "LowLimitColumn";
            // 
            // DisplayColorColumn
            // 
            this.DisplayColorColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.DisplayColorColumn.HeaderText = "DisplayColor";
            this.DisplayColorColumn.Name = "DisplayColorColumn";
            // 
            // HighColorColumn
            // 
            this.HighColorColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.HighColorColumn.HeaderText = "HighColor";
            this.HighColorColumn.Name = "HighColorColumn";
            // 
            // LowColorColumn
            // 
            this.LowColorColumn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.LowColorColumn.HeaderText = "LowColor";
            this.LowColorColumn.Name = "LowColorColumn";
            // 
            // DisplayColumn
            // 
            this.DisplayColumn.HeaderText = "Display";
            this.DisplayColumn.Name = "DisplayColumn";
            this.DisplayColumn.Text = "";
            // 
            // EditScreenView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(899, 81);
            this.ControlBox = false;
            this.Controls.Add(this.view);
            this.Name = "EditScreenView";
            ((System.ComponentModel.ISupportInitialize)(this.view)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private Controls.TView view;
        private System.Windows.Forms.DataGridViewTextBoxColumn LabelColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn DescriptionColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn ValueColumn;
        private System.Windows.Forms.DataGridViewButtonColumn AutoManualColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn HighLimitColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn LowLimitColumn;
        private System.Windows.Forms.DataGridViewButtonColumn DisplayColorColumn;
        private System.Windows.Forms.DataGridViewButtonColumn HighColorColumn;
        private System.Windows.Forms.DataGridViewButtonColumn LowColorColumn;
        private System.Windows.Forms.DataGridViewButtonColumn DisplayColumn;
    }
}