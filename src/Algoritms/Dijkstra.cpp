#include "Dijkstra.h"

std::vector<int> shortest_path(PolyMesh& mesh, int sp, int ep)
{
	// data structure used in algorithm
	std::priority_queue<node> que;							
	std::vector<int> v_pre(mesh.numVertices(), -1);					// store the id of each vertex's pre vertex
	std::vector<int> is_shortest(mesh.numVertices(),0);				// to record if a vertex's shortest path is found
	std::vector<double> dis_shortest(mesh.numVertices(),DBL_MAX);	// init each vertex's shortest distance to infinty

	// init
	dis_shortest[sp] = 0;
	v_pre[sp] = sp;
	que.push(node(sp, 0));

	// update shortest distance			
	while (!que.empty())											// since it's slower to change the value in priority queue
	{																// so, we could just push into a new item with the updated 
		node tmp = que.top();										// distance and judge if a item's shortest path has been got
		que.pop();													// by a bool list
		if (is_shortest[tmp.id] == 1)	
			continue;
		if (tmp.id == ep)
			break;
		
		is_shortest[tmp.id] = 1;
		MVert* v1 = mesh.vert(tmp.id);
		for (VertexVertexIter vv_it = mesh.vv_iter(v1); vv_it.isValid(); ++vv_it)
		{
			MVert* v2 = *vv_it;
			MEdge* e12 = mesh.edgeBetween(v1, v2);
			if (dis_shortest[v1->index()] + e12->length() < dis_shortest[v2->index()])
			{
				dis_shortest[v2->index()] = dis_shortest[v1->index()] + e12->length();
				que.push(node(v2->index(), dis_shortest[v2->index()]));
				v_pre[v2->index()] = v1->index();
			}
		}
	}

	// get the shortest path from sp to eq
	std::vector<int> path;
	int tmp_pre = v_pre[ep];
	while(tmp_pre != sp)
	{
		path.push_back(tmp_pre);
		tmp_pre = v_pre[tmp_pre];
	}
	path.push_back(sp);

	return path;
}