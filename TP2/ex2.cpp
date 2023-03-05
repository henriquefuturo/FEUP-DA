// By: Gonçalo Leão

#include "exercises.h"

bool subsetSumBF(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    bool currCandidate[n];
    subsetSize = 0;

    for(int i = 0; i < n; i++) {
        currCandidate[i] = false;
    }

    while(true) {
        unsigned int sum = 0;
        for(int i = 0; i < n; i++) {
            sum += currCandidate[i] * A[i];
        }

        if(sum == T) {
            for(int i = 0; i < n; i++) {
                if(currCandidate[i]) {
                    subset[subsetSize] = A[i];
                    subsetSize++;
                }
            }
            return true;
        }

        //da 'shift' aos elementos do vetor currCandidate
        int currIndex = 0;
        while (currCandidate[currIndex]) {
            currIndex++;
            if (currIndex == n) break;
        }

        if (currIndex == n) break;

        for (int i = 0; i < currIndex; i++) {
            currCandidate[i] = false;
        }
        currCandidate[currIndex] = true;
    }

    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

unsigned int sum(unsigned int A[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Checks if A is a subset of B
bool isSubset(unsigned int A[], unsigned int nA, unsigned int B[], unsigned int nB) {
    for(unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for(unsigned int j = 0; j < nB; j++) {
            if(A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if(!foundNum) return false;
    }
    return true;
}

TEST(TP2_Ex2, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize;

    unsigned int T = 9;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 20;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    T = 30;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), false);
}