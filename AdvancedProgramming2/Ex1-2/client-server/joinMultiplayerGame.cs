using MazeLib;
using System;
using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// Class joinMultiplayerGame. with the commands needed to join a multiplayer game
    /// inherits from ICommand
    /// </summary>
    /// <seealso cref="client_server.ICommand" />
    class joinMultiplayerGame : ICommand
    {
        /// <summary>
        /// member
        /// </summary>
        private IModel model;

        /// <summary>
        /// constructor
        /// Initializes a new model
        /// </summary>
        /// <param name="model">The model.</param>
        public joinMultiplayerGame(IModel model)
        {
            this.model = model;
        }

        /// <summary>
        /// Executes the specified arguments.
        /// which game to add the client to 
        /// </summary>
        /// <param name="args">The game to join</param>
        /// <param name="client">The client.</param>
        /// <returns>a maze from specified game.</returns>
        public string Execute(string[] args, TcpClient client = null)
        {
            string game = args[0];
            Maze maze = model.JoinToGame(game, client);
            return maze.ToJSON();
        }
    }
}