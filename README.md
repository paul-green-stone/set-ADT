# Set

## Content

[Overview](#overview)

[API](#api)

[Examples](#examples)

## Overview

Sets are collection of distinguishable objects, called *members*, grouped together because they are in some way related. Two important characteristics of sets are that their members are unordered and that no members occur more than once. Sets are important part of descrete mathemtaics, an area of mathemtaics particularly relevant to computing.

Formally, sets are written with braces around them. Thus, if $S$ is a set containing the members $1, 2$, and $3$, then $S = \{1, 2, 3\}$. Of course, because a set is unordered, this is the same as writing $S = \{3, 2, 1\}$. If a member, $m$, is in a set, $S$, then membership is indicated by writing $m \in S$, otherwise $m \notin S$. For example, in the set $S = \{1, 2, 3\}$, $2 \in S$, but $4 \notin S$.

### Definitions

1. A set containing no members is the *empty set*. The set of all possible members is the *universe*.

    $S = U$ is the universe; $S = \emptyset$.

2. Two sets are *equal* if they contain exactly the same members.

    $S~1~ = S~2~$ means $S~1~$ and $S~2~$ are equal; $S~1~ \neq S~2~$ means $S~1~$ and $S~2~$ are not equal.

3. One set, $S~1~$, is a *subset* of another set, $S~2~$, if $S~2~$ contains all of the members of $S~1~$.

    $S~1~ \subset S~2~$ means $S~1~$ is a subset of $S~2~$; $S~1~ \not\subset S~2~$ means $S~1~$ is not a subset of $S~2~$

### Basic Operations

1. The *union* of two sets, $S~1~$ and $S~2~$, is a set $S~u~$, that contains all of the members of $S~1~$ in addition to all of the members of $S~2~$.

    $S~1~ \cup S~2~$ represents the union of $S~1~$ and $S~2~$

2. The *intersection* of two sets, $S~1~$ and $S~2~$, is a set, $S~i~$, that contains only members that exist on both $S~1~$ and $S~2~$.

    $S~1~ \cap S~2~$ represents the intersection of $S~1~$ and $S~2~$

3. The *difference* of two sets, $S~1~$ and $S~2~$, is a set, $S~d~$, that contains all of the members of $S~1~$ except those in $S~2~$.

    $S~1~ - S~2~$ represents the difference of $S~1~$ and $S~2~$

## API

### Set_new

```C
Set Set_new(int (*fptr_match)(const Data, const Data), void (*fptr_print)(const Data), void (*fptr_destroy)(void*));
```

Allocates a new instance of a set data structure.

| Type | Description |
| ---- | ----------- |
| `int (*fptr_match)(const Data, const Data)` | The `fptr_match` argument is a function used by various set operations to determine if two members match. It should return *0* if two pieces of data are equal |
| `void (*fptr_print)(const Data)` | The `fptr_print` argument is a function used by `Set_print` operation to display a set content |
| `void (*fptr_destroy)(void*)` | The `fptr_destroy` argument provides a way to free dynamically allocated data when set_destroy is called. For example, if the set contains data dynamically allocated using `malloc`, destroy should be set to `free` to free the data as the set is destroyed. For structured data containing several dynamically allocated members, destroy should be set to a user-defined function that calls `free` for each dynamically allocated member as well as for the structure itsel |

**Return value**: a new instance of a set (`Set`).

### Set_print

```C
void Set_print(const Set set, void (*fptr_print)(const Data));
```

The `Set_print` operation displays the set specified by `set`. The `fptr_print` argument is a function that is called on every set member while traversng it. If `fptr_print` is NULL, the `fptr_print` function specified in `Set_new` is used.

| Type | Description |
| ---- | ----------- |
| `const Set set` | The set to be displayed |
| `void (*fptr_print)(const Data)` | The function to print data in a set |

**Return value**: none.

### Set_destroy

```C
void Set_destroy(Set* set);
```

Destroys the set specified by `set`. The `Set_destroy` operation removes all members from a set and calls the function passed as destroy to `Set_init` or `Set_set_destroy` once for each member as it is removed, provided destroy was not set to
*NULL*.

| Type | Description |
| ---- | ----------- |
| `Set* set` | A pointer set to be destroyed |

**Return value**: none.

### Set_insert

```C
int8_t Set_insert(Set set, const Data data);
```

Inserts a member into the set specified by `set`.

| Type | Description |
| ---- | ----------- |
| `Set set` | A set to insert a member into |
| `const Data data` | Data to insert |

**Return value**: *1* if inserting the member is succesful, *-1* if the member is already in the set, or *0* otherwise.

### Set_remove

```C
void Set_remove(Set set, Data data);
```

Removes the member matching `data` from the set specified by `set`.

| Type | Description |
| ---- | ----------- |
| `Set set` | A set to remove a member from |
| `Data data` | Data to remove |

**Return value**: none.

### Set_copy

```C
Set Set_copy(const Set set, size_t elm_size);
```

Makes a deep copy of a the set specified by `set`.

| Type | Description |
| ---- | ----------- |
| `const Set set` | A set to copy|
| `size_t elm_size` | Size in bytes of a member. By default `Data` is `typedef int* Data` |

**Return value**: a set `Set` that is a deep copy of a set specified by `set`.

### Set_union

```C
Set Set_union(const Set set_1, const Set set_2, size_t elm_size);
```

Allocates a new set that is the union of `set_1` and `set_2`.

| Type | Description |
| ---- | ----------- |
| `const Set set_1` | A set to union |
| `const Set set_2` | A set to union |
| `const size_t elm_size` | Size in bytes of a member. By default `Data` is `typedef int* Data` |

**Return value**: a new set `Set` which is the union of the specified ones.

### Set_intersect

```C
Set Set_intersect(const Set set_1, const Set set_2, size_t elm_size);
```

Allocates a new set that is the intersection of `set_1` and `set_2`.

| Type | Description |
| ---- | ----------- |
| `size_t elm_size` | Size in bytes of a member. By default `Data` is `typedef int* Data` |

**Return value**: a new set `Set` which is the intersection of the specified ones.

### Set_difference

```C
Set Set_difference(const Set set_1, const Set set_2, size_t elm_size);
```

Allocates a new set that is the difference of `set_1` and `set_2`.

| Type | Description |
| ---- | ----------- |
| `const Set set_1` | A set to subtract from |
| `const Set set_2` | A set to be subtracted |
| `size_t elm_size` | Size in bytes of a member. By default `Data` is `typedef int* Data` |

**Return value**: a new set `Set` which is the difference of the specified ones.

### Set_is_member

Determines whether the data specified by `data` matches that of a member in the set specified by `set`.

```C
int8_t Set_is_member(const Set set, const Data data)
```

**Return value**: *1* if the member is found, or *0* otherwise.

### Set_is_subset

Determines whether the set specified by `set_1` is a subset of the set specified by `set_2`.

```C
int8_t Set_is_subset(const Set set_1, const Set set_2);
```

**Return value**: *1* if the set is a subset, or *0* otherwise.

### Set_is_equal

Determines whether the set specified by `set_1` is equal to the set specified by `set_2`.

```C
int8_t Set_is_equal(const Set set_1, const Set set_2);
```

**Return value**: *1* if the two sets are equal, or *0* otherwise.

### Set_get_size

Gets the size of the set specified by `set`.

```C
ssize_t Set_get_size(const Set set);
```

**Return value**: number of members in the set, or *-1* if the set is *NULL*

### Set_set_print

Associates a new print function specified by `fptr_print` with the given set `set`.

```C
void Set_set_print(Set set, void (*fptr_print)(const Data));
```

**Return value**: none.

### Set_set_match

Associates a new match function specified by `fptr_match` with the given set `set`.

```C
void Set_set_match(Set set, int (*fptr_match)(const Data, const Data));
```

**Return value**: none.

### Set_set_destroy

Associates a new destroy function specified by `fptr_destroy` with the given set `set`.

```C
void Set_set_destroy(Set set, void (*fptr_destroy)(void*));
```

**Return value**: none.

## Examples

By default, `Data` is a type defenition - `typedef int* Data;`.

### How to write `print` functions

The `fptr_print` argument in the `Set_new`, `Set_print`, or `Set_set_print` operations is a function that displays a member of a set.

Consider two functions:

```C
/* typedef void* Data */
void print_int(const Data data) {
    printf("%d", *((int*) data));
}

/* default data */
void print_int2(const Data data) {
    printf("%d", *data);
}
```

### How to write `match` functions

The `fptr_print` argument in the `Set_new`, or `Set_set_match` operations is a function which is used to determine if two members match.

```C
/* typedef void* Data */
int match_int(const Data data_1, const Data data_2) {
    return (*((int*) x) - *((int*) y));
}

/* default data */
int match_int2(const Data data_1, const Data data_2) {
    return (*x - *y);
}
```

## Resources

[Mastering Algorithms with C](https://www.amazon.com/Mastering-Algorithms-Techniques-Sorting-Encryption/dp/1565924533/ref=sr_1_1?crid=1ZN4ENEQEGO5&keywords=mastering+c+algorithms&qid=1679619546&s=books&sprefix=mastering+c+algoritms%2Cstripbooks-intl-ship%2C221&sr=1-1) by Kyle Loudon.

[Data Structures, Algorithms, and Software Principles in C](https://www.amazon.com/Data-Structures-Algorithms-Software-Principles/dp/0201591189/ref=sr_1_10?crid=14MCGWUKW0F98&keywords=data+structures+and+algorithms+in+C&qid=1679784448&s=books&sprefix=data+structures+and+algorithms+in+c%2Cstripbooks-intl-ship%2C186&sr=1-10) by Thomas Standish.

[Computer Systems: A Programmer's Perspective](https://www.amazon.com/Computer-Systems-Programmers-Randal-Bryant/dp/013034074X/ref=sr_1_3?crid=1NDI8BHE4BPQM&keywords=computer+systems+a+programmer%27s+perspective&qid=1679784732&s=books&sprefix=computer+pers%2Cstripbooks-intl-ship%2C199&sr=1-3) by Randal E. Bryant, David Richard O'Hallaron.

[Patterns in C](https://leanpub.com/patternsinc) by Adam Tornhill.

[Set (mathematics)](https://en.wikipedia.org/wiki/Set_(mathematics)) Wikipedia.