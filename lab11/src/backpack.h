#ifndef BACKPACK_H
#define BACKPACK_H

typedef struct item {
    int weight;
    int cost;
} item;

typedef struct Backpack {
    int maxWeight;
    int itemsCount;
    int ** table;
    item ** order;
    item ** objects;
} Backpack;

void result(Backpack* backpack);

#endif
