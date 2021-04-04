
from Agent import *
import random,sys
import copy



noCalls = 0
kb = []

def get_count(clauses):
    dict = {}

    for clause in clauses:
        for literal in clause:
            if literal in dict:
                dict[literal] = dict[literal] + 1
            else:
                dict[literal] = 1
    return dict

def bcp(clauses,literal):
    #generating modified clause after assigning the truth value to given literal
    final_clauses = []

    for clause in clauses:
        if literal in clause:
            continue
        if (-1*literal) in clause:
            p = [x for x in clause if x != -literal]
            if (len(p) == 0):
                return -1
            final_clauses.append(p)
        else:
            final_clauses.append(clause)

    return final_clauses


def pure_literal(clauses):
    #getting the count of all literals
    dict = get_count(clauses)
    pure_literals = []

    for literal,times in dict.items():
        #checking if any clauses has the negation of the literal
        if -literal not in dict.keys():
            pure_literals.append(literal)

    for pure in pure_literals:
        clauses = bcp(clauses,pure)

    return clauses

def generate_random(clauses):
    positive = {}
    negative = {}
    dict = {}
    for clause in clauses:
        for literal in clause:
            if ( literal > 0):
               positive[literal] = positive.get(literal,0)+1
            else:
               negative[-1*literal] = negative.get(-1*literal,0)+1
            dict[abs(literal)] = dict.get(abs(literal),0) + 1
    final = 0
    mx = 0
    for key,value in dict.items():
        if value > mx:
            mx = value
            final = key
    if positive.get(key,0) >= negative.get(-key,0):
        return key
    else:
        return -key

def unit_prop(clauses):
    # all the unit clauses
    unit_clauses = [x for x in clauses if len(x) == 1]

    while (len(unit_clauses) > 0):
        unit = unit_clauses[0]
        clauses = bcp(clauses,unit[0])
        # if this is UnSatisfiable backtrack
        if clauses == -1:
            return -1
        #the clause set becomes empty, that means Satisfiable
        if not clauses:
            return clauses
        #redoing the process again
        unit_clauses = [x for x in clauses if len(x) == 1]
    return clauses


def dpll(clauses):
    #calls to dpll
    global noCalls
    noCalls = noCalls + 1
    # early termination
    if ( clauses == -1):
        return False
    for clause in clauses:
        if not clause:
            return False

    # pure literal heuristic
    clauses_after_pure = pure_literal(clauses)
    # unit clause heuristic
    clauses_after_unit = unit_prop(clauses_after_pure)
    # checking for base case
    if clauses_after_unit == -1:
        return False
    if not clauses_after_unit:
        return True
    # assigning truth value to a random literal and checking
    random_literal = generate_random(clauses_after_unit)

    return   dpll(bcp(clauses_after_unit,random_literal)) or dpll(bcp(clauses_after_unit,-random_literal))



def findPath(ag,curx,cury,tempx,tempy,visited,tempVisited):

    if ( tempx == curx and tempy == cury):
        return True

    tempVisited[curx-1][cury-1] = 1

    #going Right
    x = curx + 1
    y = cury
    if ( x >= 1 and y >= 1 and x <= 4 and y <= 4):
        if (((x == tempx) and (y == tempy)) or (visited[x-1][y-1] and (not tempVisited[x-1][y-1]))):
            ag.TakeAction('Right')
            flag = findPath(ag,x,y,tempx,tempy,visited,tempVisited)
            if flag:
                return True
            ag.TakeAction('Left')


    #going up
    x = curx
    y = cury+1
    if ( x >= 1 and y >= 1 and x <= 4 and y <= 4):
        if (((x == tempx) and (y == tempy)) or (visited[x-1][y-1] and (not tempVisited[x-1][y-1]))):
            ag.TakeAction('Up')

            flag = findPath(ag,x,y,tempx,tempy,visited,tempVisited)
            if flag:
                return True
            ag.TakeAction('Down')


    #going Left
    x = curx - 1
    y = cury
    if ( x >= 1 and y >= 1 and x <= 4 and y <= 4):
        if (((x == tempx) and (y == tempy)) or (visited[x-1][y-1] and (not tempVisited[x-1][y-1]))):
            ag.TakeAction('Left')

            flag = findPath(ag,x,y,tempx,tempy,visited,tempVisited)
            if flag:
                return True
            ag.TakeAction('Right')


    #going Down
    x = curx
    y = cury - 1
    if ( x >= 1 and y >= 1 and x <= 4 and y <= 4):
        if (((x == tempx) and (y == tempy)) or (visited[x-1][y-1] and (not tempVisited[x-1][y-1]))):
            ag.TakeAction('Down')
            flag = findPath(ag,x,y,tempx,tempy,visited,tempVisited)
            if flag:
                return True
            ag.TakeAction('Up')


    return False








def main():
    ag = Agent()
    vis = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
    atleast1pit = [x for x in range(1,17)]
    atleast1wump = [x for x in range(17,33)]
    kb.append(atleast1wump)
    #print(kb)
    kb.append(atleast1pit)
    #print(kb)
    for i in range (1,17):
        for j in range(i+1,17):
            kb.append([-i,-j])
            #print(kb)
            kb.append([-(i+16),-(j+16)])
            #print(kb)

    kb.append([-1])
    #print(kb)
    kb.append([-17])
    #print(kb)
    
    curx = 1
    cury = 1
    validMoves = [[0,1],[0,-1],[-1,0],[1,0]]
    dir = ["Up","Down","Left","Right"]
    print("Started:",1,1)
    while ( (curx != 4) or (cury != 4)):
        vis[curx-1][cury-1] = 1
        breeze,stench = ag.PerceiveCurrentLocation()
        ifBreeze = []
        ifStench = []
        for x,y in validMoves:
            tempx = curx + x
            tempy = cury + y
            if ( tempx < 1 or tempx > 4 or tempy < 1 or tempy > 4):
                continue
            if vis[tempx-1][tempy-1]:
                continue
            if breeze:
                ifBreeze.append(4*(tempx-1)+tempy)
            else:
                kb.append([-(4*(tempx-1)+tempy)])
            if stench:
                ifStench.append(4*(tempx-1)+tempy+16)
            else:
                kb.append([-(4*(tempx-1)+tempy+16)])
            #print(kb)
        if breeze:
            kb.append(ifBreeze)
        if stench:
            kb.append(ifStench)
        #print(kb)
        safe = []
        
        for i in range(1,17):
            if vis[(i-1)//4][(i-1)%4]:
                continue
            # tempkb = [x for x in kb]
            tempkb = copy.deepcopy(kb)
            tempkb.append([i,i+16])
            if (not dpll(tempkb)):
                safe.append(i)

        for i in safe:
            tempx = (i+3)//4
            tempy = (i-1)%4 + 1
            tempVisited =  [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
            path = findPath(ag,curx,cury,tempx,tempy,vis,tempVisited)
            if not path:
                continue
            curx = tempx
            cury = tempy
            break
        

    print("Reached",4,4,"From 1 1 in",noCalls,"DPLL calls")

    
if __name__=='__main__':
    main()
