//
//  Graph.h
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//
#ifndef ReducedGraph_h
#define ReducedGraph_h
#include "HashTable.h"
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                            //implement ADT ReducedGraph
/*-----------------------------------------------------------------------------*/
typedef struct s_ReducedGraph {
    TabHash * whiteHashTab;
    TabHash * blackHashTab;
    Graph g;
} ReducedGraph;

//allocates memory for the reduced graph and its two hash tables
ReducedGraph * createReducedGraph(Graph g);

//reloads all the groups of a reduced graph rG, essential if the game has been loaded
ReducedGraph * reloadGroups(ReducedGraph *rG);

void destroyReducedGraph(ReducedGraph * rG);
/*-----------------------------------------------------------------------------*/

#endif /* ReducedGraph_h */ 
