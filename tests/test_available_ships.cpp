// Regression tests for issue #3:
// Ships::AvailableShips is read and accumulated before it is initialized.
//
// The defect is invisible for a namespace-scope Ships, because C++ zero-initializes
// objects with static storage duration before their constructor runs. It shows up for
// any Ships built in storage that is not zeroed first: the indeterminate member becomes
// the ship count, so either no ships are placed (garbage >= 10) or the count is inflated
// relative to the ships actually written (garbage < 10). These tests therefore construct
// Ships in deliberately poisoned storage.
//
// main.h is not self-contained (issue #8), so the standard headers it relies on must be
// included before it.
//
// Build and run:
//   g++ -std=c++17 -Wall -Wextra -o test_available_ships tests/test_available_ships.cpp && ./test_available_ships

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <new>
#include <string>

#include "../main.h"

using namespace std;

namespace
{

int failures = 0;

void check(bool condition, const char* what)
{
    cout << (condition ? "  PASS  " : "  FAIL  ") << what << endl;
    if(!condition)
        failures++;
}

// Storage filled with a non-zero byte pattern before construction, so an uninitialized
// AvailableShips is read back as garbage rather than the 0 a zeroed buffer would give.
class Poisoned
{
    alignas(Ships) unsigned char bytes[sizeof(Ships)];

public:
    Poisoned()
    {
        memset(bytes, 0x7F, sizeof(bytes));
    }

    Ships* build()
    {
        return new (bytes) Ships();
    }

    void drop(Ships* ship)
    {
        ship->~Ships();
    }
};

// The count tracks grid cells holding a ship, so it can never leave [0, 10].
bool inRange(int count)
{
    return count >= 0 && count <= 10;
}

void testPoisonedStorageIsInitialized()
{
    Poisoned storage;
    Ships* ship = storage.build();

    const int count = ship->getAvailableShips();
    cout << "        (count from poisoned storage: " << count << ")" << endl;
    check(inRange(count), "count read from poisoned storage is within [0, 10]");

    storage.drop(ship);
}

void testRepeatedConstructionDoesNotAccumulate()
{
    bool allInRange = true;

    for(int i = 0; i < 200; i++)
    {
        Poisoned storage;
        Ships* ship = storage.build();
        if(!inRange(ship->getAvailableShips()))
            allInRange = false;
        storage.drop(ship);
    }

    check(allInRange, "200 independently constructed Ships all report a count within [0, 10]");
}

void testReuseOfStorageDoesNotAccumulate()
{
    Poisoned storage;
    bool allInRange = true;

    for(int i = 0; i < 50; i++)
    {
        Ships* ship = storage.build();
        if(!inRange(ship->getAvailableShips()))
            allInRange = false;
        storage.drop(ship);
    }

    check(allInRange, "reconstructing over the same storage never accumulates the count");
}

void testCapIsNeverExceeded()
{
    bool allCapped = true;

    for(int i = 0; i < 200; i++)
    {
        Poisoned storage;
        Ships* ship = storage.build();
        if(ship->getAvailableShips() > 10)
            allCapped = false;
        storage.drop(ship);
    }

    check(allCapped, "the 10-ship ceiling holds for every construction");
}

} // namespace

int main()
{
    cout << "Ships::AvailableShips initialization (issue #3)" << endl;
    testPoisonedStorageIsInitialized();
    testRepeatedConstructionDoesNotAccumulate();
    testReuseOfStorageDoesNotAccumulate();
    testCapIsNeverExceeded();

    cout << (failures == 0 ? "ALL TESTS PASSED" : "TESTS FAILED") << endl;
    return failures == 0 ? 0 : 1;
}
