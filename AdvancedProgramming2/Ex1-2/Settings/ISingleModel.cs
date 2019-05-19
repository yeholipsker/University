using MazeLib;
using System;
using System.ComponentModel;

namespace Settings
{
    /// <summary>
    /// Interface ISingleModel
    /// </summary>
    /// <seealso cref="System.ComponentModel.INotifyPropertyChanged" />
    public interface ISingleModel: INotifyPropertyChanged
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
        /// Gets or sets the maze property.
        /// </summary>
        /// <value>The maze property.</value>
        Maze MazeProperty { get; set; }
        /// <summary>
        /// Gets or sets the search algorithm.
        /// </summary>
        /// <value>The search algorithm.</value>
        int SearchAlgorithm { get; set; }
        /// <summary>
        /// Gets or sets the solution.
        /// </summary>
        /// <value>The solution.</value>
        string Solution { get; set; }
        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="ISingleModel"/> is win.
        /// </summary>
        /// <value><c>true</c> if win; otherwise, <c>false</c>.</value>
        bool Win { get; set; }



        /// <summary>
        /// Solves the maze.
        /// </summary>
        void SolveMaze();
        /// <summary>
        /// Generates the maze.
        /// </summary>
        void GenerateMaze();
        void Delete();
    }
}