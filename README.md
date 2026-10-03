# Group 3: Structure of the Divisors of n as a Partially Ordered Set

**Topic:** Hasse Diagrams and the Lattice of Divisors  
**Roll Numbers:** 11, 12, 13, 14, 15

## Project Description
This project models the divisors of a number n as a Partially Ordered Set (Poset) under the divisibility relation. The C program is implemented entirely from scratch to build the divisibility relation matrix, verify partial order properties (reflexive, antisymmetric, transitive), compute LUB/GLB (LCM/GCD), and automatically generate transitive-reduced edges for Hasse diagrams.

## Repository Structure
Conforming to the assignment guidelines, this submission is organized into three folders:
*   report/ - Contains the 8-12 page PDF report (Theory, Flowcharts, Analysis, Sublattices, Conclusions, and Contribution statements).
*   code/ - Contains this README and the C source code (lattice_divisors.c).
*   results/ - Contains the generated Hasse diagram images (.png files) and the terminal execution logs.

## Prerequisites
To compile and run this code, you will need:
1.  A C Compiler: standard gcc or clang.
2.  Graphviz (Optional but recommended): Required to locally render the generated .dot graph files into .png images. You can download it from graphviz.org/download/. Alternatively, you can use Graphviz Online (dreampuf.github.io/GraphvizOnline/).

## Compilation and Execution

1. Compile the code:
Open your terminal/command prompt, navigate to the code/ folder, and run:
gcc lattice_divisors.c -o lattice_divisors

2. Run the program:
On Linux / macOS:
./lattice_divisors

On Windows:
lattice_divisors.exe

3. Interactive Menu:
When you run the program, you will be prompted with a menu:
*   Press 1: Automatically runs the required assignment values (n = 12, 30, 36, 60, 210) in batch mode.
*   Press 2: Allows you to enter any custom positive integer n to test.

## Generating the Hasse Diagrams
The C program mathematically computes the transitive reduction and outputs .dot files (e.g., Hasse_12.dot). To convert these text files into hierarchical Hasse diagram images, use the Graphviz dot command in your terminal:

dot -Tpng Hasse_12.dot -o Hasse_12.png
dot -Tpng Hasse_30.dot -o Hasse_30.png
dot -Tpng Hasse_36.dot -o Hasse_36.png
dot -Tpng Hasse_60.dot -o Hasse_60.png
dot -Tpng Hasse_210.dot -o Hasse_210.png

(Move the resulting .png files into the results/ folder).

## Note on Libraries
As per the strict grading rubric, no external math or graph logic libraries were used. The adjacency matrix generation, Greatest Common Divisor (GCD), Least Common Multiple (LCM), and the transitive reduction algorithm (to remove redundant edges for the Hasse diagram) were all coded logically from scratch in standard C. Graphviz is used strictly as an external rendering tool to visualize our mathematical output.

---
Prepared for Discrete Mathematics Project | October 2026
