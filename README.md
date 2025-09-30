# N-Puzzle Solving AI

## Project Overview

This project implements an AI-based solution for the N-Puzzle problem using the A* search algorithm with two different heuristics: Hamming Distance and Manhattan Distance. The N-Puzzle is a sliding puzzle that consists of a frame of numbered square tiles in random order with one tile missing. The objective is to place the tiles in order by making sliding moves that use the empty space.

## Problem Description

The N-Puzzle problem involves a k×k grid where tiles numbered 1 to k²-1 are arranged randomly, with one empty space (represented by '*'). The goal is to arrange the tiles in ascending order from left to right, top to bottom, with the empty space in the bottom-right corner.

## Author

**Tawkir Aziz Rahman** (Student ID: 2005090)

## File Structure

```
N_Puzzle_Solving_AI_Offline_3-2/
├── 2005090.cpp          # Main implementation file
└── README.md           # Project documentation
```

## Core Components

### 1. Matrix Class

The `Matrix` class is the fundamental data structure representing a puzzle state:

#### Key Attributes:
- `vector<vector<string>> mt`: 2D vector storing the puzzle state as strings
- `ll n`: Dimension of the puzzle (k×k)
- `ll move`: Number of moves taken to reach this state from the initial state
- `Matrix *parent`: Pointer to the parent state for path reconstruction
- `ll hammingDistance`: Cached Hamming distance value
- `ll manhattanDistance`: Cached Manhattan distance value

#### Key Methods:
- `getAString()`: Converts the matrix to a string representation for state comparison
- `getOneDirectional()`: Converts 2D matrix to 1D vector in row-major order
- `findInversions()`: Counts inversions to determine puzzle solvability
- `findBlankPos()`: Locates the position of the empty space
- `moveUp()`, `moveDown()`, `moveLeft()`, `moveRight()`: Generate successor states
- `findHammingDistance()`: Calculates Hamming distance heuristic
- `findManhattanDistance()`: Calculates Manhattan distance heuristic
- `findAllMoves()`: Returns all valid successor states

### 2. A* Search Algorithm Implementation

The `starSearchAlgo` class implements the A* search algorithm:

#### Key Features:
- **Dual Heuristic Support**: Implements both Hamming and Manhattan distance heuristics
- **Solvability Check**: Determines if the initial state is solvable before attempting to solve
- **Memory Management**: Proper allocation and deallocation of matrix objects
- **Path Reconstruction**: Traces back from goal state to initial state for solution path

#### Solvability Rules:
- For odd-sized puzzles (k is odd): Solvable if inversion count is even
- For even-sized puzzles (k is even): Solvable if (inversion count + blank row from bottom) has odd parity

### 3. Heuristic Functions

#### Hamming Distance
Counts the number of tiles that are not in their correct position (excluding the blank space).

#### Manhattan Distance
Calculates the sum of Manhattan distances of all tiles from their goal positions. For each tile, it computes the absolute difference in row positions plus the absolute difference in column positions.

### 4. Priority Queue Implementation

Uses a custom comparator (`Compare` struct) for the priority queue to implement the A* algorithm's f(n) = g(n) + h(n) evaluation function:
- g(n): Number of moves from start state
- h(n): Heuristic distance (Hamming or Manhattan)
- f(n): Total estimated cost

## Algorithm Details

### A* Search Process

1. **Initialization**: Add initial state to priority queue with f(n) = h(n)
2. **Main Loop**:
   - Pop state with lowest f(n) value
   - Check if goal state is reached (heuristic distance = 0)
   - Generate all valid successor states
   - Add unexplored successors to priority queue
   - Continue until goal is found or queue is empty
3. **Path Reconstruction**: Trace parent pointers from goal to start

### State Representation

States are represented as strings using the `getAString()` method with '|' delimiters for efficient duplicate detection using hash maps.

## Input Format

```
k
tile₁₁ tile₁₂ ... tile₁ₖ
tile₂₁ tile₂₂ ... tile₂ₖ
...
tileₖ₁ tileₖ₂ ... tileₖₖ
```

Where:
- `k` is the dimension of the puzzle
- Each tile is either a number (1 to k²-1) or '*' for the empty space

## Output Format

For each heuristic (Hamming and Manhattan), the program outputs:

1. **Solvability Status**: Whether the puzzle is solvable
2. **Solution Statistics**:
   - Number of steps needed
   - Total expanded nodes
   - Total explored nodes
3. **Solution Path**: Complete sequence of states from initial to goal

## Compilation and Execution

### Prerequisites
- C++ compiler with C++11 support or higher
- GCC or Clang recommended

### Compilation
```bash
g++ -std=c++11 -O2 2005090.cpp -o n_puzzle_solver
```

### Execution
```bash
./n_puzzle_solver < input.txt
```

Or for interactive input:
```bash
./n_puzzle_solver
```

## Example Usage

### Input
```
3
1 2 3
4 * 6
7 5 8
```

### Expected Output
```
For Hamming distance:--
Steps needed using  Hamming  distance:= X
Total expanded Nodes:= Y
Total explored Nodes:= Z
[Solution path with matrices]

For Manhattan Distance:--
Steps needed using  Manhattan  distance:= X
Total expanded Nodes:= Y
Total explored Nodes:= Z
[Solution path with matrices]
```

## Performance Characteristics

### Time Complexity
- **Best Case**: O(b^d) where b is branching factor and d is solution depth
- **Worst Case**: O(b^d) for admissible heuristics
- **Average Case**: Depends on heuristic quality and problem instance

### Space Complexity
- O(b^d) for storing explored states and priority queue

### Heuristic Comparison
- **Manhattan Distance**: Generally more informed, leading to fewer expanded nodes
- **Hamming Distance**: Simpler to compute but less informed

## Technical Implementation Details

### Memory Management
- Dynamic allocation using `new` and `delete`
- Proper cleanup in destructor and `freeMatrices()` method
- Prevention of memory leaks through careful pointer management

### Data Structures
- **Priority Queue**: For A* frontier management
- **Unordered Map**: For duplicate state detection
- **Set**: For closed list management
- **Stack**: For solution path reconstruction

### Optimization Features
- **Memoization**: Caches heuristic calculations to avoid recomputation
- **Duplicate Detection**: Prevents revisiting explored states
- **Early Termination**: Stops search when goal is reached

## Utility Functions

The codebase includes several utility functions for debugging and analysis:

- `printVector()`: Prints 1D vectors
- `printVectorPair()`: Prints vectors of pairs
- `printMatrix()`: Prints 2D matrices
- `printStructure()`: Prints STL containers
- `printMatrixClass()`: Prints Matrix objects
- `printPriorityQueue()`: Prints priority queue contents (for debugging)

## Algorithm Verification

The implementation includes verification mechanisms:

1. **Solvability Check**: Prevents infinite search on unsolvable instances
2. **Inversion Counting**: Mathematical verification of puzzle solvability
3. **Path Validation**: Ensures solution path is valid through parent tracking

## Limitations and Considerations

1. **Memory Usage**: Large puzzles may require significant memory for state storage
2. **Computation Time**: Complex puzzles may take considerable time to solve
3. **Input Validation**: Limited error checking for malformed input
4. **Fixed Goal State**: Assumes standard goal configuration (1,2,3...k²-1,*)

## Educational Value

This implementation demonstrates several important computer science concepts:

- **Artificial Intelligence**: Heuristic search algorithms
- **Data Structures**: Priority queues, hash tables, graphs
- **Algorithm Design**: A* search, graph traversal
- **Problem Solving**: State space search, optimization
- **Software Engineering**: Object-oriented design, memory management

## Future Enhancements

Potential improvements could include:

1. **Bidirectional Search**: Implement bidirectional A* for better performance
2. **Pattern Database Heuristics**: More sophisticated heuristic functions
3. **Iterative Deepening A***: Memory-efficient variant
4. **GUI Interface**: Visual representation of puzzle solving
5. **Performance Metrics**: Detailed timing and memory usage analysis
6. **Input Validation**: Robust error handling and input checking

## License

This project is developed as part of an academic assignment. Please refer to your institution's academic integrity policies before using this code.

---

*This implementation serves as an educational example of AI search algorithms and should be used responsibly in accordance with academic guidelines.*