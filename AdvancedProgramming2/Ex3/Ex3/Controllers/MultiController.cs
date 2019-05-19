
using Ex3.Models;
using MazeLib;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using System.Web.Http.Description;

namespace Ex3.Controllers
{
    /// <summary>
    /// Class MultiController.
    /// </summary>
    /// <seealso cref="System.Web.Http.ApiController" />
    public class MultiController : ApiController
    {
        /// <summary>
        /// The single model
        /// </summary>
        private SingleModel singleModel = new SingleModel();

        // GET: api/Multi/5
        /// <summary>
        /// Gets the specified game.
        /// </summary>
        /// <param name="game">The game.</param>
        /// <returns>JObject.</returns>
        public JObject Get(string game)
        {
            return JObject.Parse(singleModel.GetGames(game).ToJSON());
        }

        // POST: api/Multi
        /// <summary>
        /// Posts the game.
        /// </summary>
        /// <param name="maze">The maze.</param>
        /// <returns>JObject.</returns>
        public JObject PostGame(MazeInfo maze)
        {
            Maze retMaze = singleModel.GenerateGame(maze.Name, maze.Rows, maze.Cols);
            JObject obj = JObject.Parse(retMaze.ToJSON());
            return obj;
        }

        // PUT: api/Multi/5
        /// <summary>
        /// Puts the specified identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="value">The value.</param>
        public void Put(int id, [FromBody]string value)
        {
        }

        // DELETE: api/Multi/5
        /// <summary>
        /// Deletes the specified identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        public void Delete(int id)
        {
        }
    }
}
