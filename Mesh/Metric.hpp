#ifndef _METRIC_HPP_INCLUDED_
#define _METRIC_HPP_INCLUDED_

#include "../Types/Buffer.hpp"
#include "../Types/UintGroup.hpp"
#include "../Types/Vector4.hpp"

/*
Metric determines dual inner product by symmetric matrix
*/

class Metric
{
public:
	Metric() { clear(); }
	virtual ~Metric() {}
	void clear() { m_mat = IDENTITYSYMMMATRIX4; }

	void setMatrix(const SymmMatrix4 &mat) { m_mat = mat; }
	virtual const SymmMatrix4 &mat() const { return m_mat; }

protected:
	SymmMatrix4 m_mat;
};

class FlagMetric : public Metric
{
public:
	FlagMetric();
	virtual ~FlagMetric() { clear(); }
	void clear();

	// metric matrices
	void addMetric(const SymmMatrix4 &mat, const UintGroup &flag = UINTGROUPALL);
	const SymmMatrix4 &getMetric(const uint flag) const;

protected:

	struct FlagMatrix
	{
		UintGroup flag;
		SymmMatrix4 mat;
	};

	Buffer<FlagMatrix> m_fmat; // flag-dependent matrix
};

#endif //_METRIC_HPP_INCLUDED_
