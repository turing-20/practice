import random
import copy
# import matplotlib.pyplot as plt

class EightQueens():
  def mutate_current_state_random(self,state):
    # print('mutate_current_state_random')
    random_index = random.randint(0,7)
    random_value = random.randint(0,7)
    state[random_index] = random_value
    return state

  def mutate_current_state_using_fitness(self,state):
    # print('mutate_current_state_using_fitness')
    current_state = copy.deepcopy(state)
    current_fitness = self.calculate_fitness(state)
    max_fitness = current_fitness
    max_fitness_state = copy.deepcopy(current_state)
    for i in range(8):
      state = copy.deepcopy(current_state)
      for j in range(8):
        state[j] = i
        fitness_local = self.calculate_fitness(state)
        if(max_fitness < fitness_local):
          max_fitness_state = state
          max_fitness = fitness_local
    if max_fitness_state == current_state:
      return self.mutate_current_state_random(current_state)
    return max_fitness_state
        


  def calculate_attacking_queens(self,state):
    # print('calculate_attacking_queens')
    ans = 0
    initial_row = [0]*8
    initial_diag_right = [0]*15
    initial_diag_left = [0]*15

    for i in range(8):
      initial_row[state[i]] += 1
      initial_diag_right[state[i] + i] += 1
      initial_diag_left[state[i] - i + 7] += 1

    for x in initial_row:
      ans += (x*(x-1) // 2)

    for x in initial_diag_left:
      ans += (x*(x-1) // 2)

    for x in initial_diag_right:
      ans += (x*(x-1) // 2)

    return ans

  def reproduce_child(self,initial_population, first, second):
    # print('reproduce_child')
    max_fitness = self.calculate_fitness(initial_population[first])
    ans_state = initial_population[first]
    for i in range(8):
      swapped_state = initial_population[first][0:i] + initial_population[second][i:8]
      fitness_local = self.calculate_fitness(swapped_state)
      if fitness_local > max_fitness:
        max_fitness = fitness_local
        ans_state = swapped_state
    return ans_state


  def get_random_state(self):
    # print('get_random_state')
    fitness_total = sum(self.initial_fitness)
    while True:
      for i in  range(self.initial_population_size):
        if float(random.random()) < float(float(self.initial_fitness[i]) / float(fitness_total)):
          return i

  def get_next_generation(self,initial_population):
    final_population = []

    while (len(final_population) < self.initial_population_size):
      first = self.get_random_state()
      second = self.get_random_state()

      while first == second:
        second = self.get_random_state()

      # print(first,second)
      new_state = self.reproduce_child(initial_population, first, second)
      new_state_fitness = self.calculate_fitness(new_state)
      # print(new_state)
      final_population.append(new_state)

      self.probability_to_random = 0.6 + (float(self.generation_count)/5.0)*0.1

      if new_state_fitness <= 28 and random.random() < self.probability_to_random:
        final_population[-1] = self.mutate_current_state_using_fitness(final_population[-1])

    return final_population


  def calculate_fitness(self, state):
    return (29 - self.calculate_attacking_queens(state))

  def print_queen_on_board(self,state):
    print('')
    for i in range(8):
      for j in range(8):
        if j == state[i]:
          print('Q', end=' ')
        else:
          print('0',end=' ')
      print('')
    return


  def __init__(self):
    self.initial_population_size = 20
    self.probability_to_random = 0.5

    initial_population = [[0] * 8] * self.initial_population_size
    self.initial_fitness = [1] * self.initial_population_size
    self.generation_count = 0
    generation_array = []
    max_array = []
    while max(self.initial_fitness) < 29:

      initial_population = self.get_next_generation(initial_population)
      self.generation_count += 1
      self.initial_fitness = [self.calculate_fitness(i) for i in initial_population]
      max_fintess_local = max(self.initial_fitness)
      print("GEN {} MAX {}".format(self.generation_count, max_fintess_local))
      generation_array.append(self.generation_count)
      max_array.append(max_fintess_local)

      if max_fintess_local == 29:
        for x in initial_population:
          if self.calculate_fitness(x) == 29:
            print('')
            print('Ans of best board: 29')
            self.print_queen_on_board(x)
            break
        break


    
    # plt.plot(generation_array,max_array)
    # plt.show()


class TSP():
  def get_distances(self):
    return [[0, 1000, 1000, 1000, 1000, 1000, .15, 1000, 1000, .2, 1000, .12, 1000, 1000],
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

  def get_distance_of_state(self,state):
      ans = 0
      for i in range(1,len(state)):
          ans += self.get_distances()[state[i]][state[i-1]]
      ans+= self.get_distances()[state[0]][state[13]]
      return ans

  def get_fitness(self,state):
      distance_of_state = self.get_distance_of_state(state)
      return float(1 / distance_of_state)

  def mutate_current_state(self,state):
      x=0
      y=0
      distance_min = self.get_distance_of_state(state)

      for i in range(14):
          for j in range(i + 1, 14):
              state[i], state[j] = state[j], state[i]
              distance_new = self.get_distance_of_state(state)
              if abs(distance_new - distance_min) > 0.001 and distance_new < distance_min:
                  distance_min = distance_new
                  x,y = i,j
              state[i], state[j] = state[j], state[i]

      if x == y:
          for _ in range(4):
              first_ind = random.randint(0,13)
              second_ind = random.randint(0,13)
              state[first_ind], state[second_ind] = state[second_ind], state[first_ind]
          return state

      state[x], state[y] = state[y], state[x]
      return state


  def reproduce_child(self,initial_population, first, second):
      bestChild = initial_population[first]
      bestFit = max(self.get_fitness(initial_population[first]), self.get_fitness(initial_population[second]))
  
      for i in range(14):
          for j in range(i, 14):
              childPath = [0 for _ in range(14)]
              childPath[i:j + 1] = initial_population[first][i:j + 1] 
              childPathIndex = 0
              for k in initial_population[second]:
                  if i == childPathIndex:
                      childPathIndex = j + 1
                  if k not in childPath:
                      childPath[childPathIndex] = k
                      childPathIndex += 1

              childPathFitness = self.get_fitness(childPath)

              if childPathFitness > bestFit:
                  bestChild = childPath
                  bestFit = childPathFitness


      if bestChild != initial_population[first] and bestChild != initial_population[second]:
          return bestChild

      a = random.randint(0, 13)
      b = random.randint(a, 13)

      childPath = [0 for _ in range(14)]

      childPath[a:b+1] = initial_population[first][a:b+1]

      childPathIndex = 0

      for i in initial_population[second]:
          if a == childPathIndex:
              childPathIndex = b + 1
          if i not in childPath:
              childPath[childPathIndex] = i
              childPathIndex += 1
      return childPath

  def get_random_state(self,initial_fitness):
    fitness_total = sum(initial_fitness)
    while True:
      for i in  range(20):
        if float(random.random()) < float(float(initial_fitness[i]) / float(fitness_total)):
          return i

  def get_next_generation(self,initial_population, initial_fitness):
    final_population = []

    while (len(final_population) < 20):
      first = self.get_random_state(initial_fitness)
      second = self.get_random_state(initial_fitness)

      while first == second:
        second = self.get_random_state(initial_fitness)

      new_state = self.reproduce_child(initial_population, first, second)
      final_population.append(new_state)

      if random.random() < 0.5:
        final_population[-1] = self.mutate_current_state(final_population[-1])
    return final_population

  def __init__(self):
    self.population_size = 20
    initial_population = [[0,1,2,3,4,5,6,7,8,9,10,11,12,13] for i in range(self.population_size)]
    initial_fitness_of_one_state = float(1/self.get_distance_of_state(initial_population[0]))
    initial_fitness = [initial_fitness_of_one_state for i in range(self.population_size)]

    generation_count = 0
    generation_array = []
    max_array = []
    max_all_time_fitness = initial_fitness_of_one_state

    for _ in range(500):
      initial_population = self.get_next_generation(initial_population,initial_fitness)
      generation_count += 1
      initial_fitness = [self.get_fitness(i) for i in initial_population]

      local_max_fitness = max(initial_fitness)
      print("GEN {} MAX {}".format(generation_count, local_max_fitness))

      generation_array.append(generation_count)
      max_array.append(local_max_fitness)

      if max_all_time_fitness < max(initial_fitness):
        max_all_time_fitness = max(initial_fitness)
        self.ans = initial_population[initial_fitness.index(max_all_time_fitness)]

    print('')
    print('Best fitness:', max_all_time_fitness)
    final_ans = []
    for x in self.ans:
      final_ans.append(chr(ord('A')+x))
    print('Best Path:', final_ans)

    # plt.plot(generation_array,max_array)
    # plt.show()

if __name__ == '__main__':
  print("Which progrom to run ( 1 for 8Queen, 2 for TSP ):")
  a = input("Enter: ")
  if a == '1':
    EightQueens()
  elif a == '2':
    TSP()