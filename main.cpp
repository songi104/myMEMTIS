#include <iostream>
#include <vector>
#include <cmath>


// Bin Ŭ���� ����
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

// ������ ����ü ����
struct Page {
    int address;
    int accessCount;

    Page(int addr) : address(addr), accessCount(1) {}
};


// Simulator Ŭ���� ����
class Simulator {
private:
    std::vector<Bin> bins;

public:
    // �ʱ�ȭ: 16���� Bin ����
    Simulator() {
        bins.resize(16);
    }

    // ������ �׼��� ó�� �� Bin�� ������ �Ҵ�
    void accessPage(int address) {
        int accessCount = log2(address) + 1; // �׼��� Ƚ�� ���
        if (accessCount > 16) accessCount = 16; // ������ ���� ���Ѵ�� ����

        bins[accessCount - 1].addPage(Page(address)); // �������� �ش��ϴ� Bin�� �߰�
    }

    // �� Bin�� ������ ���
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

    // ������ �׼��� ����
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

    // �� Bin�� ������ ���
    simulator.printBins();

    return 0;
}
