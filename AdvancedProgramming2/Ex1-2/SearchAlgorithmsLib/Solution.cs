using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SearchAlgorithmsLib
{
    /// <summary>
    /// class for keeping and chacking path got from algorithm
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class Solution<T>
    {
    /// <summary>
    /// members
    /// </summary>
        private List<State<T>> solList;
        public List<State<T>> SolList
        {
            get { return this.solList; }
            set { this.solList = value; }
        }
        /// <summary>
        /// gets size of state
        /// </summary>
        /// <returns></returns>
        public int GetSize()
        {
            return this.solList.Count;
        }
    }
}
