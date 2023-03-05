// By: Gonçalo Leão

#include "exercises.h"

unsigned int knapsackBF(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {
    bool candidate[n];
    int maxValue = INT16_MIN;

    for (int i = 0; i < n; i++) {
        candidate[i] = false;
    }

    while (true) {
        int weight = 0;
        int value = 0;
        for (int i = 0; i < n; i++) {
            value += candidate[i] * values[i];
            weight += candidate[i] * weights[i];
        }

        if(weight <= maxWeight && value > maxValue) {
            maxValue = value;

            for(int i = 0; i < n; i++) {
                usedItems[i] = candidate[i];
            }
        }

        //da 'shift' aos elementos do vetor Candidate
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
    return maxValue;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex6, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP2_Ex6, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}