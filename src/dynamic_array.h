#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

/**
 * Dynamic Array Implementation
 *
 * NOTE: Doesn't define dynamic array types!
 *       Types should be defined as following:
 *
 *       typedef struct {
 *           <Type> *items;
 *           size_t count;
 *           size_t capacity;
 *       } Dynamic_Array<Type>;
 */


#include <stdlib.h>
#include <string.h>

#define DA_INIT_CAP 256

#define da_append(da, item)                                                            \
    do {                                                                               \
        if((da)->count >= (da)->capacity) {                                            \
            (da)->capacity = (da)->capacity == 0 ? DA_INIT_CAP : (da)->capacity * 2;   \
            (da)->items = realloc((da)->items, (da)->capacity * sizeof(*(da)->items)); \
            assert((da)->items != NULL && "Buy more RAM lol");                         \
        }                                                                              \
                                                                                       \
        (da)->items[(da)->count++] = (item);                                           \
    } while(0)

#define da_append_many(da, new_items, new_items_count)                                        \
    do {                                                                                      \
        if((da)->count + new_items_count >= (da)->capacity) {                                 \
            if((da)->capacity == 0) {                                                         \
                (da)->capacity = DA_INIT_CAP;                                                 \
            }                                                                                 \
            while((da)->count + new_items_count > (da)->capacity) {                           \
                (da)->capacity *= 2;                                                          \
            }                                                                                 \
            (da)->items = realloc((da)->items, (da)->capacity * sizeof(*(da)->items));        \
            assert((da)->items != NULL && "Buy more RAM lol");                                \
        }                                                                                     \
        memcpy((da)->items + (da)->count, new_items, new_items_count * sizeof(*(da)->items)); \
        (da)->count += new_items_count;                                                       \
    } while(0)

#endif // DYNAMIC_ARRAY_H_
