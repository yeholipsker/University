using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// Interface IClientHandler
    /// interface with basics for client handler type classes  
    /// </summary>
    public interface IClientHandler
    {
        void HandleClient(TcpClient client);
    }
}
