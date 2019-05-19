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
    /// Interaction logic for SettingsWindow.xaml
    /// </summary>
    /// <seealso cref="System.Windows.Window" />
    /// <seealso cref="System.Windows.Markup.IComponentConnector" />
    public partial class SettingsWindow : Window
    {
        /// <summary>
        /// The Settings View Model
        /// </summary>
        private SettingsViewModel svm;
        /// <summary>
        /// Initializes a new instance of the <see cref="SettingsWindow"/> class.
        /// </summary>
        public SettingsWindow()
        {
            InitializeComponent();
            svm = new SettingsViewModel();
            this.DataContext = svm;
        }

        /// <summary>
        /// update the source.
        /// </summary>
        public void BindingUpdateSource()
        {
            BindingExpression be = ServerIP.GetBindingExpression(UCTextField.ValueProperty);
            be.UpdateSource();
            be = ServerPort.GetBindingExpression(UCTextField.ValueProperty);
            be.UpdateSource();
            be = MazeRows.GetBindingExpression(UCTextField.ValueProperty);
            be.UpdateSource();
            be = MazeCols.GetBindingExpression(UCTextField.ValueProperty);
            be.UpdateSource();
        }
        /// <summary>
        /// Handles the Click event of the OkBtn control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void OkBtn_Click(object sender, RoutedEventArgs e)
        {
            this.BindingUpdateSource();
            this.svm.SaveSettings();
            MainWindow win = (MainWindow)Application.Current.MainWindow;
            win.Show();
            this.Close();
        }

        /// <summary>
        /// Handles the Click event of the CnclBtn control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="RoutedEventArgs"/> instance containing the event data.</param>
        private void CnclBtn_Click(object sender, RoutedEventArgs e)
        {
            MainWindow win = (MainWindow)Application.Current.MainWindow;
            win.Show();
            this.Close();
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
