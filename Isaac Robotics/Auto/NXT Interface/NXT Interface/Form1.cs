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
    public partial class Form1 : Form
    {
        short RightMotorPower;
        short LeftMotorPower;

        public Form1()
        {
            RightMotorPower = 0;
            LeftMotorPower = 0;

            InitializeComponent();

            Bluetooth.Connect(5);

            KeyDown += new KeyEventHandler(KeyPressed);
        }

        void KeyPressed(object sender, KeyEventArgs e)
        {
            //Up Key Pressed
            if (e.KeyCode == Keys.Up)
            {
                RightMotorPower = -30;
                LeftMotorPower = -30;
            }

            //Down Key Pressed
            if (e.KeyCode == Keys.Down)
            {
                RightMotorPower = 30;
                LeftMotorPower = 30;
            }

            //Left Key Pressed
            if (e.KeyCode == Keys.Left)
            {
                RightMotorPower = -10;
                LeftMotorPower = 10;
            }

            //Right Key Pressed
            if (e.KeyCode == Keys.Right)
            {
                RightMotorPower = 10;
                LeftMotorPower = -10;
            }

            Console.WriteLine(LeftMotorPower.ToString() + ", " + RightMotorPower.ToString());

            Bluetooth.WriteBytes(LeftMotorPower, RightMotorPower, 0);
        }
    }
}
