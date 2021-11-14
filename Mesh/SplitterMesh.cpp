#include "SplitterMesh.hpp"
#include "../Types/RBTree.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

SplitterMesh::SplitterMesh(const uint dim)
: Mesh(dim)
{
	m_divide = 1;
	m_min = Vector4(-1e30,-1e30,-1e30,-1e30);
	m_max = Vector4( 1e30, 1e30, 1e30, 1e30);
}

void SplitterMesh::clear()
{
	Mesh::clear();
	m_divide = 1;
	m_rank.clear();
	m_min = Vector4(-1e30,-1e30,-1e30,-1e30);
	m_max = Vector4( 1e30, 1e30, 1e30, 1e30);
}

bool SplitterMesh::repeatX(const ddouble p0, const ddouble p1)
{
	if(p0 >= p1) return false;
	const uint size = getNodeSize() + getEdgeSize() + getFaceSize() + getBodySize() + getQuadSize();
	if(m_rank.size() != size)
	{
		m_rank.resize(size);
		m_rank.fill(0);
	}

	uint i, j;
	m_min.x = p0;
	m_max.x = p1;
	for(i=0, j=0; i<getNodeSize(); i++, j++)
	{
		const ddouble p = getNodePosition(i).x;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getEdgeSize(); i++, j++)
	{
		const ddouble p = getEdgeAverage(i).x;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getFaceSize(); i++, j++)
	{
		const ddouble p = getFaceAverage(i).x;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getBodySize(); i++, j++)
	{
		const ddouble p = getBodyAverage(i).x;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getQuadSize(); i++, j++)
	{
		const ddouble p = getQuadAverage(i).x;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	return true;
}

bool SplitterMesh::repeatY(const ddouble p0, const ddouble p1)
{
	if(p0 >= p1) return false;
	const uint size = getNodeSize() + getEdgeSize() + getFaceSize() + getBodySize() + getQuadSize();
	if(m_rank.size() != size)
	{
		m_rank.resize(size);
		m_rank.fill(0);
	}

	uint i, j;
	m_min.y = p0;
	m_max.y = p1;
	for(i=0, j=0; i<getNodeSize(); i++, j++)
	{
		const ddouble p = getNodePosition(i).y;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getEdgeSize(); i++, j++)
	{
		const ddouble p = getEdgeAverage(i).y;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getFaceSize(); i++, j++)
	{
		const ddouble p = getFaceAverage(i).y;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getBodySize(); i++, j++)
	{
		const ddouble p = getBodyAverage(i).y;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getQuadSize(); i++, j++)
	{
		const ddouble p = getQuadAverage(i).y;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	return true;
}

bool SplitterMesh::repeatZ(const ddouble p0, const ddouble p1)
{
	if(p0 >= p1) return false;
	const uint size = getNodeSize() + getEdgeSize() + getFaceSize() + getBodySize() + getQuadSize();
	if(m_rank.size() != size)
	{
		m_rank.resize(size);
		m_rank.fill(0);
	}

	uint i, j;
	m_min.z = p0;
	m_max.z = p1;
	for(i=0, j=0; i<getNodeSize(); i++, j++)
	{
		const ddouble p = getNodePosition(i).z;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getEdgeSize(); i++, j++)
	{
		const ddouble p = getEdgeAverage(i).z;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getFaceSize(); i++, j++)
	{
		const ddouble p = getFaceAverage(i).z;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getBodySize(); i++, j++)
	{
		const ddouble p = getBodyAverage(i).z;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getQuadSize(); i++, j++)
	{
		const ddouble p = getQuadAverage(i).z;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	return true;
}

bool SplitterMesh::repeatT(const ddouble p0, const ddouble p1)
{
	if(p0 >= p1) return false;
	const uint size = getNodeSize() + getEdgeSize() + getFaceSize() + getBodySize() + getQuadSize();
	if(m_rank.size() != size)
	{
		m_rank.resize(size);
		m_rank.fill(0);
	}

	uint i, j;
	m_min.t = p0;
	m_max.t = p1;
	for(i=0, j=0; i<getNodeSize(); i++, j++)
	{
		const ddouble p = getNodePosition(i).t;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getEdgeSize(); i++, j++)
	{
		const ddouble p = getEdgeAverage(i).t;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getFaceSize(); i++, j++)
	{
		const ddouble p = getFaceAverage(i).t;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getBodySize(); i++, j++)
	{
		const ddouble p = getBodyAverage(i).t;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	for(i=0; i<getQuadSize(); i++, j++)
	{
		const ddouble p = getQuadAverage(i).t;
		if(p < p0 || p1 <= p) m_rank[j] = m_divide;
	}
	return true;
}

bool SplitterMesh::divide(const uint divide, ddouble (*func)(const Vector4 &))
{
	if(divide == 0) return false;
	const uint size = getNodeSize() + getEdgeSize() + getFaceSize() + getBodySize() + getQuadSize();
	if(m_rank.size() != size)
	{
		m_rank.resize(size);
		m_rank.fill(0);
	}

	// Compute ordered index table
	uint i, j;
	RBTree tree;
	for(i=0, j=0; i<getNodeSize(); i++, j++)
	{
		if(m_rank[j] == m_divide) m_rank[j] *= divide;
		else tree.add(j, func(getNodePosition(i)));
	}
	for(i=0; i<getEdgeSize(); i++, j++)
	{
		if(m_rank[j] == m_divide) m_rank[j] *= divide;
		else tree.add(j, func(getEdgeAverage(i)));
	}
	for(i=0; i<getFaceSize(); i++, j++)
	{
		if(m_rank[j] == m_divide) m_rank[j] *= divide;
		else tree.add(j, func(getFaceAverage(i)));
	}
	for(i=0; i<getBodySize(); i++, j++)
	{
		if(m_rank[j] == m_divide) m_rank[j] *= divide;
		else tree.add(j, func(getBodyAverage(i)));
	}
	for(i=0; i<getQuadSize(); i++, j++)
	{
		if(m_rank[j] == m_divide) m_rank[j] *= divide;
		else tree.add(j, func(getQuadAverage(i)));
	}
	Buffer<uint> index;
	tree.getBuffer(index);
	tree.clear();

	// Create area table for ordered list
	Buffer<uint> isize(m_divide, 0);
	for(i=0; i<index.size(); i++)
	{
		const uint ii = index[i];
		isize[m_rank[ii]]++;
	}

	// Update ranks
	Buffer<uint> icount(m_divide, 0);
	Buffer<uint> iarea(m_divide, 0);
	for(i=0; i<index.size(); i++)
	{
		// Update area
		const uint ii = index[i];
		const uint r = m_rank[ii];
		if((icount[r] * divide) >= ((iarea[r] + 1) * isize[r])) iarea[r]++;

		// Update rank
		if(iarea[r] > 0) m_rank[ii] += iarea[r] * m_divide;
		icount[r]++;
	}
	m_divide *= divide;
	return true;
}

bool SplitterMesh::divideByFlag(const uint divide)
{
	if(divide == 0) return false;
	const uint size = getNodeSize() + getEdgeSize() + getFaceSize() + getBodySize() + getQuadSize();
	if(m_rank.size() != size)
	{
		m_rank.resize(size);
		m_rank.fill(0);
	}

	uint i, j;
	for(i=0, j=0; i<getNodeSize(); i++,j++)
	{
		if(m_rank[j] == m_divide) m_rank[j] *= divide;
		else
		{
			const uint flag = getNodeFlag(i);
			setNodeFlag(i, flag / divide);
			m_rank[j] += (flag % divide) * m_divide;
		}
	}
	for(i=0; i<getEdgeSize(); i++,j++)
	{
		if(m_rank[j] == m_divide) m_rank[j] *= divide;
		else
		{
			const uint flag = getEdgeFlag(i);
			setEdgeFlag(i, flag / divide);
			m_rank[j] += (flag % divide) * m_divide;
		}
	}
	for(i=0; i<getFaceSize(); i++,j++)
	{
		if(m_rank[j] == m_divide) m_rank[j] *= divide;
		else
		{
			const uint flag = getFaceFlag(i);
			setFaceFlag(i, flag / divide);
			m_rank[j] += (flag % divide) * m_divide;
		}
	}
	for(i=0; i<getBodySize(); i++,j++)
	{
		if(m_rank[j] == m_divide) m_rank[j] *= divide;
		else
		{
			const uint flag = getBodyFlag(i);
			setBodyFlag(i, flag / divide);
			m_rank[j] += (flag % divide) * m_divide;
		}
	}
	for(i=0; i<getQuadSize(); i++,j++)
	{
		if(m_rank[j] == m_divide) m_rank[j] *= divide;
		else
		{
			const uint flag = getQuadFlag(i);
			setQuadFlag(i, flag / divide);
			m_rank[j] += (flag % divide) * m_divide;
		}
	}
	m_divide *= divide;
	return true;
}

bool SplitterMesh::saveSplit(const std::string &path)
{
	if(m_rank.size() != getNodeSize() + getEdgeSize() + getFaceSize() + getBodySize() + getQuadSize()) return false;
	uint i, j, k;

	// compute link for each term
	Buffer<uint> nlocs(m_divide+1, 0);
	Buffer<uint> elocs(m_divide+1, 0);
	Buffer<uint> flocs(m_divide+1, 0);
	Buffer<uint> blocs(m_divide+1, 0);
	Buffer<uint> qlocs(m_divide+1, 0);

	Buffer<uint> nlink(getNodeSize());
	Buffer<uint> elink(getEdgeSize());
	Buffer<uint> flink(getFaceSize());
	Buffer<uint> blink(getBodySize());
	Buffer<uint> qlink(getQuadSize());

	for(i=0, j=0; i<getNodeSize(); i++) nlink[i] = nlocs[m_rank[j++]]++;
	for(i=0; i<getEdgeSize(); i++) elink[i] = elocs[m_rank[j++]]++;
	for(i=0; i<getFaceSize(); i++) flink[i] = flocs[m_rank[j++]]++;
	for(i=0; i<getBodySize(); i++) blink[i] = blocs[m_rank[j++]]++;
	for(i=0; i<getQuadSize(); i++) qlink[i] = qlocs[m_rank[j++]]++;

	// save JRM mesh for each rank
	Buffer<uint> nind(getNodeSize());
	Buffer<uint> eind(getEdgeSize());
	Buffer<uint> find(getFaceSize());
	Buffer<uint> bind(getBodySize());
	Buffer<uint> qind(getQuadSize());

	Buffer<uint> nchk(getNodeSize());
	Buffer<uint> echk(getEdgeSize());
	Buffer<uint> fchk(getFaceSize());
	Buffer<uint> bchk(getBodySize());
	Buffer<uint> qchk(getQuadSize());

	for(k=0; k<m_divide; k++)
	{
		uint nsize = 0;
		uint esize = 0;
		uint fsize = 0;
		uint bsize = 0;
		uint qsize = 0;

		nchk.fill(NONE);
		echk.fill(NONE);
		fchk.fill(NONE);
		bchk.fill(NONE);
		qchk.fill(NONE);

		for(i=0, j=0; i<getNodeSize(); i++,j++)
		{
			if(m_rank[j] != k) continue;
			nind[nsize] = i;
			nchk[i] = nsize++;
		}
		for(i=0; i<getEdgeSize(); i++,j++)
		{
			if(m_rank[j] != k) continue;
			eind[esize] = i;
			echk[i] = esize++;
		}
		for(i=0; i<getFaceSize(); i++,j++)
		{
			if(m_rank[j] != k) continue;
			find[fsize] = i;
			fchk[i] = fsize++;
		}
		for(i=0; i<getBodySize(); i++,j++)
		{
			if(m_rank[j] != k) continue;
			bind[bsize] = i;
			bchk[i] = bsize++;
		}
		for(i=0; i<getQuadSize(); i++,j++)
		{
			if(m_rank[j] != k) continue;
			qind[qsize] = i;
			qchk[i] = qsize++;
		}

		// Include necessary elements at the interface
		for(i=0; i<qsize; i++)
		{
			const uint ii = qind[i];
			if(qchk[ii] == NONE) continue;
			const Buffer<uint> &ele = getQuadBodies(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(bchk[ele[j]] != NONE) continue;
				bind[bsize] = ele[j];
				bchk[ele[j]] = bsize++;
			}
		}
		for(i=0; i<bsize; i++)
		{
			const uint ii = bind[i];
			if(bchk[ii] == NONE) continue;
			const Buffer<uint> &ele = getBodyFaces(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(fchk[ele[j]] != NONE) continue;
				find[fsize] = ele[j];
				fchk[ele[j]] = fsize++;
			}
		}
		for(i=0; i<fsize; i++)
		{
			const uint ii = find[i];
			if(fchk[ii] == NONE) continue;
			const Buffer<uint> &ele = getFaceEdges(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(echk[ele[j]] != NONE) continue;
				eind[esize] = ele[j];
				echk[ele[j]] = esize++;
			}
		}
		for(i=0; i<esize; i++)
		{
			const uint ii = eind[i];
			if(echk[ii] == NONE) continue;
			const Buffer<uint> &ele = getEdgeNodes(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(nchk[ele[j]] != NONE) continue;
				nind[nsize] = ele[j];
				nchk[ele[j]] = nsize++;
			}
		}
		for(i=0; i<nsize; i++)
		{
			const uint ii = nind[i];
			if(nchk[ii] == NONE) continue;
			const Buffer<uint> &ele = getNodeEdges(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(echk[ele[j]] != NONE) continue;
				eind[esize] = ele[j];
				echk[ele[j]] = esize++;
			}
		}
		for(i=0; i<esize; i++)
		{
			const uint ii = eind[i];
			if(echk[ii] == NONE) continue;
			const Buffer<uint> &ele = getEdgeFaces(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(fchk[ele[j]] != NONE) continue;
				find[fsize] = ele[j];
				fchk[ele[j]] = fsize++;
			}
		}
		for(i=0; i<fsize; i++)
		{
			const uint ii = find[i];
			if(fchk[ii] == NONE) continue;
			const Buffer<uint> &ele = getFaceBodies(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(bchk[ele[j]] != NONE) continue;
				bind[bsize] = ele[j];
				bchk[ele[j]] = bsize++;
			}
		}
		for(i=0; i<bsize; i++)
		{
			const uint ii = bind[i];
			if(bchk[ii] == NONE) continue;
			const Buffer<uint> &ele = getBodyQuads(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(qchk[ele[j]] != NONE) continue;
				qind[qsize] = ele[j];
				qchk[ele[j]] = qsize++;
			}
		}
		for(i=0; i<qsize; i++)
		{
			const uint ii = qind[i];
			if(qchk[ii] == NONE) continue;
			const Buffer<uint> &ele = getQuadBodies(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(bchk[ele[j]] != NONE) continue;
				bind[bsize] = ele[j];
				bchk[ele[j]] = bsize++;
			}
		}
		for(i=0; i<bsize; i++)
		{
			const uint ii = bind[i];
			if(bchk[ii] == NONE) continue;
			const Buffer<uint> &ele = getBodyFaces(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(fchk[ele[j]] != NONE) continue;
				find[fsize] = ele[j];
				fchk[ele[j]] = fsize++;
			}
		}
		for(i=0; i<fsize; i++)
		{
			const uint ii = find[i];
			if(fchk[ii] == NONE) continue;
			const Buffer<uint> &ele = getFaceEdges(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(echk[ele[j]] != NONE) continue;
				eind[esize] = ele[j];
				echk[ele[j]] = esize++;
			}
		}
		for(i=0; i<esize; i++)
		{
			const uint ii = eind[i];
			if(echk[ii] == NONE) continue;
			const Buffer<uint> &ele = getEdgeNodes(ii);
			for(j=0; j<ele.size(); j++)
			{
				if(nchk[ele[j]] != NONE) continue;
				nind[nsize] = ele[j];
				nchk[ele[j]] = nsize++;
			}
		}

		// write file
		std::ostringstream s;
		s << path << "." << k;

		std::ofstream fs(s.str().c_str(), std::ios_base::binary | std::ios::trunc);
		if(fs.fail()) return false;

		uint size;

		// header
		const char *id = "JRMP";
		fs.write(id, 4);
		fs.write((char*)&m_divide, sizeof(uint));

		// dimension
		fs.write((char*)&m_dim, sizeof(uint));

		// nodes
		fs.write((char*)&nsize, sizeof(uint));
		for(i=0; i<nsize; i++)
		{
			const uint ii = nind[i];
			const Vector4 p = getNodePosition(ii);
			const double x = double(p.x);
			const double y = double(p.y);
			const double z = double(p.z);
			const double t = double(p.t);
			fs.write((char*)&x, sizeof(double));
			if(m_dim > 1) fs.write((char*)&y, sizeof(double));
			if(m_dim > 2) fs.write((char*)&z, sizeof(double));
			if(m_dim > 3) fs.write((char*)&t, sizeof(double));
		}

		// edges
		fs.write((char*)&esize, sizeof(uint));
		for(i=0; i<esize; i++)
		{
			const uint ii = eind[i];
			const Buffer<uint> &n = getEdgeNodes(ii);
			fs.write((char*)&nchk[n[0]], sizeof(uint));
			fs.write((char*)&nchk[n[1]], sizeof(uint));
		}

		// faces
		fs.write((char*)&fsize, sizeof(uint));
		for(i=0; i<fsize; i++)
		{
			const uint ii = find[i];
			const Buffer<uint> &e = getFaceEdges(ii);
			size = e.size();
			fs.write((char*)&size, sizeof(uint));
			for(j=0; j<size; j++) fs.write((char*)&echk[e[j]], sizeof(uint));
		}

		// bodies
		fs.write((char*)&bsize, sizeof(uint));
		for(i=0; i<bsize; i++)
		{
			const uint ii = bind[i];
			const Buffer<uint> &f = getBodyFaces(ii);
			size = f.size();
			fs.write((char*)&size, sizeof(uint));
			for(j=0; j<size; j++) fs.write((char*)&fchk[f[j]], sizeof(uint));
		}

		// quads
		fs.write((char*)&qsize, sizeof(uint));
		for(i=0; i<qsize; i++)
		{
			const uint ii = qind[i];
			const Buffer<uint> &b = getQuadBodies(ii);
			size = b.size();
			fs.write((char*)&size, sizeof(uint));
			for(j=0; j<size; j++) fs.write((char*)&bchk[b[j]], sizeof(uint));
		}

		// flags
		size = nsize;
		while(size > 0 && getNodeFlag(nind[size - 1]) == 0) size--;
		fs.write((char*)&size, sizeof(uint));
		for(i=0; i<size; i++)
		{
			fs.write((char*)&m_nflag[nind[i]], sizeof(uint));
		}
		size = esize;
		while(size > 0 && getEdgeFlag(eind[size - 1]) == 0) size--;
		fs.write((char*)&size, sizeof(uint));
		for(i=0; i<size; i++)
		{
			fs.write((char*)&m_eflag[eind[i]], sizeof(uint));
		}
		size = fsize;
		while(size > 0 && getFaceFlag(find[size - 1]) == 0) size--;
		fs.write((char*)&size, sizeof(uint));
		for(i=0; i<size; i++)
		{
			fs.write((char*)&m_fflag[find[i]], sizeof(uint));
		}
		size = bsize;
		while(size > 0 && getBodyFlag(bind[size - 1]) == 0) size--;
		fs.write((char*)&size, sizeof(uint));
		for(i=0; i<size; i++)
		{
			fs.write((char*)&m_bflag[bind[i]], sizeof(uint));
		}
		size = qsize;
		while(size > 0 && getQuadFlag(qind[size - 1]) == 0) size--;
		fs.write((char*)&size, sizeof(uint));
		for(i=0; i<size; i++)
		{
			fs.write((char*)&m_qflag[qind[i]], sizeof(uint));
		}

		// weights
		size = nsize;
		while(size > 0 && getNodeWeight(nind[size - 1]) == 0.0) size--;
		fs.write((char*)&size, sizeof(uint));
		for(i=0; i<size; i++)
		{
			const double w = m_w[nind[i]];
			fs.write((char*)&w, sizeof(double));
		}

		// ranks and links
		uint beg = 0;
		fs.write((char*)&nlocs[k], sizeof(uint));
		for(i=nlocs[k]; i<nsize; i++)
		{
			const uint ii = nind[i];
			if(m_rank[ii + beg] == m_divide)
			{
				Vector4 p = getNodePosition(ii);
				if(p.x >= m_max.x) p.x += m_min.x - m_max.x;
				else if(p.x < m_min.x) p.x += m_max.x - m_min.x;
				if(p.y >= m_max.y) p.y += m_min.y - m_max.y;
				else if(p.y < m_min.y) p.y += m_max.y - m_min.y;
				if(p.z >= m_max.z) p.z += m_min.z - m_max.z;
				else if(p.z < m_min.z) p.z += m_max.z - m_min.z;
				if(p.t >= m_max.t) p.t += m_min.t - m_max.t;
				else if(p.t < m_min.t) p.t += m_max.t - m_min.t;
				uint mrankj;
				for(j=0; j<getNodeSize(); j++)
				{
					uint mrankj = m_rank[j + beg];
					if(mrankj == m_divide || mrankj == k) continue;
					if((p - getNodePosition(j)).lensq() < 1e-8) break;
				}
				if(j >= getNodeSize()) return false;
				fs.write((char*)&mrankj, sizeof(uint));
				fs.write((char*)&nlink[j], sizeof(uint));
				continue;
			}
			fs.write((char*)&m_rank[ii + beg], sizeof(uint));
			fs.write((char*)&nlink[ii], sizeof(uint));
		}
		beg += getNodeSize();
		fs.write((char*)&elocs[k], sizeof(uint));
		for(i=elocs[k]; i<esize; i++)
		{
			const uint ii = eind[i];
			if(m_rank[ii + beg] == m_divide)
			{
				Vector4 p = getEdgeAverage(ii);
				if(p.x >= m_max.x) p.x += m_min.x - m_max.x;
				else if(p.x < m_min.x) p.x += m_max.x - m_min.x;
				if(p.y >= m_max.y) p.y += m_min.y - m_max.y;
				else if(p.y < m_min.y) p.y += m_max.y - m_min.y;
				if(p.z >= m_max.z) p.z += m_min.z - m_max.z;
				else if(p.z < m_min.z) p.z += m_max.z - m_min.z;
				if(p.t >= m_max.t) p.t += m_min.t - m_max.t;
				else if(p.t < m_min.t) p.t += m_max.t - m_min.t;
				uint mrankj;
				for(j=0; j<getEdgeSize(); j++)
				{
					uint mrankj = m_rank[j + beg];
					if(mrankj == m_divide || mrankj == k) continue;
					if((p - getEdgeAverage(j)).lensq() < 1e-8) break;
				}
				if(j >= getEdgeSize()) return false;
				fs.write((char*)&mrankj, sizeof(uint));
				fs.write((char*)&elink[j], sizeof(uint));
				continue;
			}
			fs.write((char*)&m_rank[ii + beg], sizeof(uint));
			fs.write((char*)&elink[ii], sizeof(uint));
		}
		beg += getEdgeSize();
		fs.write((char*)&flocs[k], sizeof(uint));
		for(i=flocs[k]; i<fsize; i++)
		{
			const uint ii = find[i];
			if(m_rank[ii + beg] == m_divide)
			{
				Vector4 p = getFaceAverage(ii);
				if(p.x >= m_max.x) p.x += m_min.x - m_max.x;
				else if(p.x < m_min.x) p.x += m_max.x - m_min.x;
				if(p.y >= m_max.y) p.y += m_min.y - m_max.y;
				else if(p.y < m_min.y) p.y += m_max.y - m_min.y;
				if(p.z >= m_max.z) p.z += m_min.z - m_max.z;
				else if(p.z < m_min.z) p.z += m_max.z - m_min.z;
				if(p.t >= m_max.t) p.t += m_min.t - m_max.t;
				else if(p.t < m_min.t) p.t += m_max.t - m_min.t;
				uint mrankj;
				for(j=0; j<getFaceSize(); j++)
				{
					uint mrankj = m_rank[j + beg];
					if(mrankj == m_divide || mrankj == k) continue;
					if((p - getFaceAverage(j)).lensq() < 1e-8) break;
				}
				if(j >= getFaceSize()) return false;
				fs.write((char*)&mrankj, sizeof(uint));
				fs.write((char*)&flink[j], sizeof(uint));
				continue;
			}
			fs.write((char*)&m_rank[ii + beg], sizeof(uint));
			fs.write((char*)&flink[ii], sizeof(uint));
		}
		beg += getFaceSize();
		fs.write((char*)&blocs[k], sizeof(uint));
		for(i=blocs[k]; i<bsize; i++)
		{
			const uint ii = bind[i];
			if(m_rank[ii + beg] == m_divide)
			{
				Vector4 p = getBodyAverage(ii);
				if(p.x >= m_max.x) p.x += m_min.x - m_max.x;
				else if(p.x < m_min.x) p.x += m_max.x - m_min.x;
				if(p.y >= m_max.y) p.y += m_min.y - m_max.y;
				else if(p.y < m_min.y) p.y += m_max.y - m_min.y;
				if(p.z >= m_max.z) p.z += m_min.z - m_max.z;
				else if(p.z < m_min.z) p.z += m_max.z - m_min.z;
				if(p.t >= m_max.t) p.t += m_min.t - m_max.t;
				else if(p.t < m_min.t) p.t += m_max.t - m_min.t;
				uint mrankj;
				for(j=0; j<getBodySize(); j++)
				{
					uint mrankj = m_rank[j + beg];
					if(mrankj == m_divide || mrankj == k) continue;
					if((p - getBodyAverage(j)).lensq() < 1e-8) break;
				}
				if(j >= getBodySize()) return false;
				fs.write((char*)&mrankj, sizeof(uint));
				fs.write((char*)&blink[j], sizeof(uint));
				continue;
			}
			fs.write((char*)&m_rank[ii + beg], sizeof(uint));
			fs.write((char*)&blink[ii], sizeof(uint));
		}
		beg += getBodySize();
		fs.write((char*)&qlocs[k], sizeof(uint));
		for(i=qlocs[k]; i<qsize; i++)
		{
			const uint ii = qind[i];
			if(m_rank[ii + beg] == m_divide)
			{
				Vector4 p = getQuadAverage(ii);
				if(p.x >= m_max.x) p.x += m_min.x - m_max.x;
				else if(p.x < m_min.x) p.x += m_max.x - m_min.x;
				if(p.y >= m_max.y) p.y += m_min.y - m_max.y;
				else if(p.y < m_min.y) p.y += m_max.y - m_min.y;
				if(p.z >= m_max.z) p.z += m_min.z - m_max.z;
				else if(p.z < m_min.z) p.z += m_max.z - m_min.z;
				if(p.t >= m_max.t) p.t += m_min.t - m_max.t;
				else if(p.t < m_min.t) p.t += m_max.t - m_min.t;
				uint mrankj;
				for(j=0; j<getQuadSize(); j++)
				{
					uint mrankj = m_rank[j + beg];
					if(mrankj == m_divide || mrankj == k) continue;
					if((p - getQuadAverage(j)).lensq() < 1e-8) break;
				}
				if(j >= getQuadSize()) return false;
				fs.write((char*)&mrankj, sizeof(uint));
				fs.write((char*)&qlink[j], sizeof(uint));
				continue;
			}
			fs.write((char*)&m_rank[ii + beg], sizeof(uint));
			fs.write((char*)&qlink[ii], sizeof(uint));
		}

		fs.close();
	}
	return true;
}


