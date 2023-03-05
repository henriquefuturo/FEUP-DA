// By: Gonçalo Leão
// With contributions by Eduardo Almeida

#include "exercises.h"

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int maxSum = INT16_MIN;
    bool candidate[20];
    int min, max;


    for(int k = 0; k < n; k++) {
        candidate[k] = false;
    }

    while(true) {
        bool valid = true;
        int sum = 0;

        for(int k = 0; k < n; k++) {
            if(candidate[k]) max = k;
            if(candidate[k] && sum == 0) min = k;
            sum += candidate[k] * A[k];
        }

        //checks if subarray is valid
        for(int k = min; k < max; k++) {
            if(!candidate[k]) valid = false;
        }

        if(sum > maxSum && valid) {
            maxSum = max;
            i = min;
            j = max;
        }

        //da 'shift' aos elementos do vetor currCandidate
        int currIndex = 0;
        while (candidate[currIndex]) {
            currIndex++;
            if (currIndex == n) break;
        }

        if (currIndex == n) break;

        for (int k = 0; k < currIndex; k++) {
            candidate[k] = false;
        }
        candidate[currIndex] = true;
    }

    return maxSum;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceBF(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}