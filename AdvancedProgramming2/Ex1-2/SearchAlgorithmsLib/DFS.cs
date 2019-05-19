using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SearchAlgorithmsLib
{/// <summary>
/// algorithm: depth first search
/// </summary>
/// <typeparam name="T"></typeparam>
    public class DFS<T> : Searcher<T>
    {
        /// <summary>
        /// implementing the search as need to be done by dfs algorithm
        /// </summary>
        /// <param name="searchable"></param>
        /// <returns></returns>
        public override Solution<T> Search(ISearchable<T> searchable)
        {
            Reset();
            State<T> curState, initial = searchable.getInitialState();
            Stack<State<T>> stack = new Stack<State<T>>();
            initial.Cost = 0;
            stack.Push(initial);
            while(stack.Count != 0)
            {
                curState = stack.Pop();
                this.evaluatedNodes++;
                if(curState.Equals(searchable.getGoalState()))
                {
                    return BackTrace(curState,initial);
                }
                List<State<T>> succerssors = searchable.getAllPossibleStates(curState);
                foreach(State<T> state in succerssors)
                {
                    if(state.CameFrom == null && !state.Equals(initial) && !state.Equals(curState))
                    {
                        stack.Push(state);
                        state.CameFrom = curState;
                    }
                    
                }
            }
            return null;
        }
        /// <summary>
        /// resets members of dfs
        /// </summary>
        private void Reset()
        {
            this.evaluatedNodes = 0;
            State<T>.StatePool.BackToNull();
        }
    }
}
