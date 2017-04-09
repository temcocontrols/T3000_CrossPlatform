namespace T3000.Forms
{
    partial class EditSchedulesForm
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
            this.saveButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.sliderControl1 = new T3000.Controls.SliderControl();
            this.SuspendLayout();
            // 
            // saveButton
            // 
            this.saveButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.saveButton.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.saveButton.Location = new System.Drawing.Point(296, 327);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(145, 32);
            this.saveButton.TabIndex = 5;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.Save);
            // 
            // cancelButton
            // 
            this.cancelButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.cancelButton.Location = new System.Drawing.Point(447, 327);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(133, 32);
            this.cancelButton.TabIndex = 6;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            this.cancelButton.Click += new System.EventHandler(this.Cancel);
            // 
            // sliderControl1
            // 
            this.sliderControl1.AdditionalText = " H";
            this.sliderControl1.BackColor = System.Drawing.Color.Transparent;
            this.sliderControl1.BackgroundWidth = 50;
            this.sliderControl1.BorderColor = System.Drawing.Color.Black;
            this.sliderControl1.BottomValue = 24F;
            this.sliderControl1.BottomZone = true;
            this.sliderControl1.BottomZoneColor = System.Drawing.Color.Red;
            this.sliderControl1.BottomZoneValue = 18F;
            this.sliderControl1.CurrentValue = 12F;
            this.sliderControl1.CurrentValueColor = System.Drawing.Color.Black;
            this.sliderControl1.EnableIndicator = false;
            this.sliderControl1.HandlesBorderColor = System.Drawing.Color.White;
            this.sliderControl1.HandlesHeight = 8;
            this.sliderControl1.IndicatorBorderColor = System.Drawing.Color.Black;
            this.sliderControl1.IndicatorColor = System.Drawing.Color.GreenYellow;
            this.sliderControl1.IndicatorHeight = 20;
            this.sliderControl1.IndicatorText = "";
            this.sliderControl1.IndicatorWidth = 20;
            this.sliderControl1.IsSimpleIndicator = true;
            this.sliderControl1.LinesColor = System.Drawing.Color.LightGray;
            this.sliderControl1.Location = new System.Drawing.Point(12, 12);
            this.sliderControl1.LowEventMode = true;
            this.sliderControl1.MiddleHandleColor = System.Drawing.Color.GreenYellow;
            this.sliderControl1.MiddleZoneValue = 12F;
            this.sliderControl1.MiddleZoneValueAsAverage = true;
            this.sliderControl1.Name = "sliderControl1";
            this.sliderControl1.Size = new System.Drawing.Size(153, 298);
            this.sliderControl1.StepValue = 6F;
            this.sliderControl1.TabIndex = 7;
            this.sliderControl1.TimeValues = true;
            this.sliderControl1.TopValue = 0F;
            this.sliderControl1.TopZone = true;
            this.sliderControl1.TopZoneColor = System.Drawing.Color.DeepSkyBlue;
            this.sliderControl1.TopZoneValue = 6F;
            this.sliderControl1.TwoSliderMode = true;
            // 
            // EditSchedulesForm
            // 
            this.AcceptButton = this.saveButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(584, 361);
            this.Controls.Add(this.sliderControl1);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.saveButton);
            this.Name = "EditSchedulesForm";
            this.Text = "Edit schedule:";
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button cancelButton;
        private Controls.SliderControl sliderControl1;
    }
}