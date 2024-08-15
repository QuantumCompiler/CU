import numpy as np
from collections import OrderedDict
from collections import deque
maze = np.array([[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
                 [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
                 [1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1],
                 [1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
                 [1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
                 [1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1],
                 [1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1],
                 [1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1],
                 [1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1],
                 [1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1],
                 [1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1],
                 [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]])

map_distances = dict(
    chi=OrderedDict([("det",283), ("cle",345), ("ind",182)]),
    cle=OrderedDict([("chi",345), ("det",169), ("col",144), ("pit",134), ("buf",189)]),
    ind=OrderedDict([("chi",182), ("col",176)]),
    col=OrderedDict([("ind",176), ("cle",144), ("pit",185)]),
    det=OrderedDict([("chi",283), ("cle",169), ("buf",256)]),
    buf=OrderedDict([("det",256), ("cle",189), ("pit",215), ("syr",150)]),
    pit=OrderedDict([("col",185), ("cle",134), ("buf",215), ("phi",305), ("bal",247)]),
    syr=OrderedDict([("buf",150), ("phi",253), ("new",254), ("bos",312)]),
    bal=OrderedDict([("phi",101), ("pit",247)]),
    phi=OrderedDict([("pit",305), ("bal",101), ("syr",253), ("new",97)]),
    new=OrderedDict([("syr",254), ("phi",97), ("bos",215), ("pro",181)]),
    pro=OrderedDict([("bos",50), ("new",181)]),
    bos=OrderedDict([("pro",50), ("new",215), ("syr",312), ("por",107)]),
    por=OrderedDict([("bos",107)]))

map_times = dict(
    chi=dict(det=280, cle=345, ind=200),
    cle=dict(chi=345, det=170, col=155, pit=145, buf=185),
    ind=dict(chi=200, col=175),
    col=dict(ind=175, cle=155, pit=185),
    det=dict(chi=280, cle=170, buf=270),
    buf=dict(det=270, cle=185, pit=215, syr=145),
    pit=dict(col=185, cle=145, buf=215, phi=305, bal=255),
    syr=dict(buf=145, phi=245, new=260, bos=290),
    bal=dict(phi=145, pit=255),
    phi=dict(pit=305, bal=145, syr=245, new=150),
    new=dict(syr=260, phi=150, bos=270, pro=260),
    pro=dict(bos=90, new=260),
    bos=dict(pro=90, new=270, syr=290, por=120),
    por=dict(bos=120))

def path(previous, s): 
    '''
    `previous` is a dictionary chaining together the predecessor state that led to each state
    `s` will be None for the initial state
    otherwise, start from the last state `s` and recursively trace `previous` back to the initial state,
    constructing a list of states visited as we go
    '''
    if s is None:
        return []
    else:
        return path(previous, previous[s])+[s]

def pathcost(path, step_costs):
    '''
    add up the step costs along a path, which is assumed to be a list output from the `path` function above
    '''
    cost = 0
    for s in range(len(path)-1):
        cost += step_costs[path[s]][path[s+1]]
    return cost


""" depth_first - Performs a DFS on the state graph for the path between a start and goal
    Input:
        start - Node that represents the start of the path
        goal - Node that represents the desired end point of the path
        state_graph - Represents the graph that is being searched in
        return_cost - Boolean value that indicates the cost of the path
    Algorithm:
        * Create a stack of nodes with the start node as the original element in it
        * Create a set of visited nodes with the start node as the original element in it
        * Create a dictionary of previous nodes that is empty
        * While the stack is not empty
            * Pop the top most node from the stack
            * Check if that node is the goal
            * If it is
                * Update the path to the goal with the previous nodes and the goal
                * Return the path to goal and the cost if return_cost is set to true
                * Otherwise, just return the path
            * If it is not
                * Iterate over the neighbors of the current node
                * Add the neighbor to the visited set if it is not visited
                * Update the previous nodes with the current node
                * Add the neighbor to the stack
        * Return the path and cost, or just the path if designated
    Output:
        Returns the path in the search as well as the cost in the path
"""
def depth_first(start, goal, state_graph, return_cost=False):
    stack = [start]
    visited = set([start])
    previous = {start: None}
    while (stack):
        current = stack.pop()
        if (current == goal):
            path_to_goal = path(previous, goal)
            if (return_cost):
                cost = pathcost(path_to_goal, state_graph)
                return path_to_goal, cost
            else:
                return path_to_goal
        for neighbor in state_graph[current]:
            if (neighbor not in visited):
                visited.add(neighbor)
                previous[neighbor] = current
                stack.append(neighbor)
    return None if not return_cost else (None, 0)
	

# Solution:

""" maze_to_graph - Converts a maze represented as a numpy array into a graph
    Input:
        maze - 2D numpy array where 0 represents walkable cells and 1 represents walls
    Algorithm:
        * Initialize an empty dictionary to represent the graph
        * Define the directions for North, South, East, and West movements
        * Iterate over each cell in the maze
            * Initialize an empty dictionary for each cell in the graph
            * For each direction, calculate the neighboring cell's coordinates
            * Check if the neighboring cell is within the maze bounds and is walkable (contains 0)
                * If it is, add the neighbor to the current cell's dictionary in the graph with the direction as the value
    Output:
        Returns a dictionary representing the graph where keys are coordinates of cells and values are dictionaries
        of neighboring cells with directions
"""
def maze_to_graph(maze):
    ''' takes in a maze as a numpy array, converts to a graph '''
    graph = {}
    rows, cols = maze.shape
    directions = {
        'N': (1, 0),  # North
        'S': (-1, 0),   # South
        'E': (0, 1),   # East
        'W': (0, -1)   # West
    }
    for r in range(rows):
        for c in range(cols):
            graph[(c, r)] = {}
            for direction, (dr, dc) in directions.items():
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols and maze[nr, nc] == 0:
                    graph[(c, r)][(nc, nr)] = direction
    return graph