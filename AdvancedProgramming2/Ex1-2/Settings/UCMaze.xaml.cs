using MazeLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace Settings
{
    /// <summary>
    /// Interaction logic for UCMaze.xaml
    /// </summary>
    /// <seealso cref="System.Windows.Controls.UserControl" />
    /// <seealso cref="System.Windows.Markup.IComponentConnector" />
    public partial class UCMaze : UserControl
    {
        /// <summary>
        /// The maze
        /// </summary>
        Rectangle[,] maze;
        /// <summary>
        /// The height
        /// </summary>
        private double height;
        /// <summary>
        /// The width
        /// </summary>
        private double width;
        /// <summary>
        /// The player brush
        /// </summary>
        Brush playerBrush;
        /// <summary>
        /// The exit brush
        /// </summary>
        Brush exitBrush;

        /// <summary>
        /// Initializes a new instance of the <see cref="UCMaze"/> class.
        /// </summary>
        public UCMaze()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Draws the maze.
        /// </summary>
        public void DrawMaze()
        {
            this.height = myCanvas.Height / this.Rows;
            this.width = myCanvas.Width / this.Cols;
            double x = 0, y = 0;
            maze = new Rectangle[this.Rows, this.Cols];

            for (int i = 0; i < this.Rows; i++)
            {
                for (int j = 0; j < this.Cols; j++)
                {
                    if (this.MazeProperty[i, j] == CellType.Wall)
                    {
                        this.DrawRectangle(i, j, x, y, Brushes.Black);
                    }
                    else if (i == this.MazeProperty.InitialPos.Row && j == this.MazeProperty.InitialPos.Col)
                    {
                        this.playerBrush = new ImageBrush
                        {
                            ImageSource = new BitmapImage(
                            new Uri(@"pack://application:,,,/Settings;component/Mario.png", UriKind.Absolute))
                        };
                        this.DrawRectangle(i, j, x, y, this.playerBrush);
                    }
                    else if (i == this.MazeProperty.GoalPos.Row && j == this.MazeProperty.GoalPos.Col)
                    {
                        this.exitBrush = new ImageBrush
                        {
                            ImageSource = new BitmapImage(
                            new Uri(@"pack://application:,,,/Settings;component/Exit.jpg", UriKind.Absolute))
                        };
                        this.DrawRectangle(i, j, x, y, this.exitBrush);
                    }
                    else
                    {
                        this.DrawRectangle(i, j, x, y, Brushes.White);
                    }
                    y += width;
                }
                x += height;
                y = 0;
            }
            this.PlayerPosition = new Position(this.MazeProperty.InitialPos.Row, this.MazeProperty.InitialPos.Col);
        }

        /// <summary>
        /// Draws the rectangle.
        /// </summary>
        /// <param name="i">The i.</param>
        /// <param name="j">The j.</param>
        /// <param name="x">The x.</param>
        /// <param name="y">The y.</param>
        /// <param name="brush">The brush.</param>
        private void DrawRectangle(int i, int j, double x, double y, Brush brush)
        {
            maze[i, j] = new Rectangle();
            maze[i, j].Height = this.height;
            maze[i, j].Width = this.width;
            maze[i, j].Fill = brush;
            maze[i, j].StrokeThickness = 0.1;
            maze[i, j].Stroke = Brushes.Black;
            maze[i, j].SetValue(Canvas.LeftProperty, y);
            maze[i, j].SetValue(Canvas.TopProperty, x);
            myCanvas.Children.Add(maze[i, j]);
        }

        /// <summary>
        /// Shows the solution.
        /// </summary>
        public void ShowSolution()
        {
            for (int i = 0; i < this.Solution.Length; i++)
            {
                Application.Current.Dispatcher.Invoke(
                DispatcherPriority.Background,
                new Action(() =>
                {
                    Key curKey = 0;
                    switch (this.Solution[i])
                    {
                        case '0':
                            curKey = Key.Left;
                            break;
                        case '1':
                            curKey = Key.Right;
                            break;
                        case '2':
                            curKey = Key.Up;
                            break;
                        case '3':
                            curKey = Key.Down;
                            break;
                    }
                    this.mazeUC_KeyDown(this,
                    new KeyEventArgs(
                    Keyboard.PrimaryDevice,
                    PresentationSource.FromVisual((Visual)Keyboard.FocusedElement), 0, curKey)
                    {
                        RoutedEvent = Keyboard.KeyDownEvent
                    });
                }));
                System.Threading.Thread.Sleep(300);
            }
        }

        /// <summary>
        /// Gets or sets the maze property.
        /// </summary>
        /// <value>The maze property.</value>
        public Maze MazeProperty
        {
            get { return (Maze)GetValue(MazePropertyProperty); }
            set { SetValue(MazePropertyProperty, value); }
        }

        // Using a DependencyProperty as the backing store for MazeProperty.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The maze property property
        /// </summary>
        public static readonly DependencyProperty MazePropertyProperty =
            DependencyProperty.Register("MazeProperty", typeof(Maze), typeof(UCMaze));


        /// <summary>
        /// Gets or sets the rows.
        /// </summary>
        /// <value>The rows.</value>
        public int Rows
        {
            get { return (int)GetValue(RowsProperty); }
            set { SetValue(RowsProperty, value); }
        }

        // Using a DependencyProperty as the backing store for Rows.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The rows property
        /// </summary>
        public static readonly DependencyProperty RowsProperty =
            DependencyProperty.Register("Rows", typeof(int), typeof(UCMaze),
                new PropertyMetadata(Properties.Settings.Default.MazeRows));

        /// <summary>
        /// Gets or sets the cols.
        /// </summary>
        /// <value>The cols.</value>
        public int Cols
        {
            get { return (int)GetValue(ColsProperty); }
            set { SetValue(ColsProperty, value); }
        }

        // Using a DependencyProperty as the backing store for Cols.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The cols property
        /// </summary>
        public static readonly DependencyProperty ColsProperty =
            DependencyProperty.Register("Cols", typeof(int), typeof(UCMaze),
                new PropertyMetadata(Properties.Settings.Default.MazeCols));

        /// <summary>
        /// Gets or sets the solution.
        /// </summary>
        /// <value>The solution.</value>
        public string Solution
        {
            get { return (string)GetValue(SolutionProperty); }
            set { SetValue(SolutionProperty, value); }
        }

        // Using a DependencyProperty as the backing store for Solution.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The solution property
        /// </summary>
        public static readonly DependencyProperty SolutionProperty =
            DependencyProperty.Register("Solution", typeof(string), typeof(UCMaze), new PropertyMetadata(null));



        /// <summary>
        /// Gets or sets the name of the maze.
        /// </summary>
        /// <value>The name of the maze.</value>
        public string MazeName
        {
            get { return (string)GetValue(MazeNameProperty); }
            set { SetValue(MazeNameProperty, value); }
        }

        // Using a DependencyProperty as the backing store for MazeName.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The maze name property
        /// </summary>
        public static readonly DependencyProperty MazeNameProperty =
            DependencyProperty.Register("MazeName", typeof(string), typeof(UCMaze),
                new PropertyMetadata(Properties.Settings.Default.MazeName));

        /// <summary>
        /// Gets or sets the player position.
        /// </summary>
        /// <value>The player position.</value>
        public Position PlayerPosition
        {
            get { return (Position)GetValue(PlayerPositionProperty); }
            set { SetValue(PlayerPositionProperty, value); }
        }

        // Using a DependencyProperty as the backing store for PlayerPosition.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The player position property
        /// </summary>
        public static readonly DependencyProperty PlayerPositionProperty =
            DependencyProperty.Register("PlayerPosition", typeof(Position), typeof(UCMaze),
                new UIPropertyMetadata(onRowsPropertyChanged));

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="UCMaze"/> is win.
        /// </summary>
        /// <value><c>true</c> if win; otherwise, <c>false</c>.</value>
        public bool Win
        {
            get { return (bool)GetValue(WinProperty); }
            set { SetValue(WinProperty, value); }
        }

        // Using a DependencyProperty as the backing store for Win.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The win property
        /// </summary>
        public static readonly DependencyProperty WinProperty =
            DependencyProperty.Register("Win", typeof(bool), typeof(UCMaze), new PropertyMetadata(false));

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="UCMaze"/> is lose.
        /// </summary>
        /// <value><c>true</c> if lose; otherwise, <c>false</c>.</value>
        public bool Lose
        {
            get { return (bool)GetValue(LoseProperty); }
            set { SetValue(LoseProperty, value); }
        }

        // Using a DependencyProperty as the backing store for Win.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The lose property
        /// </summary>
        public static readonly DependencyProperty LoseProperty =
            DependencyProperty.Register("Lose", typeof(bool), typeof(UCMaze), new PropertyMetadata(false));

        /// <summary>
        /// Gets or sets a value indicating whether [no connection].
        /// </summary>
        /// <value><c>true</c> if [no connection]; otherwise, <c>false</c>.</value>
        public bool NoConnection
        {
            get { return (bool)GetValue(NoConnectionProperty); }
            set { SetValue(NoConnectionProperty, value); }
        }

        // Using a DependencyProperty as the backing store for Win.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The no connection property
        /// </summary>
        public static readonly DependencyProperty NoConnectionProperty =
            DependencyProperty.Register("NoConnection", typeof(bool), typeof(UCMaze), new PropertyMetadata(false));

        /// <summary>
        /// When players position property changed.
        /// </summary>
        /// <param name="d">The d.</param>
        /// <param name="e">The <see cref="DependencyPropertyChangedEventArgs"/> instance containing the event data.</param>
        private static void onRowsPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            int oldI = ((Position)e.OldValue).Row;
            int oldJ = ((Position)e.OldValue).Col;
            int newI = ((Position)e.NewValue).Row;
            int newJ = ((Position)e.NewValue).Col;
            ((UCMaze)d).maze[oldI, oldJ].Fill = Brushes.White;
            ((UCMaze)d).maze[newI, newJ].Fill = ((UCMaze)d).playerBrush;
            if (newI == ((UCMaze)d).MazeProperty.GoalPos.Row && newJ == ((UCMaze)d).MazeProperty.GoalPos.Col)
            {
                ((UCMaze)d).Lose = true;

            }
        }

        /// <summary>
        /// Handles the KeyDown event of the mazeUC control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="KeyEventArgs"/> instance containing the event data.</param>
        public void mazeUC_KeyDown(object sender, KeyEventArgs e)
        {
            int i = this.PlayerPosition.Row;
            int j = this.PlayerPosition.Col;
            switch (e.Key)
            {
                case Key.Up:
                    if (i > 0 && this.MazeProperty[i - 1, j] == CellType.Free)
                    {
                        maze[i, j].Fill = Brushes.White;
                        maze[i - 1, j].Fill = this.playerBrush;
                        this.PlayerPosition = new Position(i - 1, j);
                    }
                    break;
                case Key.Down:
                    if (i < this.Rows && this.MazeProperty[i + 1, j] == CellType.Free)
                    {
                        maze[i, j].Fill = Brushes.White;
                        maze[i + 1, j].Fill = this.playerBrush;
                        this.PlayerPosition = new Position(i + 1, j);
                    }
                    break;
                case Key.Left:
                    if (j > 0 && this.MazeProperty[i, j - 1] == CellType.Free)
                    {
                        maze[i, j].Fill = Brushes.White;
                        maze[i, j - 1].Fill = this.playerBrush;
                        this.PlayerPosition = new Position(i, j - 1);
                    }
                    break;
                case Key.Right:
                    if (j < this.Cols && this.MazeProperty[i, j + 1] == CellType.Free)
                    {
                        maze[i, j].Fill = Brushes.White;
                        maze[i, j + 1].Fill = this.playerBrush;
                        this.PlayerPosition = new Position(i, j + 1);
                    }
                    break;
            }
            if (this.PlayerPosition.Row == this.MazeProperty.GoalPos.Row &&
                this.PlayerPosition.Col == this.MazeProperty.GoalPos.Col)
            {
                this.Win = true;
            }
        }
    }
}


