
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "myDSlib.h"



int main() {


    bool printFlagLinearSearch = false;
    bool printFlagHashIndexSearch = false;

    read_file("pp-2024.csv");  
    printf("Total records appneded: %zu\n", table_size);

    
    read_file("pp-2023.csv"); 
    printf("Total records appneded: %zu\n", table_size);


    IndexEntry** index_on_street = createIndexOnStreet(table, table_size);
    printf("\nHash index on street created.\n");


    const char* target = "GEORGE STREET";


    clock_t start_linear = clock();
    searchStreetLinear(table, table_size, target, printFlagLinearSearch);
    clock_t end_linear = clock();
    double linear_time = (double)(end_linear - start_linear) / CLOCKS_PER_SEC;

    clock_t start_hash = clock();
    searchStreet(index_on_street, target, printFlagHashIndexSearch);
    clock_t end_hash = clock();
    double hash_time = (double)(end_hash - start_hash) / CLOCKS_PER_SEC;
    

    printf("\nTime (Linear Search): %.6f seconds\n", linear_time);
    printf("Time (Hash Index)   : %.6f seconds\n", hash_time);
    


    int unused = count_unused_slots(index_on_street);
    printf("\nUnused hash slots: %d out of %d (%.2f%% unused)\n", unused, INDEX_SIZE, 100.0 * unused / INDEX_SIZE);
    int used = INDEX_SIZE - unused;
    double load_factor = (double)used / INDEX_SIZE;
    printf("Hash table load factor: %.3f\n", load_factor);

    free_index(index_on_street);
    free_table();

    return 0;
}