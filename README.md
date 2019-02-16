# TspOptimization

TspOptimization is a program for solving travelling salesman problems. Travelling salesman problem (TSP) is a problem of finding a shortest route that visits n cities. Coordinates of cities are given as an input.

This is a university project on a Software Engineering Department's fourth year course called Engineering Optimization Algorithms, at the School of Electrical Engineering from University of Belgrade.

Project is done in C++ programming language.

# Algorithm description

Program uses genetic algorithm for finding shortest path. In each generation algorithm goes to selection, reproduction and mutation phase.

In selection phase, algorithm sorts individuals based on their route length.

During the reproduction phase, algorithm uses top individuals to form next generation. 

In mutation phase, some gens may be swapped with other gens from same individual.

There are four parameters that user can set:

| Parameter | Description |
| ------ | ------ |
| Population size | Number of individuals in each generation |
| Mutation factor | Probability of each gen to mutate |
| Selection limit | Number of best individuals that will form next generation |
| Number of Generations | Number of generations that algorithm has for optimization |

# Usage

Following command can be used to compile code with g++ compiler. Command should be run in the project root.

```sh
$ g++ -o app ./headers/*.h ./source/*.cpp -O3
```

This command will create bin file named app.
-O3 part is optional, it is just a flag for compiler to generate more optimized code.

To run the program, there are two commands with different number of arguments.

```sh
$ ./app input_file output_file n 

$ ./app input_file output_file n population_size mutation_factor selection_limit number_of_generations
```

First command has only 3 arguments besides program name. Input file with coordinates of cities, output file in which program will write route length and the order of cities on that route. Argument n represents number of optimization function calls before delivering output file.

Second command has 7 arguments besides program name. First three arguments are the same, and next four are parameters for algorithm. Mutation factor is type double, and other three algorithm parameters are type int.

If first commands is used, algorithm will take default parameters (40000, 0.0001, 8000, 800).
