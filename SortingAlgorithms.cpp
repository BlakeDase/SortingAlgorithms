#include <vector>
#include <math.h>
#include <iostream>
#include <chrono>

/*Radix sort. Input is a vector of integers, —
the number of digits of the largest integer, —
and if there are any negatives or not.
Function should run in O(nk) time —
n is the number of ints and k is maxDigits (k+1 if negatives)*/
std::vector<int> radixSort(std::vector<int> tbs, int maxDigits, bool negatives) {
    int ten = 1;
    for (int i = 0; i < maxDigits; i++) {
        std::vector<int> pools[10];

        /*For every integer in input vector — 
        simplify integer to current digit —
        then sort integer into pools 0-9 using digit*/
        for(int num : tbs) {
            int digit = (int)floor(abs(num)/ten) % 10;
            pools[digit].push_back(num);
        }

        tbs.clear();

        /*For every pool in pools —
        insert that pool into tbs*/
        for (std::vector<int> pool : pools) {
            if (!pool.empty()) {
                tbs.insert(tbs.end(), pool.begin(), pool.end());
            }
        }

        ten *= 10;
    }

    /*If there potentially are negatives —
    put them in reverse order —
    then insert the positive values back in*/
    if (negatives) {
        std::vector<int> negatives;
        std::vector<int> positives;

        for (int num : tbs) {
            if (num < 0) {
                negatives.push_back(num);
            } else {
                positives.push_back(num);
            }
        }

        tbs.clear();

        if (!negatives.empty()) {
            tbs.assign(negatives.rbegin(), negatives.rend());
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
