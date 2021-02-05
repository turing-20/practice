import random
import time
import matplotlib.pyplot as plt


def random_selection(population, fitness):

    # print("enter")

    sum_of_fitness = sum(fitness)

    if(sum_of_fitness == 0):
        return population[0]

    probability = [i/sum_of_fitness for i in fitness]
    a = random.choices(population, weights=probability)
    # print("exit")
    return a[0]


def reproduce(x, y):

    maxfitness = fitness_func(x)
    maxboard = x
    # for i in range(len(x)):
    #     cell = x[:i]+y[i:]
    #     fit = fitness_func(cell)

    #     if(fit > maxfitness):
    #         fit = maxfitness
    #         maxboard = cell
    # cut = random.randint(0, 7)
    # a = x[:cut]+y[cut:]
    if(maxboard == x):
        cut = random.randint(0, 7)
        maxboard = x[:cut]+y[cut:]
    # print(maxboard)
    return maxboard


def mutate(child):

    maxfitness = fitness_func(child)
    maxboard = child

    for i in range(len(child)):
        for j in range(len(child)):
            cell = child[:i]+[j+1]+child[i+1:]
            fit = fitness_func(cell)

            if(fit > maxfitness):
                maxfitness = fit
                maxboard = cell

    if(maxboard == child):
        change_cell = random.randint(0, (len(child)-1))
        return child[:change_cell]+[random.randint(1, 8)]+child[change_cell+1:]

    return maxboard

# hello = 0


def fitness_func(x):

    row_clashes = int(sum([x.count(queen)-1 for queen in x])/2)

    n = len(x)

    diagnol_clashes = 0
    left_diagonal = [0]*2*n
    right_diagnol = [0]*2*n

    for i in range(n):
        left_diagonal[i+x[i]] += 1
        right_diagnol[n+i-x[i]-1] += 1

    for i in range(2*n-1):
        diagnol_clashes += (left_diagonal[i]*(left_diagonal[i]-1))//2
        diagnol_clashes += (right_diagnol[i]*(right_diagnol[i]-1))//2

    clashes = row_clashes+diagnol_clashes

    return int(29-clashes)


def printboard(board):

    for i in range(8):
        for j in range(8):
            if(board[j] == i+1):
                print('Q', end=" ")
            else:
                print('0', end=' ')
        print('')


generation = 1
fitness_graph = []


def genetic_algorithm(population, fitness_func):

    global generation
    fitness_graph.append(max([fitness_func(x) for x in population]))
    mutation_probability = 0.05
    while(1):

        new_population = []
        fitness = [fitness_func(x) for x in population]

        for _ in range(len(population)):

            x = random_selection(population, fitness)
            y = random_selection(population, fitness)
            count = 0
            while(x == y and generation > 10 and count < 10):
                y = random_selection(population, fitness)
                count += 1

            child = reproduce(x, y)
            if(generation > 10):
                if(fitness_graph[-1] == fitness_graph[-2]):
                    mutation_probability += 0.05
                else:
                    mutation_probability = 0.05
            if(random.random() <= mutation_probability):
                child = mutate(child)

            new_population.append(child)

        population = new_population

        fitness = [fitness_func(x) for x in population]

        max_fitness = max(fitness)

        # print(max_fitness, population[fitness.index(max_fitness)], generation)

        generation += 1

        # for i in range(len(population)):
        #     print(fitness[i], population[i])

        fitness_graph.append(max_fitness)

        if(max_fitness >= 29):
            print(generation)
            y = generation
            # plt.plot(range(1, generation+1), fitness_graph)
            # plt.show()
            generation = 1
            return population, fitness, y


def findgeneration():
    # print("hello")
    population = []
    for i in range(20):
        a = []
        for j in range(8):
            a.append(1)
        population.append(a)
    # print(population)
    population, fitness, y = genetic_algorithm(
        population, fitness_func)
    board = []
    for i in range(len(population)):
        if(fitness[i] == 29):
            board = population[i]
            break
    print(board)
    # printboard(board)
    return y


if __name__ == "__main__":
    sum1 = 0

    for i in range(100):
        print(i, end=" ")
        fitness_graph = []
        sum1 += findgeneration()

    print(sum1/100)
