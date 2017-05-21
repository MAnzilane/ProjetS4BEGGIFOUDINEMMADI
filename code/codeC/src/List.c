#include "List.h"
#include <mm_malloc.h>
#include <stdlib.h>
#include <assert.h>

/*-----------------------------------------------------------------------------*/
                            //Creation Functions
/*-----------------------------------------------------------------------------*/
List *createList() {
    List *l = NULL;
    l = (List*)malloc(sizeof(List));
    if (l == NULL) {
        exit(EXIT_FAILURE);
    }
    l->sent = (Node*)malloc(sizeof(Node));

    if (l->sent == NULL) {
        exit(EXIT_FAILURE);
    }
    l->sent->pos = -1;
    l->sent->next = l->sent;
    l->sent->prev = l->sent;
    l->sizeList = 0;
    return l;
}

List *pushBack(List *l, int pos) {
    //creation of the node to be added
    Node *n = (Node*)malloc(sizeof(Node));
    n->pos = pos;

    n->prev = l->sent->prev;
    l->sent->prev->next = n;
    l->sent->prev = n;
    n->next = l->sent;;
    l->sizeList++;
    return l;
}
/*-----------------------------------------------------------------------------*/
                            //Modification Functions
/*-----------------------------------------------------------------------------*/
void destroyList(List * l) {
    Node *itr = l->sent->next;
    Node *itrBis = itr;
    while (itr != l->sent) {
        itr = itr->next;
        assert(itrBis);
        itrBis = NULL;
        free(itrBis);
        itrBis = itr;
    }
    free(l->sent);
    free(l);
}

List *popBack(List *l) {
    if (l == NULL) {
        fprintf(stderr, "dsl on ne peut pas supprimer un element sur une liste vide \n");
        exit(EXIT_FAILURE);
    }

    Node *n = l->sent->prev;
    l->sent->prev->next = n->next;
    l->sent->prev = n->prev;
    l->sizeList--;
    free(n);
    return l;
}

/*-----------------------------------------------------------------------------*/
                            //Get Functions
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //Print Functions
/*-----------------------------------------------------------------------------*/
void printList(const List *l) {
    Node *itr = l->sent;
    assert(itr->next);
    int i = 0;
    while (itr->next != l->sent) {
        printf("elem %d %d\n",i++, itr->next->pos);
        assert(itr->next);
        itr = itr->next;
    }
    printf("\n");
}
/*-----------------------------------------------------------------------------*/
                            //End
/*-----------------------------------------------------------------------------*/
