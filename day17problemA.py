s = """..........###########........................
..........#.........#........................
..........#.........#.......#########........
..........#.........#.......#.......#........
..........#.........#.......#.......#........
..........#.........#.......#.......#........
..........#.........#.......#.......#........
..........#.........#.......#.......#........
..........#########.#############...#........
..................#.........#...#...#........
............###########.....#.#########......
............#.....#...#.....#.#.#...#.#......
............#.....#...#.....#.#.#...#.#......
............#.....#...#.....#.#.#...#.#......
............#.....#.^########.#.#...#########
............#.....#...#.......#.#.....#.....#
..........#########...#.#########.....#.....#
..........#.#.........#.#.....#.......#.....#
#############.........#########.......#.....#
#.........#.............#.............#.....#
#.......#########.......#.............#.....#
#.......#.#.....#.......#...................#
#.......#.#.....#.......#...................#
#.......#.#.....#.......#...................#
#.......#.#############.#.......#############
#.......#.......#.....#.#.......#............
#.......#.......#.....#.#.......#............
#.......#.......#.....#.#.......#............
#########.......#########.......#............
......................#.........#............
......................#.........#............
......................#.........#............
......................###########............"""

s = s.split("\n")
print(s)

def allNeighbors(a, x, y):
    b = True
    b = b and (a[y-1][x] == "#")
    b = b and (a[y+1][x] == "#")
    b = b and (a[y][x-1] == "#")
    b = b and (a[y][x+1] == "#")
    return b

totalAlignment = 0
for y in range(1, len(s)-1):
    for x in range(1, len(s[0])-1):
        if (s[y][x] == "#") and allNeighbors(s, x, y):
            totalAlignment += x*y

print(totalAlignment)
