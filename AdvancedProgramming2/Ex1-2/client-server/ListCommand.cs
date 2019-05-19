using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// Class ListCommand.
    /// a class which holds a model with the command list suitable for this model
    /// </summary>
    /// <seealso cref="client_server.ICommand" />
    internal class ListCommand : ICommand
    {
        /// <summary>
        /// member
        /// </summary>
        private IModel model;

        /// <summary>
        /// constructor
        /// Initializes a new instance of model
        /// </summary>
        /// <param name="model">The model.</param>
        public ListCommand(IModel model)
        {
            this.model = model;
        }

        /// <summary>
        /// Executes the specified arguments.
        /// </summary>
        /// <param name="args">The arguments.</param>
        /// <param name="client">The client.</param>
        /// <returns>System.String.</returns>
        public string Execute(string[] args, TcpClient client = null)
        { 
            return new JArray(this.model.ShowList()).ToString();
        }
    }
}