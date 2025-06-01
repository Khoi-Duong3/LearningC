// CODE 1: Include necessary library(ies)
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include "myDSLib.h"

// -----------------
Record* table = NULL; // DO NOT CHANGE: A global pointer to save the read data from csv files (a pointer to array of Records)
size_t table_size = 0;// DO NOT CHANGE: A global variable showing the number of rows (number of Records) read from csv files (rows in table)
// -----------------

// CODE 2: ADD more global variables if you need

// CODE 3: Implement all the functions here

unsigned int hash_string(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c

    return (unsigned int)(hash % INDEX_SIZE);
}

static int parse_csv_to_record(const char *buffer, Record *Rec){

    return 0;
}

void read_file(const char *filename){
    FILE *pfile = fopen(filename, "r");
    if (!pfile){
        fprintf(stderr, "ERROR: could not open file \"%s\": %s\n",
            filename, strerror(errno));
        exit(1);
    }

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), pfile) == NULL){
        fprintf(stderr, "Could not open %s", filename);
        fclose(pfile);
        exit(1);
    }

    while (fgets(buffer, sizeof(buffer), pfile)){
        Record *newTable = realloc(table, (table_size + 1) * sizeof(Record));

        if(!newTable){
            fprintf(stderr,
                "ERROR: realloc() failed when appending record %zu.\n",
                table_size);
            fclose(pfile);
            exit(1);
        }

        table = newTable;

        Record *dest = &table[table_size];
        if (parse_csv_to_record(buffer, dest) != 0){
            fprintf(stderr, "Failed to parse the CSV file on line %zu in %s", table_size + 2, filename);
            for (size_t i = 0; i < table_size; i++){
                free(table[i].district);
            }
            free(table);
            table = NULL;
            table_size = 0;
            fclose(pfile);
            exit(1);
        }

        table_size++;
    }
    
    fclose(pfile);
}