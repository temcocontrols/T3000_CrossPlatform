namespace T3000.Forms
{
    partial class EditCustomDigitalUnitForm
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
            this.cancelButton = new System.Windows.Forms.Button();
            this.saveButton = new System.Windows.Forms.Button();
            this.offNameLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.offNameTextBox = new System.Windows.Forms.TextBox();
            this.onNameTextBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(157, 75);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(115, 23);
            this.cancelButton.TabIndex = 5;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.Cancel);
            // 
            // saveButton
            // 
            this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.saveButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.saveButton.Location = new System.Drawing.Point(14, 75);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(137, 23);
            this.saveButton.TabIndex = 4;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.Save);
            // 
            // offNameLabel
            // 
            this.offNameLabel.AutoSize = true;
            this.offNameLabel.Location = new System.Drawing.Point(12, 17);
            this.offNameLabel.Name = "offNameLabel";
            this.offNameLabel.Size = new System.Drawing.Size(53, 13);
            this.offNameLabel.TabIndex = 6;
            this.offNameLabel.Text = "Off name:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 45);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 13);
            this.label1.TabIndex = 7;
            this.label1.Text = "On name:";
            // 
            // offNameTextBox
            // 
            this.offNameTextBox.Location = new System.Drawing.Point(71, 14);
            this.offNameTextBox.Name = "offNameTextBox";
            this.offNameTextBox.Size = new System.Drawing.Size(199, 20);
            this.offNameTextBox.TabIndex = 8;
            this.offNameTextBox.TextChanged += new System.EventHandler(this.ValidateNames);
            // 
            // onNameTextBox
            // 
            this.onNameTextBox.Location = new System.Drawing.Point(71, 42);
            this.onNameTextBox.Name = "onNameTextBox";
            this.onNameTextBox.Size = new System.Drawing.Size(199, 20);
            this.onNameTextBox.TabIndex = 9;
            this.onNameTextBox.TextChanged += new System.EventHandler(this.ValidateNames);
            // 
            // EditCustomDigitalUnitForm
            // 
            this.AcceptButton = this.saveButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(282, 110);
            this.Controls.Add(this.onNameTextBox);
            this.Controls.Add(this.offNameTextBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.offNameLabel);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Name = "EditCustomDigitalUnitForm";
            this.Text = "Edit custom analog unit:";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Label offNameLabel;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox offNameTextBox;
        private System.Windows.Forms.TextBox onNameTextBox;
    }
}