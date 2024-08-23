#include <stdlib.h>
#include <stdio.h>
#include "backpack.h"

item* createItem(const int weight, const int cost) {
    item* backpack = malloc(sizeof(item));
    if (backpack == NULL) {
        return NULL;
    }
    backpack->weight = weight;
    backpack->cost = cost;
    return backpack;
}

int createBackpack(Backpack* backpack) {
    backpack->table = malloc((backpack->maxWeight + 1) * sizeof(int*));
    if (backpack->table == NULL) {
        return 1;
    }
    for (int i = 0; i <= backpack->maxWeight; i++) {
        backpack->table[i] = malloc((backpack->itemsCount + 1) * sizeof(int));
        if (backpack->table[i] == NULL) {
            return 1;
        }
    }
    backpack->order = malloc(backpack->itemsCount * sizeof(item*));
    if (backpack->order == NULL) {
        return 1;
    }
    backpack->objects = malloc(backpack->itemsCount * sizeof(item*));
    if (backpack->objects == NULL) {
        return 1;
    }
    return 0;
}

void freeBackpack(Backpack* backpack) {
    for (int i = 0; i <= backpack->maxWeight; i++) {
        free(backpack->table[i]);
    }
    for (int i = 0; i < backpack->itemsCount; i++) {
        free(backpack->order[i]);
        free(backpack->objects[i]);
    }
    free(backpack->table);
    free(backpack->order);
    free(backpack->objects);
    free(backpack);
}

int main() {
    int itemsCount, maxWeight;
    if (scanf("%d %d", &itemsCount, &maxWeight) != 2){
        return 0;
    }
    Backpack* backpack = malloc(sizeof(Backpack));
    if (backpack == NULL){
        return 0;
    }
    backpack->itemsCount = itemsCount;
    backpack->maxWeight = maxWeight;
    if (createBackpack(backpack) != 1) {
        for (int i = 0; i < backpack->itemsCount; i++) {
            backpack->order[i] = malloc(sizeof(item));
            if (backpack->order[i] == NULL){
                return 0;
            }
            backpack->order[i]->weight = 0;
            backpack->order[i]->cost = 0;
        }
        for (int i = 0; i < backpack->itemsCount; i++) {
            int weight, cost;
            if (scanf("%d %d", &weight, &cost) != 2) {
                freeBackpack(backpack);
                return 0;
            }
            backpack->objects[i] = createItem(weight, cost);
            if (backpack->objects[i]== NULL){
                freeBackpack(backpack);
                return 0;
            }
        }
        result(backpack);
    }
    freeBackpack(backpack);
    return 0;
}
