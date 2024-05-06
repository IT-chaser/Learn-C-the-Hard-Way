#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES, 
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int main(int argc, char *argv[]) {
    Person you = { .age = 0 };
    int i = 0;
    // char *in = NULL;
    int rc = 0;

    printf("What is your first name? ");
    // in = fgets(you.first_name, MAX_DATA - 1, stdin);
    // check(in != NULL, "Failed to read first name.");

    // char *firstName = gets(you.first_name);
    // rc = fscanf(stdin, "%50s", you.first_name);
    
    rc = scanf("%50s", you.first_name);
    check(rc > 0, "Failed to read first name.");

    printf("What is your last name? ");
    // in = fgets(you.last_name, MAX_DATA - 1, stdin);
    // check(in != NULL, "Failed to read last name.");
    
    // char *lastName = gets(you.last_name);
    // rc = fscanf(stdin, "%50s", you.last_name);

    rc = scanf("%50s", you.last_name);
    check(rc > 0, "Failed to read last name.");

    printf("How old are you? ");
    // int rc = fscanf(stdin, "%d", &you.age);

    // char ages[MAX_DATA];
    // in = fgets(ages, sizeof(ages), stdin);
    // you.age = atoi(ages);
    // check(in != NULL, "Failed to read age.");
    
    rc = scanf("%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for (i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    // char eyesString[MAX_DATA];
    // in = fgets(eyesString, sizeof(eyesString), stdin);
    // eyes = atoi(eyesString);
    // check(in != NULL, "You have to enter a number.");

    // rc = fscanf(stdin, "%d", &eyes);

    rc = scanf("%d", &eyes);
    check(rc > 0, "You have to enter a number");

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that is not an option.");

    printf("How much do you make an hour? ");
    // char incomes[MAX_DATA];
    // in = fgets(incomes, sizeof(incomes), stdin);
    // you.income = atof(incomes);
    // check(in != NULL, "Enter floating point number.");

    // rc = fscanf(stdin, "%f", &you.income);
    
    rc = scanf("%f", &you.income);
    check(rc > 0, "Enter floating point number.");
    
    printf("-------RESULTS------\n");

    printf("First name: %s\n", you.first_name);
    printf("Last name: %s\n", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
error:

    return -1;
}