using MazeLib;
using System;
using System.ComponentModel;

namespace Settings
{
    /// <summary>
    /// Class PlaySingleViewModel.
    /// </summary>
    /// <seealso cref="Settings.ViewModel" />
    internal class PlaySingleViewModel : ViewModel
    {
        /// <summary>
        /// The model
        /// </summary>
        private ISingleModel model;
        /// <summary>
        /// Delegate PlayerWin
        /// </summary>
        public delegate void PlayerWin();
        public event PlayerWin PlayerWinEvent;

        /// <summary>
        /// Initializes a new instance of the <see cref="PlaySingleViewModel"/> class.
        /// </summary>
        /// <param name="model">The model.</param>
        public PlaySingleViewModel(ISingleModel model)
        {
            this.model = model;
            this.model.PropertyChanged += delegate (Object sender, PropertyChangedEventArgs e)
            { NotifyPropertyChanged("VM_" + e.PropertyName); };
            
        }
        /// <summary>
        /// Gets or sets the maze property.
        /// </summary>
        /// <value>The maze property.</value>
        public Maze MazeProperty
        {
            get { return this.model.MazeProperty; }
            set { this.model.MazeProperty = value; }
        }
        /// <summary>
        /// Gets or sets the name of the maze.
        /// </summary>
        /// <value>The name of the maze.</value>
        public string MazeName
        {
            get { return this.model.MazeName; }
            set { this.model.MazeName = value; }
        }
        /// <summary>
        /// Gets or sets the maze rows.
        /// </summary>
        /// <value>The maze rows.</value>
        public int MazeRows
        {
            get { return this.model.MazeRows; }
            set { this.model.MazeRows = value; }
        }
        /// <summary>
        /// Gets or sets the maze cols.
        /// </summary>
        /// <value>The maze cols.</value>
        public int MazeCols
        {
            get { return this.model.MazeCols; }
            set { this.model.MazeCols = value; }
        }
        /// <summary>
        /// Gets or sets the vm solution.
        /// </summary>
        /// <value>The vm solution.</value>
        public string VM_Solution
        {
            get { return this.model.Solution; }
            set { this.model.Solution = value;}
        }
        /// <summary>
        /// Gets or sets a value indicating whether [vm win].
        /// </summary>
        /// <value><c>true</c> if [vm win]; otherwise, <c>false</c>.</value>
        public bool VM_Win
        {
            get
            {
                if (this.model.Win)
                {
                    PlayerWinEvent?.Invoke();
                }
                return this.model.Win;
            }
            set { this.model.Win = value; }
        }

        /// <summary>
        /// Solves the maze.
        /// </summary>
        public void SolveMaze()
        {
            this.model.SolveMaze();

        }

        internal void Delete()
        {
            this.model.Delete();
        }
    }
}