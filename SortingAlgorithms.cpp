#include <vector>
#include <math.h>
#include <iostream>

/*Radix sort. Input is a vector of integers, —
the number of digits of the largest integer, —
and if there are any negatives or not.
Function should run in O(nk) time —
n is the number of ints and k is maxDigits*/
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

/*Selection sort. Input is a vector of integers.
Function should run in O(n^2) time —
n is the number of integers*/
std::vector<int> selectionSort(std::vector<int> tbs) {
    /*For every index in the input vector —
    find the smallest integer in the rest of the vector —
    swap the smallest integer with the current index.*/
    for (int i = 0; i < tbs.size(); i++) {
        int smaller_than = tbs[i];
        int location = i;
        for (int j = i + 1; j < tbs.size(); j++) {
            if (tbs[j] < smaller_than) {
                smaller_than = tbs[j];
                location = j;
            }
        }

        tbs[location] = tbs[i];
        tbs[i] = smaller_than;
    }

    return tbs;
}

/*Bubble sort. Input is a vector of integers.
Function should run in O(n^2) time —
n is the number of integers*/
std::vector<int> bubbleSort(std::vector<int> tbs) {
    /*For every index in the input vector —
    compare the current index with the next index —
    if the next index is smaller —
    swap the two indices.
    Repeat until full loop contains no swaps.*/
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 0; i < tbs.size() - 1; i++) {
            if (tbs[i] > tbs[i+1]) {
                int temp = tbs[i];
                tbs[i] = tbs[i+1];
                tbs[i+1] = temp;
                swapped = true;
            }
        }
    }

    return tbs;
}

/*Insertion sort. Input is a vector of integers.
Function should run in O(n^2) time —
n is the number of integers*/
std::vector<int> insertionSort(std::vector<int> tbs) {
    /*For every index in the input vector —
    compare the current index with the previous index —
    if the current index is smaller —
    swap the two indices.
    Repeat until previous index value is smaller.*/
    for (int i = 0 ; i < tbs.size(); i++) {
        int j = i;
        while (j != 0 && tbs[j] < tbs[j-1]) {
            int temp = tbs[j];
            tbs[j] = tbs[j-1];
            tbs[j-1] = temp;
            j--;
        }
    }

    return tbs;
}

/*Merge sort. Input is a vector of integers.
Function should run in O(n*log(n)) time —
n is the number of integers*/
std::vector<int> mergeSort(std::vector<int> tbs) {
    /*If the input vector is of size 2 or less —
    return the sorted input vector.*/
    if (tbs.size() <= 2) {
        if (tbs.size() == 2) {
            if (tbs[0] > tbs[1]) {
                int temp = tbs[0];
                tbs[0] = tbs[1];
                tbs[1] = temp;
            }
        }

        return tbs;
    } else {
        /*Split the input vector into two halves —
        then sort each half —
        then merge the two sorted halves.*/
        int mid = ceil(tbs.size() / 2);
        std::vector<int> left = std::vector<int>(tbs.begin(), tbs.begin() + mid);
        left = mergeSort(left);

        std::vector<int> right = std::vector<int>(tbs.begin() + mid, tbs.end());
        right = mergeSort(right);

        tbs.clear();
        tbs.resize(left.size() + right.size());

        int i = 0;
        int j = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                tbs[i+j] = left[i];
                i++;
            } else {
                tbs[i+j] = right[j];
                j++;
            }
        }

        while (i < left.size()) {
            tbs[i+j] = left[i];
            i++;
        }

        while (j < right.size()) {
            tbs[i+j] = right[j];
            j++;
        }

        return tbs;
    }
}
