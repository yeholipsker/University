using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace client_server
{
    class ClientHandler1 : IClientHandler
    {
        private Controller controller;

        public ClientHandler1()
        {
            this.controller = new Controller();
        }

        public void HandleClient(TcpClient client)
        {
            Task task = new Task(() =>
            {
                NetworkStream stream = client.GetStream();
                BinaryReader reader = new BinaryReader(stream);
                BinaryWriter writer = new BinaryWriter(stream);
                while (true)
                {
                    string commandLine = reader.ReadString();
                    string result = controller.ExecuteCommand(commandLine, client);
                    if(commandLine.Contains("generate") || commandLine.Contains("solve") || 
                        commandLine.Contains("list"))
                    {
                        writer.Write(result);
                        break;
                    }
                    if(commandLine.Contains("join"))
                    {
                        writer.Write(result);
                    }
                    if (result == "close")
                    {
                        break;
                    }
                }
                client.Close();
            });
            task.Start();
        }
    }
}
