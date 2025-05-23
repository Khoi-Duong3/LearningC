#include <stdio.h>
#include <string.h> 

int main(){

    char fruits[][20] = {"Banana", "Apple", "Watermelon"};

    char names[3][25] = {0};
    int length = sizeof(names) / sizeof(names[0]);
    
    for (int i = 0; i < length; i++){
        printf("Enter a name: ");
        fgets(names[i], sizeof(names[0]), stdin);
        names[i][strlen(names[i]) - 1] = '\0';
    }

    for (int i = 0; i < length; i++){
        printf("%s\n", names[i]);
    }

    return 0;
}