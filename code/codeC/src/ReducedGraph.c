//
//  Graph.h
//  graphes
//
//  Created by Mmadi.anzilane on 14/04/2017.
//  Copyright © 2017 Mmadi.anzilane. All rights reserved.
//
#include "ReducedGraph.h"

/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/
                        //implement ADT ReducedGraph
/*-----------------------------------------------------------------------------*/
ReducedGraph * createReducedGraph(Graph g) {
    ReducedGraph * rG = malloc(sizeof(ReducedGraph));
    // rG->g = createGraph(sizeGraph);
    // rG->g = createBoardGraph(rG->g, spots, loaded);
    rG->g = g;
    rG->whiteHashTab = createTabHashRg(getNbVertexGraph(rG->g));
    rG->blackHashTab = createTabHashRg(getNbVertexGraph(rG->g));
    return rG;
}

ReducedGraph * reloadGroups(ReducedGraph *rG) {
    for (int i = 0; i < getNbVertexGraph(rG->g); i++) {
        if (rG->g->v[i]->color != EMPTY) {
            if (rG->g->v[i]->color == BLACK) {
                searchGroup(rG->blackHashTab, rG->g, i, BLACK);
            }else {
                searchGroup(rG->whiteHashTab, rG->g, i, WHITE);
            }
        }
    }
    return rG;
}

void destroyReducedGraph(ReducedGraph * rG) {
    destroyTabHash(rG->whiteHashTab, getNbVertexGraph(rG->g));
    destroyTabHash(rG->blackHashTab, getNbVertexGraph(rG->g));
    destroyGraph(rG->g);
    free(rG);
}
