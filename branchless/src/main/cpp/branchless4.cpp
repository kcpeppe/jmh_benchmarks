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
    for (int i = 0; i < 250000; i++) {
       max += maxWithBranch(values[i],values[i+1]);
       max += maxWithBranch(values[i+1],values[i+2]);
       max += maxWithBranch(values[i+2],values[i+3]);
       max += maxWithBranch(values[i+3],values[i+4]);
       max += maxWithBranch(values[i+4],values[i+5]);
       max += maxWithBranch(values[i+5],values[i+6]);
       max += maxWithBranch(values[i+6],values[i+7]);
//       max += maxWithBranch(values[i+7],values[i+8]);
//       max += maxWithBranch(values[i+8],values[i+9]);
//       max += maxWithBranch(values[i+9],values[i+10]);
//       max += maxWithBranch(values[i+10],values[i+11]);
//       max += maxWithBranch(values[i+11],values[i+12]);
//       max += maxWithBranch(values[i+12],values[i+13]);
//       max += maxWithBranch(values[i+13],values[i+14]);
//       max += maxWithBranch(values[i+14],values[i+15]);
//       max += maxWithBranch(values[i+15],values[i+16]);
    }
    clock_t end = clock();
    return end - start;
}

clock_t timeWithNoBranch(int *values) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 250000; i++) {
       max += maxWithNoBranch(values[i],values[i+1]);
       max += maxWithNoBranch(values[i+1],values[i+2]);
       max += maxWithNoBranch(values[i+2],values[i+3]);
       max += maxWithNoBranch(values[i+3],values[i+4]);
       max += maxWithNoBranch(values[i+4],values[i+5]);
       max += maxWithNoBranch(values[i+5],values[i+6]);
       max += maxWithNoBranch(values[i+6],values[i+7]);
//       max += maxWithNoBranch(values[i+7],values[i+8]);
//       max += maxWithNoBranch(values[i+8],values[i+9]);
//       max += maxWithNoBranch(values[i+9],values[i+10]);
//       max += maxWithNoBranch(values[i+10],values[i+11]);
//       max += maxWithNoBranch(values[i+11],values[i+12]);
//       max += maxWithNoBranch(values[i+12],values[i+13]);
//       max += maxWithNoBranch(values[i+13],values[i+14]);
//       max += maxWithNoBranch(values[i+14],values[i+15]);
//       max += maxWithNoBranch(values[i+15],values[i+16]);
    }
    clock_t end = clock();
    return end - start;
}

int main(int argc, char **argv) {
    int values[250009];

    for (int i = 0; i < 250009; i++)
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
