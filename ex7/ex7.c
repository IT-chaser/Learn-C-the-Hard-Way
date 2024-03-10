#include <stdio.h>

int main(int argc, char *argv[]) {
    int distance = 100;
    float power = 2.345f;
    double super_power = 56789.4532;
    char initial = 'A';
    char first_name[] = "Abdulloh";
    char last_name[] = "Aliev";

    printf("You're %d miles away\n", distance);
    printf("You have %f levels of power\n", power);
    printf("You have %f awsome super powers\n", super_power);
    printf("I have an initial %c\n", initial);
    printf("I have a first name %s\n", first_name);
    printf("I have a last name %s\n", last_name);
    printf("My full name is %s %c. %s\n", first_name, initial, last_name);

    int bugs = 100;
    double bug_rate = 1.2;
    printf("You have %d bugs at the imagenry rate of %f\n", bugs, bug_rate);

    unsigned long universe_of_defects = 1L * 1024L * 1024L * 1024L;
    printf("The entire universe has %ld bugs\n", universe_of_defects);

    double expected_bugs = bugs * bug_rate;
    printf("You are expected to have %f bugs\n", expected_bugs);

    double part_of_universe = expected_bugs / universe_of_defects;
    printf("That is only a %e portion of the universe.\n", part_of_universe);

    // this makes no sense, just a demo of something weird
    char null_byte = 'S';
    int care_parcentage = bugs * null_byte;
    printf("Which means you should care %d%%.\n", care_parcentage);

    return 0;
}