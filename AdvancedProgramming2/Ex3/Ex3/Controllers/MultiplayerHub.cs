
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Microsoft.AspNet.SignalR;
using System.Collections.Concurrent;
using Ex3.Models;
using MazeLib;
using Newtonsoft.Json.Linq;

namespace Ex3.Controllers
{
    /// <summary>
    /// Class MultiplayerHub.
    /// </summary>
    /// <seealso cref="Microsoft.AspNet.SignalR.Hub" />
    public class MultiplayerHub : Hub
    {
        /// <summary>
        /// The database
        /// </summary>
        private Ex3Context db = new Ex3Context();
        /// <summary>
        /// The connected users
        /// </summary>
        private static ConcurrentDictionary<string, string> connectedUsers =
             new ConcurrentDictionary<string, string>();
        /// <summary>
        /// The game generator
        /// </summary>
        private static ConcurrentDictionary<string, String> gameGenerator =
             new ConcurrentDictionary<string, string>();
        /// <summary>
        /// The games
        /// </summary>
        public static List<string> games = new List<string>();

        /// <summary>
        /// The model
        /// </summary>
        private SingleModel model = new SingleModel();
        /// <summary>
        /// Connects the specified user name.
        /// </summary>
        /// <param name="UserName">Name of the user.</param>
        public void Connect(string UserName)
        {
            
            connectedUsers[UserName] = Context.ConnectionId;
            SendGames();
        }


        /// <summary>
        /// Generates the game.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="username">The username.</param>
        /// <param name="rows">The rows.</param>
        /// <param name="columns">The columns.</param>
        public void GenerateGame(string name,string username, int rows, int columns)
        {
            model.GenerateGame(name, rows, columns);
            gameGenerator[name] = username;
            games.Add(name);
            SendGames();
            
        }
        /// <summary>
        /// Joins the game.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="username">The username.</param>
        public void JoinGame(string name, string username) {

            string rival = gameGenerator[name];
            string recipientId = connectedUsers[username];
            if (recipientId == null)
                return;
            string otherRecipientId = connectedUsers[rival];
            if (recipientId == null)
                return;
            Maze maze = model.GetGames(name);
            JObject obj = JObject.Parse(maze.ToJSON());
            Clients.Client(otherRecipientId).gotMaze(obj, username);
            Clients.Client(recipientId).gotMaze(obj, rival);
            games.Remove(name);
            model.DeleteGame(name);
            SendGames();
            Clients.Client(otherRecipientId).start(username);
            Clients.Client(recipientId).start(rival);
        }
        /// <summary>
        /// Gets the games.
        /// </summary>
        /// <param name="user">The user.</param>
        public void GetGames(string user)
        {
            string recipientId = connectedUsers[user];
            if (recipientId == null)
                return;

            JObject obj = new JObject();
            obj["games"] = JToken.FromObject(games);
            Clients.Client(recipientId).gotGames(obj);
        }


        /// <summary>
        /// Sends the games.
        /// </summary>
        public void SendGames()
        {
            JObject obj = new JObject();
            obj["games"] = JToken.FromObject(games);
            Clients.All.gotGames(obj);

        }
        /// <summary>
        /// Moves the specified user.
        /// </summary>
        /// <param name="user">The user.</param>
        /// <param name="text">The text.</param>
        public void Move(string user, string text)
        {
            string recipientId = connectedUsers[user];
            if (recipientId == null)
                return;
            Clients.Client(recipientId).move(text);
        }
    }
    
}