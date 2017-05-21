#include "TreeOfGameIA.h"
#include <time.h>
#include <string.h>
#include <assert.h>
// srand(time(NULL)); // initialisation de rand
// TreeGame * createTreeGame(ReducedGraph * g, int profondeur) {
//     TreeGame * tg = malloc(sizeof(TreeGame));
//     tg->g = g;
//     tg->profondeur = profondeur;
//     return tg;
// }
//
// int nbGroup(const ReducedGraph *g, int *IA, int *ADV);
// int endGame(const ReducedGraph *_g);
// int min(const ReducedGraph * gCpy, int profondeur);
// int max(const ReducedGraph * gCpy, int profondeur);
// int heuristique(const ReducedGraph *_g);


//on passe une copie car on ne veux rien modifier
int minimax(const ReducedGraph *rG, int profondeur) {
    //srand(time(NULL)); // initialisation de rand
    //creation de la copy 
    ReducedGraph * etatInit = createReducedGraph(rG->g);
    cpyReducedGraph(etatInit, rG);

    int val_max = -1;
    int val_tmp, pos;

    for (size_t i = 0; i < getNbVertexGraph(etatInit->g); i++) {
        if (etatInit->g->v[i]->color == EMPTY) {
            etatInit->g->v[i]->color = BLACK; //because I choose IA is BLACK Player
            //on cerche si ce groupe est gagnant avant de rentré dans la
            val_tmp = min(etatInit, i, BLACK, profondeur-1);
            printf("valtemp du min dans le minimax de la position %d = %d\n",i, val_tmp);
            if(val_tmp > val_max || ((val_tmp == val_max) && (rand()%2 == 0))) {
                val_max = val_tmp;
                pos = i;
            }

            etatInit->g->v[i]->color = EMPTY;
        }
    }
    return pos;
}



int min(const ReducedGraph * rG, int pos, char color, int profondeur) {
    ReducedGraph * etatInit = createReducedGraph(rG->g);
    cpyReducedGraph(etatInit, rG);
    if (profondeur == 0 || endGame(etatInit) != 0) {
        return heuristique(etatInit);
    }
    printBoard(etatInit->g);
    //srand(time(NULL)); // initialisation de rand
    // if (color == BLACK) {
    //     if (profondeur == 0 || searchGroup(etatInit->blackHashTab, etatInit->g, pos, BLACK) == 1) {
    //         return heuristique(etatInit);
    //     }
    // }else {
    //     if (profondeur == 0 || searchGroup(etatInit->whiteHashTab, etatInit->g, pos, WHITE) == 1) {
    //         return heuristique(etatInit);
    //     }
    // }

    int val_min = 1;
    int val_tmp;
    for (size_t i = 0; i < getNbVertexGraph(etatInit->g); i++) {
        if (etatInit->g->v[i]->color == EMPTY) {
            etatInit->g->v[i]->color = WHITE;
            printf("valtemp du max dans le min de la position %d = %d\n",i, val_tmp);
            val_tmp = max(etatInit, i, WHITE, profondeur-1);
            if(val_tmp > val_min || ((val_min == val_tmp) && (rand()%2 == 0))) { //ne pas oublier d'include le randome
                val_min = val_tmp;
            }
            //restoration
            etatInit->g->v[i]->color = EMPTY;
        }
    }
    return val_min;
}

int max(const ReducedGraph * rG, int pos, char color, int profondeur) {
    ReducedGraph * etatInit = createReducedGraph(rG->g);
    cpyReducedGraph(etatInit, rG);
    printBoard(etatInit->g);
    if (profondeur == 0 || endGame(etatInit) != 0) {
        return heuristique(etatInit);
    }
    //srand(time(NULL)); // initialisation de rand
    // if (color == BLACK) {
    //     if (profondeur == 0 || searchGroup(etatInit->blackHashTab, etatInit->g, pos, BLACK) == 1) {
    //         return heuristique(etatInit);
    //     }
    // }else {
    //     if (profondeur == 0 || searchGroup(etatInit->whiteHashTab, etatInit->g, pos, WHITE) == 1) {
    //         return heuristique(etatInit);
    //     }
    // }

    int val_max = -1;
    int val_tmp;
    for (size_t i = 0; i < getNbVertexGraph(etatInit->g); i++) {
        if (etatInit->g->v[i]->color == EMPTY) {
            etatInit->g->v[i]->color = BLACK;
            val_tmp = min(etatInit, i, BLACK, profondeur-1);
            printf("valtemp du min dans le max de la position %d = %d\n",i, val_tmp);
            if(val_tmp > val_max || ((val_max == val_tmp) && (rand()%2 == 0))) { //ne pas oublier d'include le randome
                val_max = val_tmp;
            }
            //restoration
            etatInit->g->v[i]->color = EMPTY;
        }
    }
    return val_max;
}


//search number of group for the player
void nbGroup(ReducedGraph *rG, int *IA, int *ADV) {
    *IA = rG->blackHashTab->nbGroups;
    *ADV = rG->whiteHashTab->nbGroups;
}


//s'il y' a un gagnant
int endGame(ReducedGraph *rG) {
    ReducedGraph * etatInit = createReducedGraph(rG->g);
    cpyReducedGraph(etatInit, rG);
    for (int i = 0; i < getNbVertexGraph(etatInit->g); i++) {
        if (etatInit->g->v[i]->color != EMPTY) {
            if (etatInit->g->v[i]->color == BLACK) {
                if (searchGroup(etatInit->blackHashTab, etatInit->g, i, BLACK) == 1) {
                    return 1;
                }
            }else {
                if (searchGroup(etatInit->whiteHashTab, etatInit->g, i, WHITE) == 1) {
                    return -1;
                }
            }
        }
    }
    return 0;
}

int heuristique(ReducedGraph * rG) {
    int win = 0;
    if ((win = endGame(rG)) != 0) {
        if (win == 1) {
            return 1;
        }else {
            return -1;
        }
    }

    int nbGroupIA = 0; int nbGroupADV;
    nbGroup(rG, &nbGroupIA, &nbGroupADV);
    if (nbGroupIA < nbGroupADV) {
        return -1;
    }else {
        return 1;
    }
}


void cpyReducedGraph(ReducedGraph * rG, const ReducedGraph *rgsrc) {
    assert(rG && rgsrc);
    cpyGraph(rG->g, rgsrc->g);
    cpyHtable(rG->whiteHashTab, rgsrc->whiteHashTab, getNbVertexGraph(rgsrc->g));
    cpyHtable(rG->blackHashTab, rgsrc->blackHashTab, getNbVertexGraph(rgsrc->g));
}



void cpyList(List * l, const List * lsrc) {
    //assert(l && lsrc);
    Node *itr = lsrc->sent->next;
    while (itr == lsrc->sent) {
        l = pushBack(l, itr->pos);
        itr = itr->next;
    }
    //assert(lsrc->sizeList == l->sizeList);
}

void cpyHtable (TabHash *tabH, const TabHash *thsrc, int sizeTab) {
    //assert(tabH && thsrc);
    for (int i = 0; i < sizeTab; ++i) {
        if (thsrc->groupList[i] != NULL) {
            cpyList(tabH->groupList[i], thsrc->groupList[i]);
            tabH->nbGroups++; 
        }
        //assert(tabH->nbGroups == thsrc->nbGroups);
    }
}

void cpyGraph (Graph g, const Graph gsrc) {
    //assert(g && gsrc);
    for (int i = 0; i < getNbVertexGraph(gsrc)+4; ++i) {
        cpyVertex(g->v[i], gsrc->v[i]);
    }
}

void cpyVertex(Vertex * v, const Vertex * vsrc) {
    //assert(v && vsrc);
    v->isInGroup = vsrc->isInGroup;
    v->groupLeader = vsrc->groupLeader;
    v->color = vsrc->color;
    v->Adjacents = vsrc->Adjacents;
}