namespace T3000.Forms
{
    partial class SelectUnitsForm
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
            this.digitalUnitsListBox = new System.Windows.Forms.ListBox();
            this.analogUnitsListBox = new System.Windows.Forms.ListBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.messageLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.numberTextBox = new System.Windows.Forms.TextBox();
            this.saveButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.editButton = new System.Windows.Forms.Button();
            this.analogUnitsLabel = new System.Windows.Forms.Label();
            this.digitalUnitsLabel = new System.Windows.Forms.Label();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // digitalUnitsListBox
            // 
            this.digitalUnitsListBox.ColumnWidth = 140;
            this.digitalUnitsListBox.FormattingEnabled = true;
            this.digitalUnitsListBox.Location = new System.Drawing.Point(355, 52);
            this.digitalUnitsListBox.MultiColumn = true;
            this.digitalUnitsListBox.Name = "digitalUnitsListBox";
            this.digitalUnitsListBox.Size = new System.Drawing.Size(341, 329);
            this.digitalUnitsListBox.TabIndex = 2;
            this.digitalUnitsListBox.SelectedIndexChanged += new System.EventHandler(this.digitalUnitsListBox_SelectedIndexChanged);
            this.digitalUnitsListBox.DoubleClick += new System.EventHandler(this.Save);
            this.digitalUnitsListBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.unitsListBox_KeyDown);
            // 
            // analogUnitsListBox
            // 
            this.analogUnitsListBox.ColumnWidth = 140;
            this.analogUnitsListBox.FormattingEnabled = true;
            this.analogUnitsListBox.Location = new System.Drawing.Point(8, 52);
            this.analogUnitsListBox.MultiColumn = true;
            this.analogUnitsListBox.Name = "analogUnitsListBox";
            this.analogUnitsListBox.Size = new System.Drawing.Size(341, 329);
            this.analogUnitsListBox.TabIndex = 1;
            this.analogUnitsListBox.SelectedIndexChanged += new System.EventHandler(this.analogUnitsListBox_SelectedIndexChanged);
            this.analogUnitsListBox.DoubleClick += new System.EventHandler(this.Save);
            this.analogUnitsListBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.unitsListBox_KeyDown);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.messageLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 389);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(708, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // messageLabel
            // 
            this.messageLabel.Name = "messageLabel";
            this.messageLabel.Size = new System.Drawing.Size(131, 17);
            this.messageLabel.Text = "Please select need units";
            // 
            // numberTextBox
            // 
            this.numberTextBox.Location = new System.Drawing.Point(8, 10);
            this.numberTextBox.Name = "numberTextBox";
            this.numberTextBox.Size = new System.Drawing.Size(100, 20);
            this.numberTextBox.TabIndex = 0;
            this.numberTextBox.TextChanged += new System.EventHandler(this.numberTextBox_TextChanged);
            this.numberTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.numberTextBox_KeyDown);
            // 
            // saveButton
            // 
            this.saveButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.saveButton.Location = new System.Drawing.Point(114, 8);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(119, 25);
            this.saveButton.TabIndex = 3;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.Save);
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(239, 8);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(110, 25);
            this.cancelButton.TabIndex = 4;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.Cancel);
            // 
            // editButton
            // 
            this.editButton.Location = new System.Drawing.Point(523, 7);
            this.editButton.Name = "editButton";
            this.editButton.Size = new System.Drawing.Size(173, 25);
            this.editButton.TabIndex = 5;
            this.editButton.Text = "Edit custom units";
            this.editButton.UseVisualStyleBackColor = true;
            this.editButton.Click += new System.EventHandler(this.EditCustomUnits);
            // 
            // analogUnitsLabel
            // 
            this.analogUnitsLabel.AutoSize = true;
            this.analogUnitsLabel.Location = new System.Drawing.Point(5, 36);
            this.analogUnitsLabel.Name = "analogUnitsLabel";
            this.analogUnitsLabel.Size = new System.Drawing.Size(68, 13);
            this.analogUnitsLabel.TabIndex = 6;
            this.analogUnitsLabel.Text = "Analog units:";
            // 
            // digitalUnitsLabel
            // 
            this.digitalUnitsLabel.AutoSize = true;
            this.digitalUnitsLabel.Location = new System.Drawing.Point(352, 36);
            this.digitalUnitsLabel.Name = "digitalUnitsLabel";
            this.digitalUnitsLabel.Size = new System.Drawing.Size(64, 13);
            this.digitalUnitsLabel.TabIndex = 7;
            this.digitalUnitsLabel.Text = "Digital units:";
            // 
            // SelectUnitsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(708, 411);
            this.Controls.Add(this.digitalUnitsLabel);
            this.Controls.Add(this.analogUnitsLabel);
            this.Controls.Add(this.editButton);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.numberTextBox);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.analogUnitsListBox);
            this.Controls.Add(this.digitalUnitsListBox);
            this.Name = "SelectUnitsForm";
            this.Text = "Select units:";
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox digitalUnitsListBox;
        private System.Windows.Forms.ListBox analogUnitsListBox;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel messageLabel;
        private System.Windows.Forms.TextBox numberTextBox;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button editButton;
        private System.Windows.Forms.Label analogUnitsLabel;
        private System.Windows.Forms.Label digitalUnitsLabel;
    }
}