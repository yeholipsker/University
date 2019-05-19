using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace client_server
{
    /// <summary>
    /// Class ClientHandler.
    /// handles the client side
    /// </summary>
    /// <seealso cref="client_server.IClientHandler" />
    class ClientHandler : IClientHandler
    {
        /// <summary>
        /// members
        /// </summary>
        private Controller controller;
        private bool multiplayerMode;

        /// <summary>
        /// constructor
        /// Initializes the members of the class
        /// </summary>
        public ClientHandler()
        {
            this.controller = new Controller();
            this.multiplayerMode = false;
        }
        /// <summary>
        /// Handles the client.
        /// </summary>
        /// <param name="client">The client.</param>
        public void HandleClient(TcpClient client)
        {
            Console.WriteLine("started the server");
            Task task = new Task(() =>
            {
                NetworkStream stream = client.GetStream();
                BinaryReader reader = new BinaryReader(stream);
                BinaryWriter writer = new BinaryWriter(stream);
                while (true)
                {
                    try {
                        string commandLine = reader.ReadString();

                        Console.WriteLine("Got command: {0}", commandLine);
                        string result = controller.ExecuteCommand(commandLine, client);
                        if (result.Contains("close") || result.Contains("deleted"))
                        {
                            break;
                        }
                        Console.WriteLine(result);
                        writer.Write(result);
                        writer.Flush();
                    }
                    catch
                    {
                        this.controller.ExecuteCommand("close",client);
                    }
                }
            });
            task.Start();
        }

        /// <summary>
        ///if the client chooses single player mode
        /// </summary>
        private void SinglePlayerMode()
        {
            this.multiplayerMode = false;
        }

        /// <summary>
        ///if the client chooses multiplayer mode
        /// </summary>
        private void MultiPlayerMode()
        {
            this.multiplayerMode = true;
        }
    }
}
