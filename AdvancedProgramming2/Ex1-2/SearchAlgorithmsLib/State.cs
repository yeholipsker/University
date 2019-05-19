using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SearchAlgorithmsLib
{/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
    public class State<T>
    {
        /// <summary>
        /// members
        /// </summary>
        private T state;
        private float cost;
        private State<T> cameFrom; 

        public T StateElement
        {
            get { return this.state; }
        }
        /// <summary>
        /// geting/seting cost of state
        /// </summary>
        public float Cost
        {
            get { return this.cost; }
            set { this.cost = value; }
        }
        /// <summary>
        /// geting/seting parrent of state
        /// </summary>
        public State<T> CameFrom
        {
            get { return this.cameFrom; }
            set { this.cameFrom = value; }
        }
        /// <summary>
        /// constructor
        /// </summary>
        /// <param name="state"></param>
        public State(T state)
        {
            this.state = state;
            this.cameFrom = null;
        }
        /// <summary>
        /// checks if equal
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        public bool Equals(State<T> s)
        {
            return state.Equals(s.state);
        }
        /// <summary>
        /// 
        /// </summary>
        public static class StatePool
        {
            static Dictionary<T, State<T>> dictionary = new Dictionary<T, State<T>>();
            public static State<T> GetState(T state)
            {
                if (dictionary.ContainsKey(state))
                {
                    return dictionary[state];
                }
                else
                {
                    State<T> newState = new State<T>(state);
                    dictionary[state] = newState;
                    return newState;
                }
            }
            /// <summary>
            /// deletes the dictionary
            /// </summary>
            public static void BackToNull()
            {
                dictionary.Clear();
            }
        }
    }
}
