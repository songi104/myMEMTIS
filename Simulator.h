#pragma once
#include <unordered_map>
#include <array>
#include <cstdint>

using namespace std;

struct Bin
{
    int page_count=0;

};

class Simulator {
public:
    Simulator(int page_size, int bin_count);
    array<Bin, 16> bins;
    unordered_map<uint64_t, int> pages_SSD;
    int page_size;
    int bin_count;
    uint64_t fast_memory_size;
    uint64_t capacity_memory_size;

    void setMomorySize(uint64_t total_memory_size, int ratio_fast, int ratio_capacity);
    
    void process(uint64_t input);
    void cooling();
    void addPage(int page_address);
    
    void migrate();
    void setThreshold();
};