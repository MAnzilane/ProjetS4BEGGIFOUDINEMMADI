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
void nbGroup(ReducedGraph *rg, int *IA, int *ADV);
int endGame(ReducedGraph *_rG);
int min(const ReducedGraph * rG, int pos, char color, int profondeur);
int max(const ReducedGraph * rG, int pos, char color, int profondeur);
int heuristique(ReducedGraph *rG);
int minimax(const ReducedGraph *rG, int profondeur);




void cpyReducedGraph(ReducedGraph * rG, const ReducedGraph *rgsrc);
void cpyList(List * l, const List * lsrc);
void cpyHtable (TabHash *tabH, const TabHash *thsrc, int sizeTab);
void cpyGraph (Graph g, const Graph gsrc);
void cpyVertex(Vertex * v, const Vertex * vsrc);
#endif /* TreeOfGameIA */
