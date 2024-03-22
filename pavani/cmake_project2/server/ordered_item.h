#ifndef ORDERED_ITEM_H
#define ORDERED_ITEM_H

typedef struct {
    int item_id;
    int quantity;
    double price;
    double total_price_with_tax;
} OrderedItem;

#endif /* ORDERED_ITEM_H */

