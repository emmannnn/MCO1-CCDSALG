CCDSALG MCO1 - Graham's Scan

Build both versions from this Code directory:

    gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -o main1 main1.c graham_scan1.c sort.c stack.c -lm
    gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -o main2 main2.c graham_scan2.c sort.c stack.c -lm

Run main1 for insertion sort (slow version) or main2 for merge sort (fast version).
When prompted, enter the input text filename and the output text filename.

Numerical robustness updates:
- The polar-angle comparator no longer groups angles using a fixed epsilon. That kind of comparison can be non-transitive and break sorting.
- The scan uses a scale-aware tolerance tied to double-precision rounding noise, instead of the previous 1e-10 turn cutoff.

The source was compiled with strict warnings and tested on the five included project input sizes, the 32,768-point maximum, duplicate/degenerate inputs, decimal-collinear data, a near-collinear hull case, and randomized inputs. This improves numerical robustness, but any floating-point tolerance necessarily represents a practical tradeoff for extremely tiny geometric turns.
