#include "simulator.h"
#include <cmath>
#include <iostream>
using namespace std;


void Bin::clear() {
    accessCount = 0;
    pages.clear();
}

void Bin::adjustBinCount() {
    if (!pages.empty()) {
        if (accessCount % 2 == 0) {
            pages.pop_back();
        }
        else {
            pages.push_back(pages.front());
        }
    }
}

//void Simulator::cooling() {
//    // 0th bin 贸府
//    bins[0].clear();
//
//    // 1-14th bin 贸府
//    for (int i = 1; i < 15; ++i) {
//        bins[i].adjustBinCount();
//    }
//
//    // 15th bin 贸府
//    if (bins[15].getAccessCount() < pow(2, 16)) {
//        bins[15].adjustBinCount();
//    }
//}

void Simulator::setThreshold() {
}

Simulator::Simulator(int page_size): page_size(page_size) {
    for (int i = 0; i < 16; i++) {
        bins[i] = new Bin();
    }
};

void Simulator::process(int input) {
    int page_address = input / page_size;
    cout << page_address << " is being processing..." << endl;
    this->addPage(page_address);
}

void Simulator::addPage(int page_address) {
    auto it = pages.find(page_address);
    if (it != pages.end()) {
        it->second++;
        //犬牢 饶 bin俊 持绢林扁
        if (it->second % 2 == 0) {
            int bin_number = static_cast<int>(log2(it->second));
            cout << bins[bin_number];
            //bin update
        }
    }
    else {
        pages[page_address] = 1;
    }
}