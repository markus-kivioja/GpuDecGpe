#ifndef _MESH_HPP_INCLUDED_
#define _MESH_HPP_INCLUDED_

#include "Metric.hpp"
#include "../Types/Buffer.hpp"
#include "../Types/UintGroup.hpp"
#include "../Types/TwoVector4.hpp"
#include <string>
#include <fstream>

/*
Mesh is a cell partitioner up to 4-dimensional space
*/

struct Node
{
	Buffer<uint> e;
};

struct Edge
{
	Buffer<uint> n;
	Buffer<uint> f;
};

struct Face
{
	Buffer<uint> e;
	Buffer<uint> b;
};

struct Body
{
	Buffer<uint> f;
	Buffer<uint> q;
};

struct Quad
{
	Buffer<uint> b;
};

class Mesh
{
public:
	Mesh(const uint dim = 4);
	virtual ~Mesh() { clear(); }
	void clear();
	void swap(Mesh &mesh);

	// load and save mesh
	bool loadJRMesh(const std::string &path);
	bool saveJRMesh(const std::string &path) const;

	// statistics
	bool saveStatistics(const std::string &path, const UintGroup &flag = UINTGROUPALL) const;

	// number of cells
	uint getNodeSize() const { return m_nsize; }
	uint getEdgeSize() const { return m_esize; }
	uint getFaceSize() const { return m_fsize; }
	uint getBodySize() const { return m_bsize; }
	uint getQuadSize() const { return m_qsize; }

	// flags
	uint getNodeFlag(const uint i) const { if(i < m_nflag.size()) return m_nflag[i]; return 0; }
	uint getEdgeFlag(const uint i) const { if(i < m_eflag.size()) return m_eflag[i]; return 0; }
	uint getFaceFlag(const uint i) const { if(i < m_fflag.size()) return m_fflag[i]; return 0; }
	uint getBodyFlag(const uint i) const { if(i < m_bflag.size()) return m_bflag[i]; return 0; }
	uint getQuadFlag(const uint i) const { if(i < m_qflag.size()) return m_qflag[i]; return 0; }

	void setNodeFlag(const uint n, const uint flag);
	void setEdgeFlag(const uint e, const uint flag);
	void setFaceFlag(const uint f, const uint flag);
	void setBodyFlag(const uint b, const uint flag);
	void setQuadFlag(const uint q, const uint flag);

	// intersections
	uint getEdgeIntersection(const uint e0, const uint e1) const { return getCommon(m_e[e0].n, m_e[e1].n); }
	uint getFaceIntersection(const uint f0, const uint f1) const { return getCommon(m_f[f0].e, m_f[f1].e); }
	uint getBodyIntersection(const uint b0, const uint b1) const { return getCommon(m_b[b0].f, m_b[b1].f); }
	uint getQuadIntersection(const uint q0, const uint q1) const { return getCommon(m_q[q0].b, m_q[q1].b); }

	// neighbors
	const Buffer<uint> &getNodeEdges(const uint n) const { return m_n[n].e; }
	Buffer<uint> getNodeFaces(const uint n) const;
	Buffer<uint> getNodeBodies(const uint n) const;
	Buffer<uint> getNodeQuads(const uint n) const;
	const Buffer<uint> &getEdgeNodes(const uint e) const { return m_e[e].n; }
	const Buffer<uint> &getEdgeFaces(const uint e) const { return m_e[e].f; }
	Buffer<uint> getEdgeBodies(const uint e) const;
	Buffer<uint> getEdgeQuads(const uint e) const;
	Buffer<uint> getFaceNodes(const uint f) const;
	const Buffer<uint> &getFaceEdges(const uint f) const { return m_f[f].e; }
	const Buffer<uint> &getFaceBodies(const uint f) const { return m_f[f].b; }
	Buffer<uint> getFaceQuads(const uint f) const;
	Buffer<uint> getBodyNodes(const uint b) const;
	Buffer<uint> getBodyEdges(const uint b) const;
	const Buffer<uint> &getBodyFaces(const uint b) const { return m_b[b].f; }
	const Buffer<uint> &getBodyQuads(const uint b) const { return m_b[b].q; }
	Buffer<uint> getQuadNodes(const uint q) const;
	Buffer<uint> getQuadEdges(const uint q) const;
	Buffer<uint> getQuadFaces(const uint q) const;
	const Buffer<uint> &getQuadBodies(const uint q) const { return m_q[q].b; }

	// more neighbors
	uint getEdgeOtherNode(const uint e, const uint n) const;

	// vector space dimension
	uint getDimension() const { return m_dim; }

	// node weight
	ddouble getNodeWeight(const uint n) const { if(n < m_w.size()) return m_w[n]; return 0.0; }
	void setNodeWeight(const uint n, const ddouble w); // squared distance d(p,p_n) = m_met.normsq(p - p_n) + w_n

	// circum-center positions
	void setNodePosition(const uint n, const Vector4 &p);
	Vector4 getNodePosition(const uint n) const;
	Vector4 getEdgePosition(const uint e) const;
	Vector4 getFacePosition(const uint f) const;
	Vector4 getBodyPosition(const uint b) const;
	Vector4 getQuadPosition(const uint q) const;

	// average of linked node positions
	Vector4 getEdgeAverage(const uint e) const;
	Vector4 getFaceAverage(const uint f) const;
	Vector4 getBodyAverage(const uint b) const;
	Vector4 getQuadAverage(const uint q) const;

	// orthogonal vectors
	Vector4 getEdgeOrthogonal(const uint e, const Vector4 &d) const;
	Vector4 getFaceOrthogonal(const uint f, const Vector4 &d) const;
	Vector4 getBodyOrthogonal(const uint b, const Vector4 &d) const;

	// primal volume vectors
	Vector4 getEdgeVector(const uint e) const;
	Vector4 getEdgeVector(const uint e, ddouble c) const;
	TwoVector4 getFaceVector(const uint f) const;
	TwoVector4 getFaceVector(const uint f, ddouble c) const;
	Vector4 getBodyVector(const uint b) const;
	Vector4 getBodyVector(const uint b, ddouble c) const;
	ddouble getQuadVector(const uint q) const;
	ddouble getQuadVector(const uint q, ddouble c) const;

	// dual volume vectors
	ddouble getNodeDualVector(const uint n) const;
	ddouble getNodeDualVector(const uint n, ddouble c) const;
	Vector4 getEdgeDualVector(const uint e) const;
	Vector4 getEdgeDualVector(const uint e, ddouble c) const;
	TwoVector4 getFaceDualVector(const uint f) const;
	TwoVector4 getFaceDualVector(const uint f, ddouble c) const;
	Vector4 getBodyDualVector(const uint b) const;
	Vector4 getBodyDualVector(const uint b, ddouble c) const;

	// diagonal Hodge terms
	ddouble getNodeHodge(const uint n) const;
	ddouble getEdgeHodge(const uint e) const;
	ddouble getFaceHodge(const uint f) const;
	ddouble getBodyHodge(const uint b) const;
	ddouble getQuadHodge(const uint q) const;

	// incidence
	ddouble getEdgeIncidence(const uint e, const uint n) const;
	ddouble getFaceIncidence(const uint f, const uint e) const;
	ddouble getBodyIncidence(const uint b, const uint f) const;
	ddouble getQuadIncidence(const uint q, const uint b) const;

	uint findNodeAt(const Vector4 &p, const ddouble rsq, uint curr = 0) const;

	// tramsformation and relocation
	virtual void transform(const Matrix4 &mat);
	void move(const Vector4 &vec);

	void setMetric(Metric *met) { m_met = met; }
	const SymmMatrix4 &getMetric() const { return (m_met ? m_met->mat() : IDENTITYSYMMMATRIX4); }

protected:

	uint m_dim; // vector space dimension
	Buffer<ddouble> m_p; // vector coordinates for each node

	// mesh elements
	uint m_nsize;
	Buffer<Node> m_n; // nodes
	uint m_esize;
	Buffer<Edge> m_e; // edges
	uint m_fsize;
	Buffer<Face> m_f; // faces
	uint m_bsize;
	Buffer<Body> m_b; // bodies
	uint m_qsize;
	Buffer<Quad> m_q; // quads

	// flags
	Buffer<uint> m_nflag; // node flags (optional)
	Buffer<uint> m_eflag; // edge flags (optional)
	Buffer<uint> m_fflag; // face flags (optional)
	Buffer<uint> m_bflag; // body flags (optional)
	Buffer<uint> m_qflag; // volume flags (optional)

	// for dual computation
	Buffer<ddouble> m_w; // node weights (optional)

	Metric *m_met; // metric to determine dual transformation

	void orderFaceEdges(const uint f);
	void orderBodyFaces(const uint b);
	void resizeNodeBuffer(const uint size);
	void resizeEdgeBuffer(const uint size);
	void resizeFaceBuffer(const uint size);
	void resizeBodyBuffer(const uint size);
	void resizeQuadBuffer(const uint size);
	uint getCommon(const Buffer<uint> &a, const Buffer<uint> &b) const;
};

#endif //_MESH_HPP_INCLUDED_
