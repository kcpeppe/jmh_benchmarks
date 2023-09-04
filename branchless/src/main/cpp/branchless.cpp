// Branchless example

#include <iostream>
#include <string.h>
#include <ctime>
using namespace std;

int __attribute__ ((noinline)) maxWithBranch(int a, int b) {
  if ( a > b)
    return a;
  else
    return b;
}

int __attribute__ ((noinline)) maxWithTernaryBranch(int a, int b) {
   return (a > b) ? a : b;
}

int __attribute__ ((noinline)) maxWithNoBranch(int a, int b) {
  return (a * (a > b)) + (b * (b >= a));
}

clock_t __attribute__ ((noinline)) timeWithBranch(int *values) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 2000000; i+=4) {
       max += maxWithBranch(values[i],values[i+1]);
       max += maxWithBranch(values[i+1],values[i+2]);
       max += maxWithBranch(values[i+2],values[i+3]);
       max += maxWithBranch(values[i+3],values[i+4]);
    }
    clock_t end = clock();
    return end - start;
}

clock_t __attribute__ ((noinline)) timeWithTernaryBranch(int *values) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 2000000; i++) {
       max += maxWithTernaryBranch(values[i],values[i+1]);
       /*max += maxWithTernaryBranch(values[i+1],values[i+2]);
       max += maxWithTernaryBranch(values[i+2],values[i+3]);
       max += maxWithTernaryBranch(values[i+3],values[i+4]);*/
    }
    clock_t end = clock();
    return end - start;
}

clock_t __attribute__ ((noinline)) timeWithNoBranch(int *values) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 2000000; i++) {
       max += maxWithNoBranch(values[i],values[i+1]);
       /*max += maxWithNoBranch(values[i+1],values[i+2]);
       max += maxWithNoBranch(values[i+2],values[i+3]);
       max += maxWithNoBranch(values[i+3],values[i+4]);*/
    }
    clock_t end = clock();
    return end - start;
}

clock_t __attribute__ ((noinline)) timeWithBranchFixedValues( int *values, int * c) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 2000000; i+=4) {
       max += maxWithBranch(values[0],values[1]);
       max += maxWithBranch(values[1],values[0]);
       max += maxWithBranch(values[0],values[0]);
       max += maxWithBranch(values[1],values[1]);
    }
    clock_t end = clock();
    *c = max;
    return end - start;
}

clock_t __attribute__ ((noinline)) timeWithTernaryBranchFixedValues(int *values, int * c) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 2000000; i+=4) {
       max += maxWithBranch(values[0],values[1]);
       max += maxWithBranch(values[1],values[0]);
       max += maxWithBranch(values[0],values[0]);
       max += maxWithBranch(values[1],values[1]);
    }
    clock_t end = clock();
    *c = max;
    return end - start;
}

clock_t __attribute__ ((noinline)) timeWithNoBranchFixedValues(int *values, int * c) {
    int max = 0;
    clock_t start = clock();
    for (int i = 0; i < 2000000; i+=4) {
       max += maxWithNoBranch(values[0],values[1]);
       max += maxWithNoBranch(values[1],values[0]);
       max += maxWithNoBranch(values[0],values[0]);
       max += maxWithNoBranch(values[1],values[1]);
    }
    clock_t end = clock();
    *c = max;
    return end - start;
}

int __attribute__ ((noinline)) blackhole(int * results) {
     int total = 0;
     for (int i = 0; i < 5; i++)
        total += results[i];
     return total;
}

int main(int argc, char **argv) {
    int values[2000001];
    int c;
    int fixedValues[2];
    int results[5];

    std::cout << maxWithNoBranch(6,7) << "\n";
    std::cout << maxWithNoBranch(7,7) << "\n";
    std::cout << maxWithNoBranch(7,6) << "\n";

    fixedValues[0] = (argc == 2) ? stoi(argv[0]) : 6;
    fixedValues[1] = (argc == 2) ? stoi(argv[1]) : 7;

    for (int i = 0; i < 2000001; i++)
        values[i] = rand() % 100;

    int trials = 5;
    for (int i = 0; i < trials; i++)
        std::cout << "Time with Branch: " << timeWithBranch(values) << "\n";
    for (int i = 0; i < trials; i++)
        std::cout << "Time with Ternary Branch: " << timeWithTernaryBranch(values) << "\n";
    for (int i = 0; i < trials; i++)
        std::cout << "Time with no Branch: " << timeWithNoBranch(values) << "\n";
    std::cout << "=================================\n";

    for (int i = 0; i < trials; i++) {
        std::cout << "Time with Branch Fixed: " << timeWithBranchFixedValues(fixedValues, &c) << "\n";
        results[i] = c;
    }
    std::cout << blackhole(results) << "\n";

    for (int i = 0; i < trials; i++) {
        std::cout << "Time with Ternary Branch Fixed: " << timeWithTernaryBranchFixedValues(fixedValues, &c) << "\n";
        results[i] = c;
    }
    std::cout << blackhole(results) << "\n";

    for (int i = 0; i < trials; i++) {
        std::cout << "Time with no Branch Fixed: " << timeWithNoBranchFixedValues(fixedValues, &c) << "\n";
        results[i] = c;
    }
    std::cout << blackhole(results) << "\n";

    std::cout << "=================================\n";

    for (int i = 0; i < trials; i++) {
        std::cout << "Time with Branch Fixed: " << timeWithBranchFixedValues(fixedValues, &c) << "\n";
        results[i] = c;
    }
    std::cout << blackhole(results) << "\n";

    for (int i = 0; i < trials; i++) {
        std::cout << "Time with Ternary Branch Fixed: " << timeWithTernaryBranchFixedValues(fixedValues, &c) << "\n";
        results[i] = c;
    }
    std::cout << blackhole(results) << "\n";

    for (int i = 0; i < trials; i++) {
        std::cout << "Time with no Branch Fixed: " << timeWithNoBranchFixedValues(fixedValues, &c) << "\n";
        results[i] = c;
    }
    std::cout << blackhole(results) << "\n";

    std::cout << "=================================\n";
    return 0;
}
