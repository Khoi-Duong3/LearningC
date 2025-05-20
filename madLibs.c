#include <stdbool.h>
#include <string.h>
#include <stdio.h>

int madLibs() {
    char noun[50] = "";
    char verb[50] = "";
    char adj1[50] = "";
    char adj2[50] = "";
    char adj3[50] = "";

    printf("Enter an adjective (descriptive word): ");
    fgets(adj1, sizeof(adj1), stdin);
    adj1[strlen(adj1) - 1] = '\0';

    printf("Enter a noun (person or animal): ");
    fgets(noun, sizeof(noun), stdin);
    noun[strlen(noun) - 1] = '\0';

    printf("Enter an adjective (descriptive word): ");
    fgets(adj2, sizeof(adj2), stdin);
    adj2[strlen(adj2) - 1] = '\0';

    printf("Enter a verb (action ending in -ing): ");
    fgets(verb, sizeof(verb), stdin);
    verb[strlen(verb) - 1] = '\0';

    printf("Enter an adjective (descriptive word): ");
    fgets(adj3, sizeof(adj3), stdin);
    adj3[strlen(adj3) - 1] = '\0';



}

int main() {

}