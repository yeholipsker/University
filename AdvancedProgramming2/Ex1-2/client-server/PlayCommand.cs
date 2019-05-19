using System;
using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// Class PlayCommand.
    /// holds the commands for playing the game
    /// </summary>
    /// <seealso cref="client_server.ICommand" />
    class PlayCommand : ICommand
    {
        /// <summary>
        /// members
        /// </summary>
        private IModel model;

        /// <summary>
        /// constructor
        /// Initializes the member of the class.
        /// </summary>
        /// <param name="model">The model.</param>
        public PlayCommand(IModel model)
        {
            this.model = model;
        }
        /// <summary>
        /// Executes the specified arguments.
        /// </summary>
        /// <param name="args">The commands.</param>
        /// <param name="client">The client.</param>
        /// <returns>a string saying "played"</returns>
        public string Execute(string[] args, TcpClient client = null)
        {
            string direction = args[0];
            this.model.PlayMove(direction, client);
            return "played";
        }
    }
}