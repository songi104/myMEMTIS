#include <iostream>
#include <vector>
#include <cmath>


// Bin 클래스 정의
class Bin {
private:
    std::vector<Page> pages;

public:
    void addPage(Page page) {
        pages.push_back(page);
    }

    int getSize() const {
        return pages.size();
    }

    void printPages() const {
        for (const auto& page : pages) {
            std::cout << "Address: " << page.address << ", Access Count: " << page.accessCount << std::endl;
        }
    }
};

// 페이지 구조체 정의
struct Page {
    int address;
    int accessCount;

    Page(int addr) : address(addr), accessCount(1) {}
};


// Simulator 클래스 정의
class Simulator {
private:
    std::vector<Bin> bins;

public:
    // 초기화: 16개의 Bin 생성
    Simulator() {
        bins.resize(16);
    }

    // 페이지 액세스 처리 및 Bin에 페이지 할당
    void accessPage(int address) {
        int accessCount = log2(address) + 1; // 액세스 횟수 계산
        if (accessCount > 16) accessCount = 16; // 마지막 빈은 무한대로 설정

        bins[accessCount - 1].addPage(Page(address)); // 페이지를 해당하는 Bin에 추가
    }

    // 각 Bin의 페이지 출력
    void printBins() const {
        for (int i = 0; i < 16; ++i) {
            std::cout << "Bin " << i << " Size: " << bins[i].getSize() << std::endl;
            bins[i].printPages();
            std::cout << std::endl;
        }
    }
};

int main() {
    Simulator simulator;

    // 페이지 액세스 예시
    simulator.accessPage(1000);
    simulator.accessPage(2000);
    simulator.accessPage(3000);
    simulator.accessPage(4000);
    simulator.accessPage(5000);
    simulator.accessPage(6000);
    simulator.accessPage(7000);
    simulator.accessPage(8000);
    simulator.accessPage(9000);
    simulator.accessPage(10000);

    // 각 Bin의 페이지 출력
    simulator.printBins();

    return 0;
}
