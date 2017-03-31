namespace T3000
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
            this.addButton = new System.Windows.Forms.Button();
            this.prgView = new System.Windows.Forms.DataGridView();
            this.Number = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Description = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.AutoManual = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.Value = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Units = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.Label = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.deleteButton = new System.Windows.Forms.Button();
            this.openButton = new System.Windows.Forms.Button();
            this.saveButton = new System.Windows.Forms.Button();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.languageMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.englishToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.germanToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.chineseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.statusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            ((System.ComponentModel.ISupportInitialize)(this.prgView)).BeginInit();
            this.menuStrip.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // addButton
            // 
            resources.ApplyResources(this.addButton, "addButton");
            this.addButton.Name = "addButton";
            this.addButton.UseVisualStyleBackColor = true;
            // 
            // prgView
            // 
            this.prgView.AllowUserToAddRows = false;
            this.prgView.AllowUserToDeleteRows = false;
            resources.ApplyResources(this.prgView, "prgView");
            this.prgView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.prgView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.prgView.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Number,
            this.Description,
            this.AutoManual,
            this.Value,
            this.Units,
            this.Label});
            this.prgView.MultiSelect = false;
            this.prgView.Name = "prgView";
            this.prgView.CellContextMenuStripChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.prgView_CellContextMenuStripChanged);
            this.prgView.CellStateChanged += new System.Windows.Forms.DataGridViewCellStateChangedEventHandler(this.prgView_CellStateChanged);
            this.prgView.CellValueChanged += new System.Windows.Forms.DataGridViewCellEventHandler(this.prgView_CellValueChanged);
            this.prgView.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler(this.prgView_PreviewKeyDown);
            // 
            // Number
            // 
            this.Number.FillWeight = 55F;
            resources.ApplyResources(this.Number, "Number");
            this.Number.Name = "Number";
            this.Number.ReadOnly = true;
            // 
            // Description
            // 
            this.Description.FillWeight = 150F;
            resources.ApplyResources(this.Description, "Description");
            this.Description.Name = "Description";
            // 
            // AutoManual
            // 
            resources.ApplyResources(this.AutoManual, "AutoManual");
            this.AutoManual.Name = "AutoManual";
            this.AutoManual.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // Value
            // 
            resources.ApplyResources(this.Value, "Value");
            this.Value.Name = "Value";
            // 
            // Units
            // 
            resources.ApplyResources(this.Units, "Units");
            this.Units.Name = "Units";
            // 
            // Label
            // 
            resources.ApplyResources(this.Label, "Label");
            this.Label.Name = "Label";
            // 
            // deleteButton
            // 
            resources.ApplyResources(this.deleteButton, "deleteButton");
            this.deleteButton.Name = "deleteButton";
            this.deleteButton.UseVisualStyleBackColor = true;
            // 
            // openButton
            // 
            resources.ApplyResources(this.openButton, "openButton");
            this.openButton.Name = "openButton";
            this.openButton.UseVisualStyleBackColor = true;
            this.openButton.Click += new System.EventHandler(this.openButton_Click);
            // 
            // saveButton
            // 
            resources.ApplyResources(this.saveButton, "saveButton");
            this.saveButton.Name = "saveButton";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.languageMenuItem});
            resources.ApplyResources(this.menuStrip, "menuStrip");
            this.menuStrip.Name = "menuStrip";
            // 
            // languageMenuItem
            // 
            this.languageMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.englishToolStripMenuItem,
            this.germanToolStripMenuItem,
            this.chineseToolStripMenuItem});
            this.languageMenuItem.Name = "languageMenuItem";
            resources.ApplyResources(this.languageMenuItem, "languageMenuItem");
            // 
            // englishToolStripMenuItem
            // 
            this.englishToolStripMenuItem.Name = "englishToolStripMenuItem";
            resources.ApplyResources(this.englishToolStripMenuItem, "englishToolStripMenuItem");
            this.englishToolStripMenuItem.Click += new System.EventHandler(this.englishToolStripMenuItem_Click);
            // 
            // germanToolStripMenuItem
            // 
            this.germanToolStripMenuItem.Name = "germanToolStripMenuItem";
            resources.ApplyResources(this.germanToolStripMenuItem, "germanToolStripMenuItem");
            this.germanToolStripMenuItem.Click += new System.EventHandler(this.germanToolStripMenuItem_Click);
            // 
            // chineseToolStripMenuItem
            // 
            this.chineseToolStripMenuItem.Name = "chineseToolStripMenuItem";
            resources.ApplyResources(this.chineseToolStripMenuItem, "chineseToolStripMenuItem");
            this.chineseToolStripMenuItem.Click += new System.EventHandler(this.chineseToolStripMenuItem_Click);
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.statusLabel});
            resources.ApplyResources(this.statusStrip, "statusStrip");
            this.statusStrip.Name = "statusStrip";
            // 
            // statusLabel
            // 
            this.statusLabel.Name = "statusLabel";
            resources.ApplyResources(this.statusLabel, "statusLabel");
            // 
            // VariablesForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.openButton);
            this.Controls.Add(this.deleteButton);
            this.Controls.Add(this.addButton);
            this.Controls.Add(this.prgView);
            this.Controls.Add(this.menuStrip);
            this.MainMenuStrip = this.menuStrip;
            this.Name = "VariablesForm";
            ((System.ComponentModel.ISupportInitialize)(this.prgView)).EndInit();
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView prgView;
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.Button deleteButton;
        private System.Windows.Forms.Button openButton;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem languageMenuItem;
        private System.Windows.Forms.ToolStripMenuItem germanToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem englishToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem chineseToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel;
        private System.Windows.Forms.DataGridViewTextBoxColumn Number;
        private System.Windows.Forms.DataGridViewTextBoxColumn Description;
        private System.Windows.Forms.DataGridViewComboBoxColumn AutoManual;
        private System.Windows.Forms.DataGridViewTextBoxColumn Value;
        private System.Windows.Forms.DataGridViewComboBoxColumn Units;
        private System.Windows.Forms.DataGridViewTextBoxColumn Label;
    }
}

