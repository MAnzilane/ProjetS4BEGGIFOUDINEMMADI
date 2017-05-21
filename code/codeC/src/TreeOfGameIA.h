//
//  TreeOfGameIA.h
//  TreeOfGameIA
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//
#ifndef TreeOfGameIA_h
#define TreeOfGameIA_h

#include "ReducedGraph.h"
#include "List.h"
#include <stdio.h>
typedef struct sTreeGame {
    ReducedGraph * rg;
    int profondeur;
}TreeGame;

//on lui passe une copie car il faut q'il modifie rien du tout
//la profondeur de recherche peut varier en fonction
TreeGame * createTreeGame(ReducedGraph * rg, int profondeur);
void nbGroup(const ReducedGraph *rg, int *IA, int *ADV);
int endGame(const ReducedGraph *_rG);
int min(ReducedGraph * rgCpy, int pos, char color, int profondeur);
int max(ReducedGraph * rgCpy, int pos, char color, int profondeur);
int heuristique(const ReducedGraph *_rG);
int minimax(ReducedGraph *rg, int profondeur);
#endif /* TreeOfGameIA */
