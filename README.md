# Travelling Salesman Problem

A solution to the [Travelling Salesman Problem](<https://en.wikipedia.org/wiki/Travelling_salesman_problem>)  

# Algorithms

## Brute Force

Searches every permutation returning the shortest, so the solution is always optimal but has O(n!) complexity.

## Genetic

An implementation of a [Genetic algorithm](<https://en.wikipedia.org/wiki/Genetic_algorithm>) using [Two-point](<https://en.wikipedia.org/wiki/Crossover_(genetic_algorithm)#Two-point_and_k-point_crossover>) crossover.

# Building from source

You will need to install the [boost libraries](https://www.boost.org/doc/libs/1_78_0/more/getting_started/unix-variants.html#easy-build-and-install)

Then run:

```
./make.sh
```

# Running

## Generate a random problem and solve it:

```
./build/apps/tsman --nodes 10 --output-dir output
```

This will generate a problem with 10 nodes, and compute a solution with outputs saved to the _output_ directory.

These outputs are:

- _graph.txt_ - the generated problem which is a [graph file](#Graph-files)

- _brute_force_path.txt_ and _genetic_path.txt_ - the vertices of the shortest path computed by each algorithm

## Read a problem from file and solve it:

```
./build/apps/tsman --graph-file graph.txt --output-dir output
```

This will read the problem from _graph.txt_ and write the solution to the output directory.


# Graph files

The graph file contains an adjacency matrix for the weighted graph.  The matrix has in position (i, j) the distance between vertices vi and vj.  If there is no path from i to j, this is represented as a dash: '-'.

# License

[GNU General Public License v3.0](https://choosealicense.com/licenses/gpl-3.0/)

