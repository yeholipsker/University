using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SearchAlgorithmsLib
{/// <summary>
/// algorithm: best first search
/// </summary>
/// <typeparam name="T"></typeparam>
    public class BFS<T> : Searcher<T>
    {
    /// <summary>
    /// implementing the search as need to be done by bfs algorithm
    /// </summary>
    /// <param name="searchable"></param>
    /// <returns></returns>
        public override Solution<T> Search(ISearchable<T> searchable)
        {
            Reset();
            State<T> initial = searchable.getInitialState();
            State<T> goal = searchable.getGoalState();
            initial.Cost = 0;
            AddToOpenList(initial);
            HashSet<State<T>> closed = new HashSet<State<T>>();
            while (OpenListSize != 0)
            {
                State<T> n = PopOpenList();
                closed.Add(n);
                if (n.Equals(goal))
                {
                    return BackTrace(n, initial);
                }
                List<State<T>> succerssors = searchable.getAllPossibleStates(n);
                foreach(State<T> state in succerssors)
                {
                    if(!closed.Contains(state) && !openList.Contains(state))
                    {
                        state.Cost = n.Cost + 1;
                        state.CameFrom = n;
                        AddToOpenList(state);
                    }
                    else
                    {
                        if(state.Cost > n.Cost + 1)
                        {
                            state.Cost = n.Cost + 1;
                            if (!openList.Contains(state))
                            {
                                AddToOpenList(state);
                            }
                            else
                            {
                                openList.UpdatePriority(state, state.Cost);
                            }
                        }
                    }
                }
            }
                return null;
        }
        /// <summary>
        /// resets members of bfs
        /// </summary>
        private void Reset()
        {
            this.openList.Clear();
            this.evaluatedNodes = 0;
            State<T>.StatePool.BackToNull();
        }
    }
}
