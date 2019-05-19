using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SearchAlgorithmsLib
{
    /// <summary>
    /// interface of the expected common functionality to any searchable class
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public interface ISearchable<T>
    {
        /// <summary>
        /// gets start of path
        /// </summary>
        /// <returns></returns>
        State<T> getInitialState();
        /// <summary>
        /// gets end of path
        /// </summary>
        /// <returns></returns>
        State<T> getGoalState();
        /// <summary>
        /// gets all possible states
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        List<State<T>> getAllPossibleStates(State<T> s);
    }
}
