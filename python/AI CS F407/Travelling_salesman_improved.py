import random
import matplotlib.pyplot as plt


city_distances = [[0, 1000, 1000, 1000, 1000, 1000, .15, 1000, 1000, .2, 1000, .12, 1000, 1000],
                  [1000, 0, 1000, 1000, 1000, 1000,
                      1000, .19, .4, 1000, 1000, 1000, 1000, .13],
                  [1000, 1000, 0, .6, .22, .4, 1000,
                      1000, .2, 1000, 1000, 1000, 1000, 1000],
                  [1000, 1000, .6, 0, 1000, .21, 1000, 1000,
                      1000, 1000, .3, 1000, 1000, 1000],
                  [1000, 1000, .22, 1000, 0, 1000, 1000,
                   1000, .18, 1000, 1000, 1000, 1000, 1000],
                  [1000, 1000, .4, .21, 1000, 0, 1000,
                      1000, 1000, 1000, .37, .6, .26, .9],
                  [.15, 1000, 1000, 1000, 1000, 1000, 0,
                   1000, 1000, 1000, .55, .18, 1000, 1000],
                  [1000, .19, 1000, 1000, 1000, 1000, 1000,
                   0, 1000, .56, 1000, 1000, 1000, .17],
                  [1000, .4, .2, 1000, .18, 1000, 1000,
                      1000, 0, 1000, 1000, 1000, 1000, .6],
                  [.2, 1000, 1000, 1000, 1000, 1000,
                      1000, .56, 1000, 0, 1000, .16, 1000, .5],
                  [1000, 1000, 1000, .3, 1000, .37, .55,
                      1000, 1000, 1000, 0, 1000, .24, 1000],
                  [.12, 1000, 1000, 1000, 1000, .6, .18,
                      1000, 1000, .16, 1000, 0, .4, 1000],
                  [1000, 1000, 1000, 1000, 1000, .26, 1000,
                   1000, 1000, 1000, .24, .4, 0, 1000],
                  [1000, .13, 1000, 1000, 1000, .9,
                      1000, .17, .6, .5, 1000, 1000, 1000, 0]
                  ]


class child:
    def __init__(self, route=['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N']):
        self.route = route
        self.fitness = self.find_fitness()


def find_distance(x):
    distance = 0
    for i in range(len(x)-1):
        try:
            distance += city_distances[ord(x[i])-65][ord(x[i+1])-65]
        except:
            print(x, i, city_distances(
                ord(x[i+1])-65), city_distances(ord(x[i])-65))
            raise Exception("Sorry, no numbers below zero")

    distance += city_distances[ord(x[-1])-65][ord(x[0])-65]
    return distance


def fitness_func(x):
    total_distance = find_distance(x)

    fitness = 1/total_distance

    return fitness


def random_selection(population, fitness):

    sum_of_fitness = sum(fitness)

    if(sum_of_fitness == 0):
        return population[0]

    probability = [i/sum_of_fitness for i in fitness]
    a = random.choices(population, weights=probability)
    # print("exit")
    return a[0]


def reproduce(x, y):

    bestchild = x
    bestfitness = fitness_func(child)
    for a in range(len(x)-1):
        for b in range(a+1, len(x)):
            # a = random.randint(0, len(x)-1)
            # b = random.randint(a+1, len(x))

            c = ['P' for _ in range(len(x))]

            c[a:b] = x[a:b]

            count = 0

            for i in range(len(y)):
                if(y[i] not in c):
                    index = 0
                    for j in range(len(c)):
                        if(c[j] == 'P'):
                            index = j
                            break
                    c[index] = y[i]
            if(fitness_func(c) > bestfitness):
                bestchild = c
                bestfitness = fitness_func(c)
    if(bestchild == x):
        a = random.randint(0, len(x)-1)
        b = random.randint(a+1, len(x))

        c = ['P' for _ in range(len(x))]

        c[a:b] = x[a:b]

        count = 0

        for i in range(len(y)):
            if(y[i] not in c):
                index = 0
                for j in range(len(c)):
                    if(c[j] == 'P'):
                        index = j
                        break
                c[index] = y[i]
        bestchild = c
    return bestchild


def mutate(x):
    bestchild = x
    bestfitness = fitness_func(bestchild)
    for i in range(len(x)):
        c = x[:]
        for j in range(i+1, len(x)):
            c[i], c[j] = c[j], c[i]
            if(bestfitness < fitness_func(c)):
                bestfitness = fitness_func(c)
                bestchild = c
    # a = random.sample(range(0, len(x)), 2)
    # swap = x[a[0]]
    # x[a[0]] = x[a[1]]
    # x[a[1]] = swap
    if(bestchild == x):
        a = random.sample(range(0, len(x)), 2)
        swap = x[a[0]]
        x[a[0]] = x[a[1]]
        x[a[1]] = swap
        bestchild = x
    return bestchild


generation = 1
fitness_graph = []


def genetic_algorithm_tsp(population):

    global generation
    mutation_probability = 0.05

    while(1):

        new_population = []
        fitness = [fitness_func(x) for x in population]

        for _ in range(len(population)):
            x = random_selection(population, fitness)
            y = random_selection(population, fitness)
            child = reproduce(x, y)
            if(generation > 10 and fitness_graph[-1] == fitness_graph[-2]):
                mutation_probability += 0.05
            else:
                mutation_probability = 0.05
            if(random.random() <= mutation_probability):
                child = mutate(child)
            new_population.append(child)

        population = new_population
        fitness = [fitness_func(x) for x in population]

        max_fitness = max(fitness)
        distances = [find_distance(x) for x in population]
        print(min(distances),
              population[fitness.index(max_fitness)], generation)
        generation += 1
        fitness_graph.append(max_fitness)

        if(generation >= 1000 or min(distances) < 3.8):

            plt.plot(range(1, generation), fitness_graph)
            plt.show()
            return


if __name__ == '__main__':
    population = []
    for i in range(20):
        child = []
        for j in range(65, 79):
            child.append(chr(j))
        population.append(child)
    genetic_algorithm_tsp(population)
    # for i in city_distances:
    #     print(len(i))
    # len(city_distances)
