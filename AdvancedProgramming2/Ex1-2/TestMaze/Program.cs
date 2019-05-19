using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MazeGeneratorLib;
using MazeLib;
using SearchAlgorithmsLib;

namespace TestMaze
{
    /********************************
    * Yehoshua Lipsker  204038533   *
    * Noam Spokoini 301291001       *
    * ex01                          *
    ********************************/
    /// <summary>
    /// the main program
    /// </summary>
    class Program
    {
        /// <summary>
        /// main function
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            CompareSolvers();
        }
        /// <summary>
        /// compares beween the diffrent algorithms and prints results of each one
        /// </summary>
        private static void CompareSolvers()
        {
            DFSMazeGenerator dfsGenerator = new DFSMazeGenerator();
            Maze maze = dfsGenerator.Generate(10,10);
            Console.WriteLine(maze.ToString());
            Adapter adapted = new Adapter(maze);
            ISearcher<Position> bfs = new BFS<Position>();
            bfs.Search(adapted);
            Console.WriteLine(bfs.GetNumberOfNodesEvaluated());
            ISearcher<Position> dfs = new DFS<Position>();
            dfs.Search(adapted);
            Console.WriteLine(dfs.GetNumberOfNodesEvaluated());
            Console.ReadKey();
        }
    }
}
