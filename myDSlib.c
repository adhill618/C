
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "myDSlib.h"
#include <stdbool.h>


Record* table = NULL;
size_t table_size = 0;


unsigned int hash_string(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  
    return (unsigned int)(hash % INDEX_SIZE);
}

void read_file(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char line[1024];
    fgets(line, sizeof(line), fp); 

    while (fgets(line, sizeof(line), fp)) {
        table = realloc(table, (table_size + 1) * sizeof(Record));
        Record* rec = &table[table_size];

        char* token = strtok(line, ",");
        strncpy(rec->transaction_id, token, MAX_TRANSACTION_ID_LEN);

        token = strtok(NULL, ",");
        rec->price = atoi(token);

        token = strtok(NULL, "-");
        rec->date.year = atoi(token);
        token = strtok(NULL, "-");
        rec->date.month = atoi(token);
        token = strtok(NULL, ",");
        rec->date.day = atoi(token);

        strncpy(rec->postcode, strtok(NULL, ","), MAX_POSTCODE_LEN);
        rec->property_type = *strtok(NULL, ",");
        rec->old_new = *strtok(NULL, ",");
        rec->duration = *strtok(NULL, ",");
        strncpy(rec->paon, strtok(NULL, ","), MAX_FIELD_LEN);
        strncpy(rec->saon, strtok(NULL, ","), MAX_FIELD_LEN);
        strncpy(rec->street, strtok(NULL, ","), MAX_FIELD_LEN);
        strncpy(rec->locality, strtok(NULL, ","), MAX_FIELD_LEN);
        strncpy(rec->town, strtok(NULL, ","), MAX_FIELD_LEN);

        char* district_temp = strtok(NULL, ",");
        rec->district = malloc(strlen(district_temp) + 1);
        strcpy(rec->district, district_temp);

        strncpy(rec->county, strtok(NULL, ","), MAX_FIELD_LEN);
        rec->record_status = *strtok(NULL, ",");
        rec->blank_col = *strtok(NULL, ",");

        table_size++;
    }

    fclose(fp);
}

IndexEntry** createIndexOnStreet(Record* table, size_t size) {
    IndexEntry** index = calloc(INDEX_SIZE, sizeof(IndexEntry*));

    for (size_t i = 0; i < size; i++) {
        unsigned int pos = hash_string(table[i].street);

        IndexEntry* new_entry = malloc(sizeof(IndexEntry));
        new_entry->key = malloc(strlen(table[i].street) + 1);
        strcpy(new_entry->key, table[i].street);
        new_entry->record_ptr = &table[i];
        new_entry->next = index[pos];
        index[pos] = new_entry;
    }

    return index;
}

void searchStreetLinear(Record* table, size_t size, const char* street, bool print) {
    for (size_t i = 0; i < size; i++) {
        if (strcmp(table[i].street, street) == 0) {
            if (print) {
                printf("Match found (linear): Street = %s | Price = %u | Postcode = %s | Date = %04d-%02d-%02d\n",
                       table[i].street,
                       table[i].price,
                       table[i].postcode,
                       table[i].date.year,
                       table[i].date.month,
                       table[i].date.day);
            }
        }
    }
}

void searchStreet(IndexEntry** index, const char* street, bool print) {
    unsigned int pos = hash_string(street);
    IndexEntry* curr = index[pos];

    while (curr) {
        if (strcmp(curr->key, street) == 0) {
            if (print) {
                printf("Match found: Street = %s | Price = %u | Postcode = %s | Date = %04d-%02d-%02d\n",
                       curr->record_ptr->street,
                       curr->record_ptr->price,
                       curr->record_ptr->postcode,
                       curr->record_ptr->date.year,
                       curr->record_ptr->date.month,
                       curr->record_ptr->date.day);
            }
        }
        curr = curr->next;
    }
}


int count_unused_slots(IndexEntry** index) {
    int count = 0;
    for (int i = 0; i < INDEX_SIZE; i++) {
        if (index[i] == NULL)
            count++;
    }
    return count;
}

void free_index(IndexEntry** index) {
    for (int i = 0; i < INDEX_SIZE; i++) {
        IndexEntry* curr = index[i];
        while (curr) {
            IndexEntry* temp = curr;
            curr = curr->next;
            free(temp->key);
            free(temp);
        }
    }
    free(index);
}

void free_table() {
    for (size_t i = 0; i < table_size; i++) {
        free(table[i].district);
    }
    free(table);
}
