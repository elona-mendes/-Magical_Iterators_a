#include "doctest.h"
#include <iostream>
#include "sources/MagicalContainer.hpp"

using namespace ariel;

// #include <stdexcept>
// #include <string.h>
// #include <sstream>
using namespace std;

TEST_CASE("Container size and add") {
    MagicalContainer container;
    CHECK(container.size() == 0);
    container.addElement(17);
    CHECK(container.size() == 1);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);
    CHECK(container.size() == 5);
}

TEST_CASE("Remove element and size"){
    MagicalContainer container;
    container.addElement(17);
    CHECK_NOTHROW(container.removeElement(17));
    CHECK(container.size() == 0);
    container.addElement(2);
    container.addElement(25);
    CHECK(container.size() == 2);
    //Try to remove element that aren't in the container.
    CHECK_THROWS(container.removeElement(17));
    CHECK(container.size() == 2);
    container.removeElement(2);
    container.removeElement(25);
    CHECK(container.size() == 0);
    //Try to remove element at empty container.
    CHECK_THROWS(container.removeElement(25));
    
}

TEST_CASE("Test AscendingIterator"){
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    MagicalContainer::AscendingIterator ascIter(container);
    CHECK(*ascIter.begin() == 2);

    int i = 0;
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        std::cout << *it << ' ';  // 2 17 25
        i ++;
    }
    // the container end came after 3 turns
    CHECK(i == 3);
    auto it = ascIter.begin();
    CHECK_NOTHROW(++it);

    CHECK(*it == 17);
    ++it;
    ++it;
    CHECK_THROWS(++it);
}

TEST_CASE("Test SideCrossIterator"){
    MagicalContainer container;
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
   

    int i = 0;
    MagicalContainer::SideCrossIterator crossIter(container);
     CHECK(*crossIter.begin() == 2);
    for (auto it = crossIter.begin(); it != crossIter.end(); ++it) {
        std::cout << *it << ' ';  // 2 25 17
        i ++;
    }
    // the container end came after 3 turns
    CHECK(i == 3);
    auto it = crossIter.begin();
    CHECK_NOTHROW(++it);

    CHECK(*it == 25);
    ++it;
    ++it;
    CHECK_THROWS(++it);
}

TEST_CASE("Test PrimeIterator"){
    MagicalContainer container;
    container.addElement(17);
    container.addElement(13);
    container.addElement(25);
   

    int i = 0;
    MagicalContainer::PrimeIterator primeIter(container);
    CHECK(*primeIter.begin() == 13);

    for (auto it = primeIter.begin(); it != primeIter.end(); ++it) {
        std::cout << *it << ' ';  // 2 3 17 
        i ++;
    }

    // the container end came after 3 turns
    CHECK(i == 2);
    auto it = primeIter.begin();
    CHECK_NOTHROW(++it);

    CHECK(*it == 17);
    ++it;
    CHECK_THROWS(++it);

    container.removeElement(17);
    container.removeElement(13);
    // no prime number rest
    CHECK(*primeIter.begin() == 0);
}