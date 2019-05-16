# Author - Yehoshua Lipsker


# Class - State. creates state of the puzzle board. consists of the board
# size, state list, path to this state and calculates manhattan distance
class State:
    def __init__(self, row_size, state_list, path):
        state_list = list(map(int, state_list))
        self.rowSize = row_size
        self.state_list = state_list
        self.boardSize = row_size * row_size
        self.emptyIndex = state_list.index(0)
        self.path = path
        self.manhattan_distance = self.calculate_manhattan_distance()

    # Method returns successors list in the order - up, down, left, right
    def successors(self):
        successors_list = []
        up_index = self.emptyIndex + self.rowSize
        down_index = self.emptyIndex - self.rowSize
        left_index = self.emptyIndex + 1
        right_index = self.emptyIndex - 1
        if up_index < self.boardSize:
            up_list = self.state_list[:]
            up_list[self.emptyIndex] = up_list[up_index]
            up_list[up_index] = 0
            successors_list.append(State(self.rowSize, up_list, self.path + 'U'))
        if down_index >= 0:
            down_list = self.state_list[:]
            down_list[self.emptyIndex] = down_list[down_index]
            down_list[down_index] = 0
            successors_list.append(State(self.rowSize, down_list, self.path + 'D'))
        if left_index % self.rowSize != 0:
            left_list = self.state_list[:]
            left_list[self.emptyIndex] = left_list[left_index]
            left_list[left_index] = 0
            successors_list.append(State(self.rowSize, left_list, self.path + 'L'))
        if right_index % self.rowSize != self.rowSize - 1:
            right_list = self.state_list[:]
            right_list[self.emptyIndex] = right_list[right_index]
            right_list[right_index] = 0
            successors_list.append(State(self.rowSize, right_list, self.path + 'R'))
        return successors_list

    # Method checks if this state equals to the goal state
    def is_goal_state(self):
        if self.state_list[self.boardSize - 1] != 0:
            return False
        for i in range(self.boardSize - 1):
            if i + 1 != self.state_list[i]:
                return False
        return True

    # Method calculates manhattan distance
    def calculate_manhattan_distance(self):
        manhattan_value = 0
        for i, state in enumerate(self.state_list):
            if state != 0:
                manhattan_value += (abs((state - 1) % self.rowSize - i % self.rowSize)
                                    + abs(int((state - 1) / self.rowSize) - int(i / self.rowSize)))
        return manhattan_value


# Function searching goal state in dfs algorithm using stack
def dfs(initial_state, depth):
    open_list = [initial_state]
    opened = 0
    while open_list:
        current_state = open_list.pop()
        opened += 1
        if current_state.is_goal_state():
            return current_state, opened
        if len(current_state.path) < depth:
            list_of_successors = current_state.successors()
            list_of_successors.reverse()
            open_list = open_list + list_of_successors
    return None, 0

# Function searching goal state in ids algorithm by calling dfs with different depths
def search_ids(initial_state):
    depth = 0
    while True:
        solution_state, opened = dfs(initial_state, depth)
        if solution_state is not None:
            break
        depth += 1
    return solution_state, opened, depth


# Function searching goal state in bfs algorithm using queue
def search_bfs(initial_state):
    open_list = [initial_state]
    opened = 0
    while open_list:
        current_state = open_list.pop(0)
        opened += 1
        if current_state.is_goal_state():
            return current_state, opened, 0
        open_list = open_list + current_state.successors()
    return None, 0, 0


# Function gets list of states and calculates fn to get the minimum value
def calculate_priority(open_list):
    min_index = 0
    min_hn = len(open_list[min_index].path) + open_list[min_index].manhattan_distance
    for i, state in enumerate(open_list):
        hn = len(state.path) + state.manhattan_distance
        if hn < min_hn:
            min_hn = hn
            min_index = i
    return min_index


# Function searching goal state in bfs algorithm using priority queue
def search_astar(initial_state):
    open_list = [initial_state]
    opened = 0
    while open_list:
        i = calculate_priority(open_list)
        current_state = open_list.pop(i)
        opened += 1
        print("out="+str(opened)+",open list size="+str(len(open_list)))
        if current_state.is_goal_state():
            return current_state, opened, len(current_state.path)
        open_list = open_list + current_state.successors()
    return None, 0, 0


# Main function - reads input, search and write to output file
def main():
    demo = State(3,[5,4,0,6,1,8,7,3,2],'')
    with open('input.txt', 'r') as f:
        lines = f.readlines()
        algorithm_id = int(lines[0])
        row_size = int(lines[1])
        initial_state = State(row_size,lines[2].split('-'), '')
        solution_state = initial_state
        opened = 0
        x = 0
    if algorithm_id is 1:
        solution_state, opened, x = search_ids(initial_state)
    elif algorithm_id is 2:
        solution_state, opened, x = search_bfs(initial_state)
    elif algorithm_id is 3:
        solution_state, opened, x = search_astar(initial_state)
    with open('output.txt', 'w') as f:
        f.write(solution_state.path + ' ' + str(opened) + ' ' + str(x))


if __name__ == "__main__":
    main()
