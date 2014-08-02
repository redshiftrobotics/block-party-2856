using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace NXT_Interface
{
    public partial class GUI : Form
    {
        public GUI()
        {
            InitializeComponent();

            Bluetooth.Connect(6);

            MouseClick += new MouseEventHandler(Mouse_Click);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Title.Text = "Connected on COM" + Bluetooth.BluetoothConnection.PortName.ToString();
        }

        private void SendButton_Click(object sender, EventArgs e)
        {
            Console.WriteLine("Click");
            Bluetooth.WriteBytes(Convert.ToInt16(SendField1.Text), Convert.ToInt16(SendField2.Text), Convert.ToInt16(SendField3.Text));
        }

        private void Mouse_Click(object sender, EventArgs e)
        {
            //MousePosition.
        }
    }
}
