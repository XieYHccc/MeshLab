#pragma once

#include"../src/PolyMesh/include/Math/MVector3.h"
#include<vector>
#define PI 3.14159265359

using namespace acamcad;
using namespace std;

// numeric calculation for vector<double>
double sum(const vector<double>& array);

double stddev(const vector<double>& array);

MVector3 cal_circum_enter(const MVector3& a, const MVector3& b, const MVector3& c);
