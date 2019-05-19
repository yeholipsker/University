
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using System.Web.Http.Description;
using Ex3.Models;
using System.Security.Cryptography;
using System.Text;

namespace Ex3.Controllers
{
    /// <summary>
    /// Class RegistryController.
    /// </summary>
    /// <seealso cref="System.Web.Http.ApiController" />
    public class RegistryController : ApiController
    {
        /// <summary>
        /// The database
        /// </summary>
        private Ex3Context db = new Ex3Context();

        // GET: api/Registry
        /// <summary>
        /// Gets the registry models.
        /// </summary>
        /// <returns>IQueryable&lt;RegistryModel&gt;.</returns>
        public IQueryable<RegistryModel> GetRegistryModels()
        {
            return db.RegistryModels;
        }

        // GET: api/Registry/5
        /// <summary>
        /// Gets the registry model.
        /// </summary>
        /// <param name="UserName">Name of the user.</param>
        /// <returns>IHttpActionResult.</returns>
        [ActionName("GetUserName")]
        public IHttpActionResult GetRegistryModel(string UserName)
        {
            string[] arr = UserName.Split(' ');
            string usern = arr[0];
            string password = arr[1];
            RegistryModel player = db.RegistryModels.SingleOrDefault(user => user.UserName == usern);
            if (player == null)
            {
                return NotFound();
            }
            if (ComputeHash(password) != player.Password)
            {
                return NotFound();
            }

            return Ok(player);
        }

        // GET: api/Registry/SetRank/username/update/0
        /// <summary>
        /// Gets the registr model.
        /// </summary>
        /// <param name="Username">The username.</param>
        /// <param name="update">The update.</param>
        /// <returns>IEnumerable&lt;RegistryModel&gt;.</returns>
        [ActionName("SetRank")]
        public IEnumerable<RegistryModel> GetRegistrModel(string Username,string update)
        {

            RegistryModel player = db.RegistryModels.SingleOrDefault(user => user.UserName == Username);
            if (update == "Win")
            {
                player.Wins += 1;
            }
            else { player.Loses+= 1; }
            db.SaveChanges();
            return db.RegistryModels.Where(m => m.UserName == Username);
        }

        // PUT: api/Registry/5
        /// <summary>
        /// Puts the registry model.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="registryModel">The registry model.</param>
        /// <returns>IHttpActionResult.</returns>
        [ResponseType(typeof(void))]
        public IHttpActionResult PutRegistryModel(int id, RegistryModel registryModel)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }

            if (id != registryModel.Id)
            {
                return BadRequest();
            }

            db.Entry(registryModel).State = EntityState.Modified;

            try
            {
                db.SaveChanges();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!RegistryModelExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return StatusCode(HttpStatusCode.NoContent);
        }

        // POST: api/Registry
        /// <summary>
        /// Posts the registry model.
        /// </summary>
        /// <param name="registryModel">The registry model.</param>
        /// <returns>IHttpActionResult.</returns>
        /// <exception cref="DbUpdateException"></exception>
        [ResponseType(typeof(RegistryModel))]
        public IHttpActionResult PostRegistryModel(RegistryModel registryModel)
        {
            if (!ModelState.IsValid)
            {
                return BadRequest(ModelState);
            }
            registryModel.Password = ComputeHash(registryModel.Password);
            
            try
            {
                if (db.RegistryModels.Where(m => m.UserName == registryModel.UserName).Any() )
                {

                    throw new DbUpdateException();
                }
                db.RegistryModels.Add(registryModel);
                db.SaveChanges();

            }
            catch (DbUpdateException)
            {
                return Conflict();
            }
                

            return CreatedAtRoute("DefaultApi", new { id = registryModel.Id }, registryModel);
        }

        // DELETE: api/Registry/5
        /// <summary>
        /// Deletes the registry model.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns>IHttpActionResult.</returns>
        [ResponseType(typeof(RegistryModel))]
        public IHttpActionResult DeleteRegistryModel(int id)
        {
            RegistryModel registryModel = db.RegistryModels.Find(id);
            if (registryModel == null)
            {
                return NotFound();
            }

            db.RegistryModels.Remove(registryModel);
            db.SaveChanges();

            return Ok(registryModel);
        }

        /// <summary>
        /// Releases the unmanaged resources that are used by the object and, optionally, releases the managed resources.
        /// </summary>
        /// <param name="disposing">true to release both managed and unmanaged resources; false to release only unmanaged resources.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                db.Dispose();
            }
            base.Dispose(disposing);
        }

        /// <summary>
        /// Registries the model exists.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        private bool RegistryModelExists(int id)
        {
            return db.RegistryModels.Count(e => e.Id == id) > 0;
        }

        /// <summary>
        /// Computes the hash.
        /// </summary>
        /// <param name="input">The input.</param>
        /// <returns>System.String.</returns>
        private string ComputeHash(string input)
        {
            SHA1 sha = SHA1.Create();
            byte[] buffer = Encoding.ASCII.GetBytes(input);
            byte[] hash = sha.ComputeHash(buffer);
            string hash64 = Convert.ToBase64String(hash);
            return hash64;
        }
    }
}