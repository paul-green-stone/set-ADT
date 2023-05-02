#ifndef SET_H
#define SET_H

/* ================================================================ */

#include "data.h"
#include "guard/guard.h"

typedef struct _set_node* Node;     /* A pointer to an incomplite type */

typedef struct _set* Set;           /* A pointer to an incomplite type */

/* ================================ */

/* Allocate a new instance of a set data structure */
extern Set Set_new(int (*fptr_match)(const Data, const Data), void (*fptr_print)(const Data), void (*fptr_destroy)(void*));

/* Display the content of the set */
extern void Set_print(const Set set, void (*fptr_print)(const Data));

/* Destroy the set */
extern void Set_destroy(Set* set);

/* Insert a member into the set */
extern int8_t Set_insert(Set set, const Data data);

/* Remove the member matching `data` from the set */
extern void Set_remove(Set set, Data data);

/* Copy the given set */
extern Set Set_copy(const Set set, size_t elm_size);

/* Build a set that is the union of set_1 and set_2 */
extern Set Set_union(const Set set_1, const Set set_2, size_t elm_size);

/* Build a set that is the intersection of set_1 and set_2 */
extern Set Set_intersect(const Set set_1, const Set set_2, size_t elm_size);

/* Build a set that is the difference of set_1 and set_2 */
extern Set Set_difference(const Set set_1, const Set set_2, size_t elm_size);

/* Determines whether the data specified by `data` matches that of a member in the set */
extern int8_t Set_is_member(const Set set, const Data data);

/* Determines whether the set specified by `set_1` is a subset of the set specified by `set_2` */
extern int8_t Set_is_subset(const Set set_1, const Set set_2);

/* Determines whether the set specified by `set_1` is equal to the set specified by set_2 */
extern int8_t Set_is_equal(const Set set_1, const Set set_2);

/* Get the size of the set */
extern ssize_t Set_get_size(const Set set);

/* Set a print function asssociated with the given set */
extern void Set_set_print(Set set, void (*fptr_print)(const Data));

/* Set a match function asssociated with the given set */
extern void Set_set_match(Set set, int (*fptr_match)(const Data, const Data));

/* Set a destroy function asssociated with the given set */
extern void Set_set_destroy(Set set, void (*fptr_destroy)(void*));

/* ================================================================ */

#endif