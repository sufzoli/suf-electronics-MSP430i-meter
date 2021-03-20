namespace Test1___SD24_Serial
{
    partial class SerialSettings
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
            this.SerialPortBox = new System.Windows.Forms.ComboBox();
            this.btnConnect = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // SerialPortBox
            // 
            this.SerialPortBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.SerialPortBox.FormattingEnabled = true;
            this.SerialPortBox.Location = new System.Drawing.Point(12, 12);
            this.SerialPortBox.Name = "SerialPortBox";
            this.SerialPortBox.Size = new System.Drawing.Size(570, 24);
            this.SerialPortBox.TabIndex = 0;
            this.SerialPortBox.SelectedIndexChanged += new System.EventHandler(this.SerialPortBox_SelectedIndexChanged);
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(12, 52);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(153, 30);
            this.btnConnect.TabIndex = 1;
            this.btnConnect.Text = "button1";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // SerialSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(593, 99);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.SerialPortBox);
            this.Name = "SerialSettings";
            this.Text = "SerialSettings";
            this.Load += new System.EventHandler(this.SerialSettings_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox SerialPortBox;
        private System.Windows.Forms.Button btnConnect;
    }
}