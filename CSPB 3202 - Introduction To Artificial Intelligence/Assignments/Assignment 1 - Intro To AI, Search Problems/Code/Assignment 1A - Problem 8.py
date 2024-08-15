import numpy as np

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