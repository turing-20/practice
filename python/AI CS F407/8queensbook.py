import random
import time
# import matplotlib.pyplot as plt


def random_selection(population, fitness_func):

    sum_of_fitness = 0
    for i in population:
        sum_of_fitness += fitness_func(i)

    if(sum_of_fitness == 0):
        # print(population[0])
        return population[0]

    probability = [(fitness_func(i)/sum_of_fitness) for i in population]
    # print(probability)
    a = random.choices(population, weights=probability)
    return a[0]


def reproduce(x, y):
    cut = random.randint(0, 7)
    a = x[:cut]+y[cut:]
    # print(a)
    return a


def mutate(child):
    # print(child)
    change_cell = random.randint(0, (len(child)-1))
    a = child[:change_cell]+[random.randint(0, 7)]+child[change_cell+1:]
    # print(a)
    return a

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
            if(board[j] == i):
                print('Q', end=" ")
            else:
                print('0', end=' ')
        print('')


generation = 1
graph = []


def genetic_algorithm(population, fitness_func):
    global generation
    while(1):
        new_population = []
        for _ in range(len(population)):
            x = random_selection(population, fitness_func)
            y = random_selection(population, fitness_func)

            child = reproduce(x, y)

            if(random.random() <= 0.03):
                child = mutate(child)

            new_population.append(child)

        population = new_population

        fitness_with_child = [[fitness_func(x), x] for x in population]
        fitness_without_child = [i[0] for i in fitness_with_child]

        max_fitness = max(fitness_without_child)

        # print(fitness_with_child[fitness_without_child.index(
        # max_fitness)], generation)
        # printboard(
        # fitness_with_child[fitness_without_child.index(max_fitness)][1])
        print(generation)
        graph.append(max_fitness)
        generation += 1

        if(max_fitness >= 29):
            print(generation)
            # plt.plot(range(2, generation+1), graph)
            # plt.show()
            return fitness_with_child[fitness_without_child.index(max_fitness)]


if __name__ == "__main__":
    population = []
    for i in range(20):
        a = []
        for j in range(8):
            a.append(0)
        population.append(a)
    fitness, board = genetic_algorithm(population, fitness_func)
    print(fitness, board)
    printboard(board)
