/* main2.c - driver program for the "fast" version of Graham's scan */
#include <stdio.h>
#include "stack.h"
#include "graham_scan.h"

/* These arrays are global because they are too big to be local variables */
Point points[MAX_SIZE];
Point hull[MAX_SIZE];

int main(void)
{
    char inputName[100];
    char outputName[100];
    FILE *inputFile;
    FILE *outputFile;
    int n, m, i;

    /* 1 and 2: ask for the filenames */
    printf("Enter input filename (with extension): ");
    if (scanf("%99s", inputName) != 1) {
        printf("Error: no input filename given\n");
        return 1;
    }

    printf("Enter output filename (with extension): ");
    if (scanf("%99s", outputName) != 1) {
        printf("Error: no output filename given\n");
        return 1;
    }

    /* 3: open the input file */
    inputFile = fopen(inputName, "r");
    if (inputFile == NULL) {
        printf("Error: cannot open %s\n", inputName);
        return 1;
    }

    /* 4: read n, then the n points */
    if (fscanf(inputFile, "%d", &n) != 1 || n < 0 || n > MAX_SIZE) {
        printf("Error: n must be from 0 to %d\n", MAX_SIZE);
        fclose(inputFile);
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (fscanf(inputFile, "%lf %lf", &points[i].x, &points[i].y) != 2) {
            printf("Error: could not read point number %d\n", i + 1);
            fclose(inputFile);
            return 1;
        }
    }

    /* 5: call the fast version of Graham's scan */
    m = grahamScan2(points, n, hull);

    /* 6: write the convex hull to the output file */
    outputFile = fopen(outputName, "w");
    if (outputFile == NULL) {
        printf("Error: cannot create %s\n", outputName);
        fclose(inputFile);
        return 1;
    }

    fprintf(outputFile, "%d\n", m);
    for (i = 0; i < m; i++) {
        fprintf(outputFile, "%10.6f  %10.6f\n", hull[i].x, hull[i].y);
    }

    /* 7: close both files */
    fclose(inputFile);
    fclose(outputFile);

    printf("Convex hull with %d points saved to %s\n", m, outputName);

    return 0;
}
