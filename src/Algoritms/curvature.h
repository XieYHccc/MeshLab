#pragma once

#include <vector>
#include "../PolyMesh/include/PolyMesh/PolyMesh.h"

using namespace acamcad;
using namespace polymesh;
using namespace std;

class mean_curvature {
public:
	mean_curvature();
	mean_curvature(PolyMesh& mesh);
	vector<double> get_curvature();

private:
	void run();
	void cal_local_ave_region();
	void cal_mean_curvature();

private: 
	PolyMesh *mesh;
	vector<double> local_ave_region;					// the area of local average region per vertex
	vector<double> curvature;


};