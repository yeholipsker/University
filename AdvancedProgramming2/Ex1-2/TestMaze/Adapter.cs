using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MazeLib;
using SearchAlgorithmsLib;

namespace TestMaze
{
    /// <summary>
    /// class adapter inherits from ISearchable
    /// </summary>
    public class Adapter : ISearchable<Position>
    {
        /// <summary>
        /// member
        /// </summary>
        private Maze maze;
        /// <summary>
        /// constructor
        /// Initializes maze
        /// </summary>
        /// <param name="maze">The maze.</param>
        public Adapter(Maze maze)
        {
            this.maze = maze;
        }
        /// <summary>
        /// gets all the possible states for path
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        public List<State<Position>> getAllPossibleStates(State<Position> s)
        {
            /// <summary>
            /// members
            /// </summary>
            State<Position> newState;
            int row = s.StateElement.Row, col = s.StateElement.Col;
            List<State<Position>> successors = new List<State<Position>>();
            if (col - 1 >= 0)
            {
                if(maze[row, col - 1] == CellType.Free)
                {
                    newState = State<Position>.StatePool.GetState(new Position(row, col - 1));
                    successors.Add(newState);
                }
            }
            if (row - 1 >= 0)
            {
                if(maze[row - 1, col] == CellType.Free)
                {
                    newState = State<Position>.StatePool.GetState(new Position(row - 1, col));
                    successors.Add(newState);
                }
            }

            if (col + 1 < this.maze.Cols)
            {
                if(maze[row, col + 1] == CellType.Free)
                {
                    newState = State<Position>.StatePool.GetState(new Position(row, col + 1));
                    successors.Add(newState);
                }
            }
            if (row + 1 < this.maze.Rows)
            {
                if (maze[row + 1, col] == CellType.Free)
                {
                    newState = State<Position>.StatePool.GetState(new Position(row + 1, col));
                    successors.Add(newState);
                }
            }
            return successors;
        }

        /// <summary>
        /// gets the last state in path
        /// </summary>
        /// <returns></returns>
        public State<Position> getGoalState()
        {
            return State<Position>.StatePool.GetState(maze.GoalPos);
        }
        /// <summary>
        /// gets the first state in path
        /// </summary>
        /// <returns></returns>
        public State<Position> getInitialState()
        {
            return State<Position>.StatePool.GetState(maze.InitialPos);
        }
    }
}
