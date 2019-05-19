using System;
using System.ComponentModel;

namespace Settings
{
    /// <summary>
    /// Class SingleViewModel.
    /// </summary>
    /// <seealso cref="Settings.ViewModel" />
    class SingleViewModel : ViewModel
    {

        /// <summary>
        /// The model
        /// </summary>
        private ISingleModel model;
        /// <summary>
        /// Initializes a new instance of the <see cref="SingleViewModel"/> class.
        /// </summary>
        /// <param name="model">The model.</param>
        public SingleViewModel(ISingleModel model)
        {
            this.model = model;
            this.model.PropertyChanged += delegate (Object sender, PropertyChangedEventArgs e)
            { NotifyPropertyChanged("VM_" + e.PropertyName); };
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
        /// Generates the maze.
        /// </summary>
        public void GenerateMaze()
        {
            this.model.GenerateMaze();
        }
        
    }
}