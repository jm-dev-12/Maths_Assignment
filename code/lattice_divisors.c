#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* =========================================================
 * 1. MATHEMATICAL OPERATIONS (From scratch)
 * ========================================================= */

// Computes the Greatest Common Divisor (GCD) which acts as the glb (greatest lower bound)
int compute_gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Computes the Least Common Multiple (LCM) which acts as the lub (least upper bound)
int compute_lcm(int a, int b) {
    // Formula: a * b = gcd(a,b) * lcm(a,b)
    return (a * b) / compute_gcd(a, b);
}

/* =========================================================
 * 2. LATTICE AND POSET ANALYSIS FUNCTION
 * ========================================================= */

// Main function to analyze the divisor lattice for a given number n
void analyze_divisor_lattice(int n) {
    printf("\n=================================================\n");
    printf("   Analysis for n = %d\n", n);
    printf("=================================================\n");

    // --- Step A: Find all divisors ---
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) count++;
    }

    int* divisors = (int*)malloc(count * sizeof(int));
    int idx = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) divisors[idx++] = i;
    }

    printf("1. Divisors (%d total): { ", count);
    for (int i = 0; i < count; i++) {
        printf("%d%s", divisors[i], (i == count - 1) ? " }\n" : ", ");
    }

    // --- Step B: Build Divisibility Relation Matrix ---
    // M[i][j] = 1 means divisors[i] divides divisors[j]
    int** M = (int**)malloc(count * sizeof(int*));
    for (int i = 0; i < count; i++) {
        M[i] = (int*)malloc(count * sizeof(int));
        for (int j = 0; j < count; j++) {
            M[i][j] = (divisors[j] % divisors[i] == 0) ? 1 : 0;
        }
    }

    // --- Step C: Verify Partial Order Properties ---
    bool reflexive = true;
    bool antisymmetric = true;
    bool transitive = true;

    for (int i = 0; i < count; i++) {
        // Reflexive: Every element divides itself (Diagonal must be 1)
        if (M[i][i] == 0) reflexive = false; 
        
        for (int j = 0; j < count; j++) {
            // Antisymmetric: If a|b and b|a, then a == b
            if (i != j && M[i][j] == 1 && M[j][i] == 1) {
                antisymmetric = false; 
            }
            // Transitive: If a|b and b|c, then a|c
            if (M[i][j] == 1) {
                for (int k = 0; k < count; k++) {
                    if (M[j][k] == 1 && M[i][k] == 0) {
                        transitive = false; 
                    }
                }
            }
        }
    }
    printf("2. Partial Order Verification:\n");
    printf("   - Reflexive:     %s\n", reflexive ? "Passed" : "Failed");
    printf("   - Antisymmetric: %s\n", antisymmetric ? "Passed" : "Failed");
    printf("   - Transitive:    %s\n", transitive ? "Passed" : "Failed");

    // --- Step D: Lattice Extremes & Sample LUB/GLB ---
    int least = divisors[0];         // Always 1 for divisors
    int greatest = divisors[count-1]; // Always n for divisors
    printf("3. Extremal Elements:\n");
    printf("   - Minimal/Least element:    %d\n", least);
    printf("   - Maximal/Greatest element: %d\n", greatest);

    // Test a sample pair if enough divisors exist
    if (count >= 3) {
        int a = divisors[1]; // Usually 2 or the smallest prime factor
        int b = divisors[2]; // Usually 3 or the next factor
        printf("4. Sample Pair Verification (%d, %d):\n", a, b);
        printf("   - glb (Greatest Lower Bound / GCD): %d\n", compute_gcd(a, b));
        printf("   - lub (Least Upper Bound / LCM):    %d\n", compute_lcm(a, b));
    }

    // --- Step E: Generate Hasse Diagram (Transitive Reduction) ---
    // We create a Graphviz .dot file. We draw an edge from a to b if a|b, 
    // a != b, AND there is no intermediate c such that a|c and c|b.
    
    char filename[30];
    sprintf(filename, "Hasse_%d.dot", n);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error creating file %s!\n", filename);
        return;
    }
    
    fprintf(fp, "digraph Hasse_%d {\n", n);
    fprintf(fp, "    // Graph styling\n");
    fprintf(fp, "    node [shape=circle, style=filled, fillcolor=lightblue, fontname=\"Helvetica-Bold\"];\n");
    fprintf(fp, "    edge [dir=none]; // Hasse diagrams omit directional arrows\n\n");

    printf("5. Hasse Diagram Edges (Transitive Reduction Applied):\n   { ");
    bool first_edge = true;
    
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (i != j && M[i][j] == 1) {
                // Check for intermediate divisor
                bool has_intermediate = false;
                for (int k = 0; k < count; k++) {
                    if (k != i && k != j && M[i][k] == 1 && M[k][j] == 1) {
                        has_intermediate = true;
                        break;
                    }
                }
                
                // If no intermediate, it's a direct edge in the Hasse diagram
                if (!has_intermediate) {
                    if (!first_edge) printf(", ");
                    printf("(%d-%d)", divisors[i], divisors[j]);
                    // Draw edge from bottom (smaller) to top (larger)
                    fprintf(fp, "    %d -> %d;\n", divisors[j], divisors[i]); 
                    first_edge = false;
                }
            }
        }
    }
    printf(" }\n");
    fprintf(fp, "}\n");
    fclose(fp);
    printf("   >> Successfully generated: '%s'\n", filename);

    // --- Memory Cleanup ---
    for (int i = 0; i < count; i++) free(M[i]);
    free(M);
    free(divisors);
}

/* =========================================================
 * 3. MAIN ENTRY POINT (Interactive Version)
 * ========================================================= */
int main() {
    int choice;
    printf("=================================================\n");
    printf("   Divisor Lattice & Hasse Diagram Generator\n");
    printf("=================================================\n");
    printf("Select Mode:\n");
    printf("  1. Run required assignment values (12, 30, 36, 60, 210)\n");
    printf("  2. Enter a custom value for n\n");
    printf("Enter choice (1 or 2): ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    if (choice == 1) {
        int test_values[] = {12, 30, 36, 60, 210};
        int num_tests = sizeof(test_values) / sizeof(test_values[0]);
        for (int i = 0; i < num_tests; i++) {
            analyze_divisor_lattice(test_values[i]);
        }
    } else if (choice == 2) {
        int custom_n;
        printf("\nEnter a positive integer n: ");
        if (scanf("%d", &custom_n) == 1 && custom_n > 0) {
            analyze_divisor_lattice(custom_n);
        } else {
            printf("Please enter a valid positive integer.\n");
        }
    } else {
        printf("Invalid choice.\n");
    }

    printf("\nAnalysis Complete. Use Graphviz to convert the .dot files to .png!\n");
    return 0;
}