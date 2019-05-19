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

namespace Settings
{
    /// <summary>
    /// Interaction logic for UC3Fields.xaml
    /// </summary>
    /// <seealso cref="System.Windows.Controls.UserControl" />
    /// <seealso cref="System.Windows.Markup.IComponentConnector" />
    public partial class UC3Fields : UserControl
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="UC3Fields"/> class.
        /// </summary>
        public UC3Fields()
        {
            InitializeComponent();
        }


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
            DependencyProperty.Register("MazeName", typeof(string), typeof(UC3Fields), 
                new PropertyMetadata(Properties.Settings.Default.MazeName));



        /// <summary>
        /// Gets or sets the maze rows.
        /// </summary>
        /// <value>The maze rows.</value>
        public int MazeRows
        {
            get { return (int)GetValue(MazeRowsProperty); }
            set { SetValue(MazeRowsProperty, value); }
        }

        // Using a DependencyProperty as the backing store for MazeRows.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The maze rows property
        /// </summary>
        public static readonly DependencyProperty MazeRowsProperty =
            DependencyProperty.Register("MazeRows", typeof(int), typeof(UC3Fields), 
                new PropertyMetadata(Properties.Settings.Default.MazeRows));



        /// <summary>
        /// Gets or sets the maze cols.
        /// </summary>
        /// <value>The maze cols.</value>
        public int MazeCols
        {
            get { return (int)GetValue(MazeColsProperty); }
            set { SetValue(MazeColsProperty, value); }
        }

        // Using a DependencyProperty as the backing store for MazeCols.  This enables animation, styling, binding, etc...
        /// <summary>
        /// The maze cols property
        /// </summary>
        public static readonly DependencyProperty MazeColsProperty =
            DependencyProperty.Register("MazeCols", typeof(int), typeof(UC3Fields), 
                new PropertyMetadata(Properties.Settings.Default.MazeCols));


    }
}
