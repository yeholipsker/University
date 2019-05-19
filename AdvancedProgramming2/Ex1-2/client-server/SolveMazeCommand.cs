using System;
using System.Net.Sockets;
using SearchAlgorithmsLib;
using TestMaze;
using MazeLib;

namespace client_server
{
    /// <summary>
    /// Class SolveMazeCommand.
    /// solves the path for the maze
    /// </summary>
    /// <seealso cref="client_server.ICommand" />
    class SolveMazeCommand : ICommand
    {
        /// <summary>
        /// member
        /// </summary>
        private IModel model;

        /// <summary>
        /// Initializes the members of the class.
        /// </summary>
        /// <param name="model">The model.</param>
        public SolveMazeCommand(IModel model)
        {
            this.model = model;
        }

        /// <summary>
        /// Executes the specified commands from args
        /// </summary>
        /// <param name="args">The commands.</param>
        /// <param name="client">The client.</param>
        /// <returns>a path.</returns>
        public string Execute(string[] args, TcpClient client = null)
        {
            string name = args[0];
            int algorithm = int.Parse(args[1]);
            return model.Solve(name, algorithm);
        }
    }
}