class Node:

    def __init__(self, position, parent=None):
        self.position = position
        self.parent = parent
        self.g = 0
        self.h = 0
        self.f = 0

    position = ()
    def __eq__(self, other):
        return self.position == other.position


    def __lt__(self, other):
        return self.f < other.f
class Astar:
    def __init__(self, start: tuple, end: tuple, grid: list):
        self.a = start
        self.b = end
        self.grid = grid

    def build_path(self, current: Node):
        path = []
        while(current):
            path.append(current)
            current = current.parent
        return path

    def find_way(self) -> list:
        start = Node(self.a)
        end = Node(self.b)
        reachable = [start]
        explored = []
        while reachable:
            current = reachable.pop()
            print(f"Current: {current.position}")
            if(current == end):
                return self.build_path(current)
            explored.append(current)
            text = "Check neighbors: "
            for y in range(-1, 2):
                for x in range(-1, 2):
                    if((x == 0 and y == 0) or x == y): continue
                    neighbor_position = (current.position[0] + x, current.position[1] + y)
                    if(0 <= neighbor_position[0] < len(self.grid)) and (0 <= neighbor_position[1] < len(self.grid)):
                        # тупик
                        if(self.grid[neighbor_position[1]][neighbor_position[0]] == 1):
                            continue

                        neighbor_node = Node(neighbor_position, current)

                        if(neighbor_node in explored):
                            continue
                        text += f"Neighbor ({neighbor_position[0]},{neighbor_position[1]})={self.grid[neighbor_position[1]][neighbor_position[0]]} "
                        neighbor_node.g = current.g + 1
                        neighbor_node.h = ((neighbor_position[0] - end.position[0]) ** 2) + ((neighbor_position[1] - end.position[1]) ** 2)  # Euclidean distance as heuristic
                        neighbor_node.f = neighbor_node.g + neighbor_node.h
                        if neighbor_node not in reachable:
                            reachable.append(neighbor_node)
                        else:
                            for reachable_node in reachable:
                                if(reachable_node == neighbor_node) and reachable_node.f > neighbor_node.f:
                                    reachable_node = neighbor_node
                                    reachable.sort()
            print(text)

        return []




