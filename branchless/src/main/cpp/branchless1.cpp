// Branchless example

#include <iostream>
#include <string.h>
#include <ctime>
using namespace std;

int maxWithBranch(int a, int b) {
  if ( a > b)
    return a;
  else
    return b;
}

int maxWithNoBranch(int a, int b) {
  return (a * (a > b)) + (b * (b >= a));
}

clock_t timeWithBranch(int a, int b) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 2000000; i++) {
       max += maxWithBranch(a,b);
    }
    clock_t end = clock();
    return end - start;
}

clock_t timeWithNoBranch(int a, int b) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 2000000; i++) {
       max += maxWithNoBranch(a,b);
    }
    clock_t end = clock();
    return end - start;
}

int main(int argc, char **argv) {
    int a, b;

    a = (argc == 2) ? stoi(argv[0]) : 6;
    b = (argc == 2) ? stoi(argv[1]) : 7;

    int trials = 5;
    for (int i = 0; i < trials; i++)
        std::cout << "Time with Branch: " << timeWithBranch(a,b) << "\n";
    for (int i = 0; i < trials; i++)
        std::cout << "Time with no Branch: " << timeWithNoBranch(a,b) << "\n";
    return 0;
}
