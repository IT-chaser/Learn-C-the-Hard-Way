#!/bin/bash

set -e

# Define the contents for each test case
test1() {
    echo "Test 1 - Creating database..."
    ./ex17 db.dat c 256 100
    echo "Result OK"
    echo
}

test2() {
    echo "Test 2 - Setting database..."
    ./ex17 db.dat s 1 alex alex@email.com
    ./ex17 db.dat s 2 adam adam@email.com
    ./ex17 db.dat s 3 joy joy@email.com
    echo "Result OK"
    echo
}

test3() {
    echo "Test 3 - Getting database"
    ./ex17 db.dat g 1
    ./ex17 db.dat g 2
    ./ex17 db.dat g 3
    echo "Result OK"
    echo
}

test4() {
    echo "Test 4 - Listing database"
    ./ex17 db.dat l
    echo "Result OK"
    echo
}

test5() {
    echo "Test 5 - Finding database..."
    ./ex17 db.dat f alex
    ./ex17 db.dat f adam
    ./ex17 db.dat f joy
}

# Main funtcion to run tests
run_tests() {
    test1
    test2
    test3
    test4
    test5
}

# Execute the tests
run_tests