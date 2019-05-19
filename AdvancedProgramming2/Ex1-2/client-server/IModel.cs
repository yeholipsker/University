using MazeLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SearchAlgorithmsLib;
using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// Interface with all of the expected common functionality to any model class
    /// </summary>
    interface IModel
    {
        /// <summary>
        /// Generates the maze.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="rows">The amount of rows.</param>
        /// <param name="cols">The amount of columns.</param>
        /// <returns>Maze.</returns>
        Maze GenerateMaze(string name, int rows, int cols);

        /// <summary>
        /// Solves the path for given maze
        /// </summary>
        /// <param name="name">The maze</param>
        /// <param name="algorithm">The algorithm to solve with.</param>
        /// <returns>the path</returns>
        string Solve(string name, int algorithm);

        /// <summary>
        /// Generates the game.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="rows">The amount of rows.</param>
        /// <param name="cols">The amount of columns.</param>
        /// <param name="client">The client for whom the game is for.</param>
        /// <returns>Maze.</returns>
        Maze GenerateGame(string name, int rows, int cols, TcpClient client);
      
        /// <summary>
        /// Joins to game.
        /// </summary>
        /// <param name="name">The name of game to join.</param>
        /// <param name="client">The client to add.</param>
        /// <returns>Maze.</returns>
        Maze JoinToGame(string name, TcpClient client);

        /// <summary>
        /// Shows the list of games.
        /// </summary>
        /// <returns>List of games;.</returns>
        List<string> ShowList();

        /// <summary>
        /// Plays the move.
        /// </summary>
        /// <param name="direction">The direction to move.</param>
        /// <param name="client">The client to move.</param>
        void PlayMove(string direction, TcpClient client);

        /// <summary>
        /// Closes the connection with specified client.
        /// </summary>
        /// <param name="name">The name of game.</param>
        /// <param name="client">The client.</param>
        void Close(string name, TcpClient client);
        void Delete(string name, TcpClient client);
    }
}
