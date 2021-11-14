#include "Metric.hpp"

FlagMetric::FlagMetric()
 : Metric()
{

}

void FlagMetric::clear()
{
	Metric::clear();
	m_fmat.clear();
}

void FlagMetric::addMetric(const SymmMatrix4 &mat, const UintGroup &flag)
{
	uint i;
	Buffer<FlagMatrix> fmat;
	fmat.resize(m_fmat.size() + 1);
	for(i=0; i<m_fmat.size(); i++)
	{
		fmat[i].mat = m_fmat[i].mat;
		fmat[i].flag = m_fmat[i].flag;
	}
	fmat[i].mat = mat;
	fmat[i].flag = flag;
	m_fmat.swap(fmat);
}

const SymmMatrix4 &FlagMetric::getMetric(const uint flag) const
{
	for(uint i=m_fmat.size(); i-->0; )
	{
		if(m_fmat[i].flag.includes(flag))
		{
			return m_fmat[i].mat;
		}
	}
	return IDENTITYSYMMMATRIX4;
}
