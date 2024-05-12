
from Astar import Astar

way = [
    [0,0,0,0,0],
    [0,1,0,0,0],
    [1,1,1,1,0],
    [1,1,1,0,0],
    [0,0,0,0,0]
]
find = Astar((0,0), (0,4), way)
ret = find.find_way()
for i in ret:
    way[i.position[1]][i.position[0]] = "2"
for y in range(0,5):
    text = ""
    for x in range(0,5):
        text += str(way[y][x])
    print(text)
