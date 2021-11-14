#ifndef _SPLITTERMESH_HPP_INCLUDED_
#define _SPLITTERMESH_HPP_INCLUDED_

#include "Mesh.hpp"

class SplitterMesh : public Mesh
{
public:
	SplitterMesh(const uint dim = 4);
	virtual ~SplitterMesh() { clear(); }
	void clear();

	bool repeatX(const ddouble p0, const ddouble p1);
	bool repeatY(const ddouble p0, const ddouble p1);
	bool repeatZ(const ddouble p0, const ddouble p1);
	bool repeatT(const ddouble p0, const ddouble p1);
	bool divide(const uint divide, ddouble (*func)(const Vector4 &));
	bool divideByFlag(const uint divide);
	bool saveSplit(const std::string &path);

protected:
	uint m_divide;
	Buffer<uint> m_rank;
	Vector4 m_min;
	Vector4 m_max;
};

#endif //_SPLITTERMESH_HPP_INCLUDED_
