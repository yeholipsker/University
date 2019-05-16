using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Windows;
using System.Windows.Controls;
using Newtonsoft.Json.Linq;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        // Consts
        public const int LOCAL_PORT = 4444;
        public const int BINDING_PORT = 8000;

        /* Data members - all of the members are double:
         * Every type of data have two instances - one for communication with localhost
         * and one for the communication with the receiver.
         */
        IPEndPoint endPointStreamer, endPointReceiver;
        TcpClient clientStreamer, clientReceiver;
        NetworkStream stream, stream2;
        BinaryReader readerStreamer, readerReceiver;
        BinaryWriter writerStreamer, writerReceiver;

        private void IP_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        // Set the window up.
        public MainWindow()
        {
            InitializeComponent();
        }

        // Connect click
        private void Connect_Click(object sender, RoutedEventArgs e)
        {
            // Connect to the receiver.
            endPointReceiver = new IPEndPoint(IPAddress.Parse(IP.Text.ToString()), BINDING_PORT);
            clientReceiver = new TcpClient();
            try
            {
                clientReceiver.Connect(endPointReceiver);
            }
            catch (Exception)
            {
                MessageBox.Show("Remote server is not running - Please try again later");
                return;
            }
            stream2 = clientReceiver.GetStream();
            stream2.ReadTimeout = 5000;
            readerReceiver = new BinaryReader(stream2);
            writerReceiver = new BinaryWriter(stream2);

            // Connect to the stream server.
            endPointStreamer = new IPEndPoint(IPAddress.Parse("127.0.0.1"), LOCAL_PORT);
            clientStreamer = new TcpClient();
            try
            {
                clientStreamer.Connect(endPointStreamer);
            } catch(Exception)
            {
                MessageBox.Show("Local server is not running - Please start server");
                return;
            }
            stream = clientStreamer.GetStream();
            stream.ReadTimeout = 5000;
            readerStreamer = new BinaryReader(stream);
            writerStreamer = new BinaryWriter(stream);

            // Make the actions available.
            Start.IsEnabled = true;
            Stop.IsEnabled = true;
            Check.IsEnabled = true;
        }

        // Create a JSON representation of the action.
        private JObject ActionToJson(String ip, int port, String action)
        {
            // Build the JSON action to return.
            JObject jsonAction = new JObject();
            jsonAction["IP"] = ip;
            jsonAction["Port"] = port;
            jsonAction["Action"] = action;

            Console.WriteLine(jsonAction);

            return jsonAction;
        }

        // Get the IP of localhost.
        private String GetLocalIPAddress()
        {
            String ipAddr = "";
            var host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (var ip in host.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    ipAddr = ip.ToString();
                }
            }
            return ipAddr;
        }

        // Action to send the server click.
        private void Action_Click(object sender, RoutedEventArgs e)
        {
            string content = (sender as Button).Content.ToString();

            // Build the JSON action to send.
            JObject jsonAction = ActionToJson(IP.Text.ToString(), Convert.ToInt32(Port.Text.ToString()), content);

            try
            {
                writerStreamer.Write(jsonAction.ToString().ToCharArray());
            } catch(IOException)
            {
                MessageBox.Show("No connection with Server");
            }

            // "Check" command - Do a connection check.
            if(content == "Check")
            {
                // Try to read the data and print a message about the connection.
                byte[] buffer = new byte[clientStreamer.ReceiveBufferSize];
                int bytesRead;
                try
                {
                    bytesRead = stream.Read(buffer, 0, clientStreamer.ReceiveBufferSize);
                    MessageBox.Show("You have connection with server");
                }
                catch (IOException)
                {
                    MessageBox.Show("Connection timeout");
                }
            }

            // "Start" command - Sent the IP address & port to the receiver.
            if (content == "Start")
            {
                try
                {
                    JObject jsonActionToReceiver = ActionToJson(GetLocalIPAddress(), Convert.ToInt32(Port.Text.ToString()), content);
                    writerReceiver.Write(jsonActionToReceiver.ToString());
                }
                catch (IOException)
                {
                    MessageBox.Show("No connection with remote client");
                }
            }
        }
    }
}