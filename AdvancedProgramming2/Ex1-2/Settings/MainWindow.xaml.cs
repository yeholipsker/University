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
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    /// <seealso cref="System.Windows.Window" />
    /// <seealso cref="System.Windows.Markup.IComponentConnector" />
    public partial class MainWindow : Window
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="MainWindow"/> class.
        /// </summary>
        public MainWindow()
        {
            InitializeComponent();

        }

        /// <summary>
        /// Handles the Click event of the Settings control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void Settings_Click(object sender, RoutedEventArgs e)
        {
            SettingsWindow sw = new SettingsWindow();
            sw.Show();
            this.Hide();
        }

        /// <summary>
        /// Handles the Click event of the SinglePlayer control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void SinglePlayer_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                SingleWindow sw = new SingleWindow();
                sw.Show();
                this.Hide();
            }
            catch
            {
                MessageBox.Show("No conection with server!");
            }
        }

        /// <summary>
        /// Handles the Click event of the MultiPlayer control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void MultiPlayer_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                MultiWindow mw = new MultiWindow();
                mw.Show();
                this.Hide();
            }
            catch
            {
                MessageBox.Show("No conection with server!");
            }
        }
    }
}
