using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MazeLib;
using MazeGeneratorLib;
using SearchAlgorithmsLib;
using TestMaze;
using System.Net.Sockets;
using System.IO;

namespace client_server
{
    class Model : IModel
    {
        /// <summary>
        /// members 
        /// </summary>
        
        private DFSMazeGenerator dFSMazeGenerator;
        private Dictionary<string, Maze> mazes;
        private Dictionary<string, Maze> games;
        private Dictionary<string, PlayersClients> clients;
        private Dictionary<string, string> solutions;

        /// <summary>
        /// constructor
        /// Initializes all the members
        /// </summary>
        public Model()
        {
            dFSMazeGenerator = new DFSMazeGenerator();
            this.mazes = new Dictionary<string, Maze>();
            this.solutions = new Dictionary<string, string>();
            this.games = new Dictionary<string, Maze>();
            this.clients = new Dictionary<string, PlayersClients>();
        }

        /// <summary>
        /// Generates the game.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="rows">The amount of rows.</param>
        /// <param name="cols">The amount of columns.</param>
        /// <param name="client">The client for whom the game is for.</param>
        /// <returns>Maze.</returns>
        public Maze GenerateGame(string name, int rows, int cols, TcpClient client)
        {
            Maze maze = this.dFSMazeGenerator.Generate(rows, cols);
            maze.Name = name;
            this.games.Add(name, maze);
            PlayersClients pClients = new PlayersClients(client);
            this.clients.Add(name, pClients);
            //while(!pClients.HasTowPlayers)
            //{
            //    System.Threading.Thread.Sleep(50);
            //}
            return maze;
        }

        /// <summary>
        /// Generates the maze.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="rows">The amount of rows.</param>
        /// <param name="cols">The amount of columns.</param>
        /// <returns>Maze.</returns>
        public Maze GenerateMaze(string name, int rows, int cols)
        {
            Maze maze = this.dFSMazeGenerator.Generate(rows, cols);
            maze.Name = name;
            this.mazes.Add(name, maze);
            return maze;
        }

        /// <summary>
        /// Solves the path for given maze
        /// </summary>
        /// <param name="name">The maze</param>
        /// <param name="algorithm">The algorithm to solve with.</param>
        /// <returns>the path</returns>
        public string Solve(string name, int algorithm)
        {
            //if (this.solutions.ContainsKey(name))
            //{
            //    return this.solutions[name];
            //}
            Solution<Position> solution = null;
            Adapter adapted = new Adapter(mazes[name]);
            ISearcher<Position> searcher = null;
            switch (algorithm)
            {
                case 0:
                    searcher = new BFS<Position>();
                    break;
                case 1:
                    searcher = new DFS<Position>();
                    break;
            }
            solution = searcher.Search(adapted);
            SolveSolution solveSolution = new SolveSolution(name, solution, searcher.GetNumberOfNodesEvaluated());
            string toJSON = solveSolution.ToJSON();
            //solutions.Add(name, toJSON);
            return toJSON;
        }

        /// <summary>
        /// Joins to game.
        /// </summary>
        /// <param name="name">The name of game to join.</param>
        /// <param name="client">The client to add.</param>
        /// <returns>Maze.</returns>
        public Maze JoinToGame(string name,TcpClient client)
        {
            this.clients[name].AddPlayer(client);
            TcpClient competitorClient = this.clients[name].GetCompetitor(client);
            NetworkStream stream = competitorClient.GetStream();
            BinaryWriter writer = new BinaryWriter(stream);
            writer.Write(name);
            return games[name];
        }

        /// <summary>
        /// Shows the list of games.
        /// </summary>
        /// <returns>List of games;.</returns>
        public List<string> ShowList()
        {
            List<string> show = new List<string>();
            foreach (KeyValuePair<string, Maze> entry in this.games)
            {
                show.Add(entry.Value.Name);
            }
            return show;
        }

        /// <summary>
        /// Plays the move.
        /// </summary>
        /// <param name="direction">The direction to move.</param>
        /// <param name="client">The client to move.</param>
        public void PlayMove(string direction, TcpClient client)
        {
            string gameName = "";
            TcpClient competitorClient = null;
            foreach (KeyValuePair<string, PlayersClients> entry in this.clients)
            {
                if (entry.Value.HasPlayerClient(client))
                {
                    competitorClient = entry.Value.GetCompetitor(client);
                    gameName = entry.Key;
                }
            }
            Move move = new Move(gameName, competitorClient, direction);
            move.SendToCompetitor();
        }

        /// <summary>
        /// Closes the connection with specified client.
        /// </summary>
        /// <param name="name">The name of game.</param>
        /// <param name="client">The client.</param>
        public void Close(string name, TcpClient client)
        {
            this.games.Remove(name);
            TcpClient competitorClient = this.clients[name].GetCompetitor(client);
            NetworkStream stream = competitorClient.GetStream();
            BinaryWriter writer = new BinaryWriter(stream);
            writer.Write("close");
            this.clients.Remove(name);
        }

        /// <summary>
        /// Deletes the specified name.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="client">The client.</param>
        public void Delete(string name, TcpClient client)
        {
            this.mazes.Remove(name);
        }
    }
}
