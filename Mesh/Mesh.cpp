#include "Mesh.hpp"
#include "../Output/Text.hpp"
#include <iostream>

Mesh::Mesh(const uint dim)
{
	if(dim < 1) m_dim = 1;
	else if(dim > 4) m_dim = 4;
	else m_dim = dim;

	m_nsize = 0;
	m_esize = 0;
	m_fsize = 0;
	m_bsize = 0;
	m_qsize = 0;
	m_met = NULL;
}

void Mesh::clear()
{
	resizeNodeBuffer(0);
	m_nsize = 0;
	resizeEdgeBuffer(0);
	m_esize = 0;
	resizeFaceBuffer(0);
	m_fsize = 0;
	resizeBodyBuffer(0);
	m_bsize = 0;
	resizeQuadBuffer(0);
	m_qsize = 0;

	// flags
	m_nflag.clear(); // node flags (optional)
	m_eflag.clear(); // edge flags (optional)
	m_fflag.clear(); // face flags (optional)
	m_bflag.clear(); // body flags (optional)
	m_qflag.clear(); // body flags (optional)

	m_w.clear(); // node weights (optional)
	m_met = NULL;
}

void Mesh::swap(Mesh &mesh)
{
	const uint mdim = m_dim;
	m_dim = mesh.m_dim;
	mesh.m_dim = mdim;

	m_p.swap(mesh.m_p);

	const uint mnsize = m_nsize;
	m_nsize = mesh.m_nsize;
	mesh.m_nsize = mnsize;
	m_n.swap(mesh.m_n);

	const uint mesize = m_esize;
	m_esize = mesh.m_esize;
	mesh.m_esize = mesize;
	m_e.swap(mesh.m_e);

	const uint mfsize = m_fsize;
	m_fsize = mesh.m_fsize;
	mesh.m_fsize = mfsize;
	m_f.swap(mesh.m_f);

	const uint mbsize = m_bsize;
	m_bsize = mesh.m_bsize;
	mesh.m_bsize = mbsize;
	m_b.swap(mesh.m_b);

	const uint mqsize = m_qsize;
	m_qsize = mesh.m_qsize;
	mesh.m_qsize = mqsize;
	m_q.swap(mesh.m_q);

	m_nflag.swap(mesh.m_nflag);
	m_eflag.swap(mesh.m_eflag);
	m_fflag.swap(mesh.m_fflag);
	m_bflag.swap(mesh.m_bflag);
	m_qflag.swap(mesh.m_qflag);

	m_w.swap(mesh.m_w);

	Metric *mmet = m_met;
	m_met = mesh.m_met;
	mesh.m_met = mmet;
}

bool Mesh::loadJRMesh(const std::string &path)
{
	std::ifstream fs(path.c_str(), std::ios::binary | std::ios::in);
	if(fs.fail()) return false;

	// header
	char id[4];
	fs.read(id, 4);
	if(strncmp(id, "JRM1", 4) != 0)
	{
		fs.close();
		return false;
	}

	clear();
	uint i, size, index, flag;

	// dimension
	fs.read((char*)&m_dim, sizeof(uint));

	// nodes
	fs.read((char*)&m_nsize, sizeof(uint));
	resizeNodeBuffer(m_nsize);
	for(i=0; i<m_nsize; i++)
	{
		double x,y,z,t;
		fs.read((char*)&x, sizeof(double));
		if(m_dim > 1) fs.read((char*)&y, sizeof(double));
		if(m_dim > 2) fs.read((char*)&z, sizeof(double));
		if(m_dim > 3) fs.read((char*)&t, sizeof(double));
		setNodePosition(i, Vector4(ddouble(x), ddouble(y), ddouble(z), ddouble(t)));
	}

	// edges
	fs.read((char*)&m_esize, sizeof(uint));
	resizeEdgeBuffer(m_esize);
	for(i=0; i<m_esize; i++)
	{
		fs.read((char*)&index, sizeof(uint));
		const uint n0 = index;
		fs.read((char*)&index, sizeof(uint));
		const uint n1 = index;
		m_e[i].n.resize(2);
		m_e[i].n[0] = n0;
		m_n[n0].e.push_back(i);
		m_e[i].n[1] = n1;
		m_n[n1].e.push_back(i);
	}

	// faces
	fs.read((char*)&m_fsize, sizeof(uint));
	resizeFaceBuffer(m_fsize);
	for(i=0; i<m_fsize; i++)
	{
		fs.read((char*)&size, sizeof(uint));
		m_f[i].e.resize(uint(size));
		for(uint j=0; j<m_f[i].e.size(); j++)
		{
			fs.read((char*)&index, sizeof(uint));
			m_f[i].e[j] = index;
			m_e[index].f.push_back(i);
		}
		orderFaceEdges(i);
	}

	// bodies
	fs.read((char*)&m_bsize, sizeof(uint));
	resizeBodyBuffer(m_bsize);
	for(i=0; i<m_bsize; i++)
	{
		fs.read((char*)&size, sizeof(uint));
		m_b[i].f.resize(uint(size));
		for(uint j=0; j<m_b[i].f.size(); j++)
		{
			fs.read((char*)&index, sizeof(uint));
			m_b[i].f[j] = index;
			m_f[index].b.push_back(i);
		}
		orderBodyFaces(i);
	}

	// quads
	fs.read((char*)&m_qsize, sizeof(uint));
	resizeQuadBuffer(m_qsize);
	for(i=0; i<m_qsize; i++)
	{
		fs.read((char*)&size, sizeof(uint));
		m_q[i].b.resize(uint(size));
		for(uint j=0; j<m_q[i].b.size(); j++)
		{
			fs.read((char*)&index, sizeof(uint));
			m_q[i].b[j] = index;
			m_b[index].q.push_back(i);
		}
	}

	// flags
	fs.read((char*)&size, sizeof(uint));
	m_nflag.resize(size);
	for(i=0; i<size; i++)
	{
		fs.read((char*)&flag, sizeof(uint));
		m_nflag[i] = flag;
	}
	fs.read((char*)&size, sizeof(uint));
	m_eflag.resize(size);
	for(i=0; i<size; i++)
	{
		fs.read((char*)&flag, sizeof(uint));
		m_eflag[i] = flag;
	}
	fs.read((char*)&size, sizeof(uint));
	m_fflag.resize(size);
	for(i=0; i<size; i++)
	{
		fs.read((char*)&flag, sizeof(uint));
		m_fflag[i] = flag;
	}
	fs.read((char*)&size, sizeof(uint));
	m_bflag.resize(size);
	for(i=0; i<size; i++)
	{
		fs.read((char*)&flag, sizeof(uint));
		m_bflag[i] = flag;
	}
	fs.read((char*)&size, sizeof(uint));
	m_qflag.resize(size);
	for(i=0; i<size; i++)
	{
		fs.read((char*)&flag, sizeof(uint));
		m_qflag[i] = flag;
	}

	// weights
	fs.read((char*)&size, sizeof(uint));
	m_w.resize(size);
	for(i=0; i<size; i++)
	{
		double w;
		fs.read((char*)&w, sizeof(double));
		m_w[i] = w;
	}
	fs.close();
	return true;
}

bool Mesh::saveJRMesh(const std::string &path) const
{
	std::ofstream fs(path.c_str(), std::ios_base::binary | std::ios::trunc);
	if(fs.fail()) return false;

	// header
	const char *id = "JRM1";
	fs.write(id, 4);

	uint i, j, size;

	// dimension
	fs.write((char*)&m_dim, sizeof(uint));

	// nodes
	fs.write((char*)&m_nsize, sizeof(uint));
	for(i=0; i<m_nsize; i++)
	{
		const Vector4 p = getNodePosition(i);
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
	fs.write((char*)&m_esize, sizeof(uint));
	for(i=0; i<m_esize; i++)
	{
		const Buffer<uint> &n = getEdgeNodes(i);
		fs.write((char*)&n[0], sizeof(uint));
		fs.write((char*)&n[1], sizeof(uint));
	}

	// faces
	fs.write((char*)&m_fsize, sizeof(uint));
	for(i=0; i<m_fsize; i++)
	{
		const Buffer<uint> &e = getFaceEdges(i);
		size = e.size();
		fs.write((char*)&size, sizeof(uint));
		for(j=0; j<size; j++) fs.write((char*)&e[j], sizeof(uint));
	}

	// bodies
	fs.write((char*)&m_bsize, sizeof(uint));
	for(i=0; i<m_bsize; i++)
	{
		const Buffer<uint> &f = getBodyFaces(i);
		size = f.size();
		fs.write((char*)&size, sizeof(uint));
		for(j=0; j<size; j++) fs.write((char*)&f[j], sizeof(uint));
	}

	// quads
	fs.write((char*)&m_qsize, sizeof(uint));
	for(i=0; i<m_qsize; i++)
	{
		const Buffer<uint> &b = getQuadBodies(i);
		size = b.size();
		fs.write((char*)&size, sizeof(uint));
		for(j=0; j<size; j++) fs.write((char*)&b[j], sizeof(uint));
	}

	// flags
	size = m_nflag.size();
	while(size > 0 && m_nflag[size - 1] == 0) size--;
	fs.write((char*)&size, sizeof(uint));
	for(i=0; i<size; i++)
	{
		fs.write((char*)&m_nflag[i], sizeof(uint));
	}
	size = m_eflag.size();
	while(size > 0 && m_eflag[size - 1] == 0) size--;
	fs.write((char*)&size, sizeof(uint));
	for(i=0; i<size; i++)
	{
		fs.write((char*)&m_eflag[i], sizeof(uint));
	}
	size = m_fflag.size();
	while(size > 0 && m_fflag[size - 1] == 0) size--;
	fs.write((char*)&size, sizeof(uint));
	for(i=0; i<size; i++)
	{
		fs.write((char*)&m_fflag[i], sizeof(uint));
	}
	size = m_bflag.size();
	while(size > 0 && m_bflag[size - 1] == 0) size--;
	fs.write((char*)&size, sizeof(uint));
	for(i=0; i<size; i++)
	{
		fs.write((char*)&m_bflag[i], sizeof(uint));
	}
	size = m_qflag.size();
	while(size > 0 && m_qflag[size - 1] == 0) size--;
	fs.write((char*)&size, sizeof(uint));
	for(i=0; i<size; i++)
	{
		fs.write((char*)&m_qflag[i], sizeof(uint));
	}

	// weights
	size = m_w.size();
	while(size > 0 && m_w[size - 1] == 0.0) size--;
	fs.write((char*)&size, sizeof(uint));
	for(i=0; i<size; i++)
	{
		const double w = m_w[i];
		fs.write((char*)&w, sizeof(double));
	}
	fs.close();
	return true;
}

bool Mesh::saveStatistics(const std::string &path, const UintGroup &flag) const
{
	uint i;
	Text out;

	// neighbour elements
	if(m_nsize > 0) out << "nodes:  " << m_nsize << std::endl;
	if(m_esize > 0) out << "edges:  " << m_esize << std::endl;
	if(m_fsize > 0) out << "faces:  " << m_fsize << std::endl;
	if(m_bsize > 0) out << "bodies: " << m_bsize << std::endl;
	if(m_qsize > 0) out << "quads:  " << m_qsize << std::endl << std::endl;
	out << "euler:  " << int(m_nsize - m_esize + m_fsize - m_bsize + m_qsize) << std::endl << std::endl;

	Buffer<uint> links(8, 0);
	out << "links:  \t0\t1\t2\t3\t4\t5\t6\tmore\taverage";
	if(m_esize > 0)
	{
		uint sum = 0;
		uint num = 0;
		for(i=0; i<m_esize; i++)
		{
			if(!flag.includes(getEdgeFlag(i))) continue;
			const uint li = getEdgeNodes(i).size();
			links[li < links.size() ? li : links.size() - 1]++;
			num += li;
			sum++;
		}
		out << std::endl << "edge->node:";
		for(i=0; i<links.size(); i++)
		{
			out << "\t" << links[i];
			links[i] = 0;
		}
		out << "\t" << ddouble(num) / ddouble(sum);
	}
	if(m_fsize > 0)
	{
		uint sum = 0;
		uint num = 0;
		for(i=0; i<m_fsize; i++)
		{
			if(!flag.includes(getFaceFlag(i))) continue;
			const uint li = getFaceEdges(i).size();
			links[li < links.size() ? li : links.size() - 1]++;
			num += li;
			sum++;
		}
		out << std::endl << "face->edge:";
		for(i=0; i<links.size(); i++)
		{
			out << "\t" << links[i];
			links[i] = 0;
		}
		out << "\t" << ddouble(num) / ddouble(sum);
	}
	if(m_bsize > 0)
	{
		uint sum = 0;
		uint num = 0;
		for(i=0; i<m_bsize; i++)
		{
			if(!flag.includes(getBodyFlag(i))) continue;
			const uint li = getBodyFaces(i).size();
			links[li < links.size() ? li : links.size() - 1]++;
			num += li;
			sum++;
		}
		out << std::endl << "body->face:";
		for(i=0; i<links.size(); i++)
		{
			out << "\t" << links[i];
			links[i] = 0;
		}
		out << "\t" << ddouble(num) / ddouble(sum);
	}
	if(m_qsize > 0)
	{
		uint sum = 0;
		uint num = 0;
		for(i=0; i<m_qsize; i++)
		{
			if(!flag.includes(getQuadFlag(i))) continue;
			const uint li = getQuadBodies(i).size();
			links[li < links.size() ? li : links.size() - 1]++;
			num += li;
			sum++;
		}
		out << std::endl << "quad->body:";
		for(i=0; i<links.size(); i++)
		{
			out << "\t" << links[i];
			links[i] = 0;
		}
		out << "\t" << ddouble(num) / ddouble(sum);
	}
	if(m_qsize > 0)
	{
		uint sum = 0;
		uint num = 0;
		for(i=0; i<m_bsize; i++)
		{
			if(!flag.includes(getBodyFlag(i))) continue;
			const uint li = getBodyQuads(i).size();
			links[li < links.size() ? li : links.size() - 1]++;
			num += li;
			sum++;
		}
		out << std::endl << "body->quad:";
		for(i=0; i<links.size(); i++)
		{
			out << "\t" << links[i];
			links[i] = 0;
		}
		out << "\t" << ddouble(num) / ddouble(sum);
	}
	if(m_bsize > 0)
	{
		uint sum = 0;
		uint num = 0;
		for(i=0; i<m_fsize; i++)
		{
			if(!flag.includes(getFaceFlag(i))) continue;
			const uint li = getFaceBodies(i).size();
			links[li < links.size() ? li : links.size() - 1]++;
			num += li;
			sum++;
		}
		out << std::endl << "face->body:";
		for(i=0; i<links.size(); i++)
		{
			out << "\t" << links[i];
			links[i] = 0;
		}
		out << "\t" << ddouble(num) / ddouble(sum);
	}
	if(m_fsize > 0)
	{
		uint sum = 0;
		uint num = 0;
		for(i=0; i<m_esize; i++)
		{
			if(!flag.includes(getEdgeFlag(i))) continue;
			const uint li = getEdgeFaces(i).size();
			links[li < links.size() ? li : links.size() - 1]++;
			num += li;
			sum++;
		}
		out << std::endl << "edge->face:";
		for(i=0; i<links.size(); i++)
		{
			out << "\t" << links[i];
			links[i] = 0;
		}
		out << "\t" << ddouble(num) / ddouble(sum);
	}
	if(m_esize > 0)
	{
		uint sum = 0;
		uint num = 0;
		for(i=0; i<m_nsize; i++)
		{
			if(!flag.includes(getNodeFlag(i))) continue;
			const uint li = getNodeEdges(i).size();
			links[li < links.size() ? li : links.size() - 1]++;
			num += li;
			sum++;
		}
		out << std::endl << "node->edge:";
		for(i=0; i<links.size(); i++)
		{
			out << "\t" << links[i];
			links[i] = 0;
		}
		out << "\t" << ddouble(num) / ddouble(sum);
	}
	out << std::endl << std::endl;

	// Cell statistics
	out << "Cell statistics:  min\tmean\tmax" << std::endl;
	ddouble vole = 0.0;
	ddouble volf = 0.0;
	ddouble volb = 0.0;
	ddouble volq = 0.0;
	Vector3 sum = Vector3(1e30,0,-1e30);
	Vector3 sumd = Vector3(1e30,0,-1e30);
	Vector3 sumh = Vector3(1e30,0,-1e30);
	uint count = 0;
	for(i=0; i<m_nsize; i++)
	{
		if(!flag.includes(getNodeFlag(i))) continue;
		count++;

		ddouble len = getNodeWeight(i);
		if(len < sum.x) sum.x = len;
		sum.y += len;
		if(len > sum.z) sum.z = len;

		len = getNodeDualVector(i);
		if(len < sumd.x) sumd.x = len;
		sumd.y += len;
		if(len > sumd.z) sumd.z = len;

		len = getNodeHodge(i);
		if(len < sumh.x) sumh.x = len;
		sumh.y += len;
		if(len > sumh.z) sumh.z = len;
	}
	if(count > 0)
	{
		out << "node weight:      " << sum.x << " \t" << sum.y / ddouble(count) << " \t" << sum.z << std::endl;
		out << "node unit:        1 \t1 \t1" << std::endl;
		if(m_esize == 0) out << "node dual unit:   ";
		else if(m_fsize == 0) out << "node dual length: ";
		else if(m_bsize == 0) out << "node dual area:   ";
		else out << "node dual volume: ";
		out << sumd.x << " \t" << sumd.y / ddouble(count) << " \t" << sumd.z << std::endl;
		out << "node Hodge:       " << sumh.x << " \t" << sumh.y / ddouble(count) << " \t" << sumh.z << std::endl;
	}
	sum = Vector3(1e30,0,-1e30);
	sumd = Vector3(1e30,0,-1e30);
	sumh = Vector3(1e30,0,-1e30);
	count = 0;
	for(i=0; i<m_esize; i++)
	{
		if(!flag.includes(getEdgeFlag(i))) continue;
		count++;

		ddouble len = getEdgeVector(i).len();
		if(len < sum.x) sum.x = len;
		sum.y += len;
		if(len > sum.z) sum.z = len;
		if(getEdgeFaces(i).size() < 2) vole += len;

		len = getEdgeDualVector(i).len();
		if(len < sumd.x) sumd.x = len;
		sumd.y += len;
		if(len > sumd.z) sumd.z = len;

		len = getEdgeHodge(i);
		if(len < sumh.x) sumh.x = len;
		sumh.y += len;
		if(len > sumh.z) sumh.z = len;
	}
	if(count > 0)
	{
		out << "edge length:      " << sum.x << " \t" << sum.y / ddouble(count) << " \t" << sum.z << std::endl;
		if(m_fsize == 0) out << "edge dual unit:   ";
		else if(m_bsize == 0) out << "edge dual length: ";
		else if(m_qsize == 0) out << "edge dual area:   ";
		else out << "edge dual volume: ";
		out << sumd.x << " \t" << sumd.y / ddouble(count) << " \t" << sumd.z << std::endl;
		out << "edge Hodge:       " << sumh.x << " \t" << sumh.y / ddouble(count) << " \t" << sumh.z << std::endl;
	}
	sum = Vector3(1e30,0,-1e30);
	sumd = Vector3(1e30,0,-1e30);
	sumh = Vector3(1e30,0,-1e30);
	count = 0;
	for(i=0; i<m_fsize; i++)
	{
		if(!flag.includes(getFaceFlag(i))) continue;
		count++;

		ddouble len = getFaceVector(i).len();
		if(len < sum.x) sum.x = len;
		sum.y += len;
		if(len > sum.z) sum.z = len;
		if(getFaceBodies(i).size() < 2) volf += len;

		len = getFaceDualVector(i).len();
		if(len < sumd.x) sumd.x = len;
		sumd.y += len;
		if(len > sumd.z) sumd.z = len;

		len = getFaceHodge(i);
		if(len < sumh.x) sumh.x = len;
		sumh.y += len;
		if(len > sumh.z) sumh.z = len;
	}
	if(count > 0)
	{
		out << "face area:        " << sum.x << " \t" << sum.y / ddouble(count) << " \t" << sum.z << std::endl;
		if(m_bsize == 0) out << "face dual unit:   ";
		else if(m_qsize == 0) out << "face dual length: ";
		else out << "face dual area:   ";
		out << sumd.x << " \t" << sumd.y / ddouble(count) << " \t" << sumd.z << std::endl;
		out << "face Hodge:       " << sumh.x << " \t" << sumh.y / ddouble(count) << " \t" << sumh.z << std::endl;
	}
	sum = Vector3(1e30,0,-1e30);
	sumd = Vector3(1e30,0,-1e30);
	sumh = Vector3(1e30,0,-1e30);
	count = 0;
	for(i=0; i<m_bsize; i++)
	{
		if(!flag.includes(getBodyFlag(i))) continue;
		count++;

		ddouble len = getBodyVector(i).len();
		if(len < sum.x) sum.x = len;
		sum.y += len;
		if(len > sum.z) sum.z = len;
		if(getBodyQuads(i).size() < 2) volb += len;

		len = getBodyDualVector(i).len();
		if(len < sumd.x) sumd.x = len;
		sumd.y += len;
		if(len > sumd.z) sumd.z = len;

		len = getBodyHodge(i);
		if(len < sumh.x) sumh.x = len;
		sumh.y += len;
		if(len > sumh.z) sumh.z = len;
	}
	if(count > 0)
	{
		out << "body volume:      " << sum.x << " \t" << sum.y / ddouble(count) << " \t" << sum.z << std::endl;
		if(m_qsize == 0) out << "body dual unit:   ";
		else out << "body dual length: ";
		out << sumd.x << " \t" << sumd.y / ddouble(count) << " \t" << sumd.z << std::endl;
		out << "body Hodge:       " << sumh.x << " \t" << sumh.y / ddouble(count) << " \t" << sumh.z << std::endl;
	}
	sum = Vector3(1e30,0,-1e30);
	sumh = Vector3(1e30,0,-1e30);
	count = 0;
	for(i=0; i<m_qsize; i++)
	{
		if(!flag.includes(getQuadFlag(i))) continue;
		count++;

		ddouble len = getQuadVector(i);
		if(len < sum.x) sum.x = len;
		sum.y += len;
		if(len > sum.z) sum.z = len;
		volq += len;

		len = getQuadHodge(i);
		if(len < sumh.x) sumh.x = len;
		sumh.y += len;
		if(len > sumh.z) sumh.z = len;
	}
	if(count > 0)
	{
		out << "quad volume:      " << sum.x << " \t" << sum.y / ddouble(count) << " \t" << sum.z << std::endl;
		out << "quad dual unit:   1 \t1 \t1" << std::endl;
		out << "quad Hodge:       " << sumh.x << " \t" << sumh.y / ddouble(count) << " \t" << sumh.z << std::endl;
	}

	if(m_esize > 0) out << std::endl << "total edge:       " << vole << std::endl;
	if(m_fsize > 0) out << "total face:       " << volf << std::endl;
	if(m_bsize > 0) out << "total body:       " << volb << std::endl;
	if(m_qsize > 0) out << "total quad:       " << volq << std::endl;

	out.save(path);
	return true;
}

void Mesh::setNodeFlag(const uint n, const uint flag)
{
	if(n >= m_nflag.size())
	{
		if(flag == 0) return;
		uint i = m_nflag.size();
		m_nflag.resize(m_nsize);
		while(i<m_nsize) m_nflag[i++] = 0;
	}
	m_nflag[n] = flag;
}

void Mesh::setEdgeFlag(const uint e, const uint flag)
{
	if(e >= m_eflag.size())
	{
		if(flag == 0) return;
		uint i = m_eflag.size();
		m_eflag.resize(m_esize);
		while(i<m_esize) m_eflag[i++] = 0;
	}
	m_eflag[e] = flag;
}

void Mesh::setFaceFlag(const uint f, const uint flag)
{
	if(f >= m_fflag.size())
	{
		if(flag == 0) return;
		uint i = m_fflag.size();
		m_fflag.resize(m_fsize);
		while(i<m_fsize) m_fflag[i++] = 0;
	}
	m_fflag[f] = flag;
}

void Mesh::setBodyFlag(const uint b, const uint flag)
{
	if(b >= m_bflag.size())
	{
		if(flag == 0) return;
		uint i = m_nflag.size();
		m_bflag.resize(m_bsize);
		while(i<m_bsize) m_bflag[i++] = 0;
	}
	m_bflag[b] = flag;
}

void Mesh::setQuadFlag(const uint q, const uint flag)
{
	if(q >= m_qflag.size())
	{
		if(flag == 0) return;
		uint i = m_nflag.size();
		m_qflag.resize(m_qsize);
		while(i<m_qsize) m_qflag[i++] = 0;
	}
	m_qflag[q] = flag;
}


Buffer<uint> Mesh::getNodeFaces(const uint n) const
{
	const Buffer<uint> &ne = getNodeEdges(n);
	Buffer<uint> f(ne.size());
	uint l = 0;
	for(uint i=0; i<ne.size(); i++)
	{
		const Buffer<uint> &ef = getEdgeFaces(ne[i]);
		for(uint j=0; j<ef.size(); j++) f.gatherOnce(ef[j], l);
	}
	f.resize(l);
	return f;
}

Buffer<uint> Mesh::getNodeBodies(const uint n) const
{
	const Buffer<uint> f = getNodeFaces(n);
	Buffer<uint> b(f.size());
	uint l = 0;
	for(uint i=0; i<f.size(); i++)
	{
		const Buffer<uint> &fb = getFaceBodies(f[i]);
		for(uint j=0; j<fb.size(); j++) b.gatherOnce(fb[j], l);
	}
	b.resize(l);
	return b;
}

Buffer<uint> Mesh::getNodeQuads(const uint n) const
{
	const Buffer<uint> b = getNodeBodies(n);
	Buffer<uint> q(b.size());
	uint l = 0;
	for(uint i=0; i<b.size(); i++)
	{
		const Buffer<uint> &bq = getBodyQuads(b[i]);
		for(uint j=0; j<bq.size(); j++) q.gatherOnce(bq[j], l);
	}
	q.resize(l);
	return q;
}

Buffer<uint> Mesh::getEdgeBodies(const uint e) const
{
	const Buffer<uint> &f = getEdgeFaces(e);
	Buffer<uint> b(f.size());
	uint l = 0;
	for(uint i=0; i<f.size(); i++)
	{
		const Buffer<uint> &fb = getFaceBodies(f[i]);
		for(uint j=0; j<fb.size(); j++) b.gatherOnce(fb[j], l);
	}
	b.resize(l);
	return b;
}

Buffer<uint> Mesh::getEdgeQuads(const uint e) const
{
	const Buffer<uint> b = getEdgeBodies(e);
	Buffer<uint> q(b.size());
	uint l = 0;
	for(uint i=0; i<b.size(); i++)
	{
		const Buffer<uint> &bq = getBodyQuads(b[i]);
		for(uint j=0; j<bq.size(); j++) q.gatherOnce(bq[j], l);
	}
	q.resize(l);
	return q;
}

Buffer<uint> Mesh::getFaceNodes(const uint f) const
{
	const Buffer<uint> &e = m_f[f].e;
	Buffer<uint> n(e.size());
	for(uint i=0; i<e.size(); i++)
	{
		const uint j = (i > 0 ? i : e.size()) - 1;
		n[i] = getEdgeIntersection(e[i], e[j]);
		if(n[i] == NONE)
		{
			std::cout << "ihme ";
			for(uint k=0; k<e.size(); k++)
			{
				std::cout << "(" << getEdgeNodes(e[k])[0] << " " << getEdgeNodes(e[k])[1] << ")";
			}
			std::cout << std::endl;
		}
	}
	return n;
}

Buffer<uint> Mesh::getFaceQuads(const uint f) const
{
	const Buffer<uint> &b = getFaceBodies(f);
	Buffer<uint> q(b.size());
	uint l = 0;
	for(uint i=0; i<b.size(); i++)
	{
		const Buffer<uint> &bq = getBodyQuads(b[i]);
		for(uint j=0; j<bq.size(); j++) q.gatherOnce(bq[j], l);
	}
	q.resize(l);
	return q;
}

Buffer<uint> Mesh::getBodyNodes(const uint b) const
{
	const Buffer<uint> e = getBodyEdges(b);
	Buffer<uint> n(e.size());
	uint l = 0;
	for(uint i=0; i<e.size(); i++)
	{
		const Buffer<uint> &en = getEdgeNodes(e[i]);
		for(uint j=0; j<en.size(); j++) n.gatherOnce(en[j], l);
	}
	n.resize(l);
	return n;
}

Buffer<uint> Mesh::getBodyEdges(const uint b) const
{
	const Buffer<uint> &f = getBodyFaces(b);
	Buffer<uint> e(f.size());
	uint l = 0;
	for(uint i=0; i<f.size(); i++)
	{
		const Buffer<uint> &fe = getFaceEdges(f[i]);
		for(uint j=0; j<fe.size(); j++) e.gatherOnce(fe[j], l);
	}
	e.resize(l);
	return e;
}

Buffer<uint> Mesh::getQuadNodes(const uint q) const
{
	const Buffer<uint> e = getQuadEdges(q);
	Buffer<uint> n(e.size());
	uint l = 0;
	for(uint i=0; i<e.size(); i++)
	{
		const Buffer<uint> &en = getEdgeNodes(e[i]);
		for(uint j=0; j<en.size(); j++) n.gatherOnce(en[j], l);
	}
	n.resize(l);
	return n;
}

Buffer<uint> Mesh::getQuadEdges(const uint q) const
{
	const Buffer<uint> f = getQuadFaces(q);
	Buffer<uint> e(f.size());
	uint l = 0;
	for(uint i=0; i<f.size(); i++)
	{
		const Buffer<uint> &fe = getFaceEdges(f[i]);
		for(uint j=0; j<fe.size(); j++) e.gatherOnce(fe[j], l);
	}
	e.resize(l);
	return e;
}

Buffer<uint> Mesh::getQuadFaces(const uint q) const
{
	const Buffer<uint> &b = getQuadBodies(q);
	Buffer<uint> f(b.size());
	uint l = 0;
	for(uint i=0; i<b.size(); i++)
	{
		const Buffer<uint> &bf = getBodyFaces(b[i]);
		for(uint j=0; j<bf.size(); j++) f.gatherOnce(bf[j], l);
	}
	f.resize(l);
	return f;
}

uint Mesh::getEdgeOtherNode(const uint e, const uint n) const
{
	const Buffer<uint> &en = getEdgeNodes(e);
	if(n == en[0]) return en[1];
	if(n == en[1]) return en[0];
	return NONE;
}

void Mesh::setNodeWeight(const uint n, const ddouble w)
{
	if(n >= m_w.size())
	{
		if(w == 0.0) return;
		uint i = m_w.size();
		m_w.resize(m_nsize);
		while(i<m_nsize) m_w[i++] = 0.0;
	}
	m_w[n] = w;
}

void Mesh::setNodePosition(const uint n, const Vector4 &p)
{
	const uint nn = m_dim * n;
	m_p[nn] = p.x;
	if(m_dim == 1) return;
	m_p[nn+1] = p.y;
	if(m_dim == 2) return;
	m_p[nn+2] = p.z;
	if(m_dim == 3) return;
	m_p[nn+3] = p.t;
}

Vector4 Mesh::getNodePosition(const uint n) const
{
	const uint nn = m_dim * n;
	Vector4 p(m_p[nn],0,0,0);
	if(m_dim == 1) return p;
	p.y = m_p[nn+1];
	if(m_dim == 2) return p;
	p.z = m_p[nn+2];
	if(m_dim == 3) return p;
	p.t = m_p[nn+3];
	return p;
}

Vector4 Mesh::getEdgePosition(const uint e) const
{
	const Buffer<uint> &n = m_e[e].n;
	const Vector4 p = getNodePosition(n[0]);
	const Vector4 d = getNodePosition(n[1]) - p;
	const ddouble w = (getNodeWeight(n[1]) - getNodeWeight(n[0])) / getMetric().normsq(d);
	return p + 0.5 * (1.0 + w) * d;
}

Vector4 Mesh::getFacePosition(const uint f) const
{
	const Buffer<uint> &e = getFaceEdges(f);
	const uint size = e.size();
	if(m_dim == 2)
	{
		const Vector2 p = getEdgePosition(e[0]).toVector2();
		const SymmMatrix2 met = getMetric().toSymmMatrix2();
		SymmMatrix2 mA(ZEROSYMMMATRIX2);
		Vector2 vB(0,0);
		for(uint i=0; i<size; i++)
		{
			const Vector2 vi = met * getEdgeVector(e[i]).toVector2();
			mA += SymmMatrix2(vi);
			if(i > 0) vB += vi * vi.dot(getEdgePosition(e[i]).toVector2() - p);
		}
		return Vector4(p + mA.inverse() * vB, 0,0);
	}
	if(m_dim == 3)
	{
		const Vector3 p = getEdgePosition(e[0]).toVector3();
		const SymmMatrix3 met = getMetric().toSymmMatrix3();
		SymmMatrix3 mA(ZEROSYMMMATRIX3);
		Vector3 vB(0,0,0);
		for(uint i=0; i<size; i++)
		{
			const Vector3 vi = met * getEdgeVector(e[i]).toVector3();
			mA += SymmMatrix3(vi);
			if(i > 0) vB += vi * vi.dot(getEdgePosition(e[i]).toVector3() - p);
		}
		mA += SymmMatrix3(getFaceVector(f).wedgeT().toVector3());
		return Vector4(p + mA.inverse() * vB, 0);
	}

	const Vector4 p = getEdgePosition(e[0]);
	const SymmMatrix4 &met = getMetric();
	SymmMatrix4 mA(ZEROSYMMMATRIX4);
	Vector4 vB(0,0,0,0);
	for(uint i=0; i<size; i++)
	{
		const Vector4 vi = met * getEdgeVector(e[i]);
		mA += SymmMatrix4(vi);
		if(i > 0) vB += vi * vi.dot(getEdgePosition(e[i]) - p);
	}
	const TwoVector4 fv = getFaceVector(f);
	mA += SymmMatrix4(fv.wedgeX()) + SymmMatrix4(fv.wedgeY()) + SymmMatrix4(fv.wedgeZ()) + SymmMatrix4(fv.wedgeT());
	return p + mA.inverse() * vB;
}

Vector4 Mesh::getBodyPosition(const uint b) const
{
	const Buffer<uint> e = getBodyEdges(b);
	const uint size = e.size();
	if(m_dim == 3)
	{
		const Vector3 p = getEdgePosition(e[0]).toVector3();
		const SymmMatrix3 met = getMetric().toSymmMatrix3();
		SymmMatrix3 mA(ZEROSYMMMATRIX3);
		Vector3 vB(0,0,0);
		for(uint i=0; i<size; i++)
		{
			const Vector3 vi = met * getEdgeVector(e[i]).toVector3();
			mA += SymmMatrix3(vi);
			if(i > 0) vB += vi * vi.dot(getEdgePosition(e[i]).toVector3() - p);
		}
		return Vector4(p + mA.inverse() * vB, 0);
	}

	const Vector4 p = getEdgePosition(e[0]);
	const SymmMatrix4 &met = getMetric();
	SymmMatrix4 mA(ZEROSYMMMATRIX4);
	Vector4 vB(0,0,0,0);
	for(uint i=0; i<size; i++)
	{
		const Vector4 vi = met * getEdgeVector(e[i]);
		mA += SymmMatrix4(vi);
		if(i > 0) vB += vi * vi.dot(getEdgePosition(e[i]) - p);
	}
	mA += SymmMatrix4(getBodyVector(b));
	return p + mA.inverse() * vB;
}

Vector4 Mesh::getQuadPosition(const uint q) const
{
	const Buffer<uint> e = getQuadEdges(q);
	const uint size = e.size();
	const Vector4 p = getEdgePosition(e[0]);
	const SymmMatrix4 &met = getMetric();
	SymmMatrix4 mA(ZEROSYMMMATRIX4);
	Vector4 vB(0,0,0,0);
	for(uint i=0; i<size; i++)
	{
		const Vector4 vi = met * getEdgeVector(e[i]);
		mA += SymmMatrix4(vi);
		if(i > 0) vB += vi * vi.dot(getEdgePosition(e[i]) - p);
	}
	return p + mA.inverse() * vB;
}

Vector4 Mesh::getEdgeAverage(const uint e) const
{
	const Buffer<uint> &n = getEdgeNodes(e);
	return 0.5 * (getNodePosition(n[0]) + getNodePosition(n[1]));
}

Vector4 Mesh::getFaceAverage(const uint f) const
{
	const Buffer<uint> n = getFaceNodes(f);
	Vector4 p(0,0,0,0);
	for(uint i=0; i<n.size(); i++)
	{
		p += getNodePosition(n[i]);
	}
	return p / ddouble(n.size());
}

Vector4 Mesh::getBodyAverage(const uint b) const
{
	const Buffer<uint> n = getBodyNodes(b);
	Vector4 p(0,0,0,0);
	for(uint i=0; i<n.size(); i++)
	{
		p += getNodePosition(n[i]);
	}
	return p / ddouble(n.size());
}

Vector4 Mesh::getQuadAverage(const uint q) const
{
	const Buffer<uint> n = getQuadNodes(q);
	Vector4 p(0,0,0,0);
	for(uint i=0; i<n.size(); i++)
	{
		p += getNodePosition(n[i]);
	}
	return p / ddouble(n.size());
}

Vector4 Mesh::getEdgeOrthogonal(const uint e, const Vector4 &d) const
{
	if(m_dim == 1) return Vector4(0,0,0,0);
	const Vector4 v0 = getEdgeVector(e);
	return d - d.dot(v0) / v0.lensq() * v0;
}

Vector4 Mesh::getFaceOrthogonal(const uint f, const Vector4 &d) const
{
	if(m_dim == 2) return Vector4(0,0,0,0);
	uint i;
	const Buffer<uint> &e = getFaceEdges(f);
	Buffer<Vector4> v(e.size());
	for(i=0; i<v.size(); i++) v[i] = getEdgeVector(e[i]);
	const ddouble sq0 = v[0].lensq();

	v[1] -= v[1].dot(v[0]) / sq0 * v[0];
	ddouble sq1 = v[1].lensq();
	for(i=2; i<v.size(); i++)
	{
		v[i] -= v[i].dot(v[0]) / sq0 * v[0];
		const ddouble sqi = v[i].lensq();
		if(sqi > sq1)
		{
			sq1 = sqi;
			v[1] = v[i];
		}
	}
	return d - d.dot(v[0]) / sq0 * v[0] - d.dot(v[1]) / sq1 * v[1];
}

Vector4 Mesh::getBodyOrthogonal(const uint b, const Vector4 &d) const
{
	if(m_dim == 3) return Vector4(0,0,0,0);
	uint i;
	const Buffer<uint> e = getBodyEdges(b);
	Buffer<Vector4> v(e.size());
	for(i=0; i<v.size(); i++) v[i] = getEdgeVector(e[i]);
	const ddouble sq0 = v[0].lensq();

	v[1] -= v[1].dot(v[0]) / sq0 * v[0];
	ddouble sq1 = v[1].lensq();
	for(i=2; i<v.size(); i++)
	{
		v[i] -= v[i].dot(v[0]) / sq0 * v[0];
		const ddouble sqi = v[i].lensq();
		if(sqi > sq1)
		{
			sq1 = sqi;
			const Vector4 v1 = v[1];
			v[1] = v[i];
			v[i] = v1;
		}
	}

	v[2] -= v[2].dot(v[1]) / sq1 * v[1];
	ddouble sq2 = v[2].lensq();
	for(i=3; i<v.size(); i++)
	{
		v[i] -= v[i].dot(v[1]) / sq1 * v[1];
		const ddouble sqi = v[i].lensq();
		if(sqi > sq2)
		{
			sq2 = sqi;
			v[2] = v[i];
		}
	}
	return d - d.dot(v[0]) / sq0 * v[0] - d.dot(v[1]) / sq1 * v[1] - d.dot(v[2]) / sq2 * v[2];
}

Vector4 Mesh::getEdgeVector(const uint e) const
{
	const Buffer<uint> &n = getEdgeNodes(e);
	return getNodePosition(n[1]) - getNodePosition(n[0]);
}

Vector4 Mesh::getEdgeVector(const uint e, ddouble c) const
{
	if(m_fsize == 0) c /= 6.0;
	else if(m_bsize == 0) c /= 8.0;
	else if(m_qsize == 0) c /= 10.0;
	else c /= 12.0;

	const Vector4 p = getEdgePosition(e);
	const Buffer<uint> &n = getEdgeNodes(e);
	const Vector4 r0 = p - getNodePosition(n[0]);
	const Vector4 r1 = getNodePosition(n[1]) - p;
	return (1.0 + c * r0.lensq()) * r0 + (1.0 + c * r1.lensq()) * r1;
}


TwoVector4 Mesh::getFaceVector(const uint f) const
{
	const Buffer<uint> n = getFaceNodes(f);
	const Vector4 p = getNodePosition(n[0]);
	TwoVector4 v(0,0,0,0,0,0);
	Vector4 b = getNodePosition(n[1]) - p;
	for(uint i=2; i<n.size(); i++)
	{
		const Vector4 a = b;
		b = getNodePosition(n[i]) - p;
		v += TwoVector4(a,b);
	}
	return 0.5 * v;
}

TwoVector4 Mesh::getFaceVector(const uint f, ddouble c) const
{
	if(m_bsize == 0) c /= 8.0;
	else if(m_qsize == 0) c /= 10.0;
	else c /= 12.0;

	TwoVector4 v(0,0,0,0,0,0);
	const Vector4 p = getFacePosition(f);
	const Buffer<uint> &e = getFaceEdges(f);
	for(uint i=0; i<e.size(); i++)
	{
		const Vector4 r = getEdgePosition(e[i]) - p;
		v += (1.0 + c * r.lensq()) * getFaceIncidence(f, e[i]) * TwoVector4(r, getEdgeVector(e[i]));
	}
	return 0.5 * v;
}

Vector4 Mesh::getBodyVector(const uint b) const
{
	const Buffer<uint> &f = getBodyFaces(b);
	Buffer<ddouble> inc(f.size());
	inc[0] = 1.0 / 3.0;
	Vector4 v(0,0,0,0);
	const Vector4 p = getNodePosition(getEdgeNodes(getFaceEdges(f[0])[0])[0]);
	for(uint i=1; i<f.size(); i++)
	{
		for(uint j=0; j<i; j++)
		{
			const uint e = getCommon(getFaceEdges(f[i]), getFaceEdges(f[j]));
			if(e != NONE)
			{
				inc[i] = -getFaceIncidence(f[i], e) * getFaceIncidence(f[j], e) * inc[j];
				break;
			}
		}
		const TwoVector4 fv = getFaceVector(f[i]);
		const Vector4 d = inc[i] * (getNodePosition(getEdgeNodes(getFaceEdges(f[i])[0])[0]) - p);
		v += fv.wedge(d);
	}
	return v;
}

Vector4 Mesh::getBodyVector(const uint b, ddouble c) const
{
	if(m_qsize == 0) c /= 10.0;
	else c /= 12.0;

	Vector4 v(0,0,0,0);
	const Vector4 p = getBodyPosition(b);
	const Buffer<uint> &f = getBodyFaces(b);
	Buffer<ddouble> inc(f.size());
	inc[0] = 1.0 / 3.0;
	for(uint i=0; i<f.size(); i++)
	{
		for(uint j=0; j<i; j++)
		{
			const uint e = getCommon(getFaceEdges(f[i]), getFaceEdges(f[j]));
			if(e != NONE)
			{
				inc[i] = -getFaceIncidence(f[i], e) * getFaceIncidence(f[j], e) * inc[j];
				break;
			}
		}
		const Vector4 r = getFacePosition(f[i]) - p;
		v += (1.0 + c * r.lensq()) * inc[i] * getFaceVector(f[i]).wedge(r);
	}
	return v;
}


ddouble Mesh::getQuadVector(const uint q) const
{
	const Buffer<uint> &b = getQuadBodies(q);
	const Vector4 p = getNodePosition(getEdgeNodes(getFaceEdges(getBodyFaces(b[0])[0])[0])[0]);
	ddouble v = 0.0;
	for(uint i=1; i<b.size(); i++)
	{
		const Vector4 d = getNodePosition(getEdgeNodes(getFaceEdges(getBodyFaces(b[i])[0])[0])[0]) - p;
		v += fabs(getBodyVector(b[i]).dot(d));
	}
	return 0.25 * v;
}

ddouble Mesh::getQuadVector(const uint q, ddouble c) const
{
	c /= 12.0;
	ddouble v = 0.0;
	const Vector4 p = getQuadPosition(q);
	const Buffer<uint> &b = getQuadBodies(q);
	for(uint i=1; i<b.size(); i++)
	{
		const Vector4 r = getBodyPosition(b[i]) - p;
		v += (1.0 + c * r.lensq()) * getQuadIncidence(q, b[i]) * getBodyVector(b[i]).dot(r);
	}
	return 0.25 * v;
}

ddouble Mesh::getNodeDualVector(const uint n) const
{
	if(m_esize == 0) return 1.0; // 0-dimensional mesh

	ddouble v = 0.0;
	const Vector4 p = getNodePosition(n);
	const Buffer<uint> &e = getNodeEdges(n);
	for(uint i=0; i<e.size(); i++)
	{
		v += getEdgeIncidence(e[i], n) * getEdgeDualVector(e[i]).dot(p - getEdgePosition(e[i]));
	}
	if(m_fsize == 0) return v; // 1-dimensional mesh
	if(m_bsize == 0) return 0.5 * v; // 2-dimensional mesh
	if(m_qsize == 0) return v / 3.0; // 3-dimensional mesh
	return 0.25 * v; // 4-dimensional mesh
}

ddouble Mesh::getNodeDualVector(const uint n, ddouble c) const
{
	if(m_esize == 0) return 1.0; // 0-dimensional mesh

	ddouble cc;
	if(m_fsize == 0) { cc = 1.0; c /= 6.0; }
	else if(m_bsize == 0) { cc = 0.5; c /= 16.0; }
	else if(m_qsize == 0) { cc = 1.0 / 3.0; c /= 30.0; }
	else { cc = 0.25; c /= 48.0; }

	ddouble v = 0.0;
	const Vector4 p = getNodePosition(n);
	const Buffer<uint> &e = getNodeEdges(n);
	for(uint i=0; i<e.size(); i++)
	{
		const Vector4 r = p - getEdgePosition(e[i]);
		v += (cc + c * r.lensq()) * getEdgeIncidence(e[i], n) * getEdgeDualVector(e[i]).dot(r);
	}
	return v;
}

Vector4 Mesh::getEdgeDualVector(const uint e) const
{
	if(m_fsize == 0) return getEdgeVector(e).unit(); // 1-dimensional mesh

	Vector4 v(0,0,0,0);
	const Vector4 ep = getEdgePosition(e);
	const Buffer<uint> &f = getEdgeFaces(e);
	for(uint i=0; i<f.size(); i++)
	{
		v += getFaceIncidence(f[i], e) * getFaceDualVector(f[i]).wedge(getFacePosition(f[i]) - ep);
	}
	if(m_bsize == 0) return v; // 2-dimensional mesh
	if(m_qsize == 0) return 0.5 * v; // 3-dimensional mesh
	return v / 3.0; // 4-dimensional mesh
}

Vector4 Mesh::getEdgeDualVector(const uint e, ddouble c) const
{
	if(m_fsize == 0) return getEdgeVector(e).unit(); // 1-dimensional mesh

	ddouble cc;
	if(m_bsize == 0) { cc = 1.0; c /= 8.0; }
	else if(m_qsize == 0) { cc = 0.5; c /= 20.0; }
	else { cc = 1.0 / 3.0; c /= 36.0; }

	Vector4 v(0,0,0,0);
	const Vector4 p = getEdgePosition(e);
	const Buffer<uint> &f = getEdgeFaces(e);
	for(uint i=0; i<f.size(); i++)
	{
		const Vector4 r = getFacePosition(f[i]) - p;
		v += (cc + c * r.lensq()) * getFaceIncidence(f[i], e) * getFaceDualVector(f[i]).wedge(r);
	}
	return v;
}

TwoVector4 Mesh::getFaceDualVector(const uint f) const
{
	if(m_bsize == 0) return getFaceVector(f).dual().unit(); // 2-dimensional mesh

	TwoVector4 v(0,0,0,0,0,0);
	const Vector4 fp = getFacePosition(f);
	const Buffer<uint> &b = getFaceBodies(f);
	for(uint i=0; i<b.size(); i++)
	{
		v += getBodyIncidence(b[i], f) * TwoVector4(getBodyDualVector(b[i]), getBodyPosition(b[i]) - fp);
	}
	if(m_qsize == 0) return v; // 3-dimensional mesh
	return 0.5 * v; // 4-dimensional mesh
}

TwoVector4 Mesh::getFaceDualVector(const uint f, ddouble c) const
{
	if(m_bsize == 0) return getFaceVector(f).dual().unit(); // 2-dimensional mesh

	ddouble cc;
	if(m_qsize == 0) { cc = 1.0; c /= 10.0; }
	else { cc = 0.5; c /= 24.0; }

	TwoVector4 v(0,0,0,0,0,0);
	const Vector4 p = getFacePosition(f);
	const Buffer<uint> &b = getFaceBodies(f);
	for(uint i=0; i<b.size(); i++)
	{
		const Vector4 r = getBodyPosition(b[i]) - p;
		v += (cc + c * r.lensq()) * getBodyIncidence(b[i], f) * TwoVector4(getBodyDualVector(b[i]), r);
	}
	return v;
}

Vector4 Mesh::getBodyDualVector(const uint b) const
{
	if(m_qsize == 0) return -getBodyVector(b).unit(); // 3-dimensional mesh

	// 4-dimensional mesh
	Vector4 v(0,0,0,0);
	const Vector4 bp = getBodyPosition(b);
	const Buffer<uint> &q = getBodyQuads(b);
	for(uint i=0; i<q.size(); i++)
	{
		v += getQuadIncidence(q[i], b) * (bp - getQuadPosition(q[i]));
	}
	return v;
}

Vector4 Mesh::getBodyDualVector(const uint b, ddouble c) const
{
	if(m_qsize == 0) return -getBodyVector(b).unit(); // 3-dimensional mesh

	// 4-dimensional mesh
	c /= 12.0;
	Vector4 v(0,0,0,0);
	const Vector4 p = getBodyPosition(b);
	const Buffer<uint> &q = getBodyQuads(b);
	for(uint i=0; i<q.size(); i++)
	{
		const Vector4 r = p - getQuadPosition(q[i]);
		v += (1.0 + c * r.lensq()) * getQuadIncidence(q[i], b) * r;
	}
	return v;
}

ddouble Mesh::getNodeHodge(const uint n) const
{
	return getNodeDualVector(n);
}

ddouble Mesh::getEdgeHodge(const uint e) const
{
	const Vector4 ev = getEdgeVector(e);
	const Vector4 edv = getEdgeDualVector(e);
	return ev.dot(edv) / ev.lensq();
}

ddouble Mesh::getFaceHodge(const uint f) const
{
	const TwoVector4 fv = getFaceVector(f);
	if(m_bsize == 0) return 1.0 / fv.len(); // 2-dimensional mesh

	const TwoVector4 fdv = getFaceDualVector(f);
	return fv.wedge(fdv) / fv.lensq();
}

ddouble Mesh::getBodyHodge(const uint b) const
{
	const Vector4 bv = getBodyVector(b);
	if(m_qsize == 0) return 1.0 / bv.len(); // 3-dimensional mesh

	const Vector4 bdv = getBodyDualVector(b);
	return -(bv.dot(bdv) / bv.lensq());
}

ddouble Mesh::getQuadHodge(const uint q) const
{
	return 1.0 / getQuadVector(q);
}

ddouble Mesh::getEdgeIncidence(const uint e, const uint n) const
{
	const Buffer<uint> &en = getEdgeNodes(e);
	if(n == en[0]) return -1.0;
	if(n == en[1]) return 1.0;
	return 0.0;
}

void Mesh::orderFaceEdges(const uint f) // ensure the circular order of edges
{
	uint i, j;
	Buffer<uint> &e = m_f[f].e;
	for(i=e.size(); i-->2; )
	{
		const uint ej = e[i-1];
		if(getEdgeIntersection(e[i], ej) != NONE) continue;

		for(j=i-2; j>0 && getEdgeIntersection(e[i], e[j]) == NONE; j--);
		e[i-1] = e[j];
		e[j] = ej;
	}

	for(i=0; i<e.size(); i++)
	{
		const uint j = (i > 0 ? i : e.size()) - 1;
		if(getEdgeIntersection(e[j], e[i]) == NONE) std::cout << "outous " << i << std::endl;
	}
}

ddouble Mesh::getFaceIncidence(const uint f, const uint e) const
{
	const Buffer<uint> &fe = getFaceEdges(f);
	if(e == fe[0])
	{
		const uint n = getEdgeNodes(e)[0];
		const Buffer<uint> &en = getEdgeNodes(fe[1]);
		if(n == en[0] || n == en[1]) return -1.0;
		return 1.0;
	}
	for(uint i=1; i<fe.size(); i++)
	{
		if(e == fe[i])
		{
			const uint n = getEdgeNodes(e)[0];
			const Buffer<uint> &en = getEdgeNodes(fe[i - 1]);
			if(n == en[0] || n == en[1]) return 1.0;
			return -1.0;
		}
	}
	return 0.0;
}

void Mesh::orderBodyFaces(const uint b) // ensure the circular order of edges
{
	Buffer<uint> &f = m_b[b].f;

	uint i, j;
	uint level0 = 0;
	uint level1 = 1;
	uint level2 = f.size();
	for(i=level1; i+1<f.size(); )
	{
		const uint fi = f[i];
		for(j=level0; j<level1 && getFaceIntersection(fi,f[j])==NONE; j++);
		if(j < level1) ++i; // contact found
		else // contact not found -> put f[i] to the back
		{
			f[i] = f[--level2];
			f[level2] = fi;
		}
		if(i == level2) // next level
		{
			level0 = level1;
			level1 = level2;
			level2 = f.size();
		}
	}
}

ddouble Mesh::getBodyIncidence(const uint b, const uint f) const
{
	const Buffer<uint> &bf = getBodyFaces(b);

	// is f the first face in the list?
	if(f == bf[0]) return 1.0;

	// find f from the list
	uint i = 1;
	while(f != bf[i]) { if(++i >= bf.size()) return 0.0; }

	// find the incidence recursively
	ddouble res = 1.0;
	for(uint j=0; j<i; )
	{
		const uint e = getCommon(getFaceEdges(bf[i]), getFaceEdges(bf[j]));
		if(e == NONE) { ++j; continue; }

		res *= -getFaceIncidence(bf[i], e) * getFaceIncidence(bf[j], e);
		if(j == 0) return res;
		i = j;
		j = 0;
	}
	return 0.0;
}

ddouble Mesh::getQuadIncidence(const uint q, const uint b) const
{
	const Buffer<uint> &vb = getQuadBodies(q);
	for(uint i=0; i<vb.size(); i++)
	{
		if(b == vb[i])
		{
			const Vector4 d = getQuadAverage(q) - getBodyAverage(b);
			return (d.dot(getBodyVector(b)) > 0.0 ? 1.0 : -1.0);
		}
	}
	return 0.0;
}

uint Mesh::findNodeAt(const Vector4 &p, const ddouble rsq, uint curr) const
{
	if(m_nsize == 0) return NONE;

	// check starter node
	if(curr >= m_nsize) curr = 0;

	// travel and find the nearest node
	uint i;
	ddouble currsq = (getNodePosition(curr) - p).lensq();
	while(true)
	{
		const uint prev = curr;
		const Buffer<uint> &e = getNodeEdges(prev);
		for(i=0; i<e.size(); i++)
		{
			const uint next = getEdgeOtherNode(e[i], prev);
			const ddouble nextsq = (getNodePosition(next) - p).lensq();
			if(nextsq < currsq)
			{
				curr = next;
				currsq = nextsq;
				if(currsq < rsq) return curr;
			}
		}
		if(prev == curr) break;
	}

	// not found by travel -> search through all
	for(i=0; i<m_nsize; i++)
	{
		if((getNodePosition(i) - p).lensq() < rsq) return i;
	}
	return NONE;
}

void Mesh::transform(const Matrix4 &mat)
{
	for(uint i=0; i<m_nsize; i++)
	{
		setNodePosition(i, mat * getNodePosition(i));
	}
	//getMetric() *= (mat * mat.transpose()).getSymmetric().inverse();
}

void Mesh::move(const Vector4 &vec)
{
	for(uint i=0; i<m_nsize; i++)
	{
		setNodePosition(i, vec + getNodePosition(i));
	}
}

void Mesh::resizeNodeBuffer(const uint size)
{
	if(size == m_n.size()) return;
	m_p.resize(m_dim * size);
	const uint minsize = size < m_n.size() ? size : m_n.size();
	if(minsize == 0)
	{
		m_n.resize(size);
		return;
	}

	// resize buffer keeping the old sub-buffers
	uint i;
	Buffer<uint> *e = new Buffer<uint>[minsize];
	for(i=0; i<minsize; i++) m_n[i].e.swap(e[i]);
	m_n.resize(size);
	for(i=0; i<minsize; i++) m_n[i].e.swap(e[i]);
	delete[] e;
}

void Mesh::resizeEdgeBuffer(const uint size)
{
	if(size == m_e.size()) return;
	const uint minsize = size < m_e.size() ? size : m_e.size();
	if(minsize == 0)
	{
		m_e.resize(size);
		return;
	}

	// resize buffer keeping the old sub-buffers
	uint i;
	Buffer<uint> *n = new Buffer<uint>[minsize];
	Buffer<uint> *f = new Buffer<uint>[minsize];
	for(i=0; i<minsize; i++) { m_e[i].n.swap(n[i]); m_e[i].f.swap(f[i]); }
	m_e.resize(size);
	for(i=0; i<minsize; i++) { m_e[i].n.swap(n[i]); m_e[i].f.swap(f[i]); }
	delete[] n;
	delete[] f;
}

void Mesh::resizeFaceBuffer(const uint size)
{
	if(size == m_f.size()) return;
	const uint minsize = size < m_f.size() ? size : m_f.size();
	if(minsize == 0)
	{
		m_f.resize(size);
		return;
	}

	// resize buffer keeping the old sub-buffers
	uint i;
	Buffer<uint> *e = new Buffer<uint>[minsize];
	Buffer<uint> *b = new Buffer<uint>[minsize];
	for(i=0; i<minsize; i++) { m_f[i].e.swap(e[i]); m_f[i].b.swap(b[i]); }
	m_f.resize(size);
	for(i=0; i<minsize; i++) { m_f[i].e.swap(e[i]); m_f[i].b.swap(b[i]); }
	delete[] e;
	delete[] b;
}

void Mesh::resizeBodyBuffer(const uint size)
{
	if(size == m_b.size()) return;
	const uint minsize = size < m_b.size() ? size : m_b.size();
	if(minsize == 0)
	{
		m_b.resize(size);
		return;
	}

	// resize buffer keeping the old sub-buffers
	uint i;
	Buffer<uint> *f = new Buffer<uint>[minsize];
	Buffer<uint> *q = new Buffer<uint>[minsize];
	for(i=0; i<minsize; i++) { m_b[i].f.swap(f[i]); m_b[i].q.swap(q[i]); }
	m_b.resize(size);
	for(i=0; i<minsize; i++) { m_b[i].f.swap(f[i]); m_b[i].q.swap(q[i]); }
	delete[] f;
	delete[] q;
}

void Mesh::resizeQuadBuffer(const uint size)
{
	if(size == m_q.size()) return;
	const uint minsize = size < m_q.size() ? size : m_q.size();
	if(minsize == 0)
	{
		m_q.resize(size);
		return;
	}

	// resize buffer keeping the old sub-buffers
	uint i;
	Buffer<uint> *b = new Buffer<uint>[minsize];
	for(i=0; i<minsize; i++) m_q[i].b.swap(b[i]);
	m_q.resize(size);
	for(i=0; i<minsize; i++) m_q[i].b.swap(b[i]);
	delete[] b;
}

uint Mesh::getCommon(const Buffer<uint> &a, const Buffer<uint> &b) const
{
	for(uint i=0; i<a.size(); i++)
	{
		for(uint j=0; j<b.size(); j++)
		{
			if(a[i] == b[j]) return a[i];
		}
	}
	return NONE;
}
