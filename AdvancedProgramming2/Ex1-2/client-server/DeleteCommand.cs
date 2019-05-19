using System;
using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// Class DeleteCommand.
    /// </summary>
    /// <seealso cref="client_server.ICommand" />
    internal class DeleteCommand : ICommand
    {
        /// <summary>
        /// The model
        /// </summary>
        private IModel model;

        /// <summary>
        /// Initializes a new instance of the <see cref="DeleteCommand"/> class.
        /// </summary>
        /// <param name="model">The model.</param>
        public DeleteCommand(IModel model)
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
            string name = args[0];
            this.model.Delete(name, client);
            return "deleted";
        }
    }
}