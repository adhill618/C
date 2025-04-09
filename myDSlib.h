#ifndef MYDSLIB_H
#define MYDSLIB_H

#include <stddef.h>
#include <stdbool.h>

#define MAX_FIELD_LEN 100
#define MAX_TRANSACTION_ID_LEN 39
#define MAX_POSTCODE_LEN 9

#define INDEX_SIZE 100007

typedef struct {
    int year, month, day;
} Date;

typedef struct {
    char transaction_id[MAX_TRANSACTION_ID_LEN];
    unsigned int price;
    Date date;
    char postcode[MAX_POSTCODE_LEN];
    char property_type;
    char old_new;
    char duration;
    char paon[MAX_FIELD_LEN];
    char saon[MAX_FIELD_LEN];
    char street[MAX_FIELD_LEN];            
    char locality[MAX_FIELD_LEN];
    char town[MAX_FIELD_LEN];
    char *district;
    char county[MAX_FIELD_LEN];
    char record_status;
    char blank_col;
} Record;

typedef struct IndexEntry {
    char* key;
    Record* record_ptr;
    struct IndexEntry* next;
} IndexEntry;

extern Record* table;
extern size_t table_size;


unsigned int hash_string(const char* str);

void read_file(const char* filename);

IndexEntry** createIndexOnStreet(Record* table, size_t size);

void searchStreetLinear(Record* table, size_t size, const char* street, bool print);
void searchStreet(IndexEntry** index, const char* street, bool print);


int count_unused_slots(IndexEntry** index);
void free_index(IndexEntry** index);
void free_table();

#endif
