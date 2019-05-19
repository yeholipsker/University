using MazeLib;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Settings
{
    /// <summary>
    /// Class MultiViewModel.
    /// </summary>
    /// <seealso cref="Settings.ViewModel" />
    class MultiViewModel :ViewModel
    {
        /// <summary>
        /// Delegate PlayerWin
        /// </summary>
        public delegate void PlayerWin();
        public event PlayerWin PlayerWinEvent;
        /// <summary>
        /// Delegate PlayerLose
        /// </summary>
        public delegate void PlayerLose();
        public event PlayerLose PlayerLoseEvent;
        /// <summary>
        /// Delegate NoConnection
        /// </summary>
        public delegate void NoConnection();
        public event NoConnection NoConnectionEvent;
        /// <summary>
        /// The model
        /// </summary>
        private IMultiModel model;
        /// <summary>
        /// Initializes a new instance of the <see cref="MultiViewModel"/> class.
        /// </summary>
        /// <param name="model">The model.</param>
        public MultiViewModel(IMultiModel model)
        {
            this.model = model;
            this.model.PropertyChanged += delegate (Object sender, PropertyChangedEventArgs e)
            { NotifyPropertyChanged("VM_" + e.PropertyName); };
        }

        /// <summary>
        /// Gets or sets the vm maze property.
        /// </summary>
        /// <value>The vm maze property.</value>
        public Maze VM_MazeProperty
        {
            get { return this.model.MazeProperty; }
            set
            { this.model.MazeProperty = value; }
        }

        /// <summary>
        /// Gets or sets the vm maze rows.
        /// </summary>
        /// <value>The vm maze rows.</value>
        public int VM_MazeRows
        {
            get { return model.MazeRows; }
            set { model.MazeRows = value; }
        }

        /// <summary>
        /// Gets or sets the vm maze cols.
        /// </summary>
        /// <value>The vm maze cols.</value>
        public int VM_MazeCols
        {
            get { return model.MazeCols; }
            set { model.MazeCols = value; }
        }

        /// <summary>
        /// Gets or sets the name of the vm maze.
        /// </summary>
        /// <value>The name of the vm maze.</value>
        public string VM_MazeName
        {
            get { return model.MazeName; }
            set { model.MazeName = value; }
        }

        /// <summary>
        /// Closes this instance.
        /// </summary>
        internal void Close()
        {
            this.model.close();
        }

        /// <summary>
        /// Gets or sets the vm player position.
        /// </summary>
        /// <value>The vm player position.</value>
        public Position VM_PlayerPosition
        {
            get { return this.model.PlayerPosition; }
            set { this.model.PlayerPosition = value; }
        }

        /// <summary>
        /// Gets or sets the vm list of games.
        /// </summary>
        /// <value>The vm list of games.</value>
        public List<string> VM_ListOfGames
        {
            get { return this.model.ListOfGames; }
            set { this.model.ListOfGames = value; }
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
        /// Gets or sets a value indicating whether [vm lose].
        /// </summary>
        /// <value><c>true</c> if [vm lose]; otherwise, <c>false</c>.</value>
        public bool VM_Lose
        {
            get
            {
                if (this.model.Lose)
                {
                    PlayerLoseEvent?.Invoke();
                }
                return this.model.Lose;
            }
            set { this.model.Lose = value; }
        }

        /// <summary>
        /// Gets or sets a value indicating whether [vm no connection].
        /// </summary>
        /// <value><c>true</c> if [vm no connection]; otherwise, <c>false</c>.</value>
        public bool VM_NoConnection
        {
            get
            {
                if (this.model.NoConnection)
                {
                    NoConnectionEvent?.Invoke();
                }
                return this.model.NoConnection;
            }
            set { this.model.NoConnection = value; }
        }

        /// <summary>
        /// Moves the specified key.
        /// </summary>
        /// <param name="key">The key.</param>
        public void Move(Key key)
        {
            this.model.Move(key);
        }

        /// <summary>
        /// Gets the list.
        /// </summary>
        public void GetList()
        {
            this.model.GetList();
        }

        /// <summary>
        /// Generates the game.
        /// </summary>
        public void GenerateGame()
        {
            this.model.GenerateGame();
        }

        /// <summary>
        /// Joins the game.
        /// </summary>
        public void JoinGame()
        {
            this.model.JoinGame(this.GameToJoin);
        }

        /// <summary>
        /// Gets or sets the game to join.
        /// </summary>
        /// <value>The game to join.</value>
        public string GameToJoin
        {
            get { return model.GameToJoin; }
            set
            {
                model.GameToJoin = value;
            }
        }
    }

}
