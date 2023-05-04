#include "set.h"

/* ================================ */

struct _set_node {
    Data data;

    struct _set_node* next;
};

struct _set {
    ssize_t size;
    struct _set_node* head;
    struct _set_node* tail;

    int (*fptr_match)(const Data, const Data);
    void (*fptr_print)(const Data);
    void (*fptr_destroy)(void*);
};

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

static Node Node_new(const Data data) {
    Node node = NULL;

    if (data != NULL) {
        if ((node = (Node) malloc(sizeof(struct _set_node))) != NULL) {
            node->data = (Data) data;
            node->next = NULL;
        }
        else {
            warn_with_sys_msg("Memory allocation failure");
        }
    }
    else {
        warn_with_user_msg(__func__, "data can't be NULL");
    }

    return node;
}

/* ================================ */

static Data Node_destroy(Node* node) {
    Data data = NULL;

    if ((node != NULL) && (*node != NULL)) {
        data = (*node)->data;
        (*node)->next = NULL;

        /* Clear memory*/
        memset(*node, 0, sizeof(struct _set_node));
        /* Deallocate memory */
        free(*node);

        *node = NULL;
    }

    return data;
}

/* ================================ */

static Data Set_remove_first(Set set) {
    Node node = NULL;
    Data data = NULL;

    if (set->size > 0) {
        node = set->head;

        switch (set->size) {
            case 1:
                set->head = set->tail = NULL;

                break ;

            default:
                set->head = node->next;

                break ;
        }

        data = Node_destroy(&node);
        set->size--;
    }

    return data;
}

/* ================================ */

static Node Set_find(const Set set, const Data data) {
    Node node = NULL;

    for (Node temp = set->head; temp != NULL; temp = temp->next) {
        if (set->fptr_match(temp->data, data) == 0) {
            node = temp;

            break ;
        }
    }

    return node;
}

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

Set Set_new(int (*fptr_match)(const Data, const Data), void (*fptr_print)(const Data), void (*fptr_destroy)(void*)) {
    Set set = NULL;

    if ((set = (Set) malloc(sizeof(struct _set))) != NULL) {
        set->size = 0;
        set->head = set->tail = NULL;

        set->fptr_destroy = fptr_destroy;
        set->fptr_match = fptr_match;
        set->fptr_print = fptr_print;
    }
    else {
        warn_with_sys_msg("Memory allocation failure");
    }

    return set;
}

/* ================================ */

void Set_print(const Set set, void (*fptr_print)(const Data)) {
    void (*alt_fptr_print)(const Data) = NULL;

    if (set != NULL) {
        if ((set->fptr_print == NULL) && (fptr_print == NULL)) {
            warn_with_user_msg(__func__, "there is no associated `print` function with the given set");

            return ;
        }

        printf("{");

        if (set->size > 0) {
            alt_fptr_print = (fptr_print != NULL) ? fptr_print : set->fptr_print;

            for (Node node = set->head; node != NULL; node = node->next) {
                alt_fptr_print(node->data);

                if (node->next != NULL) {
                    printf(", ");
                }
            }
        }

        printf("}\n");
    }
    else {
        warn_with_user_msg(__func__, "provided set is NULL");
    }

    return ;
}

/* ================================ */

void Set_destroy(Set* set) {
    Data data = NULL;

    if ((set != NULL) && (*set != NULL)) {
        while ((*set)->size > 0) {
            data = Set_remove_first(*set);

            if ((*set)->fptr_destroy != NULL) {
                (*set)->fptr_destroy(data);
            }
        }

        /* Clear memory */
        memset(*set, 0, sizeof(struct _set));
        /* Dealloce memory */
        free(*set);

        *set = NULL;
    }
    else {
        warn_with_user_msg(__func__, "provided set pointer and/or set is NULL");
    }

    return ;
}

/* ================================ */

int8_t Set_insert(Set set, const Data data) {
    int8_t result = 0;
    Node node = NULL;

    if (set != NULL) {
        /* The provided set doesn't contain given data */
        if ((node = Set_find(set, data)) == NULL) {
            if ((node = Node_new(data)) != NULL) {
                switch (set->size) {
                    case 0:
                        set->head = set->tail = node;

                        break ;

                    default:
                        set->tail->next = node;
                        set->tail = node;

                        break ;
                }

                set->size++;
                result = 1;
            }
        }
        else {
            result = -1;
        }
    }
    else {
        warn_with_user_msg(__func__, "provided set is NULL");
    }

    return result;
}

/* ================================ */

void Set_remove(Set set, Data data) {
    Node node = NULL;
    Node previous = NULL, current = NULL;

    if (set != NULL) {
        if (data != NULL) {
            if (set->fptr_match != NULL) {
                if ((node = Set_find(set, data)) != NULL) {

                    if (node == set->head) {
                        set->head = set->head->next;
                    }
                    else {
                        for (current = set->head, previous = NULL; current != node; previous = current, current = current->next) ;

                        previous->next = current->next;
                    }

                    set->size--;

                    data = Node_destroy(&node);

                    if (set->fptr_destroy != NULL) {
                        set->fptr_destroy(data);
                    }
                }
            }
            else {
                warn_with_user_msg(__func__, "there is no associated `match` function with the given set");
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "provided set is NULL");
    }

    return ;
}

/* ================================ */

ssize_t Set_get_size(const Set set) {
    return (set != NULL) ? set->size : -1;
}


/* ================================ */

Set Set_copy(const Set set, size_t elm_size) {
    Set new_set = NULL;

    if (set != NULL) {
        if ((new_set = Set_new(set->fptr_match, set->fptr_print, set->fptr_destroy)) != NULL) {
            if (set->size > 0) {
                for (Node temp = set->head; temp != NULL; temp = temp->next) {
                    Data data = NULL;

                    if ((data = (Data) malloc(sizeof(elm_size))) != NULL) {
                        *data = *(temp->data);

                        Set_insert(new_set, data);
                    }
                    else {
                        warn_with_user_msg(__func__, "Memory allocation failure");

                        Set_destroy(&new_set);

                        return new_set;
                    }
                }
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "Provided set is NULL");
    }

    return new_set;
}

/* ================================ */

Set Set_union(const Set set_1, const Set set_2, size_t elm_size) {
    Set set_u = NULL;
    Data data = NULL;

    if ((set_1 != NULL) && (set_2 != NULL)) {
        if ((set_u = Set_copy(set_1, elm_size)) != NULL) {
            for (Node temp = set_2->head; temp != NULL; temp = temp->next) {
                if (Set_find(set_u, temp->data) == NULL) {
                    if ((data = (Data) malloc(elm_size)) != NULL) {
                        *data = *(temp->data);

                        if (Set_insert(set_u, data) == 0) {
                            warn_with_user_msg(__func__, "Memory allocation failure.");

                            Set_destroy(&set_u);
                        }
                    }
                    else {
                        warn_with_user_msg(__func__, "Memory allocation failure.");

                        Set_destroy(&set_u);
                    }
                }
            }   
        }
    }
    else if ((set_1 == NULL) || (set_2) == NULL) {
        return Set_copy((set_1 != NULL) ? set_1 : (set_2 != NULL) ? set_2 : NULL, elm_size);
    }

    return set_u;
}

/* ================================ */

Set Set_intersect(const Set set_1, const Set set_2, size_t elm_size) {
    Set set_i = NULL;
    Data data = NULL;

    if ((set_1 != NULL) && (set_2 != NULL)) {
        if ((set_i = Set_new(set_1->fptr_match, set_1->fptr_print, set_1->fptr_destroy)) != NULL) {
            Node temp = (Set_get_size(set_1) < Set_get_size(set_2)) ? set_1->head : set_2->head;
            Set set_t = (Set_get_size(set_1) < Set_get_size(set_2)) ? set_2 : set_1;

            for (; temp != NULL; temp = temp->next) {
                if ((Set_find(set_t, temp->data)) != NULL) {
                    if ((data = (Data) malloc(elm_size)) != NULL) {
                        *data = *(temp->data);

                        if (Set_insert(set_i, data) == 0) {
                            warn_with_user_msg(__func__, "Memory allocation failure.");

                            Set_destroy(&set_i);
                        }
                    }
                    else {
                        warn_with_user_msg(__func__, "Memory allocation failure.");

                        Set_destroy(&set_i);
                    }
                }
            }
        }
    }

    return set_i;
}

/* ================================ */

Set Set_difference(const Set set_1, const Set set_2, size_t elm_size) {
    Set set_d = NULL;
    Data data = NULL;

    if ((set_1 != NULL) && (set_2 != NULL)) {
        if ((set_d = Set_new(set_1->fptr_match, set_1->fptr_print, set_1->fptr_destroy)) != NULL) {
            for (Node temp = set_1->head; temp != NULL; temp = temp->next) {
                if (Set_find(set_2, temp->data) == NULL) {
                    if ((data = (Data) malloc(elm_size)) != NULL) {
                        *data = *(temp->data);

                        if (Set_insert(set_d, data) == 0) {
                            warn_with_user_msg(__func__, "Memory allocation failure.");

                            Set_destroy(&set_d);
                        }
                    }
                    else {
                        warn_with_user_msg(__func__, "Memory allocation failure.");

                        Set_destroy(&set_d);
                    }
                }
            }
        }
    }

    return set_d;
}

/* ================================ */

int8_t Set_is_member(const Set set, const Data data) {
    int8_t result = 0;

    for (Node temp = set->head; temp != NULL; temp = temp->next) {
        if (set->fptr_match(temp->data, data) == 0) {
            result = 1;

            break ;
        }
    }

    return result;
}

/* ================================ */

int8_t Set_is_subset(const Set set_1, const Set set_2) {
    int8_t result = 0;

    if ((set_1 != NULL) && (set_2 != NULL)) {
        if (Set_get_size(set_1) <= Set_get_size(set_2)) {
            for (Node temp = set_1->head; temp != NULL; temp = temp->next) {
                if ((result = Set_is_member(set_2, temp->data)) == 0) {
                    return result;
                }
            }
        }
    }

    return result;
}

/* ================================ */

int8_t Set_is_equal(const Set set_1, const Set set_2) {
    int8_t result = 0;

    if ((set_1 != NULL) && (set_2 != NULL)) {
        if (Set_get_size(set_1) == Set_get_size(set_2)) {
            for (Node temp = set_1->head; temp != NULL; temp = temp->next) {
                if ((result = Set_is_member(set_2, temp->data)) == 0) {
                    return result;
                }
            }
        }
    }

    return result;
}

/* ================================ */

void Set_set_print(Set set, void (*fptr_print)(const Data)) {
    if (set != NULL) {
        set->fptr_print = fptr_print;
    }

    return ;
}

/* ================================ */

void Set_set_match(Set set, int (*fptr_match)(const Data, const Data)) {
    if (set != NULL) {
        set->fptr_match = fptr_match;
    }

    return ;
}

/* ================================ */

void Set_set_destroy(Set set, void (*fptr_destroy)(void*)) {
    if (set != NULL) {
        set->fptr_destroy = fptr_destroy;
    }

    return ;
}