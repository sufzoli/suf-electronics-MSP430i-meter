using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Threading;
using System.IO.Ports;

namespace Test1___SD24_Serial
{
    public partial class SerialSettings : Form
    {
        SerialPort _com;
        MainForm _form;
        Thread _serialThread;
        private Dictionary<int, string> PortList;
        public SerialSettings(SerialPort com, MainForm form)
        {
            InitializeComponent();
            this._com = com;
            this._form = form;
            this._serialThread = new Thread(new ThreadStart(_form.SerialWorker));
        }

        private void SerialSettings_Load(object sender, EventArgs e)
        {
            int ItemID;
            this.PortList = new Dictionary<int, string>();
            SerialPortBox.Items.Clear();
            foreach (COMPortInfo comPort in COMPortInfo.GetCOMPortsInfo())
            {
                ItemID = SerialPortBox.Items.Add(comPort.Description);
                this.PortList.Add(ItemID, comPort.Name);
            }
            if(this._com.IsOpen)
            {
                if(this.PortList.Values.Contains(this._com.PortName))
                {
                    SerialPortBox.SelectedIndex = this.PortList.First(x => x.Value == this._com.PortName).Key;
                    SerialPortBox.Enabled = false;
                }
                else
                {
                    this._com.Close();  // The serial port doesn't exists anymore so close it
                    this._serialThread.Abort();
                }
            }
            btnConnect.Text = this._com.IsOpen ? "Disconnect" : "Connect";
            btnConnect.Enabled = this._com.IsOpen || SerialPortBox.SelectedIndex != -1;
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (_com.IsOpen)
            {
                _com.Close();
                this._serialThread.Abort();
            }
            else
            {
                _com.PortName = PortList[SerialPortBox.SelectedIndex];
                _com.Open();
                this._serialThread.Start();
            }
            btnConnect.Text = this._com.IsOpen ? "Disconnect" : "Connect";
            SerialPortBox.Enabled = !this._com.IsOpen;
        }

        private void SerialPortBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            btnConnect.Enabled = this._com.IsOpen || SerialPortBox.SelectedIndex != -1;
        }
    }
}
