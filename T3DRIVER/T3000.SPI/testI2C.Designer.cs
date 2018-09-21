namespace T3000.I2C
{
    partial class TestI2C
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
            this.rbutChannel1 = new System.Windows.Forms.RadioButton();
            this.rbutChannel0 = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.numSpeed = new System.Windows.Forms.NumericUpDown();
            this.cmdStartSPITest = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numSpeed)).BeginInit();
            this.SuspendLayout();
            // 
            // rbutChannel1
            // 
            this.rbutChannel1.AutoSize = true;
            this.rbutChannel1.Checked = true;
            this.rbutChannel1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rbutChannel1.Location = new System.Drawing.Point(107, 16);
            this.rbutChannel1.Name = "rbutChannel1";
            this.rbutChannel1.Size = new System.Drawing.Size(73, 17);
            this.rbutChannel1.TabIndex = 0;
            this.rbutChannel1.TabStop = true;
            this.rbutChannel1.Text = "Channel 1";
            this.rbutChannel1.UseVisualStyleBackColor = true;
            // 
            // rbutChannel0
            // 
            this.rbutChannel0.AutoSize = true;
            this.rbutChannel0.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.rbutChannel0.Location = new System.Drawing.Point(107, 40);
            this.rbutChannel0.Name = "rbutChannel0";
            this.rbutChannel0.Size = new System.Drawing.Size(73, 17);
            this.rbutChannel0.TabIndex = 1;
            this.rbutChannel0.Text = "Channel 0";
            this.rbutChannel0.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.rbutChannel0);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.rbutChannel1);
            this.groupBox2.Controls.Add(this.numSpeed);
            this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(12, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(198, 64);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Initial Parameters";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(6, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Speed";
            // 
            // numSpeed
            // 
            this.numSpeed.Increment = new decimal(new int[] {
            10000000,
            0,
            0,
            0});
            this.numSpeed.Location = new System.Drawing.Point(6, 38);
            this.numSpeed.Maximum = new decimal(new int[] {
            100000000,
            0,
            0,
            0});
            this.numSpeed.Minimum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.numSpeed.Name = "numSpeed";
            this.numSpeed.Size = new System.Drawing.Size(91, 20);
            this.numSpeed.TabIndex = 2;
            this.numSpeed.Value = new decimal(new int[] {
            50000000,
            0,
            0,
            0});
            // 
            // cmdStartSPITest
            // 
            this.cmdStartSPITest.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmdStartSPITest.Location = new System.Drawing.Point(18, 148);
            this.cmdStartSPITest.Name = "cmdStartSPITest";
            this.cmdStartSPITest.Size = new System.Drawing.Size(192, 39);
            this.cmdStartSPITest.TabIndex = 6;
            this.cmdStartSPITest.Text = "START SPI TEST";
            this.cmdStartSPITest.UseVisualStyleBackColor = true;
            this.cmdStartSPITest.Click += new System.EventHandler(this.cmdStartSPITest_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(216, 23);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(213, 164);
            this.textBox1.TabIndex = 7;
            // 
            // TestI2C
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(455, 204);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.cmdStartSPITest);
            this.Controls.Add(this.groupBox2);
            this.Name = "TestI2C";
            this.Text = "TestSPI";
            this.Load += new System.EventHandler(this.TestSPI_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numSpeed)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.RadioButton rbutChannel0;
        private System.Windows.Forms.RadioButton rbutChannel1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numSpeed;
        private System.Windows.Forms.Button cmdStartSPITest;
        private System.Windows.Forms.TextBox textBox1;
    }
}