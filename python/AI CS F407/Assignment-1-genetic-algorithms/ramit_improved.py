import random
import matplotlib.pyplot as plt

# random.seed(69)


class stateObj:

    def __init__(self, boardSize=8, board=None):

        self.n = boardSize
        self.board = board or [0 for _ in range(self.n)]
        # print(self.board)
        self.fitness = self.findFitness()

    def __gt__(self, other):

        return self.fitness > other.fitness

    def findFitness(self, board=None):

        fitness = 29
        row = [0 for _ in range(8)]
        diag1 = [0 for _ in range(15)]
        diag2 = [0 for _ in range(15)]

        board = board or self.board

        for i in range(self.n):

            cur = board[i]

            row[cur] += 1
            diag1[cur + i] += 1
            diag2[7 + cur - i] += 1

        for i in row:
            fitness -= (i * (i - 1) // 2)
        for i in diag1:
            fitness -= (i * (i - 1) // 2)
        for i in diag2:
            fitness -= (i * (i - 1) // 2)

        return fitness

    def crossover(self, other, index=None):

        index = index or random.randint(0, self.n - 1)
        return self.board[:index] + other.board[index:]


class GeneticAlgo:

    def __init__(self, population=20, mutProb=0.05, boardSize=8):

        self.population = population
        self.generation = 0
        # initial population size = 20
        self.states = [stateObj(boardSize) for _ in range(20)]
        self.sumFitness = sum([state.fitness for state in self.states])
        self.maxFitness = max([state.fitness for state in self.states])

        self.fitness = [1]

        self.mutProb = mutProb
        self.boardSize = boardSize

    def mutate(self, state):

        col = None
        row = None
        maxFit = state.fitness

        for i in range(self.boardSize):
            for j in range(self.boardSize):
                newFit = stateObj(
                    board=state.board[:i] + [j] + state.board[i+1:]).findFitness()

                if maxFit < newFit:
                    maxFit = newFit
                    col = i
                    row = j

        # state.board[col or random.randint(0, self.boardSize - 1)] = row or random.randint(0, self.boardSize - 1)

        if col == None or row == None:
            state.board[random.randint(0, 7)] = random.randint(0, 7)
            return

        state.board[col] = row

    def randomPick(self):

        # while True:
        #     for i in range(len(self.states)):
        #         if random.random() < self.states[i].fitness / self.sumFitness:
        #             return i

        prob = [i.fitness / self.sumFitness for i in self.states]
        return random.choices(range(0, len(prob)), weights=prob)[0]

    def reproduce(self, x, y):

        return stateObj(board=self.states[x].crossover(self.states[y]))

    def nextGen(self):

        children = []

        while len(children) < self.population:

            x = self.randomPick()
            y = x
            while(x == y):
                y = self.randomPick()

            newChild = self.reproduce(x, y)

            if newChild.fitness < 29 and random.random() < self.mutProb:
                self.mutate(newChild)
                newChild.fitness = newChild.findFitness()

            children.append(newChild)

        return children

    def run(self):

        defMutProb = self.mutProb
        mutProbs = [1 / self.mutProb]

        while self.maxFitness < 29:

            self.states = self.nextGen()
            self.sumFitness = sum([state.fitness for state in self.states])
            self.maxFitness = max([state.fitness for state in self.states])

            self.fitness.append(self.maxFitness)
            mutProbs.append(1 / self.mutProb)

            if(self.fitness[-1] == self.fitness[-2]):
                self.mutProb += 0.05
            else:
                self.mutProb = defMutProb

            self.generation += 1

            print("\nCurrent Generation:", self.generation)
            print("Current prime specimen:", self.maxFitness)

            maxState = self.states[0]
            for i in self.states:
                if self.maxFitness == i.fitness:
                    maxState = i
            print(maxState.board)

            if self.maxFitness == 29:
                printBoard(maxState.board)

            # for i in self.states:
            #     print(i.board, "\t", i.fitness)

        plt.plot(range(self.generation + 1), self.fitness)
        plt.plot(range(self.generation + 1), mutProbs)
        plt.show()
        # plt.show()

        # print("Number of Gens:", self.generation)

        return self.generation


def printBoard(state):

    for i in range(8):
        for j in state:
            if j != i:
                print("x", end=" ")
            else:
                print("Q", end=" ")

        print("")


if __name__ == "__main__":

    algo = GeneticAlgo(25, 0.05)

    algo.run()

    # avgGen = 0

    # for i in range(100):
    #     print("Loop", i)
    #     algo = GeneticAlgo()
    #     avgGen += algo.run() / 100

    # print("\n\n Average Gens:", avgGen)
