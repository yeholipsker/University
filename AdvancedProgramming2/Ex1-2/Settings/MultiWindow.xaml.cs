using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
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
    /// Interaction logic for MultiWindow.xaml
    /// </summary>
    /// <seealso cref="System.Windows.Window" />
    /// <seealso cref="System.Windows.Markup.IComponentConnector" />
    public partial class MultiWindow : Window
    {
        /// <summary>
        /// The Multi View Model
        /// </summary>
        private MultiViewModel mvm;
        /// <summary>
        /// The model
        /// </summary>
        private IMultiModel model;

        /// <summary>
        /// Initializes a new instance of the <see cref="MultiWindow"/> class.
        /// </summary>
        public MultiWindow()
        {
            InitializeComponent();
            this.model = new ApplicationMultiModel();
            mvm = new MultiViewModel(this.model);
            this.DataContext = mvm;
        }

        /// <summary>
        /// Handles the Click event of the JoinBtun control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void JoinBtun_Click(object sender, RoutedEventArgs e)
        {
            this.mvm.JoinGame();
            PlayMultiWindow pw = new PlayMultiWindow(this.model);
            pw.Show();
            this.Hide();
        }

        /// <summary>
        /// Handles the Click event of the StartBtun control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void StartBtun_Click(object sender, RoutedEventArgs e)
        {
            this.mvm.GenerateGame();
            PlayMultiWindow pmw = new PlayMultiWindow(this.model);
            pmw.Show();
            this.Hide();
        }

        /// <summary>
        /// Handles the DropDownOpened event of the gamesList control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private void gamesList_DropDownOpened(object sender, EventArgs e)
        {
            this.mvm.GetList();
        }

        private void Window_Closing(object sender, CancelEventArgs e)
        {
            MainWindow win = (MainWindow)Application.Current.MainWindow;
            win.Show();
        }
    }
}
