#pragma once
#include <vector>
#include <unordered_map>
#include <array>

using namespace std;

class Bin {

public:
    Bin() : accessCount(0) {}
    vector<int> pages;
    int accessCount;
    void clear();
    void adjustBinCount();
    int getAccessCount() const { return accessCount; }
};


class Simulator {
private:
    int page_size;
    unordered_map<int, int> pages;

public:
    array<Bin*, 16> bins;
    Simulator(int page_size);
    
    void process(int input);
    
    void addPage(int page_address);
    //void cooling();
    void setThreshold();
};