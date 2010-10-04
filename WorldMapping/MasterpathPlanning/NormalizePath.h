#ifndef NORMALIZEPATH_H_INCLUDED
#define NORMALIZEPATH_H_INCLUDED

#include "MasterpathPlanning.h"
struct TraceNode *  GetANormalizedLineFromNodes(struct TraceNode * rawnodes,unsigned int rawnodes_size,unsigned int *str8nodes_size);
unsigned char ClearLinePath(struct NodeData * world,struct NodeNeighborsCount *world_neighbors,unsigned int world_x,unsigned int world_size,unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void GetTheShortestNormalizedLineFromNodes(struct NodeData * world,struct NodeNeighborsCount *world_neighbors,unsigned int world_x,unsigned int world_size,struct TraceNode * str8nodes,unsigned int *str8nodes_size);

#endif // NORMALIZEPATH_H_INCLUDED