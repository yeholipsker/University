using MazeLib;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.ComponentModel;

namespace Settings
{
    /// <summary>
    /// Class SingleModel.
    /// </summary>
    /// <seealso cref="Settings.ISingleModel" />
    class SingleModel : ISingleModel
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
        /// The solution
        /// </summary>
        private string solution;
        /// <summary>
        /// The win
        /// </summary>
        private bool win;
        
        public event PropertyChangedEventHandler PropertyChanged;


        /// <summary>
        /// Initializes a new instance of the <see cref="SingleModel"/> class.
        /// </summary>
        public SingleModel()
        {
            this.ep = new IPEndPoint(IPAddress.Parse(Properties.Settings.Default.ServerIP),
                Convert.ToInt32(Properties.Settings.Default.ServerPort));
            this.client = new TcpClient();
            
                this.client.Connect(ep);
            this.stream = client.GetStream();
            
            this.reader = new BinaryReader(this.stream);
            this.writer = new BinaryWriter(this.stream);
            this.win = false;
        }
        /// <summary>
        /// Gets or sets the name of the maze.
        /// </summary>
        /// <value>The name of the maze.</value>
        public string MazeName { get; set; }
        /// <summary>
        /// Gets or sets the maze rows.
        /// </summary>
        /// <value>The maze rows.</value>
        public int MazeRows { get; set; }
        /// <summary>
        /// Gets or sets the maze cols.
        /// </summary>
        /// <value>The maze cols.</value>
        public int MazeCols { get; set; }
        /// <summary>
        /// Gets or sets the maze property.
        /// </summary>
        /// <value>The maze property.</value>
        public Maze MazeProperty { get; set; }
        /// <summary>
        /// Gets or sets the search algorithm.
        /// </summary>
        /// <value>The search algorithm.</value>
        public int SearchAlgorithm
        {
            get { return Properties.Settings.Default.SearchAlgorithm; }
            set { Properties.Settings.Default.SearchAlgorithm = value; }
        }


        /// <summary>
        /// Gets or sets the solution.
        /// </summary>
        /// <value>The solution.</value>
        public string Solution
        {
            get { return this.solution; }
            set
            {
                this.solution = value;
                NotifyPropertyChanged("Solution");
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="ISingleModel" /> is win.
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
        /// Generates the maze.
        /// </summary>
        public void GenerateMaze()
        {
            this.writer.Write("generate " + MazeName + " " + MazeRows + " " + MazeCols);
            string mazeJson = this.reader.ReadString();
            MazeProperty = Maze.FromJSON(mazeJson);
        }
        /// <summary>
        /// Solves the maze.
        /// </summary>
        public void SolveMaze()
        {
            this.writer.Write("solve " + MazeName + " " + SearchAlgorithm);
            string temp = this.reader.ReadString();
            int from = temp.IndexOf("Solution\": \"") + 12;
            int to = temp.IndexOf("\",\r\n  \"NodesEvaluated");
            Solution = temp.Substring(from, to - from);
        }
        /// <summary>
        /// Notifies the property changed.
        /// </summary>
        /// <param name="propName">Name of the property.</param>
        public void NotifyPropertyChanged(string propName)
        {
            this.PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propName));
        }

        public void Delete()
        {
            this.writer.Write("delete " + this.MazeName);
        }
    }
}