#pragma once

#include <vector>
#include "../PolyMesh/include/PolyMesh/PolyMesh.h"
#include <queue>

using namespace acamcad;
using namespace polymesh;

struct node						// the element to be put into priority queue
{
	node(int id, double dis)
	{
		this->id = id;
		this->dis = dis;

	}

	bool operator<(const node& rhs) const { return dis > rhs.dis; }

	int id;
	double dis;

};

std::vector<int> shortest_path(PolyMesh& mesh, int sp, int ep);