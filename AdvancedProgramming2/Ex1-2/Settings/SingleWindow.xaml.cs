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
    /// Interaction logic for SingleWindow.xaml
    /// </summary>
    /// <seealso cref="System.Windows.Window" />
    /// <seealso cref="System.Windows.Markup.IComponentConnector" />
    public partial class SingleWindow : Window
    {
        /// <summary>
        /// The Single View Model
        /// </summary>
        private SingleViewModel svm;
        /// <summary>
        /// The model
        /// </summary>
        private ISingleModel model;
        /// <summary>
        /// Initializes a new instance of the <see cref="SingleWindow"/> class.
        /// </summary>
        public SingleWindow()
        {
            InitializeComponent();
            this.model = new SingleModel();
            svm = new SingleViewModel(this.model);
            this.DataContext = svm;
        }

        /// <summary>
        /// Handles the Click event of the playBtn control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void playBtn_Click(object sender, RoutedEventArgs e)
        {
            svm.GenerateMaze();
            PlaySingleWindow pw = new PlaySingleWindow(this.model);
            pw.Show();
            this.Hide();
        }

        /// <summary>
        /// Handles the Closing event of the Window control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.ComponentModel.CancelEventArgs"/> instance containing the event data.</param>
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            MainWindow win = (MainWindow)Application.Current.MainWindow;
            win.Show();
        }

        
    }
}
