using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client_server
{
    /// <summary>
    /// Class Program.
    /// the main program.
    /// </summary>
    class Program
    {
        /// <summary>
        /// Defines the entry point of the application.
        /// </summary>
        /// <param name="args">The arguments.</param>
        static void Main(string[] args)
        {
            ClientHandler ch = new ClientHandler();
            Server server = new Server(8000, ch);
            server.Start();
            Console.ReadKey();
            server.Stop();
        }
    }
}
