using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Settings
{
    /// <summary>
    /// Class SettingsViewModel.
    /// </summary>
    /// <seealso cref="Settings.ViewModel" />
    class SettingsViewModel : ViewModel
    {
        /// <summary>
        /// The model
        /// </summary>
        private ISettingsModel model;
        /// <summary>
        /// Initializes a new instance of the <see cref="SettingsViewModel"/> class.
        /// </summary>
        public SettingsViewModel()
        {
            this.model = new ApplicationSettingsModel();
        }
        /// <summary>
        /// Gets or sets the server ip.
        /// </summary>
        /// <value>The server ip.</value>
        public string ServerIP
        {
            get { return model.ServerIP; }
            set { model.ServerIP = value; }
        }
        /// <summary>
        /// Gets or sets the server port.
        /// </summary>
        /// <value>The server port.</value>
        public int ServerPort
        {
            get { return model.ServerPort; }
            set { model.ServerPort = value; }
        }
        /// <summary>
        /// Gets or sets the maze rows.
        /// </summary>
        /// <value>The maze rows.</value>
        public int MazeRows
        {
            get { return model.MazeRows; }
            set { model.MazeRows = value; }
        }
        /// <summary>
        /// Gets or sets the maze cols.
        /// </summary>
        /// <value>The maze cols.</value>
        public int MazeCols
        {
            get { return model.MazeCols; }
            set { model.MazeCols = value; }
        }
        /// <summary>
        /// Gets or sets the search algorithm.
        /// </summary>
        /// <value>The search algorithm.</value>
        public int SearchAlgorithm
        {
            get { return model.SearchAlgorithm; }
            set { model.SearchAlgorithm = value; }
        }
        /// <summary>
        /// Saves the settings.
        /// </summary>
        public void SaveSettings()
        {
            model.SaveSettings();
        }
    }
}
