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
    for (int i = 0; i < 2000000; i++) {
       max += maxWithBranch(values[i],values[i+1]);
    }
    clock_t end = clock();
    return end - start;
}

clock_t timeWithNoBranch(int *values) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 2000000; i++) {
       max += maxWithNoBranch(values[i],values[i+1]);
    }
    clock_t end = clock();
    return end - start;
}

int main(int argc, char **argv) {
    int values[2000001];

    for (int i = 0; i < 2000001; i++)
        values[i] = rand() % 100;

    int trials = 5;
    for (int i = 0; i < trials; i++)
        std::cout << "Time with Branch: " << timeWithBranch(values) << "\n";
    for (int i = 0; i < trials; i++)
        std::cout << "Time with no Branch: " << timeWithNoBranch(values) << "\n";

    return 0;
}
