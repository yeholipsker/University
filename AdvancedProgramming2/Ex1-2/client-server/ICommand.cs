using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace client_server
{
    /// <summary>
    /// interface with basics for commands type classes
    /// </summary>
    interface ICommand
    {
        /// <summary>
        /// Executes the specified arguments.
        /// </summary>
        /// <param name="args">The arguments.</param>
        /// <param name="client">The client.</param>
        /// <returns>System.String.</returns>
        string Execute(string[] args, TcpClient client = null);
    }
}
