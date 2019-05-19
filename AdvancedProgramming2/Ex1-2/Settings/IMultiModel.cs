using MazeLib;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Settings
{
    /// <summary>
    /// Interface IMultiModel
    /// </summary>
    /// <seealso cref="System.ComponentModel.INotifyPropertyChanged" />
    public interface IMultiModel: INotifyPropertyChanged
    {

        /// <summary>
        /// Gets or sets the name of the maze.
        /// </summary>
        /// <value>The name of the maze.</value>
        string MazeName { get; set; }
        /// <summary>
        /// Gets or sets the maze rows.
        /// </summary>
        /// <value>The maze rows.</value>
        int MazeRows { get; set; }
        /// <summary>
        /// Gets or sets the maze cols.
        /// </summary>
        /// <value>The maze cols.</value>
        int MazeCols { get; set; }
        /// <summary>
        /// Gets or sets the list of games.
        /// </summary>
        /// <value>The list of games.</value>
        List<string> ListOfGames { get; set; }
        /// <summary>
        /// Gets or sets the maze property.
        /// </summary>
        /// <value>The maze property.</value>
        Maze MazeProperty { get; set; }
        /// <summary>
        /// Gets or sets the game to join.
        /// </summary>
        /// <value>The game to join.</value>
        string GameToJoin { get; set; }
        /// <summary>
        /// Gets or sets the player position.
        /// </summary>
        /// <value>The player position.</value>
        Position PlayerPosition { get; set; }
        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IMultiModel"/> is win.
        /// </summary>
        /// <value><c>true</c> if win; otherwise, <c>false</c>.</value>
        bool Win { get; set; }
        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IMultiModel"/> is lose.
        /// </summary>
        /// <value><c>true</c> if lose; otherwise, <c>false</c>.</value>
        bool Lose { get; set; }
        /// <summary>
        /// Gets or sets a value indicating whether [no connection].
        /// </summary>
        /// <value><c>true</c> if [no connection]; otherwise, <c>false</c>.</value>
        bool NoConnection { get; set; }
        /// <summary>
        /// Joins the game.
        /// </summary>
        /// <param name="game">The game.</param>
        void JoinGame(string game);
        /// <summary>
        /// Generates the game.
        /// </summary>
        void GenerateGame();
        /// <summary>
        /// Gets the list.
        /// </summary>
        void GetList();
        /// <summary>
        /// Moves the specified direction.
        /// </summary>
        /// <param name="direction">The direction.</param>
        void Move(Key direction);
        /// <summary>
        /// Closes this instance.
        /// </summary>
        void close();
    }
}
