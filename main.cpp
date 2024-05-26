#include "simulator.h"
#include <iostream>
using namespace std;

int main() {

    const int PAGE_SIZE = 4;
    Simulator simulator(PAGE_SIZE);
    for (int i = 0; i < 10; i++) {
        simulator.process(1000*i);
    }

    return 0;
}
