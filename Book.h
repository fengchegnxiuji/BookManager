#include <iostream>
#include <string>
#include "pch.h"

class Book {
private:
    int No;
    int cap;
    double Price;
    int lend;
    std::string name;
public:
    Book(int a = 0, int b = 0, double c = 0, std::string name = "Unknown") : No(a), cap(b), Price(c), lend(0), name(name) {}
    int getNo() { return No; }
    int getCap() { return cap; }
    void AddBook(int n) { cap+=n; }
    void LendBook(int n) { cap-=n; lend+=n; }
    void GiveBack(int n) { cap += n; lend -= n; };
    int getLend() { return lend; }
    double getPrice() { return Price; }
    std::string getName() { return name; }
};