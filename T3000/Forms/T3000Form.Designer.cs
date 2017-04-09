namespace T3000.Forms
{
    partial class T3000Form
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(T3000Form));
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadPRGToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.savePRGToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.upgradeMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.controlMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.inputsMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.outputsMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.variablesMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.programsMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.controllersMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.screensMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.schedulesMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.holidaysMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.languageMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.englishToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.germanToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.chineseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.statusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.buttonsToolStrip = new System.Windows.Forms.ToolStrip();
            this.inputsButton = new System.Windows.Forms.ToolStripButton();
            this.outputsButton = new System.Windows.Forms.ToolStripButton();
            this.variablesButton = new System.Windows.Forms.ToolStripButton();
            this.programsButton = new System.Windows.Forms.ToolStripButton();
            this.controllersButton = new System.Windows.Forms.ToolStripButton();
            this.screensButton = new System.Windows.Forms.ToolStripButton();
            this.schedulesButton = new System.Windows.Forms.ToolStripButton();
            this.holidaysButton = new System.Windows.Forms.ToolStripButton();
            this.menuStrip.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.buttonsToolStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip
            // 
            this.menuStrip.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.controlMenuItem,
            this.languageMenuItem});
            resources.ApplyResources(this.menuStrip, "menuStrip");
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.RenderMode = System.Windows.Forms.ToolStripRenderMode.System;
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadPRGToolStripMenuItem,
            this.savePRGToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.upgradeMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            resources.ApplyResources(this.fileToolStripMenuItem, "fileToolStripMenuItem");
            // 
            // loadPRGToolStripMenuItem
            // 
            this.loadPRGToolStripMenuItem.Name = "loadPRGToolStripMenuItem";
            resources.ApplyResources(this.loadPRGToolStripMenuItem, "loadPRGToolStripMenuItem");
            this.loadPRGToolStripMenuItem.Click += new System.EventHandler(this.LoadPrg);
            // 
            // savePRGToolStripMenuItem
            // 
            resources.ApplyResources(this.savePRGToolStripMenuItem, "savePRGToolStripMenuItem");
            this.savePRGToolStripMenuItem.Name = "savePRGToolStripMenuItem";
            this.savePRGToolStripMenuItem.Click += new System.EventHandler(this.SavePrg);
            // 
            // saveAsToolStripMenuItem
            // 
            resources.ApplyResources(this.saveAsToolStripMenuItem, "saveAsToolStripMenuItem");
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.SaveAsPrg);
            // 
            // upgradeMenuItem
            // 
            resources.ApplyResources(this.upgradeMenuItem, "upgradeMenuItem");
            this.upgradeMenuItem.Name = "upgradeMenuItem";
            this.upgradeMenuItem.Click += new System.EventHandler(this.Upgrade);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            resources.ApplyResources(this.exitToolStripMenuItem, "exitToolStripMenuItem");
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.Exit);
            // 
            // controlMenuItem
            // 
            this.controlMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.inputsMenuItem,
            this.outputsMenuItem,
            this.variablesMenuItem,
            this.programsMenuItem,
            this.controllersMenuItem,
            this.screensMenuItem,
            this.schedulesMenuItem,
            this.holidaysMenuItem});
            this.controlMenuItem.Name = "controlMenuItem";
            resources.ApplyResources(this.controlMenuItem, "controlMenuItem");
            // 
            // inputsMenuItem
            // 
            resources.ApplyResources(this.inputsMenuItem, "inputsMenuItem");
            this.inputsMenuItem.Name = "inputsMenuItem";
            this.inputsMenuItem.Click += new System.EventHandler(this.ShowInputs);
            // 
            // outputsMenuItem
            // 
            resources.ApplyResources(this.outputsMenuItem, "outputsMenuItem");
            this.outputsMenuItem.Name = "outputsMenuItem";
            this.outputsMenuItem.Click += new System.EventHandler(this.ShowOutputs);
            // 
            // variablesMenuItem
            // 
            resources.ApplyResources(this.variablesMenuItem, "variablesMenuItem");
            this.variablesMenuItem.Name = "variablesMenuItem";
            this.variablesMenuItem.Click += new System.EventHandler(this.ShowVariables);
            // 
            // programsMenuItem
            // 
            resources.ApplyResources(this.programsMenuItem, "programsMenuItem");
            this.programsMenuItem.Name = "programsMenuItem";
            this.programsMenuItem.Click += new System.EventHandler(this.ShowPrograms);
            // 
            // controllersMenuItem
            // 
            resources.ApplyResources(this.controllersMenuItem, "controllersMenuItem");
            this.controllersMenuItem.Name = "controllersMenuItem";
            this.controllersMenuItem.Click += new System.EventHandler(this.ShowControllers);
            // 
            // screensMenuItem
            // 
            resources.ApplyResources(this.screensMenuItem, "screensMenuItem");
            this.screensMenuItem.Name = "screensMenuItem";
            this.screensMenuItem.Click += new System.EventHandler(this.ShowScreens);
            // 
            // schedulesMenuItem
            // 
            resources.ApplyResources(this.schedulesMenuItem, "schedulesMenuItem");
            this.schedulesMenuItem.Name = "schedulesMenuItem";
            this.schedulesMenuItem.Click += new System.EventHandler(this.ShowSchedules);
            // 
            // holidaysMenuItem
            // 
            resources.ApplyResources(this.holidaysMenuItem, "holidaysMenuItem");
            this.holidaysMenuItem.Name = "holidaysMenuItem";
            this.holidaysMenuItem.Click += new System.EventHandler(this.ShowHolidays);
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
            this.englishToolStripMenuItem.Click += new System.EventHandler(this.SelectEnglish);
            // 
            // germanToolStripMenuItem
            // 
            this.germanToolStripMenuItem.Name = "germanToolStripMenuItem";
            resources.ApplyResources(this.germanToolStripMenuItem, "germanToolStripMenuItem");
            this.germanToolStripMenuItem.Click += new System.EventHandler(this.SelectGerman);
            // 
            // chineseToolStripMenuItem
            // 
            this.chineseToolStripMenuItem.Name = "chineseToolStripMenuItem";
            resources.ApplyResources(this.chineseToolStripMenuItem, "chineseToolStripMenuItem");
            this.chineseToolStripMenuItem.Click += new System.EventHandler(this.SelectChinese);
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
            // buttonsToolStrip
            // 
            this.buttonsToolStrip.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.buttonsToolStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.inputsButton,
            this.outputsButton,
            this.variablesButton,
            this.programsButton,
            this.controllersButton,
            this.screensButton,
            this.schedulesButton,
            this.holidaysButton});
            resources.ApplyResources(this.buttonsToolStrip, "buttonsToolStrip");
            this.buttonsToolStrip.Name = "buttonsToolStrip";
            // 
            // inputsButton
            // 
            this.inputsButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            resources.ApplyResources(this.inputsButton, "inputsButton");
            this.inputsButton.Name = "inputsButton";
            this.inputsButton.Click += new System.EventHandler(this.ShowInputs);
            // 
            // outputsButton
            // 
            this.outputsButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            resources.ApplyResources(this.outputsButton, "outputsButton");
            this.outputsButton.Name = "outputsButton";
            this.outputsButton.Click += new System.EventHandler(this.ShowOutputs);
            // 
            // variablesButton
            // 
            this.variablesButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            resources.ApplyResources(this.variablesButton, "variablesButton");
            this.variablesButton.Name = "variablesButton";
            this.variablesButton.Click += new System.EventHandler(this.ShowVariables);
            // 
            // programsButton
            // 
            this.programsButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            resources.ApplyResources(this.programsButton, "programsButton");
            this.programsButton.Name = "programsButton";
            this.programsButton.Click += new System.EventHandler(this.ShowPrograms);
            // 
            // controllersButton
            // 
            this.controllersButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            resources.ApplyResources(this.controllersButton, "controllersButton");
            this.controllersButton.Name = "controllersButton";
            this.controllersButton.Click += new System.EventHandler(this.ShowControllers);
            // 
            // screensButton
            // 
            this.screensButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            resources.ApplyResources(this.screensButton, "screensButton");
            this.screensButton.Name = "screensButton";
            this.screensButton.Click += new System.EventHandler(this.ShowScreens);
            // 
            // schedulesButton
            // 
            this.schedulesButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            resources.ApplyResources(this.schedulesButton, "schedulesButton");
            this.schedulesButton.Name = "schedulesButton";
            this.schedulesButton.Click += new System.EventHandler(this.ShowSchedules);
            // 
            // holidaysButton
            // 
            this.holidaysButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            resources.ApplyResources(this.holidaysButton, "holidaysButton");
            this.holidaysButton.Name = "holidaysButton";
            this.holidaysButton.Click += new System.EventHandler(this.ShowHolidays);
            // 
            // T3000Form
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.buttonsToolStrip);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.menuStrip);
            this.MainMenuStrip = this.menuStrip;
            this.Name = "T3000Form";
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.buttonsToolStrip.ResumeLayout(false);
            this.buttonsToolStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadPRGToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem savePRGToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem controlMenuItem;
        private System.Windows.Forms.ToolStripMenuItem variablesMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel statusLabel;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem languageMenuItem;
        private System.Windows.Forms.ToolStripMenuItem englishToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem germanToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem chineseToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem inputsMenuItem;
        private System.Windows.Forms.ToolStripMenuItem outputsMenuItem;
        private System.Windows.Forms.ToolStripMenuItem screensMenuItem;
        private System.Windows.Forms.ToolStrip buttonsToolStrip;
        private System.Windows.Forms.ToolStripButton variablesButton;
        private System.Windows.Forms.ToolStripMenuItem upgradeMenuItem;
        private System.Windows.Forms.ToolStripMenuItem programsMenuItem;
        private System.Windows.Forms.ToolStripMenuItem controllersMenuItem;
        private System.Windows.Forms.ToolStripMenuItem holidaysMenuItem;
        private System.Windows.Forms.ToolStripMenuItem schedulesMenuItem;
        private System.Windows.Forms.ToolStripButton inputsButton;
        private System.Windows.Forms.ToolStripButton outputsButton;
        private System.Windows.Forms.ToolStripButton programsButton;
        private System.Windows.Forms.ToolStripButton controllersButton;
        private System.Windows.Forms.ToolStripButton screensButton;
        private System.Windows.Forms.ToolStripButton schedulesButton;
        private System.Windows.Forms.ToolStripButton holidaysButton;
    }
}