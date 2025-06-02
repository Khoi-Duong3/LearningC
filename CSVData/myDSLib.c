// CODE 1: Include necessary library(ies)
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
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

static char *strip_quotes(char *s) {
    size_t len = strlen(s);
    if (len >= 2 && s[0] == '"' && s[len-1] == '"') {
        s[len-1] = '\0';    // remove trailing quote
        return s + 1;       // skip leading quote
    }
    return s;
}

static int parse_csv_to_record(const char *buffer, Record *Rec){

    char parseBuffer[1024];
    strncpy(parseBuffer, buffer, sizeof(parseBuffer) - 1);
    parseBuffer[sizeof(parseBuffer) - 1] = '\0';

    char *token = strtok(parseBuffer, ",");
    if (!token){
        return -1;
    }
    token = strip_quotes(token);
    strncpy((*Rec).transaction_id, token, MAX_TRANSACTION_ID_LEN);
    (*Rec).transaction_id[MAX_TRANSACTION_ID_LEN - 1] = '\0';

    token = strtok(NULL, ",");
    if (!token){
        return -1;
    }
    token = strip_quotes(token);
    (*Rec).price = (unsigned) strtoul(token, NULL, 10);

    token = strtok(NULL, ",");
    if (!token){
        return -1;
    }
    token = strip_quotes(token);
    {
        int year, month, day;
        if (sscanf(token, "%4d-%2d-%2d", &year, &month, &day) != 3){
            return -1;
        }
        (*Rec).date.year = year;
        (*Rec).date.month = month;
        (*Rec).date.day = day;
    }

    token = strtok(NULL, ",");
    if(!token){
        return -1;
    }
    token = strip_quotes(token);
    strncpy((*Rec).postcode, token, MAX_POSTCODE_LEN);
    (*Rec).postcode[MAX_POSTCODE_LEN - 1] = '\0';

    token = strtok(NULL, ",");
    if (!token || strlen(token) < 1){
        return -1;
    }
    token = strip_quotes(token);
    (*Rec).property_type = token[0];

    token = strtok(NULL, ",");
    if (!token || strlen(token) < 1){
        return -1;
    }
    token = strip_quotes(token);
    (*Rec).old_new = token[0];

    token = strtok(NULL, ",");
    if (!token || strlen(token) < 1){
        return -1;
    }
    token = strip_quotes(token);
    (*Rec).duration = token[0];

    token = strtok(NULL, ",");
    if (!token){
        return -1;
    }
    token = strip_quotes(token);
    strncpy((*Rec).paon, token, MAX_FIELD_LEN);
    (*Rec).paon[MAX_FIELD_LEN - 1] = '\0';

    token = strtok(NULL, ",");
    if (!token){
        return -1;
    }
    token = strip_quotes(token);
    strncpy((*Rec).saon, token, MAX_FIELD_LEN);
    (*Rec).saon[MAX_FIELD_LEN - 1] = '\0';

    token = strtok(NULL, ",");
    if(!token){
        return -1;
    }
    token = strip_quotes(token);
    strncpy((*Rec).street, token, MAX_FIELD_LEN);
    (*Rec).street[MAX_FIELD_LEN - 1] = '\0';

    token = strtok(NULL, ",");
    if(!token){
        return -1;
    }
    token = strip_quotes(token);
    strncpy((*Rec).locality, token, MAX_FIELD_LEN);
    (*Rec).locality[MAX_FIELD_LEN - 1] = '\0';

    token = strtok(NULL, ",");
    if(!token){
        return -1;
    }
    token = strip_quotes(token);
    strncpy((*Rec).town, token, MAX_FIELD_LEN);
    (*Rec).town[MAX_FIELD_LEN - 1] = '\0';

    token = strtok(NULL, ",");
    if(!token){
        return -1;
    }
    token = strip_quotes(token);
    (*Rec).district = strdup(token);
    if (!(*Rec).district){
        return -1;
    }

    token = strtok(NULL, ",");
    if(!token){
        return -1;
    }
    token = strip_quotes(token);
    strncpy((*Rec).county, token, MAX_FIELD_LEN);
    (*Rec).county[MAX_FIELD_LEN - 1] = '\0';

    token = strtok(NULL, ",");
    if (!token || strlen(token) < 1){
        return -1;
    }
    token = strip_quotes(token);
    (*Rec).record_status = token[0];

    token = strtok(NULL, ",");
    if (!token || strlen(token) < 1){
        return -1;
    }
    token = strip_quotes(token);
    (*Rec).blank_col = token[0];

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