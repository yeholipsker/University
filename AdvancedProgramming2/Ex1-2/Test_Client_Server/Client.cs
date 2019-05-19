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
    class Client
    {
        private bool multiPlayer;

        public Client()
        {
            this.multiPlayer = false;
        }

        public void RunClient()
        {
            while (true)
            {
                IPEndPoint ep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 4567);
                TcpClient client = new TcpClient();
                client.Connect(ep);
                Console.WriteLine("You are connected");
                NetworkStream stream = client.GetStream();
                BinaryReader reader = new BinaryReader(stream);
                BinaryWriter writer = new BinaryWriter(stream);
                string acceptedMessage = "";
                string sndMsg = "";

                Console.WriteLine("enter command");
                string command = Console.ReadLine();
                writer.Write(command);
                writer.Flush();
                string result = reader.ReadString();
                Console.WriteLine("got message back from the server");
                Console.WriteLine(result);
                if (command.Contains("start") || command.Contains("join"))
                {
                    this.MultiPlayerMode();
                    Task writeTask = new Task(() =>
                    {
                        while (this.multiPlayer)
                        {
                            Console.WriteLine("Please enter a command: ");
                            sndMsg = Console.ReadLine();
                            writer.Write(sndMsg);
                            writer.Flush();
                            Console.WriteLine("command was sent");
                            if (sndMsg.Contains("generate") || sndMsg.Contains("solve"))
                            {
                                this.SinglePlayerMode();
                            }
                            if (sndMsg.Contains("close"))
                            {
                                this.SinglePlayerMode();
                            }
                        }
                    });
                    writeTask.Start();
                    while (this.multiPlayer)
                    {
                        acceptedMessage = reader.ReadString();
                        Console.Write("Message accepted: ");
                        Console.WriteLine(acceptedMessage);
                        if (acceptedMessage == "close")
                        {
                            this.SinglePlayerMode();
                            writer.Dispose();
                        }
                    }
                }
                reader.Dispose();
                stream.Dispose();
                client.Close();
            }
        }

        private void SinglePlayerMode()
        {
            this.multiPlayer = false;
        }

        private void MultiPlayerMode()
        {
            this.multiPlayer = true;
        }
    }
}
