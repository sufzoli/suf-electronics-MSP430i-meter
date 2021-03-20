namespace Test1___SD24_Serial
{
    partial class MainForm
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.settingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lblValA = new System.Windows.Forms.Label();
            this.lblValB = new System.Windows.Forms.Label();
            this.lblValC = new System.Windows.Forms.Label();
            this.lblValD = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.settingsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(270, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // settingsToolStripMenuItem
            // 
            this.settingsToolStripMenuItem.Name = "settingsToolStripMenuItem";
            this.settingsToolStripMenuItem.Size = new System.Drawing.Size(74, 24);
            this.settingsToolStripMenuItem.Text = "&Settings";
            this.settingsToolStripMenuItem.Click += new System.EventHandler(this.settingsToolStripMenuItem_Click);
            // 
            // lblValA
            // 
            this.lblValA.Font = new System.Drawing.Font("Courier New", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lblValA.Location = new System.Drawing.Point(12, 43);
            this.lblValA.Name = "lblValA";
            this.lblValA.Size = new System.Drawing.Size(236, 46);
            this.lblValA.TabIndex = 1;
            this.lblValA.Text = "-00000000";
            this.lblValA.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblValB
            // 
            this.lblValB.Font = new System.Drawing.Font("Courier New", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lblValB.Location = new System.Drawing.Point(12, 89);
            this.lblValB.Name = "lblValB";
            this.lblValB.Size = new System.Drawing.Size(236, 46);
            this.lblValB.TabIndex = 2;
            this.lblValB.Text = "-00000000";
            this.lblValB.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblValC
            // 
            this.lblValC.Font = new System.Drawing.Font("Courier New", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lblValC.Location = new System.Drawing.Point(12, 135);
            this.lblValC.Name = "lblValC";
            this.lblValC.Size = new System.Drawing.Size(236, 46);
            this.lblValC.TabIndex = 3;
            this.lblValC.Text = "-00000000";
            this.lblValC.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblValD
            // 
            this.lblValD.Font = new System.Drawing.Font("Courier New", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lblValD.Location = new System.Drawing.Point(12, 181);
            this.lblValD.Name = "lblValD";
            this.lblValD.Size = new System.Drawing.Size(236, 46);
            this.lblValD.TabIndex = 4;
            this.lblValD.Text = "-00000000";
            this.lblValD.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(270, 246);
            this.Controls.Add(this.lblValD);
            this.Controls.Add(this.lblValC);
            this.Controls.Add(this.lblValB);
            this.Controls.Add(this.lblValA);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem settingsToolStripMenuItem;
        private System.Windows.Forms.Label lblValA;
        private System.Windows.Forms.Label lblValB;
        private System.Windows.Forms.Label lblValC;
        private System.Windows.Forms.Label lblValD;
    }
}

