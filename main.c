#include "set.h"
#include <time.h>

#define NO_ELEMENTS 5

void print_int(Data data);

int match_int(Data data1, Data data2) {
    return (*((int*) data1) - *((int*) data2));
}

/* ================================ */

int main(int argc, char** argv) {
    Set setA = NULL;
    Set setB = NULL;
    Data data = NULL;
    time_t t;

    srand((unsigned) time(&t));

    int array1[NO_ELEMENTS] = {1, 2, 3, 10, 2};
    int array2[NO_ELEMENTS] = {10, 9, 8, 1, 8};

    if ((setA = Set_new(match_int, print_int, NULL)) != NULL) {
        printf("Ok\n");

        for (size_t i = 0; i < NO_ELEMENTS; i++) {
            // Data x = (int*) malloc(sizeof(int));

            // *x = rand() % 50;

            Set_insert(setA, (array1 + i));
        }

        printf("setA: ");
        Set_print(setA, NULL);
    }

    if ((setB = Set_new(match_int, print_int, NULL)) != NULL) {
        printf("Ok\n");

        for (size_t i = 0; i < NO_ELEMENTS; i++) {
            // Data x = (int*) malloc(sizeof(int));

            // *x = rand() % 50;

            // Set_insert(setB, x);
        }
        
        printf("setB: ");
        Set_print(setB, NULL);
    }

    
    Set set = NULL;

    /* empty set laws */
    // set = Set_intersect(setA, setB, sizeof(int));
    // set = Set_union(setA, setB, sizeof(int));

    /* idempotency laws */
    set = Set_union(setA, setA, sizeof(int));
    printf("set: ");
    Set_print(set, NULL);

    Set_destroy(&setA);
    Set_destroy(&setB);
    Set_destroy(&set);

    return EXIT_SUCCESS;
}

/* ================================ */

void print_int(Data data) {
    printf("%d", *data);
}