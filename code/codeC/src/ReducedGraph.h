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
    Graph rG;
} ReducedGraph;

ReducedGraph * createReducedGraph(Graph g);
ReducedGraph * reloadGroups(Graph g, ReducedGraph *_rG);

void destroyReducedGraph(ReducedGraph * _rG);
/*-----------------------------------------------------------------------------*/

#endif /* ReducedGraph_h */ 
