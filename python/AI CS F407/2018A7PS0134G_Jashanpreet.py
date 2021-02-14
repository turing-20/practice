import random
# import matplotlib.pyplot as plt


class queens():
    def __init__(self):
        population = []
        for i in range(20):
            a = []
            for j in range(8):
                a.append(1)
            population.append(a)
        self.generation = 1
        self.fitness_graph = [1]
        population, fitness, y = self.genetic_algorithm(population)
        board = []
        for i in range(len(population)):
            if(fitness[i] == 29):
                board = population[i]
                break
        self.printboard(board)

    def genetic_algorithm(self, population):
        self.fitness_graph.append(
            max([self.fitness_func(x) for x in population]))
        mutation_probability = 0.05
        while(1):

            new_population = []
            fitness = [self.fitness_func(x) for x in population]

            for _ in range(len(population)):

                x = self.random_selection(population, fitness)
                y = self.random_selection(population, fitness)
                count = 0
                while(x == y and self.generation > 10 and count < 5):
                    y = self.random_selection(population, fitness)
                    count += 1

                child = self.reproduce(x, y)
                if(self.generation > 10):
                    if(self.fitness_graph[-1] == self.fitness_graph[-2]):
                        mutation_probability += 0.05
                    else:
                        mutation_probability = 0.05
                if(random.random() <= mutation_probability):
                    child = self.mutate(child)

                new_population.append(child)

            population = new_population

            fitness = [self.fitness_func(x) for x in population]

            max_fitness = max(fitness)

            print("Max fitness:", max_fitness,
                  "Generation:", self.generation)

            self.generation += 1

            # for i in range(len(population)):
            #     print(fitness[i], population[i])

            self.fitness_graph.append(max_fitness)

            if(max_fitness >= 29):
                # print(max_fitness, self.generation-1)
                print("\n\n")
                print("Best solution:\n")
                print("Fitness:", max_fitness, "\nState:",
                      population[fitness.index(max_fitness)])
                print()
                y = self.generation
                # plt.plot(range(1, self.generation+2), self.fitness_graph)
                # plt.xlabel("Generation")
                # plt.ylabel("Fitness")
                # plt.title("8 Queens Improved")
                # plt.show()
                return population, fitness, y

    def printboard(self, board):

        for i in range(8):
            for j in range(8):
                if(board[j] == i+1):
                    print('Q', end=" ")
                else:
                    print('0', end=' ')
            print('')

    def fitness_func(self, x):

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

    def mutate(self, child):

        maxfitness = self.fitness_func(child)
        maxboard = child

        for i in range(len(child)):
            for j in range(len(child)):
                cell = child[:i]+[j+1]+child[i+1:]
                fit = self.fitness_func(cell)

                if(fit > maxfitness):
                    maxfitness = fit
                    maxboard = cell

        if(maxboard == child):
            change_cell = random.randint(0, (len(child)-1))
            return child[:change_cell]+[random.randint(1, 8)]+child[change_cell+1:]

        return maxboard

    def reproduce(self, x, y):

        maxfitness = self.fitness_func(x)
        maxboard = x
        for i in range(len(x)):
            cell = x[:i]+y[i:]
            fit = self.fitness_func(cell)

            if(fit > maxfitness):
                fit = maxfitness
                maxboard = cell
        cut = random.randint(0, 7)
        a = x[:cut]+y[cut:]
        if(maxboard == x):
            cut = random.randint(0, 7)
            maxboard = x[:cut]+y[cut:]
        # print(maxboard)
        return maxboard

    def random_selection(self, population, fitness):

        # print("enter")

        sum_of_fitness = sum(fitness)

        if(sum_of_fitness == 0):
            return population[0]

        probability = [i/sum_of_fitness for i in fitness]
        a = random.choices(population, weights=probability)
        # print("exit")
        return a[0]


class TSP():
    def __init__(self):
        population = []
        for i in range(20):
            child = []
            for j in range(65, 79):
                child.append(chr(j))
            population.append(child)
        self.generation = 1
        self.city_distances = [[0, 1000, 1000, 1000, 1000, 1000, .15, 1000, 1000, .2, 1000, .12, 1000, 1000],
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
        self.fitness_graph = [self.fitness_func(population[0])]
        self.bestchild = population[0]
        self.bestfitness = self.fitness_func(self.bestchild)
        print(self.bestfitness, 1)
        self.genetic_algorithm_tsp(population)
        print("BEST CHILD: ")
        print(self.bestfitness, self.bestchild)

    def genetic_algorithm_tsp(self, population):
        mutation_probability = 0.05
        while(1):

            new_population = []
            fitness = [self.fitness_func(x) for x in population]

            for _ in range(len(population)):
                x = self.random_selection(population, fitness)
                y = self.random_selection(population, fitness)
                child = self.reproduce(x, y)
                if(self.generation > 10 and self.fitness_graph[-1] == self.fitness_graph[-2]):
                    mutation_probability += 0.05
                else:
                    mutation_probability = 0.05
                if(random.random() <= mutation_probability):
                    child = self.mutate(child)
                new_population.append(child)

            population = new_population
            fitness = [self.fitness_func(x) for x in population]

            max_fitness = max(fitness)
            distances = [self.find_distance(x) for x in population]
            self.generation += 1
            print(max_fitness, self.generation)
            if(self.bestfitness < max_fitness):
                self.bestfitness = max_fitness
                self.bestchild = population[fitness.index(max_fitness)][:]
            self.fitness_graph.append(max_fitness)

            if(self.generation >= 500):

                # plt.plot(range(1, self.generation+1), self.fitness_graph)
                # plt.xlabel("Generation")
                # plt.ylabel("Fitness")
                # plt.title("TSP Improved")
                # plt.show()
                return

    def mutate(self, x):
        bestchild = x
        bestfitness = self.fitness_func(bestchild)
        for i in range(len(x)):
            c = x[:]
            for j in range(i+1, len(x)):
                c[i], c[j] = c[j], c[i]
                if(bestfitness < self.fitness_func(c)):
                    bestfitness = self.fitness_func(c)
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

    def reproduce(self, x, y):

        bestchild = x
        bestfitness = self.fitness_func(x)
        for a in range(len(x)-1):
            for b in range(a+1, len(x)):

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
                if(self.fitness_func(c) > bestfitness):
                    bestchild = c
                    bestfitness = self.fitness_func(c)
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

    def fitness_func(self, x):
        total_distance = self.find_distance(x)

        fitness = 1/total_distance

        return fitness

    def random_selection(self, population, fitness):

        sum_of_fitness = sum(fitness)

        if(sum_of_fitness == 0):
            return population[0]

        probability = [i/sum_of_fitness for i in fitness]
        a = random.choices(population, weights=probability)
        # print("exit")
        return a[0]

    def find_distance(self, x):
        distance = 0
        for i in range(len(x)-1):
            try:
                distance += self.city_distances[ord(x[i])-65][ord(x[i+1])-65]
            except:
                print(x, i, self.city_distances(
                    ord(x[i+1])-65), self.city_distances(ord(x[i])-65))
                raise Exception("Sorry, no numbers below zero")

        distance += self.city_distances[ord(x[-1])-65][ord(x[0])-65]
        return distance


if __name__ == "__main__":
    print("Enter 1 for 8 queens")
    print("Enter 2 for TSP")

    while(True):
        a = input("Enter: ")

        if(a == '1'):
            queens()
            break
        if(a == '2'):
            TSP()
            break
        else:
            print("Invalid input try again")
