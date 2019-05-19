
using Ex3.Models;
using MazeLib;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace Ex3.Controllers
{
    /// <summary>
    /// Class SingleController.
    /// </summary>
    /// <seealso cref="System.Web.Http.ApiController" />
    public class SingleController : ApiController
    {
        /// <summary>
        /// The single model
        /// </summary>
        private SingleModel singleModel = new SingleModel();
        // GET: api/Single
        /// <summary>
        /// Gets this instance.
        /// </summary>
        /// <returns>IEnumerable&lt;System.String&gt;.</returns>
        public IEnumerable<string> Get()
        {
            return new string[] { "value1", "value2" };
        }

        // GET: api/Single/name/rows/cols
        /// <summary>
        /// Gets the maze.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="rows">The rows.</param>
        /// <param name="cols">The cols.</param>
        /// <returns>JObject.</returns>
        public JObject GetMaze(string name, int rows, int cols)
        {
            Maze maze = singleModel.GenerateMaze(name, rows, cols);
            JObject obj = JObject.Parse(maze.ToJSON());
            return obj;
        }

        // GET: api/Single/name/rows/cols
        /// <summary>
        /// Gets the sol.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="algo">The algo.</param>
        /// <returns>JObject.</returns>
        public JObject GetSol(string name, int algo)
        {
            JObject obj = JObject.Parse(singleModel.Solve(name, algo));
            return obj;
        }

        // POST: api/Single
        /// <summary>
        /// Posts the specified value.
        /// </summary>
        /// <param name="value">The value.</param>
        public void Post([FromBody]string value)
        {
        }

        // PUT: api/Single/5
        /// <summary>
        /// Puts the specified identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="value">The value.</param>
        public void Put(int id, [FromBody]string value)
        {
        }

        // DELETE: api/Single/5
        /// <summary>
        /// Deletes the specified identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        public void Delete(int id)
        {
        }
    }
}
