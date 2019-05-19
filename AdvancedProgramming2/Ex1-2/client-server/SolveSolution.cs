using MazeLib;
using Newtonsoft.Json.Linq;
using SearchAlgorithmsLib;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace client_server
{
    /// <summary>
    /// Class SolveSolution.
    /// </summary>
    class SolveSolution
    {
        /// <summary>
        /// members
        /// </summary>
        private string name;
        private Solution<Position> solution;
        private List<int> directions;
        private int nodesEvaluated;

        /// <summary>
        /// constructor
        /// Initializes the members of the class.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="solution">The solution.</param>
        /// <param name="nodesEvaluated">The nodes evaluated.</param>
        public SolveSolution(string name, Solution<Position> solution, int nodesEvaluated)
        {
            this.name = name;
            this.solution = solution;
            this.directions = new List<int>();
            this.nodesEvaluated = nodesEvaluated;
        }

        /// <summary>
        /// converts to json.
        /// </summary>
        /// <returns>System.String.</returns>
        public string ToJSON()
        {
            JObject mazeObj = new JObject();
            mazeObj["Name"] = this.name;
            mazeObj["Solution"] = ConvertSolution();
            mazeObj["NodesEvaluated"] = this.nodesEvaluated.ToString();
            return mazeObj.ToString();
        }

        /// <summary>
        /// Converts the solution.
        /// adss the directions to a list
        /// </summary>
        /// <returns>string with directions for the path.</returns>
        private string ConvertSolution()
        {
            for(int i = 0; i < this.solution.GetSize() - 1; i++)
            {
                int tCol = this.solution.SolList[i].StateElement.Col;
                int tRow = this.solution.SolList[i].StateElement.Row;
                int nCol = this.solution.SolList[i + 1].StateElement.Col;
                int nRow = this.solution.SolList[i + 1].StateElement.Row;
                if (tCol == nCol && tRow > nRow) //up 2
                {
                    this.directions.Add(2);
                }
                if (tCol < nCol && tRow == nRow) //right 1
                {
                    this.directions.Add(1);
                }
                if (tCol > nCol && tRow == nRow) //left 0
                {
                    this.directions.Add(0);
                }
                if (tCol == nCol && tRow < nRow) //down 3                               
                {
                    this.directions.Add(3);
                }
            }
            return string.Join("", this.directions.ToArray());

        }
    }
}
