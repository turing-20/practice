import random
import matplotlib.py

city = [[0, 1000, 1000, 1000, 1000, 1000, .15, 1000, 1000, .2, 1000, .12, 1000, 1000], [1000, 0, 1000, 1000, 1000, 1000, 1000, .19, .4, 1000, 1000, 1000, 1000, .13], [1000, 1000, 0, .6, .22, .4, 1000, 1000, .2, 1000, 1000, 1000, 1000, 1000], [1000, 1000, .6, 0, 1000, .21, 1000, 1000, 1000, 1000, .3, 1000, 1000, 1000], [1000, 1000, .22, 1000, 0, 1000, 1000, 1000, .18, 1000, 1000, 1000, 1000, 1000], [1000, 1000, .4, .21, 1000, 0, 1000, 1000, 1000, 1000, .37, .6, .26, .9], [.15, 1000, 1000, 1000, 1000, 1000, 0, 1000, 1000, 1000, .55, .18, 1000, 1000], [1000, .19, 1000, 1000, 1000, 1000, 1000, 0, 1000, .56, 1000, 1000, 1000, .17], [1000, .4, .2, 1000, .18, 1000, 1000, 1000, 0, 1000, 1000, 1000, 1000, .6],
        [.2, 1000, 1000, 1000, 1000, 1000, 1000, .56, 1000, 0, 1000, .16, 1000, .5],
        [1000, 1000, 1000, .3, 1000, .37, .55,
            1000, 1000, 1000, 0, 1000, .24, 1000],
        [.12, 1000, 1000, 1000, 1000, .6, .18, 1000, 1000, .16, 1000, 0, .4, 1000],
        [1000, 1000, 1000, 1000, 1000, .26, 1000,
            1000, 1000, 1000, .24, .4, 0, 1000],
        [1000, .13, 1000, 1000, 1000, .9, 1000, .17, .6, .5, 1000, 1000, 1000, 0]
        ]


def randomStateCalc(fitness_array):
    fitnessSUMTotal = sum(fitness_array)
    while True:
        for i in range(20):
            fitness_ratio = fitness_array[i] / fitnessSUMTotal
            if random.random() < fitness_ratio:
                return i


def getdist(child):
    distance = 0
    for i in range(len(child)-1):
        distance += city[i][i+1]
    distance += city[-1][0]
    return distance


def fitness(child):
    return 1/getdist(child)


def reproduce(parent1, parent2):
    best_fitness = fitness(parent1)
    best_child = parent1[::]

    for i in range(0, 13):
        for j in range(i+1, 14):

            temp_child = ['_' for i in range(len(parent1))]
            temp_child[i:j] = parent1[i:j]

            for a in range(len(parent2)):
                if(parent2[a] not in temp_child):
                    for b in range(0, 14):
                        if(temp_child[b] != '_'):
                            temp_child[b] = parent2[a]
                            break
            if(best_fitness < fitness(temp_child)):
                best_fitness = fitness(temp_child)
                best_child = temp_child
    return best_child


def mutate(child):
    best_fitness = fitness(child)
    final = child[::]
    for idx1 in range(len(child)):
        for idx2 in range(idx1+1, len(child)):
            temp = child[::]
            temp[idx1], temp[idx2] = temp[idx2], temp[idx1]
            if(fitness(temp) > best_fitness):
                final = temp[::]
                best_fitness = fitness(temp)
    if(final == child):
        idx = random.sample(range(0, len(child)), 2)
        idx1 = idx[0]
        idx2 = idx[1]
        child[idx1], child[idx2] = child[idx2], child[idx1]
        return child
    return final


def nextGeneration(states, fitness_array):
    next_state = list()
    while 1:
        if len(next_state) == 20:
            break
        one, two = randomStateCalc(
            fitness_array), randomStateCalc(fitness_array)
        new_state = reproduce(initial_population, one, two)
        final_population.append(new_state)

        fitness_prob = 0.5
        if random.random() < fitness_prob:
            new_state[-1] = mutate(new_state[-1])
    return new_state


def geneticTSP():


if __name__ == '__main__':
