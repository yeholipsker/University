using MazeLib;
using System;
using System.IO;
using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// Class startMultiplayerGame.
    /// sets a multiplayer game
    /// </summary>
    /// <seealso cref="client_server.ICommand" />
    class startMultiplayerGame : ICommand
    {
        /// <summary>
        /// member
        /// </summary>
        private IModel model;

        public startMultiplayerGame(IModel model)
        {
            this.model = model;
        }

        /// <summary>
        /// Executes the specified arguments.
        /// name, num of rows and columns
        /// </summary>
        /// <param name="args">The arguments: name, num of rows and columns</param>
        /// <param name="client">The client.</param>
        /// <returns>converted maze from maze to string for json</returns>
        public string Execute(string[] args, TcpClient client = null)
        {
            string name = args[0];
            int rows = int.Parse(args[1]);
            int cols = int.Parse(args[2]);
            Maze maze = model.GenerateGame(name, rows, cols, client);

            return maze.ToJSON();
            //return "";
        }
    }
}