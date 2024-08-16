from genetic_algorithm import GeneticAlgorithm
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib_inline
if __name__ == "__main__":
    # TODO Experiment 1...
    # Starting with the following
    ga = GeneticAlgorithm(
        population_size=50,
        mutation_rate=0.1,
        mutation_strength=1,
        crossover_rate=0.5,
        num_generations=50,
    )
    # We will then vary each parameter and notice its effects on the best fitness value, and average of mean fitness value
    best_solutions, best_fitness_values, average_fitness_values = ga.evolve(seed=100)
    print(best_fitness_values)
    