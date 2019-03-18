namespace T3000.LEDS
{
    partial class LEDTestingForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LEDTestingForm));
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.chkONOFF = new System.Windows.Forms.CheckBox();
            this.DimPercent = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.DimPercent)).BeginInit();
            this.SuspendLayout();
            // 
            // comboBox1
            // 
            this.comboBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(23, 12);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(163, 28);
            this.comboBox1.TabIndex = 0;
            // 
            // chkONOFF
            // 
            this.chkONOFF.AutoSize = true;
            this.chkONOFF.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.chkONOFF.Location = new System.Drawing.Point(207, 17);
            this.chkONOFF.Name = "chkONOFF";
            this.chkONOFF.Size = new System.Drawing.Size(120, 20);
            this.chkONOFF.TabIndex = 1;
            this.chkONOFF.Text = "Change State";
            this.chkONOFF.UseVisualStyleBackColor = true;
            this.chkONOFF.CheckedChanged += new System.EventHandler(this.chkONOFF_CheckedChanged);
            // 
            // DimPercent
            // 
            this.DimPercent.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DimPercent.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.DimPercent.Location = new System.Drawing.Point(350, 15);
            this.DimPercent.Name = "DimPercent";
            this.DimPercent.Size = new System.Drawing.Size(50, 24);
            this.DimPercent.TabIndex = 2;
            this.DimPercent.ValueChanged += new System.EventHandler(this.DimPercent_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(404, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 20);
            this.label1.TabIndex = 3;
            this.label1.Text = "% DIM";
            // 
            // LEDTestingForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.BackColor = System.Drawing.Color.LightGray;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(632, 612);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.DimPercent);
            this.Controls.Add(this.chkONOFF);
            this.Controls.Add(this.comboBox1);
            this.DoubleBuffered = true;
            this.Name = "LEDTestingForm";
            this.Text = "LEDTestingForm";
            this.Load += new System.EventHandler(this.LEDTestingForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.DimPercent)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.CheckBox chkONOFF;
        private System.Windows.Forms.NumericUpDown DimPercent;
        private System.Windows.Forms.Label label1;
    }
}