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
    /// Interaction logic for PlayMultiWindow.xaml
    /// </summary>
    /// <seealso cref="System.Windows.Window" />
    /// <seealso cref="System.Windows.Markup.IComponentConnector" />
    public partial class PlayMultiWindow : Window
    {
        /// <summary>
        /// The Multi View Model
        /// </summary>
        private MultiViewModel pmvm;
        /// <summary>
        /// Initializes a new instance of the <see cref="PlayMultiWindow"/> class.
        /// </summary>
        /// <param name="model">The model.</param>
        public PlayMultiWindow(IMultiModel model)
        {
            InitializeComponent();
            this.pmvm = new MultiViewModel(model);
            this.DataContext = this.pmvm;
            this.pmvm.PlayerWinEvent += gameFinished;
            this.pmvm.PlayerLoseEvent += LosegameFinished;
            this.pmvm.NoConnectionEvent += NoConnections;
        }

        /// <summary>
        /// Notify there is no connection.
        /// </summary>
        private void NoConnections()
        {
            MessageBox.Show(this, "No conection with server!");
            this.Closing -= Window_Closing;
            MainWindow win = (MainWindow)Application.Current.MainWindow;
            win.Show();
            this.Close();
        }

        /// <summary>
        /// the game finished and player lost.
        /// </summary>
        private void LosegameFinished()
        {
            MessageBox.Show(this, "You lost! =( ");
            this.pmvm.NoConnectionEvent -= NoConnections;
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
                this.pmvm.Close();
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
            MyUCMaze.DrawMaze();
            this.KeyDown += MyUCMaze_KeyDown;
            this.KeyDown += MyUCMaze.mazeUC_KeyDown;


        }

        /// <summary>
        /// Handles the Loaded event of the OtherUCMaze control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void OtherUCMaze_Loaded(object sender, RoutedEventArgs e)
        {
            OtherUCMaze.DrawMaze();
        }

        /// <summary>
        /// Handles the KeyDown event of the MyUCMaze control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="KeyEventArgs"/> instance containing the event data.</param>
        private void MyUCMaze_KeyDown(object sender, KeyEventArgs e)
        {
            this.pmvm.Move(e.Key);
        }

        /// <summary>
        /// Handles the Click event of the MMenuBtn control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void MMenuBtn_Click(object sender, RoutedEventArgs e)
        {
            if ((MessageBox.Show("Are you sure you want to go back to main menu?", "Confirm action", MessageBoxButton.OKCancel))
                == MessageBoxResult.OK)
            {
                this.pmvm.Close();
                MainWindow win = (MainWindow)Application.Current.MainWindow;
                win.Show();
                this.Closing -= Window_Closing;
                this.Close();
            }
        }
        /// <summary>
        /// the game finished and player won.
        /// </summary>
        private void gameFinished()
        {
            MessageBox.Show(this, "You Won!");
            this.pmvm.NoConnectionEvent -= NoConnections;
            this.pmvm.Close();
            MainWindow win = (MainWindow)Application.Current.MainWindow;
            win.Show();
            this.Closing -= Window_Closing;
            this.Close();
        }
    }
}
