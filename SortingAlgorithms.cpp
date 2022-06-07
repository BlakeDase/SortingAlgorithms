#include <vector>
#include <math.h>

/*Radix sort to sort a vector of integers of any size.
Input is a vector (any length) of integers (any integer) —
and the number of digits of the largest integer.
You can put any number as maxDigits, but that will add time to the program —
you add O(n) time for each digit */
std::vector<int> radixSort(std::vector<int> tbs, int maxDigits) {
    for (int i = 0; i < maxDigits; i++) { //One loop iteration for every digit
        std::vector<std::vector<int>> pools = {{},{},{},{},{},{},{},{},{},{}};

        /*For every integer in input vector — 
        simplify integer to current digit —
        then sort integer into pools 0-9 using digit*/
        for(int num : tbs) {
            int digit = (int)floor(num/pow(10, i)) % 10;
            pools[digit].push_back(num);
        }

        tbs.clear();

        /*For every pool in pools —
        if the pool isn't empty —
        insert pool into input vector*/
        for (std::vector<int> pool : pools) {
            if (!pool.empty()) {
                tbs.insert(tbs.end(), pool.begin(), pool.end());
            }
        }
    }

    return tbs;
}

