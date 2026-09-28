#include <stdio.h>

#define TABLE_SIZE 11
#define N 8

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void initializeTable(int table[]) {
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = -1;
}

int insertHash(int table[], int key) {
    int index = hashFunction(key);
    int start = index;
    int collisions = 0;

    while (table[index] != -1) {
        collisions++;
        index = (index + 1) % TABLE_SIZE;

        if (index == start) {
            printf("Hash table is full. Cannot insert %d.\n", key);
            return collisions;
        }
    }

    table[index] = key;
    return collisions;
}

int hashSearch(int table[], int key, int *comparisons) {
    int index = hashFunction(key);
    int start = index;
    *comparisons = 0;

    while (table[index] != -1) {
        (*comparisons)++;
        if (table[index] == key)
            return index;

        index = (index + 1) % TABLE_SIZE;
        if (index == start)
            break;
    }

    return -1;
}

int linearSearch(int a[], int n, int key, int *comparisons) {
    *comparisons = 0;

    for (int i = 0; i < n; i++) {
        (*comparisons)++;
        if (a[i] == key)
            return i;
    }

    return -1;
}

void displayTable(int table[]) {
    printf("\nHash Table:\n");
    printf("Index\tValue\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] == -1)
            printf("%d\t-\n", i);
        else
            printf("%d\t%d\n", i, table[i]);
    }
}

int main() {
    int songIDs[N] = {105, 210, 315, 420, 525, 630, 735, 840};
    int table[TABLE_SIZE];

    initializeTable(table);

    printf("GROUP 7 - HASHING USING DIVISION METHOD\n");
    printf("Table size = %d\n", TABLE_SIZE);

    printf("\nInsertion results:\n");
    printf("ID\tHash Index\tCollisions\n");

    int totalCollisions = 0;

    for (int i = 0; i < N; i++) {
        int index = hashFunction(songIDs[i]);
        int collisions = insertHash(table, songIDs[i]);

        printf("%d\t%d\t\t%d\n", songIDs[i], index, collisions);
        totalCollisions += collisions;
    }

    displayTable(table);

    printf("\nTotal collisions = %d\n", totalCollisions);
    printf("Number of keys = %d\n", N);
    printf("Load factor = %.2f\n", (float)N / TABLE_SIZE);

    int key;
    char choice;

    do {
        int hashComparisons, linearComparisons;
        int hashPosition, linearPosition;

        printf("\nEnter a song ID to search: ");
        scanf("%d", &key);

        hashPosition = hashSearch(table, key, &hashComparisons);
        linearPosition = linearSearch(songIDs, N, key, &linearComparisons);

        printf("\nSearch result for %d:\n", key);

        if (hashPosition != -1)
            printf("Hashing: Found at table index %d, comparisons = %d\n",
                   hashPosition, hashComparisons);
        else
            printf("Hashing: Not found, comparisons = %d\n", hashComparisons);

        if (linearPosition != -1)
            printf("Linear Search: Found at array position %d, comparisons = %d\n",
                   linearPosition, linearComparisons);
        else
            printf("Linear Search: Not found, comparisons = %d\n",
                   linearComparisons);

        printf("\nSearch again? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
