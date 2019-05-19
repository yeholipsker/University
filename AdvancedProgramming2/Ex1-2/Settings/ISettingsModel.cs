namespace Settings
{
    /// <summary>
    /// Interface ISettingsModel
    /// </summary>
    interface ISettingsModel
    {
        /// <summary>
        /// Gets or sets the server ip.
        /// </summary>
        /// <value>The server ip.</value>
        string ServerIP { get; set; }
        /// <summary>
        /// Gets or sets the server port.
        /// </summary>
        /// <value>The server port.</value>
        int ServerPort { get; set; }
        /// <summary>
        /// Gets or sets the maze rows.
        /// </summary>
        /// <value>The maze rows.</value>
        int MazeRows { get; set; }
        /// <summary>
        /// Gets or sets the maze cols.
        /// </summary>
        /// <value>The maze cols.</value>
        int MazeCols { get; set; }
        /// <summary>
        /// Gets or sets the search algorithm.
        /// </summary>
        /// <value>The search algorithm.</value>
        int SearchAlgorithm { get; set; }

        /// <summary>
        /// Saves the settings.
        /// </summary>
        void SaveSettings();
    }
}