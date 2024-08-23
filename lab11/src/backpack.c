#include <stdlib.h>
#include <stdio.h>
#include "backpack.h"

int max(const int x, const int y) {
    return x >= y ? x : y;
}

int maxCost(Backpack* backpack) {
    for (int i = 0; i < backpack->maxWeight + 1; i++) {
        backpack->table[i][0] = 0;
    }
    for (int i = 0; i < backpack->itemsCount + 1; i++) {
        backpack->table[0][i] = 0;
    }
    for (int i = 1; i < backpack->itemsCount + 1; i++) {
        for (int j = 1; j < backpack->maxWeight + 1; j++) {
            int x = backpack->table[j][i - 1];
            if (j < backpack->objects[i - 1]->weight) {
                backpack->table[j][i] = x;
            }
            else {
                int y = backpack->objects[i - 1]->cost + backpack->table[j - backpack->objects[i - 1]->weight] [i - 1];
                backpack->table[j][i] = max(x, y);
            }
        }
    }
    return backpack->table[backpack->maxWeight][backpack->itemsCount];
}

int backpackInside(Backpack* backpack, const int maxWeight, const int itemCount) {
    if (maxWeight > 0 && itemCount > 0) {
        if (backpack->table[maxWeight][itemCount] == backpack->table[maxWeight][itemCount - 1]) {
            return backpackInside(backpack, maxWeight, itemCount - 1);
        }
        else {
            backpack->order[itemCount - 1]->weight = backpack->objects[itemCount - 1]->weight;
            backpack->order[itemCount - 1]->cost = backpack->objects[itemCount - 1]->cost;
            return backpackInside(backpack, maxWeight - backpack->objects[itemCount - 1]->weight, itemCount - 1);
        }
    }
    return 0;
}

void result(Backpack* backpack) {
    int resCost = maxCost(backpack);
    printf("%d\n", resCost);
    backpackInside(backpack, backpack->maxWeight, backpack->itemsCount);
    for (int i = 0; i < backpack->itemsCount; i++) {
        if (backpack->order[i]->weight != 0 && backpack->order[i]->cost != 0) {
            printf("%d %d\n", backpack->order[i]->weight, backpack->order[i]->cost);
        }
    }
}
