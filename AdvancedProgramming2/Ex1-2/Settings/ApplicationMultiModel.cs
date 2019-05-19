using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MazeLib;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.ComponentModel;
using System.Collections.ObjectModel;
using Newtonsoft.Json;
using System.Windows.Input;

namespace Settings
{
    /// <summary>
    /// Class ApplicationMultiModel.
    /// </summary>
    /// <seealso cref="Settings.IMultiModel" />
    class ApplicationMultiModel : IMultiModel
    {
        /// <summary>
        /// The end point
        /// </summary>
        private IPEndPoint ep;
        /// <summary>
        /// The client
        /// </summary>
        private TcpClient client;
        /// <summary>
        /// The stream
        /// </summary>
        private NetworkStream stream;
        /// <summary>
        /// The reader
        /// </summary>
        private BinaryReader reader;
        /// <summary>
        /// The writer
        /// </summary>
        private BinaryWriter writer;
        /// <summary>
        /// The list of games
        /// </summary>
        private List<string> listOfGames;
        /// <summary>
        /// The this maze
        /// </summary>
        private Maze thisMaze;
        /// <summary>
        /// The maze rows
        /// </summary>
        private int mazeRows;
        /// <summary>
        /// The maze cols
        /// </summary>
        private int mazeCols;
        /// <summary>
        /// The maze name
        /// </summary>
        private string mazeName;
        /// <summary>
        /// The player position
        /// </summary>
        private Position playerPosition;
        /// <summary>
        /// The no connection
        /// </summary>
        private bool noConnection;
        /// <summary>
        /// The win
        /// </summary>
        private bool win;
        /// <summary>
        /// The lose
        /// </summary>
        private bool lose;
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Initializes a new instance of the <see cref="ApplicationMultiModel"/> class.
        /// </summary>
        public ApplicationMultiModel()
        {
            this.ep = new IPEndPoint(IPAddress.Parse(Properties.Settings.Default.ServerIP),
            Convert.ToInt32(Properties.Settings.Default.ServerPort));
            this.client = new TcpClient();
            this.client.Connect(ep);
            this.stream = client.GetStream();
            this.reader = new BinaryReader(this.stream);
            this.writer = new BinaryWriter(this.stream);
            this.noConnection = false;
        }
        /// <summary>
        /// Gets or sets the maze rows.
        /// </summary>
        /// <value>The maze rows.</value>
        public int MazeRows
        {
            get { return this.mazeRows; }
            set
            {
                if (this.mazeRows != value)
                {
                    this.mazeRows = value;
                    this.NotifyPropertyChanged("MazeRows");
                }
            }
        }
        /// <summary>
        /// Gets or sets the maze cols.
        /// </summary>
        /// <value>The maze cols.</value>
        public int MazeCols
        {
            get { return this.mazeCols; }
            set
            {
                if (this.mazeCols != value)
                {
                    this.mazeCols = value;
                    this.NotifyPropertyChanged("MazeCols");
                }
            }
        }
        /// <summary>
        /// Gets or sets the list of games.
        /// </summary>
        /// <value>The list of games.</value>
        public List<string> ListOfGames
        {
            get { return this.listOfGames; }
            set
            {
                if (this.listOfGames != value)
                {
                    this.listOfGames = value;
                    this.NotifyPropertyChanged("ListOfGames");
                }
            }
        }
        /// <summary>
        /// Gets or sets the name of the maze.
        /// </summary>
        /// <value>The name of the maze.</value>
        public string MazeName
        {
            get { return this.mazeName; }
            set
            {
                if (this.mazeName != value)
                {
                    this.mazeName = value;
                    this.NotifyPropertyChanged("MazeName");
                }
            }
        }

        /// <summary>
        /// Gets or sets the maze property.
        /// </summary>
        /// <value>The maze property.</value>
        public Maze MazeProperty
        {
            get { return this.thisMaze; }
            set
            {
                if (this.thisMaze != value)
                {
                    this.thisMaze = value;
                    this.NotifyPropertyChanged("MazeProperty");
                }
            }
        }

        /// <summary>
        /// Gets or sets the game to join.
        /// </summary>
        /// <value>The game to join.</value>
        public string GameToJoin { get; set; }

        /// <summary>
        /// Gets or sets the player position.
        /// </summary>
        /// <value>The player position.</value>
        public Position PlayerPosition
        {
            get { return this.playerPosition; }
            set
            {
                this.playerPosition = value;
                this.NotifyPropertyChanged("PlayerPosition");
            }
        }
        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="ApplicationMultiModel"/> is win.
        /// </summary>
        /// <value><c>true</c> if win; otherwise, <c>false</c>.</value>
        public bool Win
        {
            get { return this.win; }
            set
            {
                this.win = value;
                NotifyPropertyChanged("Win");
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="ApplicationMultiModel"/> is lose.
        /// </summary>
        /// <value><c>true</c> if lose; otherwise, <c>false</c>.</value>
        public bool Lose
        {
            get { return this.lose; }
            set
            {
                this.lose = value;
                NotifyPropertyChanged("Lose");
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether [no connection].
        /// </summary>
        /// <value><c>true</c> if [no connection]; otherwise, <c>false</c>.</value>
        public bool NoConnection
        {
            get
            {
                return this.noConnection;
            }
            set
            {
                this.noConnection = value;
                NotifyPropertyChanged("NoConnection");
            }
        }
        /// <summary>
        /// Generates the game.
        /// </summary>
        public void GenerateGame()
        {
            this.writer.Write("start " + MazeName + " " + MazeRows + " " + MazeCols);
            string mazeJson = this.reader.ReadString();
            MazeProperty = Maze.FromJSON(mazeJson);
            string start = null;
            start = this.reader.ReadString();
            GetDirection();
        }

        /// <summary>
        /// Gets the direction.
        /// </summary>
        private void GetDirection()
        {

            new Task(() =>
        {
            while (true)
            {
                try
                {

                    string direction = this.reader.ReadString();
                    int i = this.PlayerPosition.Row;
                    int j = this.PlayerPosition.Col;
                    if (direction.Contains("close"))
                    {
                        this.NoConnection = true;
                    }
                    if (direction.Contains("up"))
                    {
                        if (i > 0 && this.MazeProperty[i - 1, j] == CellType.Free)
                        {
                            this.PlayerPosition = new Position(i - 1, j);
                        }
                    }
                    if (direction.Contains("down"))
                    {
                        if (i < this.MazeRows && this.MazeProperty[i + 1, j] == CellType.Free)
                        {
                            this.PlayerPosition = new Position(i + 1, j);
                        }
                    }
                    if (direction.Contains("left"))
                    {
                        if (j > 0 && this.MazeProperty[i, j - 1] == CellType.Free)
                        {
                            this.PlayerPosition = new Position(i, j - 1);
                        }
                    }
                    if (direction.Contains("right"))
                    {
                        if (j < this.MazeCols && this.MazeProperty[i, j + 1] == CellType.Free)
                        {
                            this.PlayerPosition = new Position(i, j + 1);
                        }
                    }
                }
                catch
                {
                    this.NoConnection = true;
                }
            }
        }).Start();

        }

        /// <summary>
        /// Joins the game.
        /// </summary>
        /// <param name="game">The game.</param>
        public void JoinGame(string game)
        {
            this.writer.Write("join " + game);
            string mazeJson = this.reader.ReadString();
            MazeProperty = Maze.FromJSON(mazeJson);
            MazeCols = MazeProperty.Cols;
            MazeRows = MazeProperty.Rows;
            MazeName = MazeProperty.Name;
            GetDirection();
        }
        /// <summary>
        /// Gets the list.
        /// </summary>
        public void GetList()
        {
            this.writer.Write("list ");
            string listJson = this.reader.ReadString();
            this.ListOfGames = JsonConvert.DeserializeObject<List<string>>(listJson);
        }

        /// <summary>
        /// Notifies the property changed.
        /// </summary>
        /// <param name="propName">Name of the property.</param>
        public void NotifyPropertyChanged(string propName)
        {
            this.PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propName));
        }

        /// <summary>
        /// Moves the specified key.
        /// </summary>
        /// <param name="key">The key.</param>
        public void Move(Key key)
        {
            string direction = null;
            switch (key)
            {
                case Key.Left:
                    direction = "left";
                    break;
                case Key.Right:
                    direction = "right";
                    break;
                case Key.Up:
                    direction = "up";
                    break;
                case Key.Down:
                    direction = "down";
                    break;
            }
            this.writer.Write("play " + direction);
        }

        /// <summary>
        /// Closes this instance.
        /// </summary>
        public void close()
        {
            this.writer.Write("close " + this.MazeName);
        }
    }
}
