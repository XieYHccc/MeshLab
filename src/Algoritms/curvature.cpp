#include "curvature.h"
#include "math.h"
mean_curvature::mean_curvature()
{
}

mean_curvature::mean_curvature(PolyMesh& mesh)
	:mesh(&mesh)
{
	run();
}

vector<double> mean_curvature::get_curvature()
{
	return curvature;
}
void mean_curvature::run()
{
	cal_local_ave_region();
	cal_mean_curvature();
}

void mean_curvature::cal_local_ave_region() 
{
	local_ave_region = vector<double>(mesh->numVertices(),0);

	for (MPolyFace* face : mesh->polyfaces())
	{
		// judge if it's a obtuse triangle
		bool isObtuseAngle = false;
		MVert* obtuseVertex;
		MHalfedge* he = face->halfEdge();
		MHalfedge* he_next = he->next(), * he_prev = he->prev();
		MVert* v_from_he = he->fromVertex(), * v_from_he_next = he_next->fromVertex(), * v_from_he_prev = he_prev->fromVertex();
		MVector3 vec_he = he->tangent(), vec_he_next = he_next->tangent(), vec_he_prev = he_prev->tangent();
		if (vectorAngle(vec_he, -vec_he_prev) > PI / 2)
		{
			isObtuseAngle = true;
			obtuseVertex = v_from_he;
		}
		else if (vectorAngle(vec_he_next, -vec_he) > PI / 2.0)
		{
			isObtuseAngle = true;
			obtuseVertex = v_from_he_next;
		}
		else if (vectorAngle(vec_he_prev, -vec_he_next) > PI / 2.0)
		{
			isObtuseAngle = true;
			obtuseVertex = v_from_he_prev;
		}

		// calculate area and assign to each vertex
		if (isObtuseAngle)
		{
			double area = 0.5 * norm(cross(vec_he, -vec_he_prev));
			for (MVert* fv : mesh->polygonVertices(face))
			{
				if (fv == obtuseVertex)
					local_ave_region[fv->index()] += area / 4;
				else
				{
					local_ave_region[fv->index()] += area / 2;
				}
			}
		}
		else
		{
			MVector3 cc = cal_circum_enter(v_from_he->position(), v_from_he_next->position(), v_from_he_prev->position());
			for (MHalfedge* fhe : mesh->polygonHalfedges(face))
			{
				MVector3 edgeMidpoint = 0.5 * (fhe->fromVertex()->position() + fhe->toVertex()->position());
				double edgeLength = fhe->edge()->length();
				double partArea = 0.5 * edgeLength * (cc - edgeMidpoint).norm();
				local_ave_region[fhe->fromVertex()->index()] += 0.5 * partArea;
				local_ave_region[fhe->toVertex()->index()] += 0.5 * partArea;
			}
		}

	}
}

void mean_curvature::cal_mean_curvature()
{
	curvature = vector<double>(mesh->numVertices(), 0);
	for (MVert* v : mesh->vertices())
	{
		MVector3 vec_temp = {0.0,0.0,0.0}, p_v = v->position();
		for (auto voh_it = mesh->voh_iter(v); voh_it.isValid(); ++voh_it)
		{
			MHalfedge* voh_next = (*voh_it)->next();
			MVert* voh_to = (*voh_it)->toVertex(), * voh_next_to = voh_next->toVertex();
			MVector3 p_voh_to = voh_to->position(), p_voh_next_to = voh_next_to->position();
			double angle_voh = vectorAngle(p_v - p_voh_to, p_voh_next_to - p_voh_to),
				angle_voh_next = vectorAngle(p_voh_to - p_voh_next_to, p_v - p_voh_next_to);
			vec_temp += (p_voh_to - p_v) / tan(angle_voh_next);
			vec_temp += (p_voh_next_to - p_v) / tan(angle_voh);
		}
		vec_temp /= 4 * local_ave_region[v->index()];
		double abs_curv = vec_temp.norm();
		if (dot(vec_temp, v->normal()) > 0)
			curvature[v->index()] = -abs_curv;
		else
			curvature[v->index()] = abs_curv;
	}
}