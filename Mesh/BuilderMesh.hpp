#ifndef _BUILDERMESH_HPP_INCLUDED_
#define _BUILDERMESH_HPP_INCLUDED_

#include "Mesh.hpp"
#include "../Types/UintGroup.hpp"

/*
BuilderMesh is a Mesh with several building routines
*/

class BuilderMesh : public Mesh
{
public:
	BuilderMesh(const uint dim = 4);
	virtual ~BuilderMesh() { clear(); }
	void clear();

	void createCopy(const Mesh &mesh);
	void createGrid(const Vector4 &minp, const Vector4 &maxp, const ddouble h);
	void createTriangleGrid(const Vector2 &minp, const Vector2 &maxp, const ddouble h, const bool rect = false);

	bool createRepeated(const Mesh &mesh, const Vector4 &pos, const Vector4 &dir, const uint steps);
	void createIntersection(const Mesh &mesh, const Vector4 &v, const ddouble dot); // create intersection mesh at plane x, where v.dot(x) = dot

	// add and remove elements
	uint addNode(const Vector4 &p);
	uint addEdge(const uint n0, const uint n1);
	uint addFace(const Buffer<uint> &e);
	uint addBody(const Buffer<uint> &f);
	uint addQuad(const Buffer<uint> &b);
	void removeNode(const uint n);
	void removeEdge(const uint e);
	void removeFace(const uint f);
	void removeBody(const uint b);
	void removeQuad(const uint q);
	uint detachNode(const uint n);
	uint detachEdge(const uint e);
	uint detachFace(const uint f);
	uint detachBody(const uint b);
	uint detachQuad(const uint q);
	uint detachEdgeRecursive(const uint e);
	uint detachFaceRecursive(const uint f);
	uint detachBodyRecursive(const uint b);
	uint detachQuadRecursive(const uint q);
	void removeDetached();
	void removeNodes(const Buffer<uint> &n);
	void removeEdges(const Buffer<uint> &e);
	void removeFaces(const Buffer<uint> &f);
	void removeBodies(const Buffer<uint> &b);
	void removeQuads(const Buffer<uint> &q);

	// flags
	void fillNodeFlags(const uint flag, const UintGroup &oldflag = UINTGROUPALL);
	void fillEdgeFlags(const uint flag, const UintGroup &oldflag = UINTGROUPALL);
	void fillFaceFlags(const uint flag, const UintGroup &oldflag = UINTGROUPALL);
	void fillBodyFlags(const uint flag, const UintGroup &oldflag = UINTGROUPALL);
	void fillQuadFlags(const uint flag, const UintGroup &oldflag = UINTGROUPALL);
	void fillFlags(const uint flag, const UintGroup &oldflag = UINTGROUPALL);
	void fillBoundaryFlags(const uint flag, const UintGroup &oldflag = UINTGROUPALL);
	void fillFlags(const Vector4 &minp, const Vector4 &maxp, const uint flag, const UintGroup &oldflag = UINTGROUPALL);
	void removeByFlags(const UintGroup &flag = UINTGROUPALL);

	// combine with other mesh
	void combine(const Mesh &mesh);

	// stretch mesh
	void stretchLinear(const Vector4 &v, const uint steps, const UintGroup &flag = UINTGROUPALL, const uint flagMiddle = 0, const uint flagEnd = 0);

	// repeat mesh blocks
	bool repeatMiddle(const Vector4 &pos, const Vector4 &dir, const uint steps);

protected:

	void stretch(const Buffer<uint> &n, const uint steps, const UintGroup &flag, const uint flagMiddle, const uint flagEnd);

	// tables of detached cells
	uint m_dns;
	Buffer<uint> m_dn;
	uint m_des;
	Buffer<uint> m_de;
	uint m_dfs;
	Buffer<uint> m_df;
	uint m_dbs;
	Buffer<uint> m_db;
	uint m_dqs;
	Buffer<uint> m_dq;

};

#endif //_BUILDERMESH_HPP_INCLUDED_
