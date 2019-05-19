
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Ex3.Models
{
    /// <summary>
    /// Class RegistryModel.
    /// </summary>
    public class RegistryModel
    {

        /// <summary>
        /// Gets or sets the identifier.
        /// </summary>
        /// <value>The identifier.</value>
        public int Id { get; set; }
        /// <summary>
        /// Gets or sets the name of the user.
        /// </summary>
        /// <value>The name of the user.</value>
        [Required]
        public String UserName { get; set; }
        /// <summary>
        /// Gets or sets the password.
        /// </summary>
        /// <value>The password.</value>
        [Required]
        public string Password { get; set; }
        /// <summary>
        /// Gets or sets the email.
        /// </summary>
        /// <value>The email.</value>
        [Required]
        public string Email { get; set; }

        /// <summary>
        /// Gets or sets the wins.
        /// </summary>
        /// <value>The wins.</value>
        public int Wins { get; set; }
        /// <summary>
        /// Gets or sets the loses.
        /// </summary>
        /// <value>The loses.</value>
        public int Loses { get; set; }
    } 
}
