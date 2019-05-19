using MazeLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace client_server
{
    /// <summary>
    /// Class that generates the commands for new maze. inherits from Icomand
    /// </summary>
    /// <seealso cref="client_server.ICommand" />
    class GenerateMazeCommand : ICommand
    {
        /// <summary>
        /// member
        /// </summary>
        private IModel model;

        /// <summary>
        /// constructor
        /// </summary>
        /// <param name="model">The model.</param>
        public GenerateMazeCommand(IModel model)
        {
            this.model = model;
        }
        /// <summary>
        /// Executes the specified arguments, amount of columns and rows for maze etc...
        /// </summary>
        /// <param name="args">The arguments.</param>
        /// <param name="client">The client.</param>
        /// <returns>System.String.</returns>
        public string Execute(string[] args, TcpClient client = null)
        {
            string name = args[0];
            int rows = int.Parse(args[1]);
            int cols = int.Parse(args[2]);
            Maze maze = model.GenerateMaze(name, rows, cols);
            return maze.ToJSON();
        }
    }
}
