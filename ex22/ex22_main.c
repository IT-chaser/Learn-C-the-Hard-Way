#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "John Adam Ali";

void scope_demo(int *count) {
    log_info("count is: %d", *count);

    if (*count > 10) {
        int nums = 100;

        log_info("count in this scope is %d", nums);
    }

    log_info("count is at exit: %d", *count);

    *count = 3000;

    log_info("count after assign: %d", *count);
}

int main(int argc, char *argv[]) {
    // test out THE_AGE accessors
    log_info("My name: %s, age: %d", MY_NAME, get_age());

    set_age(100);

    log_info("My age is now: %d", get_age());

    // test out the THE_SIZE extern
    log_info("THE_SIZE is: %d", THE_SIZE);
    print_size();

    THE_SIZE = 9;

    log_info("THE_SIZE is now: %d", THE_SIZE);
    print_size();

    // test the ratio function static
    log_info("Ratio at first: %f, %f", update_ratio(2.0), *ratioPtr);
    log_info("Ratio again: %f, %f", update_ratio(10.0), *ratioPtr);
    log_info("Ratio once more: %f, %f", update_ratio(300.0), *ratioPtr);

    // test the scope demo
    int count = 4;
    scope_demo(&count);
    count *= 20;
    log_info("count after calling scope_demo1: %d", count);
    scope_demo(&count);

    log_info("count after calling scope_demo: %d", count);

    return 0;
}