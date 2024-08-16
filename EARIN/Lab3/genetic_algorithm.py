import random
from functions import styblinski_tang_2d
import numpy as np
import numpy.typing as npt

def set_seed(seed: int) -> None:
    # Set fixed random seed to make the results reproducible
    random.seed(seed)
    np.random.seed(seed)


class GeneticAlgorithm:
    def __init__(
        self,
        population_size: int,
        mutation_rate: float,
        mutation_strength: float,
        crossover_rate: float,
        num_generations: int,
    ):
        self.population_size = population_size
        self.mutation_rate = mutation_rate
        self.mutation_strength = mutation_strength
        self.crossover_rate = crossover_rate
        self.num_generations = num_generations

    def initialize_population(self) -> npt.ArrayLike:
        # TODO Initialize the population and return the result
        # Initialize a collection, of {population_size} number of individuals, where each individual has a random pair of (x, y), where x and y range in [-5, 5]
        return np.random.uniform(-5, 5, (self.population_size, 2))

    def evaluate_population(self, population: npt.ArrayLike) -> npt.ArrayLike:
        # TODO Evaluate the fitness of the population and return the values for each individual in the population
        return styblinski_tang_2d(population[:, 0], population[:, 1])

    def BinSearch(self, x, p):
        low = 0
        high = len(x)
        mid = 0
        
        while low<=high:
            mid = (high+low) // 2
            
            if x[mid] < p:
                low = mid + 1
            elif x[mid] > p:
                high = mid - 1
        return mid
    def selection(self, population: npt.ArrayLike, fitness_values: npt.ArrayLike) -> npt.ArrayLike:
        # TODO Implement selection mechanism and return the selected individual
        #Let's construct matrix with rank, population, fitness values, and probabilities
        matrix = np.zeros((self.population_size, 1))
        fitness_values = np.reshape(fitness_values, (-1, 1))
        matrix = np.hstack((matrix, population))
        matrix = np.hstack((matrix, fitness_values))
        
        sorted_indices = np.lexsort((matrix[:, 3],))
        matrix_ascending = matrix[np.flipud(sorted_indices)]
        ranks = np.arange(1, (self.population_size+1))     # Initializes an array of ranks from 1 to self.population_size
        matrix_ascending[:, 0] = ranks
        N_rank = np.sum(ranks)
        probabilities = ranks/N_rank
        probabilities = np.reshape(probabilities, (-1, 1))
        matrix_ascending = np.hstack((matrix_ascending, probabilities))
        CDF = np.zeros(len(ranks))
        o = 0
        for i in range(len(probabilities)):
            CDF[i] = probabilities[i] + o
            o = CDF[i]
        p = np.random.uniform(0, 1, len(probabilities))
        indices = np.zeros(len(probabilities))
        for i in range(len(p)):
            ind = self.BinSearch(CDF, p[i])
            indices[i] = ind
        ind = np.array(indices, dtype=int)
        parents = matrix_ascending[ind][:, 1:3]
        return parents.reshape(((self.population_size // 2)), 4)

    def crossover(self, parents: npt.ArrayLike) -> npt.ArrayLike:
        # TODO Implement the crossover mechanism over the parents and return the offspring
        alpha = np.random.uniform(0, 1)
        beta = 1 - alpha
        for i in range(len(parents)):
            if (np.random.uniform(0,1) < self.crossover_rate):
                c1 = self.crossover_helper(parents[i], alpha, beta)
                parents[i] = c1
        return parents
    
    def crossover_helper(self, parents, alpha, beta):
        return np.array([alpha*parents[0]+beta*parents[2], alpha*parents[1]+beta*parents[3], beta*parents[0]+alpha*parents[2], beta*parents[1]+alpha*parents[3]])

    
    def mutate(self, individuals) -> npt.ArrayLike:
        # TODO Implement mutation mechanism over the given individuals and return the results
        for i in range(len(individuals)):
            if (np.random.normal(0,1) < self.mutation_rate):
                gaussian = np.random.normal(0, self.mutation_strength, (1, 4))
                individuals[i] = individuals[i] + gaussian
                   
        return individuals
    
    
    def evolve(self, seed: int) -> ...:
        # Run the genetic algorithm and return the lists that contain the best solution for each generation,
        #   the best fitness for each generation and average fitness for each generation
        set_seed(seed)

        population = self.initialize_population()

        best_solutions = np.zeros((self.num_generations,2))
        best_fitness_values = np.zeros((self.num_generations, 1))
        average_fitness_values = np.zeros((self.num_generations, 1))

        for generation in range(self.num_generations):
            fitness_values = self.evaluate_population(population)
            parents_for_reproduction = self.selection(population, fitness_values)
            offspring = self.crossover(parents_for_reproduction)
            population = self.mutate(offspring)
            population = population.reshape(-1, 2)
            
            # TODO compute fitness of the new generation and save the best solution, best fitness and average fitness
            
            fitness_values = self.evaluate_population(population)
            min = fitness_values.min()
            best_fitness_values[generation] = min
            best_solutions[generation] = population[np.where(fitness_values == min)[0][0]]
            average_fitness_values[generation] = np.mean(fitness_values)
            
            

        return best_solutions, best_fitness_values, average_fitness_values