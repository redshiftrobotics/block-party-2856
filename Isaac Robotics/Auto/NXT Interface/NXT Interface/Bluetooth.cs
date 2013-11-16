using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NXT_Interface
{
    static class Bluetooth
    {
        static SerialPort BluetoothConnection = new SerialPort();

        static public void WriteBytes(short A, short B, short C)
        {
            //declare command
            byte[] Command = { 0x00, 0x09, 0x00, 0x06, (byte)A, (byte)(A >> 8), (byte)B, (byte)(B >> 8), (byte)C, (byte)(C >> 8) };

            // Declare a 2 bytes vector to store the message length header 
            Byte[] MessageLength = { 0x00, 0x00 };

            //set the LSB to the length of the message 
            MessageLength[0] = (byte)Command.Length;

            //send the 2 bytes header 
            BluetoothConnection.Write(MessageLength, 0, MessageLength.Length);

            // send the message itself 
            BluetoothConnection.Write(Command, 0, Command.Length);
        }

        static public void Connect(int ComPort)
        {
            BluetoothConnection.PortName = "COM" + ComPort.ToString();
            // Replace this COM port by the appropriate one on your computer

            BluetoothConnection.ReadTimeout = 1500;

            BluetoothConnection.Open();
        }

        static public void Disconnect()
        {
            BluetoothConnection.Close();
        }
    }
}
