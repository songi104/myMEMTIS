#include "simulator.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//parameter
const int PAGE_SIZE = 4;
const int BIN_COUNT = 16;
const int COOLING_INTERVAL = 10*10000;
const int MIGRATION_INTERVAL = 1*10000;
const int ratio_fast_memory = 1;
const int ratio_capacity_memory = 2;
uint64_t rss_size = 0.5* 1024; //rss는 나중에 전체 메모리 크기로 바뀔 수도 있고 아직은 모르겠다


int main() {


    Simulator simulator(PAGE_SIZE, BIN_COUNT);
    simulator.setMomorySize(rss_size, ratio_fast_memory, ratio_capacity_memory);

    ifstream inputFile("../data/trace_prefON.pout");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file!" << std::endl;
        return 1;
    }


    int count =0;
    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string type, address_str;
        uint64_t address;
        double timestamp;

        if (!(iss >> type >> address_str >> timestamp)) {
            cout << line << "is not matching with format!" << endl;
            continue; // Skip any line that doesn't match the format
        }

        address = stoull(address_str, nullptr, 16);
        simulator.process(address);
        count++;
    
        if (count % MIGRATION_INTERVAL == 0) {
            simulator.setThreshold();
            //simulator.migrate();
        }

        if (count % COOLING_INTERVAL == 0) {
            //simulator.cooling();
        }
    }

    return 0;
}
