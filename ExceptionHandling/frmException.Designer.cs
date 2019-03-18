namespace ExceptionHandling
{
    partial class frmException
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmException));
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.cmdAccept = new System.Windows.Forms.Button();
            this.cmdCopy = new System.Windows.Forms.Button();
            this.cmdSaveToFile = new System.Windows.Forms.Button();
            this.lblCustomMessage = new System.Windows.Forms.Label();
            this.txtExceptionDetail = new System.Windows.Forms.TextBox();

			 this.cmdTerminateApp = new System.Windows.Forms.Button();
            this.tableLayoutPanel1.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.flowLayoutPanel1, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.lblCustomMessage, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.txtExceptionDetail, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 16.58986F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 83.41014F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 35F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(442, 217);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.Controls.Add(this.cmdAccept);
            this.flowLayoutPanel1.Controls.Add(this.cmdCopy);
            this.flowLayoutPanel1.Controls.Add(this.cmdSaveToFile);
            this.flowLayoutPanel1.Controls.Add(this.cmdTerminateApp);
            this.flowLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.flowLayoutPanel1.FlowDirection = System.Windows.Forms.FlowDirection.RightToLeft;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(3, 184);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(436, 30);
            this.flowLayoutPanel1.TabIndex = 0;
            // 
            // cmdAccept
            // 
            this.cmdAccept.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.cmdAccept.Location = new System.Drawing.Point(358, 3);
            this.cmdAccept.Name = "cmdAccept";
            this.cmdAccept.Size = new System.Drawing.Size(75, 23);
            this.cmdAccept.TabIndex = 0;
            this.cmdAccept.Text = "&Accept";
            this.cmdAccept.UseVisualStyleBackColor = true;
            this.cmdAccept.Click += new System.EventHandler(this.cmdAccept_Click);
// 
            // cmdCopy
            // 
            this.cmdCopy.DialogResult = System.Windows.Forms.DialogResult.Ignore;
            this.cmdCopy.Location = new System.Drawing.Point(277, 3);
            this.cmdCopy.Name = "cmdCopy";
            this.cmdCopy.Size = new System.Drawing.Size(75, 23);
            this.cmdCopy.TabIndex = 2;
            this.cmdCopy.Text = "&Copy";
            this.cmdCopy.UseVisualStyleBackColor = true;
            this.cmdCopy.Click += new System.EventHandler(this.cmdCopy_Click);
            // 
            // cmdSaveToFile
            // 
            this.cmdSaveToFile.DialogResult = System.Windows.Forms.DialogResult.Ignore;
            this.cmdSaveToFile.Location = new System.Drawing.Point(196, 3);
            this.cmdSaveToFile.Name = "cmdSaveToFile";
            this.cmdSaveToFile.Size = new System.Drawing.Size(75, 23);
            this.cmdSaveToFile.TabIndex = 3;
            this.cmdSaveToFile.Text = "&Save";
            this.cmdSaveToFile.UseVisualStyleBackColor = true;
            this.cmdSaveToFile.Click += new System.EventHandler(this.cmdSaveToFile_Click);
            // 
            // lblCustomMessage
            // 
            this.lblCustomMessage.AutoSize = true;
            this.lblCustomMessage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblCustomMessage.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCustomMessage.Location = new System.Drawing.Point(3, 0);
            this.lblCustomMessage.Name = "lblCustomMessage";
            this.lblCustomMessage.Size = new System.Drawing.Size(436, 30);
            this.lblCustomMessage.TabIndex = 1;
            this.lblCustomMessage.Text = "CustomMessage goes here";
            this.lblCustomMessage.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // txtExceptionDetail
            // 
            this.txtExceptionDetail.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtExceptionDetail.Font = new System.Drawing.Font("Lucida Console", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtExceptionDetail.Location = new System.Drawing.Point(3, 33);
            this.txtExceptionDetail.Multiline = true;
            this.txtExceptionDetail.Name = "txtExceptionDetail";
            this.txtExceptionDetail.Size = new System.Drawing.Size(436, 145);
            this.txtExceptionDetail.TabIndex = 2;
            this.txtExceptionDetail.Text = "Exception details goes here";
            // 
            // cmdTerminateApp
            // 
            this.cmdTerminateApp.DialogResult = System.Windows.Forms.DialogResult.Abort;
            this.cmdTerminateApp.Location = new System.Drawing.Point(115, 3);
            this.cmdTerminateApp.Name = "cmdTerminateApp";
            this.cmdTerminateApp.Size = new System.Drawing.Size(75, 23);
            this.cmdTerminateApp.TabIndex = 4;
            this.cmdTerminateApp.Text = "&Terminate";
            this.cmdTerminateApp.UseVisualStyleBackColor = true;
            this.cmdTerminateApp.Click += new System.EventHandler(this.cmdTerminateApp_Click);
            // 
            // frmException
            // 
            this.AcceptButton = this.cmdAccept;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cmdCopy;
            this.ClientSize = new System.Drawing.Size(442, 217);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmException";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "T3000 CrossPlatform Exception Handling";
            this.TopMost = true;
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Button cmdAccept;
        private System.Windows.Forms.Button cmdCopy;
        private System.Windows.Forms.Label lblCustomMessage;
        private System.Windows.Forms.TextBox txtExceptionDetail;
        private System.Windows.Forms.Button cmdSaveToFile;
        private System.Windows.Forms.Button cmdTerminateApp;
    }
}