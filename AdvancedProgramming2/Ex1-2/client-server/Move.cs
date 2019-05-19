using Newtonsoft.Json.Linq;
using System;
using System.IO;
using System.Net.Sockets;

namespace client_server
{
    /// <summary>
    /// Class Move.
    /// handels the movement in game
    /// </summary>
    class Move
    {
        /// <summary>
        /// members
        /// </summary>
        private string gameName;
        private TcpClient competitorClient;
        private string direction;

        /// <summary>
        /// constructor
        /// Initializes the members of Move
        /// </summary>
        /// <param name="gameName">Name of the game.</param>
        /// <param name="competitorClient">The competitor client.</param>
        /// <param name="direction">The direction.</param>
        public Move(string gameName, TcpClient competitorClient, string direction)
        {
            this.gameName = gameName;
            this.competitorClient = competitorClient;
            this.direction = direction;
        }

        /// <summary>
        /// Sends a message to the competitor.
        /// </summary>
        public void SendToCompetitor()
        {
            NetworkStream stream = this.competitorClient.GetStream();
            BinaryWriter writer = new BinaryWriter(stream);
            writer.Write(this.ToJSON());
        }

        /// <summary>
        /// for using json.
        /// </summary>
        /// <returns>System.String.</returns>
        public string ToJSON()
        {
            JObject moveObj = new JObject();
            moveObj["Name"] = this.gameName;
            moveObj["Direction"] = this.direction;
            return moveObj.ToString();
        }
    }
}