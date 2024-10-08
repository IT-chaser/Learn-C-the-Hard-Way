#include <stdio.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person Person_create(char *name, int age, int height, int weight) {
    struct Person who;
    who.name = strdup(name);
    who.age = age;
    who.height = height;
    who.weight = weight;

    return who;
}

void Person_print(struct Person who) {
    printf("Name: %s\n", who.name);
    printf("Age: %d\n", who.age);
    printf("Height: %d\n", who.height);
    printf("Weight: %d\n", who.weight);
}

int main(int argc, char *argv[]) {
    // make two people structures
    struct Person joe = Person_create("Joe Alex", 32, 64, 140);

    struct Person frank = Person_create("Sardor Aliev", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", &joe);
    Person_print(joe);

    printf("-----\n");

    printf("Frank is at memory location %p:\n", &frank);
    Person_print(frank);

    printf("-----\n");

    // make everyone age 20 years and print them again
    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    printf("-----\n");

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);

    return 0;   
}