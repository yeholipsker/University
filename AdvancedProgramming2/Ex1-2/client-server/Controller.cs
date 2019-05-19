using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace client_server
{
    /// <summary>
    /// class for the controllers needed. has method for executing wanted command
    /// </summary>
    class Controller
    {
        /// <summary>
        /// members
        /// </summary>
        private Dictionary<string, ICommand> commands;
        private IModel model;
        /// <summary>
        /// constructor
        /// </summary>
        public Controller()
        {
            model = new Model();
            commands = new Dictionary<string, ICommand>();
            commands.Add("generate", new GenerateMazeCommand(model));
            commands.Add("solve", new SolveMazeCommand(model));
            commands.Add("start", new startMultiplayerGame(model));
            commands.Add("join", new joinMultiplayerGame(model));
            commands.Add("list", new ListCommand(model));
            commands.Add("play", new PlayCommand(model));
            commands.Add("close", new CloseCommand(model));
            commands.Add("delete", new DeleteCommand(model));
        }

        /// <summary>
        /// Executes the command.
        /// </summary>
        /// <param name="commandLine">The command line.</param>
        /// <param name="client">The client.</param>
        /// <returns>System.String.</returns>
        public string ExecuteCommand(string commandLine, TcpClient client)
        {
            string[] arr = commandLine.Split(' ');
            string commandKey = arr[0];
            if (!commands.ContainsKey(commandKey))
                return "Command not found";
            string[] args = arr.Skip(1).ToArray();
            ICommand command = commands[commandKey];
            return command.Execute(args, client);
        }
    }
}
