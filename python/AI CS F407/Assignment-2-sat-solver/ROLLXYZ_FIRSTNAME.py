#!/usr/bin/env python3
from Agent import *  # See the Agent.py file
from pysat.solvers import Glucose3
import time
import math
# All your code can go here.

# You can change the main function as you wish. Run this program to see the output. Also see Agent.py code.

kb = Glucose3()
ag = Agent()
validMoves = [[1, 0], [-1, 0], [0, -1], [0, 1]]

# grid = [[0 for i in range(4)] for i in range(4)]:

safe_set = set()
visited = set()

seen_set = set()

total_path = []


def find_neighbours(cur_loc):

    neighbours = []

    for x, y in validMoves:
        tempx = cur_loc[0] + x
        tempy = cur_loc[1] + y
        if (tempx < 1 or tempx > 4 or tempy < 1 or tempy > 4):
            continue
        neighbours.append(((tempy-1)*4+tempx))

    return neighbours


def convert(loc):
    return ((loc[1]-1)*4+loc[0])


def update_sets():
    visited.add(convert(ag.FindCurrentLocation()))

    neighbours = find_neighbours(ag.FindCurrentLocation())

    for i in neighbours:
        seen_set.add(i)

    to_remove = []
    for i in seen_set:
        if not kb.solve(assumptions=[i]):
            safe_set.add(i)
            to_remove.append(i)
    for i in to_remove:
        seen_set.remove(i)


def convert_back(loc):

    # if(loc<=4):
    #     return [loc,1]
    # if(loc>4 and loc<9):
    #     return [,2]

    return [(loc - 1) % 4+1, (loc - 1) // 4+1]


def move():

    path = []

    source = convert(ag.FindCurrentLocation())

    destination = 0

    for i in safe_set:
        if(i not in visited):
            if(destination < i):
                destination = i
    # print("destination= ", destination)
    # print("visited= ", visited)
    pred = [-1 for i in range(17)]

    queue = []

    visited_bfs = [False for i in range(17)]

    visited_bfs[source] = True

    queue.append(source)
    flag = 0
    while(len(queue) != 0):
        u = queue[0]
        queue.pop(0)

        neighbours = set(find_neighbours(convert_back(u)))
        # time.sleep(1)
        # print("convert_back= ", convert_back(u))
        neighbours = list(neighbours.intersection(safe_set))
        # print("u= ", u, " neighbours= ", neighbours, "dest= ", destination)

        for i in neighbours:

            if(visited_bfs[i] == False):
                visited_bfs[i] = True
                pred[i] = u

                queue.append(i)

                if(i == destination):
                    flag = 1
                    break
        if(flag == 1):
            break
    # print(path)
    while(destination != source):
        path.append(destination)
        destination = pred[destination]
    # print(path)

    for i in reversed(path):
        cur_loc = convert(ag.FindCurrentLocation())
        total_path.append(convert_back(i))
        if((cur_loc-i) == 1):
            ag.TakeAction('Left')
        if((i-cur_loc) == 1):
            ag.TakeAction('Right')
        if((cur_loc-i) == 4):
            ag.TakeAction('Down')
        if((i-cur_loc) == 4):
            ag.TakeAction('Up')


def Take_Action():
    update_sets()

    move()


def percept(percept):
    if(percept == "=0"):
        return 0
    elif(percept == '=1'):
        return 1
    else:
        return 2


def Add_clauses(mines, cur_loc):

    neighbours = find_neighbours(cur_loc)

    if(mines == 0):
        for i in neighbours:
            kb.add_clause([-i])

    if(mines == 1):
        kb.add_clause([i for i in neighbours])

        for i in range(len(neighbours)-1):
            for j in range(i+1, len(neighbours)):
                kb.add_clause([-neighbours[i], -neighbours[j]])

    if(mines == 2):
        for i in neighbours:
            kb.add_clause([j for j in neighbours if j != i])


def main():

    global kb

    kb.add_clause(range(1, 17))
    kb.add_clause([-1])
    kb.add_clause([-16])

    total_path.append([1, 1])
    while(ag.FindCurrentLocation() != [4, 4]):
        visited.add(convert(ag.FindCurrentLocation()))
        # total_path.append(ag.FindCurrentLocation())
        # print(ag.FindCurrentLocation())
        mines = percept(ag.PerceiveCurrentLocation())

        cur_loc = ag.FindCurrentLocation()

        Add_clauses(mines, cur_loc)

        Take_Action()
    # total_path.append([4, 4])
    print(total_path)
    # for i in range(1, 17):
    #     print(convert_back(i))


if __name__ == '__main__':
    main()
