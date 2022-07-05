#include <vector>
#include <math.h>
#include <iostream>

/*Radix sort. Input is a vector of integers —
and the number of digits of the largest integer.
Function should run in O(nk) time —
n is the number of ints and k is maxDigits*/
std::vector<int> radixSort(std::vector<int> tbs, int maxDigits) {
    for (int i = 0; i < maxDigits; i++) {
        std::vector<int> pools[10];

        /*For every integer in input vector — 
        simplify integer to current digit —
        then sort integer into pools 0-9 using digit*/
        for(int num : tbs) {
            int digit = (int)floor(abs(num)/pow(10, i)) % 10;
            pools[digit].push_back(num);
        }    

        tbs.clear();
        std::vector<int> negatives;
        std::vector<int> positives;

        /*For every pool in pools —
        and for every integer in the pool —
        if the integer is negative, push into negatives —
        else push it into positives */
        for (std::vector<int> pool : pools) {
            if (!pool.empty()) {

                for (int num : pool) {
                    if (num < 0) {
                        negatives.push_back(num);
                    } else {
                        positives.push_back(num);
                    }
                }
            }
        }

        /*Move negatives into tbs from back to front —
        and then positives normally into tbs*/
        if (!negatives.empty()) {
            tbs.insert(tbs.end(), negatives.rbegin(), negatives.rend());
        }

        if (!positives.empty()) {
            tbs.insert(tbs.end(), positives.begin(), positives.end());
        }

    }

    return tbs;
}

/*Counting sort. Input is a vector of integers, —
the smallest integer, and the largest integer.
Function should run in O(n+k) time —
n is the number of ints and k is the range from min to max*/
std::vector<int> countingSort(std::vector<int> tbs, int min, int max) {
    std::vector<int> count(max - min + 1, 0);

    /*For every integer in the input vector —
    increment the tally of that integer in count*/
    for (int i = 0; i < tbs.size(); i++) {
        count[tbs[i] - min]++;
    }

    /*For every one time an integer is tallied —
    add that integer to the output vector once.
    Starting from the min integer.*/
    int j = 0;
    for (int i = 0; i < count.size(); i++) {
        while (count[i] > 0) {
            tbs[j] = min + i;
            count[i]--;
            j++;
        }
    }

    return tbs;
}
