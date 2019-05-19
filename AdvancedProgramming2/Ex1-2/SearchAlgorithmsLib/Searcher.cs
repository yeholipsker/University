using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Priority_Queue;

namespace SearchAlgorithmsLib
{
    /// <summary>
    /// an abstruct class inheriting from the isearcher interface.
    /// implemence the methods that all algorithms share
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public abstract class Searcher<T> : ISearcher<T>
    {
        /// <summary>
        /// members
        /// </summary>
        protected SimplePriorityQueue<State<T>> openList;
        protected int evaluatedNodes;

        /// <summary>
        /// consructor
        /// </summary>
        public Searcher()
        {
            openList = new SimplePriorityQueue<State<T>>();
            evaluatedNodes = 0;
        }
        /// <summary>
        /// counts evaluated lists and removes them from queue
        /// </summary>
        /// <returns>
        /// queue without top
        /// </returns>
        protected State<T> PopOpenList()
        {
            this.evaluatedNodes++;
            return openList.Dequeue();
        }
        /// <summary>
        /// gets size of list
        /// </summary>
        public int OpenListSize
        {
            get {return openList.Count;}
        }

        /// <summary>
        /// implementing methods from isearcher interface.
        /// </summary>
        /// <returns>Number Of Nodes Evaluated</returns>
        public int GetNumberOfNodesEvaluated()
        {
            return this.evaluatedNodes;
        }
        /// <summary>
        /// the type of searcher for specific task
        /// </summary>
        /// <param name="searchable">the algorithm</param>
        /// <returns></returns>
            public abstract Solution<T> Search(ISearchable<T> searchable);
        /// <summary>
        /// adding to queue
        /// </summary>
        /// <param name="state"></param>
        public void AddToOpenList(State<T> state)
        {
            this.openList.Enqueue(state, state.Cost);
        }
        /// <summary>
        /// gives the list with the path found by the algorithm
        /// </summary>
        /// <param name="state">current place on path</param>
        /// <param name="initial">begining of path</param>
        /// <returns>the path</returns>
        public Solution<T> BackTrace(State<T> state, State<T> initial)
        {
            Solution<T> sol = new Solution<T>();
            List<State<T>> solList = new List<State<T>>();
            do
            {
                solList.Add(state);
                state = state.CameFrom;
            } while (!state.Equals(initial));
            solList.Add(initial);
            solList.Reverse();
            sol.SolList = solList;
            return sol;
        }
    }
}
