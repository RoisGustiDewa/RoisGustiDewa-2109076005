#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int POPULATION_SIZE = 100;
const int MAX_GENERATIONS = 100;
const int TARGET_VALUE = 30;
const int CHROMOSOME_LENGTH = 4;
const int MAX_MUTATION_RANGE = 5;
const double MUTATION_RATE = 0.1;

struct Chromosome {
    vector<int> genes;
    int fitness;

    Chromosome() {
        genes.resize(CHROMOSOME_LENGTH);
        fitness = 0;
    }
};

// Function to generate a random chromosome
Chromosome generateChromosome() {
    Chromosome chromosome;
    for (int i = 0; i < CHROMOSOME_LENGTH; ++i) {
        chromosome.genes[i] = rand() % (TARGET_VALUE + 1);
    }
    return chromosome;
}

// Function to evaluate the fitness of a chromosome
int evaluateFitness(const Chromosome& chromosome) {
    int result = chromosome.genes[0] + 4 * chromosome.genes[1] + 2 * chromosome.genes[2] + 3 * chromosome.genes[3];
    return abs(TARGET_VALUE - result);
}

// Function to perform chromosome selection based on fitness
vector<Chromosome> selection(const vector<Chromosome>& population) {
    vector<Chromosome> selectedPopulation;
    for (int i = 0; i < POPULATION_SIZE / 2; ++i) {
        int index1 = rand() % POPULATION_SIZE;
        int index2 = rand() % POPULATION_SIZE;
        const Chromosome& chromosome1 = population[index1];
        const Chromosome& chromosome2 = population[index2];
        selectedPopulation.push_back(chromosome1.fitness < chromosome2.fitness ? chromosome1 : chromosome2);
    }
    return selectedPopulation;
}

// Function to perform crossover between two chromosomes
Chromosome crossover(const Chromosome& parent1, const Chromosome& parent2) {
    Chromosome child;
    int crossoverPoint = rand() % CHROMOSOME_LENGTH;
    for (int i = 0; i < crossoverPoint; ++i) {
        child.genes[i] = parent1.genes[i];
    }
    for (int i = crossoverPoint; i < CHROMOSOME_LENGTH; ++i) {
        child.genes[i] = parent2.genes[i];
    }
    return child;
}

// Function to perform mutation on a chromosome
void mutate(Chromosome& chromosome) {
    for (int i = 0; i < CHROMOSOME_LENGTH; ++i) {
        double randomProbability = (double)rand() / RAND_MAX;
        if (randomProbability < MUTATION_RATE) {
            chromosome.genes[i] = (chromosome.genes[i] + (rand() % (2 * MAX_MUTATION_RANGE + 1))) % (TARGET_VALUE + 1);
        }
    }
}

int main() {
    srand(time(NULL));

    vector<Chromosome> population;
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        population.push_back(generateChromosome());
    }

    int generation = 0;
    while (generation < MAX_GENERATIONS) {
        // Evaluation
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            population[i].fitness = evaluateFitness(population[i]);
        }

        // Selection
        vector<Chromosome> selectedPopulation = selection(population);

        // Crossover
        vector<Chromosome> newPopulation;
        for (int i = 0; i < POPULATION_SIZE / 2; ++i) {
            Chromosome parent1 = selectedPopulation[i];
            Chromosome parent2 = selectedPopulation[i + POPULATION_SIZE / 2];
            Chromosome child1 = crossover(parent1, parent2);
            Chromosome child2 = crossover(parent2, parent1);
            newPopulation.push_back(child1);
            newPopulation.push_back(child2);
        }

        // Mutation
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            mutate(newPopulation[i]);
        }

        population = newPopulation;
        generation++;
    }

    // Find the best chromosome
    Chromosome bestChromosome = population[0];
    for (int i = 1; i < POPULATION_SIZE; ++i) {
        if (population[i].fitness < bestChromosome.fitness) {
            bestChromosome = population[i];
        }
    }

    // Print the best solution
    cout << "Best solution found: ";
    for (int i = 0; i < CHROMOSOME_LENGTH; ++i) {
        cout << bestChromosome.genes[i] << " ";
    }
    cout << endl;

    return 0;
}
