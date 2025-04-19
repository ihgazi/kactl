#include <bits/stdc++.h>
using namespace std;

int main() {
    std::random_device rd;
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

    // Define the range [1, 100]
    std::uniform_int_distribution<> dis1(1,1000);
    int l = dis1(gen);
}
