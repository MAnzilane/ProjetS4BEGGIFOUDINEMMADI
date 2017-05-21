#include "TreeOfGameIA.h"
#include <time.h>
// srand(time(NULL)); // initialisation de rand
TreeGame * createTreeGame(ReducedGraph * rg, int profondeur) {
    TreeGame * tg = malloc(sizeof(TreeGame));
    tg->rg = rg;
    tg->profondeur = profondeur;
    return tg;
}
//
// int nbGroup(const ReducedGraph *rg, int *IA, int *ADV);
// int endGame(const ReducedGraph *_rG);
// int min(const ReducedGraph * rgCpy, int profondeur);
// int max(const ReducedGraph * rgCpy, int profondeur);
// int heuristique(const ReducedGraph *_rG);


//on passe une copie car on ne veux rien modifier
int minimax(ReducedGraph *rg, int profondeur) {
    srand(time(NULL)); // initialisation de rand
    int val_max = -1;
    int val_tmp, pos;

    for (size_t i = 0; i < getNbVertexGraph(rg->rG); i++) {
        if (rg->rG->v[i]->color == EMPTY) {
            rg->rG->v[i]->color = BLACK; //because I choose IA is BLACK Player
            //on cerche si ce groupe est gagnant avant de rentré dans la
            val_tmp = min(rg, i, BLACK, profondeur-1);
            if(val_tmp > val_max || ((val_tmp == val_max) && (rand()%2 == 0))) {
                val_max = val_tmp;
                pos = i;
            }

            rg->rG->v[i]->color = EMPTY;
        }
    }
    return pos;
}



int min(ReducedGraph * rgCpy, int lastPos, char color, int profondeur) {
    srand(time(NULL)); // initialisation de rand
    if (profondeur == 0 || searchGroup (rgCpy->blackHashTab, rgCpy->rG, lastPos, color) == 1) {
        return heuristique(rgCpy);
    }

    int val_min = 1;
    int val_tmp;
    for (size_t i = 0; i < getNbVertexGraph(rgCpy->rG); i++) {
        if (rgCpy->rG->v[i]->color == EMPTY) {
            rgCpy->rG->v[i]->color = BLACK;
            val_tmp = max(rgCpy, i ,BLACK, profondeur-1);
            if(val_tmp > val_min || ((val_min == val_tmp) && (rand()%2 == 0))) { //ne pas oublier d'include le randome
                val_min = val_tmp;
            }
            //restoration
            rgCpy->rG->v[i]->color = EMPTY;
        }
    }
    return val_min;
}

int max(ReducedGraph * rgCpy, int lastPos, char color, int profondeur) {
    srand(time(NULL)); // initialisation de rand
    if (profondeur == 0 || searchGroup (rgCpy->blackHashTab, rgCpy->rG, lastPos, color) == 1) {
        return heuristique(rgCpy);
    }

    int val_max = -1;
    int val_tmp;
    for (size_t i = 0; i < getNbVertexGraph(rgCpy->rG); i++) {
        if (rgCpy->rG->v[i]->color == EMPTY) {
            rgCpy->rG->v[i]->color = WHITE;
            val_tmp = min(rgCpy, i,  WHITE, profondeur-1);
            if(val_tmp > val_max || ((val_max == val_tmp) && (rand()%2 == 0))) { //ne pas oublier d'include le randome
                val_max = val_tmp;
            }
            //restoration
            rgCpy->rG->v[i]->color = EMPTY;
        }
    }
    return val_max;
}


//search number of group for the player
void nbGroup(const ReducedGraph *rg, int *IA, int *ADV) {
    *IA = rg->blackHashTab->nbGroups;
    *ADV = rg->whiteHashTab->nbGroups;
}


//s'il y' a un gagnant
int endGame(const ReducedGraph *rg) {
    for (size_t i = 0; i < getNbVertexGraph(rg->rG); i++) {
        if ((*rg).blackHashTab->groupList[i]) {
            if (isAWinningGroup((*rg).blackHashTab->groupList[i], getB1Graph(getSizeGraph(rg->rG)), getB2Graph(getSizeGraph(rg->rG))) == 1) {
                return 1; //iA is a winner
            }
        }
    }

    for (size_t i = 0; i < getNbVertexGraph(rg->rG); i++) {
        if (rg->whiteHashTab->groupList[i]) {
            if (isAWinningGroup(rg->whiteHashTab->groupList[i], getW1Graph(getSizeGraph(rg->rG)), getW2Graph(getSizeGraph(rg->rG))) == 1) {
                return 2;
            }
        }
    }

    return 0;
}

int heuristique(const ReducedGraph * rg) {
    int win = 0;
    if ((win = endGame(rg)) != 0) {
        if (win == 1) {
            return 1;
        }else {
            return 2;
        }
    }

    int nbGroupIA = 0; int nbGroupADV;
    nbGroup(rg, &nbGroupIA, &nbGroupADV);
    if (nbGroupIA - nbGroupADV < 0) {
        return -1;
    }else {
        return 1;
    }
}
