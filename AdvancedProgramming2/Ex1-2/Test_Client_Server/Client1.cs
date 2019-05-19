using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Test_Client_Server
{
    class Client1
    {
        public void RunClient()
        {
            while (true)
            {
                IPEndPoint ep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 4567);
                TcpClient client = new TcpClient();
                client.Connect(ep);
                NetworkStream stream = client.GetStream();
                BinaryReader reader = new BinaryReader(stream);
                BinaryWriter writer = new BinaryWriter(stream);
                Console.WriteLine("Please enter a command: ");
                string command = Console.ReadLine();
                writer.Write(command);
                string result = reader.ReadString();
                Console.WriteLine("got message back from the server:");
                Console.WriteLine(result);
                if (command.Contains("start") || command.Contains("join"))
                {
                    while (true)
                    {
                        Task writeTask = new Task(() =>
                        {
                            while (true)
                            {
                                Console.WriteLine("Please enter a command: ");
                                string sndMsg = Console.ReadLine();
                                writer.Write(sndMsg);
                                if (sndMsg.Contains("close"))
                                {
                                    break;
                                }
                            }
                        });
                        writeTask.Start();
                        while (true)
                        {
                            Console.WriteLine("Message accepted: ");
                            string acceptedMessage = reader.ReadString();
                            Console.WriteLine(acceptedMessage);
                            if (acceptedMessage == "close")
                            {
                                break;
                            }
                        }
                        client.Close();
                    }
                }
            }
        }
    }
}
