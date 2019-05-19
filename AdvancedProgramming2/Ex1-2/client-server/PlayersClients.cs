using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// Class PlayersClients.
    /// handles the clients playing the game
    /// </summary>
    internal class PlayersClients
    {
        /// <summary>
        /// members
        /// </summary>
        private TcpClient creator;
        private TcpClient joinner;
        /// <summary>
        /// Gets or sets a value indicating whether this instance has tow players.
        /// </summary>
        /// <value><c>true</c> if this instance has tow players; otherwise, <c>false</c>.</value>
        public bool HasTowPlayers
        {
            get; set;
        }

        /// <summary>
        /// constructor
        /// Initializesthe members of the class.
        /// </summary>
        /// <param name="client">The client.</param>
        public PlayersClients(TcpClient client)
        {
            this.creator = client;
            this.joinner = null;
            this.HasTowPlayers = false;
        }

        /// <summary>
        /// Adds the player to a game.
        /// </summary>
        /// <param name="joinner">The joinner.</param>
        public void AddPlayer(TcpClient joinner)
        {
            this.joinner = joinner;
            this.HasTowPlayers = true;
        }

        /// <summary>
        /// Gets the competitor.
        /// </summary>
        /// <param name="client">The client.</param>
        /// <returns>TcpClient.</returns>
        public TcpClient GetCompetitor(TcpClient client)
        {
            if (client == this.creator)
            {
                return this.joinner;
            }
            if (client == this.joinner)
            {
                return this.creator;
            }
            return null;
        }

        /// <summary>
        /// Determines whether the client is joining the game or the creator of one
        /// </summary>
        /// <param name="client">The client.</param>
        /// <returns><c>true</c> if the client is the creatorj/joins; otherwise, <c>false</c>.</returns>
        public bool HasPlayerClient(TcpClient client)
        {
            return client == this.creator || client == this.joinner;
        }
    }
}