using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO.Ports;

namespace Test1___SD24_Serial
{
    public partial class MainForm : Form
    {
        SerialSettings _serialDialog;
        SerialPort _com;
        Dictionary<char, Label> adclabels;
        public MainForm()
        {
            InitializeComponent();
            _com = new SerialPort();
            _com.BaudRate = 115200;
            _com.Parity = Parity.None;
            _com.DataBits = 8;
            _com.StopBits = StopBits.One;
            _com.NewLine = "\r\n";
            _serialDialog = new SerialSettings(this._com,this);
            adclabels = new Dictionary<char, Label>();
            adclabels.Add('a', this.lblValA);
            adclabels.Add('b', this.lblValB);
            adclabels.Add('c', this.lblValC);
            adclabels.Add('d', this.lblValD);
            
        }
        private void SetADCText(string serialStr)
        {
            Int32 adc_value;
            if (serialStr.Length == 7)
            {
                adc_value = Convert.ToInt32(serialStr.Substring(1), 16);
                adc_value <<= 8;
                adc_value /= 256;
                adclabels[serialStr.ToCharArray()[0]].Text = adc_value.ToString();
            }
        }

        private void settingsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _serialDialog.ShowDialog();
        }
        public void SerialWorker()
        {
            string serialStr;
            while(true)
            {
                serialStr = this._com.ReadLine();
                if (serialStr.Length == 7)
                {
                    adclabels[serialStr.ToCharArray()[0]].Invoke(new SetADCTextCallBack(this.SetADCText), new object[] { serialStr });
                }
            }
        }
        delegate void SetADCTextCallBack(string serialStr);
    }
}
