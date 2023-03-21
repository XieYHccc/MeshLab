#include "math.h"


double sum(const vector<double>& array)
{
    double sum = 0.0;
    for (int i = 0; i < array.size(); i++)
        sum += array[i];
    return sum;
}

double stddev(const vector<double>& array)
{
    size_t n = array.size();
    double sum_array = sum(array);
    double mean_array = sum_array / array.size();
    double variance = 0.0;
    for (size_t i = 0; i < n; i++) {
        variance += pow(array[i] - mean_array, 2);
    }
    variance /= array.size();
    double std_deviation = sqrt(variance);

    return std_deviation;
}

MVector3 cal_circum_enter(const MVector3& a, const MVector3& b, const MVector3& c)
{
    MVector3 ac = c - a, ab = b - a;
    MVector3 abXac = cross(ab, ac), abXacXab = cross(abXac, ab), acXabXac = cross(ac, abXac);
    return a + (abXacXab * ac.normSq() + acXabXac * ab.normSq()) / (2.0 * abXac.normSq());
}