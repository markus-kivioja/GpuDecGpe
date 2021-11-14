#ifndef _DELAUNAYMESH_HPP_INCLUDED_
#define _DELAUNAYMESH_HPP_INCLUDED_

#include "BuilderMesh.hpp"

/*
DelaunayMesh is a convex weighted Delaunay mesh
*/

class DelaunayMesh : public BuilderMesh
{
public:
	DelaunayMesh(const uint dim = 4);
	virtual ~DelaunayMesh() { clear(); }
	void clear();

	// create 2d grids
	void createHexagonGrid(const Vector2 &minp, const Vector2 &maxp, const ddouble h);
	void createSnubSquareGrid(const Vector2 &minp, const Vector2 &maxp, const ddouble h);
	void createTetrilleGrid(const Vector2 &minp, const Vector2 &maxp, const ddouble h);

	// create 3d grids
	void createFccGrid(const Vector3 &minp, const Vector3 &maxp, const ddouble h);
	void createBccGrid(const Vector3 &minp, const Vector3 &maxp, const ddouble h);
	void createTruncatedOctahedraGrid(const Vector3 &minp, const Vector3 &maxp, const ddouble h); // dual of BCC
	void createA15Grid(const Vector3 &minp, const Vector3 &maxp, const ddouble h);
	void createC15Grid(const Vector3 &minp, const Vector3 &maxp, const ddouble h);
	void createZGrid(const Vector3 &minp, const Vector3 &maxp, const ddouble h);

	// find nearest node
	uint findNode(const Vector4 &p, uint curr = 0) const;
	bool findCell(const Vector4 &p, uint &curr) const;

	// insert and erase Delaunay nodes
	uint insertNode(const Vector4 &p, const ddouble w, uint nearNode = 0);
	bool eraseNode(const uint n);

	void transform(const Matrix4 &mat);

protected:

	ddouble getRadiusSq(const Vector4 &p, const uint node) const { return getMetric().normsq(p - getNodePosition(node)) + getNodeWeight(node); }
	ddouble getRadiusSq(const Vector4 &p, const Buffer<uint> &n) const;
	bool isInSphere(const Vector4 &p, const ddouble sq, const uint node) const { return isInSphere(p, sq, Buffer<uint>(1, node)); }
	bool isInSphere(const Vector4 &p, const ddouble sq, const Buffer<uint> &n) const;
	bool isOutsideSphere(const Vector4 &p, const ddouble sq, const Buffer<uint> &n) const;
	void increaseDimension();
	uint mergeFace(const uint f);
	uint mergeBody(const uint b);
	uint mergeQuad(const uint q);


};

#endif //_DELAUNAYMESH_HPP_INCLUDED_
