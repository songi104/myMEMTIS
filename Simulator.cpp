#include "simulator.h"
#include <cmath>
#include <iostream>
using namespace std;


void Simulator::cooling() {
	cout << "start cooling ..." << endl;

	//half down every page access count
	for (auto& page : pages_SSD) {
		page.second = static_cast<int>(page.second/2);
	}


    // 1-14th bin 처리
    for (int i = 0; i < bin_count-1; i++) {
		bins[i].page_count = bins[i + 1].page_count;
    }

    // 15th bin 처리
	bins[15].page_count = 0;
	for (auto& entry : pages_SSD) {
		int& access_count = entry.second;
		if (access_count >= (1 << 15)) {
			bins[15].page_count++;
		}
		else {
			bins[14].page_count++;
		}
	}
	cout << "end cooling ...\n";
}

void Simulator::setThreshold() {
	// Calculate hot threshold, Thot
	int s = 0;
	int b = bin_count - 1;
	int Thot, Twarm, Tcold;
	bool flag = false;
	while (b >= 0 && (s + page_size*bins[b].page_count) <= fast_memory_size) {
		s += page_size*bins[b].page_count;
		b--;
		if (!flag && bins[b].page_count != 0) {
			cout << "max bin : " << b << endl;
			flag = true;
		}
	}
	Thot = b + 1;

	if (Thot == 0) {
		Twarm = 0;
		Tcold = 0;
		
	}
	else {

		// Calculate warm threshold, Twarm
		int alpha = 1; // Adjust alpha as needed
		if (s > fast_memory_size * alpha) {
			Twarm = Thot;
		}
		else {
			Twarm = Thot - 1;
		}

		// Calculate cold threshold, Tcold
		Tcold = Twarm - 1;
	}
    cout << "Hot threshold (Thot): " << Thot << endl;
    cout << "Warm threshold (Twarm): " << Twarm << endl;
    cout << "Cold threshold (Tcold): " << Tcold << endl;
}



Simulator::Simulator(int page_size, int bin_count)
: page_size(page_size), bin_count(bin_count)
{
}

void Simulator::setMomorySize(uint64_t total_memory_size, int ratio_fast, int ratio_capacity)
{
	double ff = static_cast<double>(ratio_fast) / (ratio_fast + ratio_capacity);
	double cc = static_cast<double>(ratio_capacity) / (ratio_fast + ratio_capacity);

	this->fast_memory_size = static_cast<uint64_t>(ff * total_memory_size);
	this->capacity_memory_size = static_cast<uint64_t>(cc * total_memory_size);
	cout << "Setting Memory " << ratio_fast << ":" << ratio_capacity << endl;
	cout << "fast memory size: " << fast_memory_size << endl;
	cout << "capacity_memory_size: " << capacity_memory_size << endl;
}

void Simulator::process(uint64_t page_address) {
	uint64_t page_id = page_address / page_size;
	//cout << "page_id: "<< page_id << " is being processing..." << endl;
	if (page_id < 0) {
		cout << "buffer overflow" << endl;
	}
	this->addPage(page_id);
	
}

void Simulator::addPage(int page_id) {
	auto it = pages_SSD.find(page_id);
	if (it == pages_SSD.end()) {
		//없음
		pages_SSD[page_id] = 1;
		bins[0].page_count++;

	}
	else {
		//이미 존재
		//pages.access_count ++
		it->second++;
		int& access_count = it->second;
		//확인 후 bin에 넣어주기
		if ((access_count & (access_count - 1)) == 0) {
			int bin_number = min(bin_count, static_cast<int>(log2(it->second)));

			//cout << bins[bin_number];
			//bin update
			bins[bin_number].page_count++;
			if (bin_number != 0) {
				bins[--bin_number].page_count--;
			}
		}
	}
}