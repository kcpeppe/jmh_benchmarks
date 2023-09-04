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

clock_t timeWithBranch(int *values) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 500000; i++) {
       max += maxWithBranch(values[i],values[i+1]);
       max += maxWithBranch(values[i+1],values[i+2]);
       max += maxWithBranch(values[i+2],values[i+3]);
       max += maxWithBranch(values[i+3],values[i+4]);
    }
    clock_t end = clock();
    return end - start;
}

clock_t timeWithNoBranch(int *values) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 500000; i++) {
       max += maxWithNoBranch(values[i],values[i+1]);
       max += maxWithNoBranch(values[i+1],values[i+2]);
       max += maxWithNoBranch(values[i+2],values[i+3]);
       max += maxWithNoBranch(values[i+3],values[i+4]);
    }
    clock_t end = clock();
    return end - start;
}

int main(int argc, char **argv) {
    int values[500005];

    for (int i = 0; i < 500005; i++)
        values[i] = rand() % 100;

    int trials = 10;
    for (int i = 0; i < trials; i++)
        std::cout << "Time with no Branch: " << timeWithNoBranch(values) << "\n";
    for (int i = 0; i < trials; i++)
        std::cout << "Time with Branch: " << timeWithBranch(values) << "\n";
    for (int i = 0; i < trials; i++)
        std::cout << "Time with no Branch: " << timeWithNoBranch(values) << "\n";
    for (int i = 0; i < trials; i++)
        std::cout << "Time with Branch: " << timeWithBranch(values) << "\n";


    return 0;
}
