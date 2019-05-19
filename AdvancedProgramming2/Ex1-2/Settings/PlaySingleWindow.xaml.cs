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
using System.Windows.Shapes;

namespace Settings
{
    /// <summary>
    /// Interaction logic for PlaySingleWindow.xaml
    /// </summary>
    /// <seealso cref="System.Windows.Window" />
    /// <seealso cref="System.Windows.Markup.IComponentConnector" />
    public partial class PlaySingleWindow : Window
    {
        /// <summary>
        /// The Play Single View Model
        /// </summary>
        private PlaySingleViewModel psvm;
        /// <summary>
        /// The model
        /// </summary>
        private ISingleModel model;
        /// <summary>
        /// Initializes a new instance of the PlaySingleWindow class.
        /// </summary>
        /// <param name="model">The model.</param>
        public PlaySingleWindow(ISingleModel model)
        {
            InitializeComponent();
            this.model = model;
            this.psvm = new PlaySingleViewModel(this.model);
            this.DataContext = this.psvm;
            this.psvm.PlayerWinEvent += gameFinished;           
        }



        /// <summary>
        /// finish the game.
        /// </summary>
        private void gameFinished()
        {
            MessageBox.Show("You Won!");
            this.psvm.Delete();
            MainWindow win = (MainWindow)Application.Current.MainWindow;
            win.Show();
            this.Closing -= Window_Closing;
            this.Close();
        }

        /// <summary>
        /// Handles the Closing event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if ((MessageBox.Show("Are you sure you want to go back to main menu?", "Confirm action", MessageBoxButton.OKCancel))
                == MessageBoxResult.OK)
            {
                this.psvm.Delete();
                MainWindow win = (MainWindow)Application.Current.MainWindow;
                win.Show();
            }
        }

        /// <summary>
        /// Handles the Loaded event of the UCMaze control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void UCMaze_Loaded(object sender, RoutedEventArgs e)
        {
            UCMaze.DrawMaze();
            this.KeyDown += UCMaze.mazeUC_KeyDown;
        }

        /// <summary>
        /// Handles the Click event of the SolveBtn control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void SolveBtn_Click(object sender, RoutedEventArgs e)
        {
            if (this.psvm.VM_Solution == null)
            {
                this.psvm.SolveMaze();
            }
            UCMaze.DrawMaze();
            UCMaze.ShowSolution();
        }

        /// <summary>
        /// Handles the Click event of the RestartBtn control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void RestartBtn_Click(object sender, RoutedEventArgs e)
        {
            if ((MessageBox.Show("Are you sure you want to go back to restart?", "Confirm action", MessageBoxButton.OKCancel))
                == MessageBoxResult.OK)
            {
                UCMaze.DrawMaze();
            }
        }

        /// <summary>
        /// Handles the Click event of the MMenuBtn control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void MMenuBtn_Click(object sender, RoutedEventArgs e)
        {
            if((MessageBox.Show("Are you sure you want to go back to main menu?", "Confirm action", MessageBoxButton.OKCancel))
                == MessageBoxResult.OK)
            {
                this.psvm.Delete();
                MainWindow win = (MainWindow)Application.Current.MainWindow;
                win.Show();
                this.Closing -= Window_Closing;
                this.Close();
            }
        }
    }
}
