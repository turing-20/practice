import random
import time
# import matplotlib.pyplot as plt


def random_selection(population, fitness):

    sum_of_fitness = sum(fitness)

    if(sum_of_fitness == 0):
        return population[0]

    probability = [i/sum_of_fitness for i in fitness]
    a = random.choices(population, weights=probability)

    return a[0]


def reproduce(x, y):

    maxfitness = fitness_func(x)
    maxboard = x
    for i in range(len(x)):
        cell = x[:i]+y[i:]
        fit = fitness_func(cell)

        if(fit > maxfitness):
            fit = maxfitness
            maxboard = cell
    # cut = random.randint(0, 7)
    # a = x[:cut]+y[cut:]
    if(maxboard == x):
        cut = random.randint(0, 7)
        return x[:cut]+y[cut:]

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
        return child[:change_cell]+[random.randint(0, 7)]+child[change_cell+1:]

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
            if(board[j] == i):
                print('Q', end=" ")
            else:
                print('0', end=' ')
        print('')


generation = 1


def genetic_algorithm(population, fitness_func):

    global generation

    while(1):

        new_population = []
        fitness = [fitness_func(x) for x in population]

        for _ in range(len(population)):

            x = random_selection(population, fitness)
            y = random_selection(population, fitness)

            while(x == y and generation > 10):
                y = random_selection(population, fitness)

            child = reproduce(x, y)

            if(random.random() <= 0.05):
                child = mutate(child)

            new_population.append(child)

        population = new_population

        fitness = [fitness_func(x) for x in population]

        max_fitness = max(fitness)

        print(max_fitness, population[fitness.index(max_fitness)], generation)

        generation += 1

        if(max_fitness >= 29):
            print(generation)
            return population, fitness


if __name__ == "__main__":
    population = []
    for i in range(50):
        a = []
        for j in range(8):
            a.append(0)
        population.append(a)
    population, fitness = genetic_algorithm(population, fitness_func)
    board = []
    for i in range(len(population)):
        if(fitness[i] == 29):
            board = population[i]
            break
    printboard(board)
