#ifndef _UINTGROUP_HPP_INCLUDED_
#define _UINTGROUP_HPP_INCLUDED_

#include "Buffer.hpp"

class UintGroup
{
public:
	UintGroup() {}
	UintGroup(const uint i)
	{
		m_sec.push_back(UintSection(i, i, 0));
	}
	UintGroup(const uint i0, const uint i1, const uint ip = 0)
	{
		m_sec.push_back(UintSection(i0, i1, ip));
	}
	UintGroup(const UintGroup &ug)
	{
		m_sec = ug.m_sec;
	}
	UintGroup &operator = (const UintGroup &ug)
	{
		m_sec = ug.m_sec;
		return *this;
	}
	void combine(const UintGroup &ug)
	{
		m_sec.combine(ug.m_sec);
	}
	bool includes(const uint i) const
	{
		for(uint j=0; j<m_sec.size(); j++)
		{
			const UintSection &sec = m_sec[j];
			const uint ij = (sec.ip == 0 ? i : (i % m_sec[j].ip));
			if(sec.i0 <= ij && ij <= sec.i1) return true;
		}
		return false;
	}

protected:
	struct UintSection
	{
		uint i0;
		uint i1;
		uint ip;
		UintSection(const uint ai0 = 0, const uint ai1 = 0, const uint aip = 0)
		{
			i0 = ai0;
			i1 = ai1;
			ip = aip;
		}
	};

	Buffer<UintSection> m_sec;
};

const UintGroup UINTGROUPALL(0, uint(-1), 0);

#endif //_UINTGROUP_HPP_INCLUDED_
