// By: Gonçalo Leão

#include "exercises.h"
#include <iostream>
#include <iostream>
bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    bool candidate[n];
    int minQuantity = INT16_MAX;
    unsigned int S[n];

    for(int i = 0; i < n; i++) {
        candidate[i] = false;
    }

    while (true) {
        unsigned int quantity = 0;
        unsigned int total = 0;

        for (int i = 0; i < n; i++) {
            S[i] = Stock[i];
        }

        for (int i = n-1; i >= 0; i--) {
            if (!candidate[i]) continue;
               while (S[i] > 0) {
                if (total + C[i] > T) break;
                total += C[i];
                S[i] -= 1;
                quantity++;
            }
            if(total == T) break;
        }

        if(total == T) {
            if (quantity < minQuantity) {
                minQuantity = quantity;
                for (int i = 0; i < n; i++) {
                    usedCoins[i] = abs((long)S[i] - (long)Stock[i]);
                }
            }
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

    if(minQuantity != INT16_MAX) return true;
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex4, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP2_Ex4, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP2_Ex4, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}