using System;
using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// closes the connection 
    /// </summary>
    class CloseCommand : ICommand
    {
        /// <summary>
        /// members
        /// </summary>
        private IModel model;

        /// <summary>
        /// constructor
        /// </summary>
        /// <param name="model">
        /// the model of the command
        /// </param>
        public CloseCommand(IModel model)
        {
            this.model = model;
        }

        /// <summary>
        /// method for closing the connection
        /// </summary>
        /// <param name="args">
        /// name of client </param>
        /// <param name="client">the tcp client which we need to close</param>
        /// <returns> a message saying closed</returns>
        public string Execute(string[] args, TcpClient client = null)
        {
            string name = args[0];
            this.model.Close(name, client);
            return "close";
        }
    }
}