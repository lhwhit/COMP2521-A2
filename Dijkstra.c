// Dijkstra API implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dijkstra.h"
#include "Graph.h"
#include "PQ.h"

ShortestPaths dijkstra(Graph g, Vertex src) {
	
	// Initialising ShortestPaths
	ShortestPaths * sps = (ShortestPaths*)malloc(sizeof(ShortestPaths));
	sps->src = src;
	sps->numNodes = GraphNumVertices(g);
	sps->dist = malloc(sps->numNodes*sizeof(int));
	sps->pred = malloc(sps->numNodes*sizeof(PredNode *));
	PQ queue = PQNew();

	// Setting all initial distances from source node to all other nodes to be infinity
	// except for distance to source node itself 
	// Setting all pred to be NULL
	for (int i = 0; i < sps->numNodes; i++) {
		if (i != src) {
			sps->dist[i] = INFINITY;
			sps->pred[i] = NULL;
		} else {
			sps->dist[i] = 0;
			sps->pred[i] = NULL;
		}
		// Adding all the nodes to PQ with their priority based on distance
		// from source node (currently infinity)
		PQInsert(queue, i, sps->dist[i]);
	}

	while (!PQIsEmpty(queue)) {
		int next = PQDequeue(queue);
		AdjList hasEdge = GraphOutIncident(g, next);

		// Cycle through all outward edges and compare dist(src,a) + dist(a,b) with current dist(src,b)
		while (hasEdge != NULL) {
			if (sps->dist[next] != INFINITY)	{		
				if (sps->dist[next] + hasEdge->weight < sps->dist[hasEdge->v]) {
					// Update dist(src,b)
					sps->dist[hasEdge->v] = sps->dist[next] + hasEdge->weight;
					if (sps->pred[hasEdge->v] == NULL) {
						PredNode *new = malloc(sizeof(PredNode));
						new->v = next;
						new->next = NULL;
						sps->pred[hasEdge->v] = new;
					} else {
						PredNode *p;
						p = sps->pred[hasEdge->v]->next;
						sps->pred[hasEdge->v]->v = next;
						sps->pred[hasEdge->v]->next = NULL;

					........	
				 	
					}
					// Update the priority of vertex b
					PQUpdate(queue, hasEdge->v, sps->dist[hasEdge->v]);
				} else if (sps->dist[next] + hasEdge->weight == sps->dist[hasEdge->v]) {

			.......






				}
			}
			hasEdge = hasEdge->next;
		}
	}
	PQFree(queue);
	return *sps;
}

void showShortestPaths(ShortestPaths sps) {
	// This function is not called, so I donot debug.
	printf("The shortest distance array for %d is:\n", sps.src);
	for (int i = 0; i < sps.numNodes; i++) {
		printf("%d: %d", i, sps.dist[i]);
	}
	printf("The previous node array for %d is:\n", sps.src);
	for (int i = 0; i < sps.numNodes; i++) {
		printf("%d: %p", i, sps.pred[i]);
	}
}

void freeShortestPaths(ShortestPaths sps) {
	for (int i = 0; i < sps.numNodes; i++) {
	 	while(sps.pred[i]) {
			PredNode *q = sps.pred[i];
			sps.pred[i] = q->next;
			free(q);
		}		
	}
	free(sps.dist);
	free(sps.pred);
}
