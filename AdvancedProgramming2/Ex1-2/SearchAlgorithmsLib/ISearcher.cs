using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SearchAlgorithmsLib
{
    /// <summary>
    /// interface of the expected common functionality to any searcher
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public interface ISearcher<T>
    {
        /// <summary>
        /// the search method
        /// </summary>
        /// <param name="searchable"></param>
        /// <returns></returns>
        Solution<T> Search(ISearchable<T> searchable);

        /// <summary>
        ///  get how many nodes were evaluated by the algorithm
        /// </summary>
        int GetNumberOfNodesEvaluated();
    }
}
