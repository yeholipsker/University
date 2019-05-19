using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// Class Server.
    /// handles server side
    /// </summary>
    class Server
    {

        /// <summary>
        /// members
        /// </summary>
        private int port;
        private TcpListener listener;
        private IClientHandler ch;

        /// <summary>
        /// constructor
        /// Initializes the members class.
        /// </summary>
        /// <param name="port">The port.</param>
        /// <param name="ch">The ch.</param>
        public Server(int port, IClientHandler ch)
        {
            this.port = port;
            this.ch = ch;
        }

        /// <summary>
        /// opens the server side
        /// </summary>
        public void Start()
        {
            IPEndPoint ep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), port);
            listener = new TcpListener(ep);
            listener.Start();
            Console.WriteLine("Waiting for connections...");
            Task task = new Task(() => {
                while (true)
                {
                    try
                    {
                        TcpClient client = listener.AcceptTcpClient();
                        Console.WriteLine("Got new connection");
                        ch.HandleClient(client);
                    }
                    catch (SocketException)
                    {
                        break;
                    }
                }
            });
            task.Start();
        }

        /// <summary>
        /// stops listening for clients.
        /// </summary>
        public void Stop()
        {
            listener.Stop();
        }
    }
}
