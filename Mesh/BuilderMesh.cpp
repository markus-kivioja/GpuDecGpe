#include "BuilderMesh.hpp"
#include <iostream>

BuilderMesh::BuilderMesh(const uint dim)
: Mesh(dim)
{
	m_dns = 0;
	m_des = 0;
	m_dfs = 0;
	m_dbs = 0;
	m_dqs = 0;
}

void BuilderMesh::clear()
{
	Mesh::clear();

	m_dns = 0;
	m_dn.clear();
	m_des = 0;
	m_de.clear();
	m_dfs = 0;
	m_df.clear();
	m_dbs = 0;
	m_db.clear();
	m_dqs = 0;
	m_dq.clear();
}

void BuilderMesh::createCopy(const Mesh &mesh)
{
	clear();
	combine(mesh);
/*	uint i;

	const uint nsize = mesh.getNodeSize();
	resizeNodeBuffer(nsize);
	for(i=0; i<nsize; i++)
	{
		const uint n = addNode(mesh.getNodePosition(i));
		setNodeWeight(n, mesh.getNodeWeight(i));
		setNodeFlag(n, mesh.getNodeFlag(i));
	}
	const uint esize = mesh.getEdgeSize();
	resizeEdgeBuffer(esize);
	for(i=0; i<esize; i++)
	{
		const uint e = addEdge(mesh.getEdgeNodes(i)[0], mesh.getEdgeNodes(i)[1]);
		setEdgeFlag(e, mesh.getEdgeFlag(i));
	}
	const uint fsize = mesh.getFaceSize();
	resizeFaceBuffer(fsize);
	for(i=0; i<fsize; i++)
	{
		const uint f = addFace(mesh.getFaceEdges(i));
		setFaceFlag(f, mesh.getFaceFlag(i));
	}
	const uint bsize = mesh.getBodySize();
	resizeBodyBuffer(bsize);
	for(i=0; i<bsize; i++)
	{
		const uint b = addBody(mesh.getBodyFaces(i));
		setBodyFlag(b, mesh.getBodyFlag(i));
	}
	const uint qsize = mesh.getQuadSize();
	resizeQuadBuffer(qsize);
	for(i=0; i<qsize; i++)
	{
		const uint q = addQuad(mesh.getQuadBodies(i));
		setQuadFlag(q, mesh.getQuadFlag(i));
	}
*/}

void BuilderMesh::createGrid(const Vector4 &minp, const Vector4 &maxp, const ddouble h)
{
	clear();
	const Vector4 d = maxp - minp;
	const uint nx = uint(fabs(d.x) / h + 0.5);
	const uint ny = uint(fabs(d.y) / h + 0.5);
	const uint nz = uint(fabs(d.z) / h + 0.5);
	const uint nt = uint(fabs(d.t) / h + 0.5);
	addNode(minp);
	if(nx > 0) stretchLinear(Vector4(d.x,0,0,0), nx, 0, 0);
	if(ny > 0) stretchLinear(Vector4(0,d.y,0,0), ny, 0, 0);
	if(nz > 0) stretchLinear(Vector4(0,0,d.z,0), nz, 0, 0);
	if(nt > 0) stretchLinear(Vector4(0,0,0,d.t), nt, 0, 0);
}

void BuilderMesh::createTriangleGrid(const Vector2 &minp, const Vector2 &maxp, const ddouble h, const bool rect)
{
	clear();
	Vector2 d = maxp - minp;
	const uint xsize = uint(fabs(d.x) / h + 0.5);
	if(xsize == 0) return createGrid(Vector4(minp.x,minp.y,0,0), Vector4(minp.x,maxp.y,0,0), sqrt(0.75)*h);
	const uint ysize = uint(fabs(d.y) / (sqrt(0.75) * h) + 0.5);
	const uint xmax = xsize + 1;
	const uint ymax = ysize + 1;

	resizeNodeBuffer((2 * xmax + 1) * ymax / 2);
	resizeEdgeBuffer((xsize + xmax) * ymax / 2 + 2 * xmax * ysize);
	resizeFaceBuffer((xsize + xmax) * ysize);

	// create nodes
	uint xi, yi, i, j;
	for(yi=0; yi<=ysize; yi++)
	{
		const uint pair = (yi % 2);
		const ddouble py = minp.y + yi * d.y / ddouble(ysize);
		if(pair == 1)
		{
			addNode(Vector4((rect ? minp.x : minp.x - 0.5 * d.x / ddouble(xsize)),py,0,0));
		}
		for(xi=0; xi<=xsize; xi++)
		{
			addNode(Vector4(minp.x + (rect && xi == xsize ? xi : xi + 0.5 * pair) * d.x / ddouble(xsize),py,0,0));
		}
	}

	// create x-edges
	i = 0;
	for(yi=0; yi<=ysize; yi++)
	{
		const uint pair = (yi % 2);
		i++;
		for(xi=1-pair; xi<=xsize; xi++)
		{
			addEdge(i, i-1);
			i++;
		}
	}

	// create y-edges
	i = xmax;
	for(yi=1; yi<=ysize; yi++)
	{
		const uint pair = (yi % 2);
		if(pair == 1) i++;
		for(xi=0; xi<=xsize; xi++)
		{
			// create y-edges
			addEdge(i-pair, i-xmax-1);
			addEdge(i, i-xmax-pair);
			i++;
		}
	}

	// create faces
	i = xsize;
	j = (xsize + xmax) * ymax / 2;
	for(yi=1; yi<=ysize; yi++)
	{
		const uint pair = (yi % 2);
		if(pair > 0) i++;
		for(xi=0; xi<=xsize; xi++)
		{
			Buffer<uint> e(3);
			e[0] = j;
			if(xi > 0)
			{
				e[1] = j-1;
				e[2] = i-pair*xmax;
				addFace(e);
				i++;
			}
			e[1] = j+1;
			e[2] = i-xmax+pair*(xmax-1);
			addFace(e);
			j += 2;
		}
	}
}

bool BuilderMesh::createRepeated(const Mesh &mesh, const Vector4 &pos, const Vector4 &dir, const uint steps)
{
	uint i, j, k;
	const ddouble dirsq = dir.lensq();

	// find a slot for each existing cell
	const uint qsize = mesh.getQuadSize();
	Buffer<uint> qslot(qsize);
	Buffer<uint> qind(qsize);
	Buffer<uint> qs(5, 0);
	for(i=0; i<qsize; i++)
	{
		const Vector4 p = mesh.getQuadAverage(i) - pos;
		const ddouble dot = p.dot(dir);
		if(dot < 0.0) qslot[i] = 0;
		else if(dot < dirsq) qslot[i] = 2;
		else qslot[i] = 4;
		qind[i] = qs[qslot[i]]++;
	}
	if(qs[1] != qs[3]) return false;
	const uint bsize = mesh.getBodySize();
	Buffer<uint> bslot(bsize);
	Buffer<uint> bind(bsize);
	Buffer<uint> bs(5, 0);
	for(i=0; i<bsize; i++)
	{
		const Buffer<uint> &par = mesh.getBodyQuads(i);
		if(par.empty())
		{
			const Vector4 p = mesh.getBodyAverage(i) - pos;
			const ddouble dot = p.dot(dir);
			if(dot < 0.0) bslot[i] = 0;
			else if(dot < dirsq) bslot[i] = 2;
			else bslot[i] = 4;
		}
		else
		{
			bslot[i] = qslot[par[0]];
			for(j=1; j<par.size(); j++)
			{
				const uint jslot = qslot[par[j]];
				if(jslot != bslot[i]) bslot[i] = 2 * uint((bslot[i] + jslot) / 4) + 1;
			}
		}
		bind[i] = bs[bslot[i]]++;
	}
	if(bs[1] != bs[3]) return false;
	const uint fsize = mesh.getFaceSize();
	Buffer<uint> fslot(fsize);
	Buffer<uint> find(fsize);
	Buffer<uint> fs(5, 0);
	for(i=0; i<fsize; i++)
	{
		const Buffer<uint> &par = mesh.getFaceBodies(i);
		if(par.empty())
		{
			const Vector4 p = mesh.getFaceAverage(i) - pos;
			const ddouble dot = p.dot(dir);
			if(dot < 0.0) fslot[i] = 0;
			else if(dot < dirsq) fslot[i] = 2;
			else fslot[i] = 4;
		}
		else
		{
			fslot[i] = bslot[par[0]];
			for(j=1; j<par.size(); j++)
			{
				const uint jslot = bslot[par[j]];
				if(jslot != fslot[i]) fslot[i] = 2 * uint((fslot[i] + jslot) / 4) + 1;
			}
		}
		find[i] = fs[fslot[i]]++;
	}
	if(fs[1] != fs[3]) return false;
	const uint esize = mesh.getEdgeSize();
	Buffer<uint> eslot(esize);
	Buffer<uint> eind(esize);
	Buffer<uint> es(5, 0);
	for(i=0; i<esize; i++)
	{
		const Buffer<uint> &par = mesh.getEdgeFaces(i);
		if(par.empty())
		{
			const Vector4 p = mesh.getEdgeAverage(i) - pos;
			const ddouble dot = p.dot(dir);
			if(dot < 0.0) eslot[i] = 0;
			else if(dot < dirsq) eslot[i] = 2;
			else eslot[i] = 4;
		}
		else
		{
			eslot[i] = fslot[par[0]];
			for(j=1; j<par.size(); j++)
			{
				const uint jslot = fslot[par[j]];
				if(jslot != eslot[i]) eslot[i] = 2 * uint((eslot[i] + jslot) / 4) + 1;
			}
		}
		eind[i] = es[eslot[i]]++;
	}
	if(es[1] != es[3]) return false;
	const uint nsize = mesh.getNodeSize();
	Buffer<uint> nslot(nsize);
	Buffer<uint> nind(nsize);
	Buffer<uint> ns(5, 0);
	for(i=0; i<nsize; i++)
	{
		const Buffer<uint> &par = mesh.getNodeEdges(i);
		if(par.empty())
		{
			const Vector4 p = getNodePosition(i) - pos;
			const ddouble dot = p.dot(dir);
			if(dot < 0.0) nslot[i] = 0;
			else if(dot < dirsq) nslot[i] = 2;
			else nslot[i] = 4;
		}
		else
		{
			nslot[i] = eslot[par[0]];
			for(j=1; j<par.size(); j++)
			{
				const uint jslot = eslot[par[j]];
				if(jslot != nslot[i]) nslot[i] = 2 * uint((nslot[i] + jslot) / 4) + 1;
			}
		}
		nind[i] = ns[nslot[i]]++;
	}
	if(ns[1] != ns[3]) return false;

	// re-organize slot[3] to have matching cells with slot[1]
	uint node = 0;
	Buffer<uint> nmatch(ns[1]);
	for(i=0; i<nsize; i++)
	{
		if(nslot[i] != 1) continue;
		node = mesh.findNodeAt(mesh.getNodePosition(i) + dir, 1e-13, node);
		if(node == NONE || nslot[node] != 3) return false;
		nind[node] = nind[i];
		nmatch[nind[i]] = node;
	}
	Buffer<uint> ematch(es[1]);
	for(i=0; i<esize; i++)
	{
		if(eslot[i] != 1) continue;
		const Vector4 p = mesh.getEdgeAverage(i) + dir;
		const Buffer<uint> &par = mesh.getNodeEdges(nmatch[nind[mesh.getEdgeNodes(i)[0]]]);
		for(j=0; j<par.size(); j++)
		{
			if(eslot[par[j]] != 3) continue;
			if((mesh.getEdgeAverage(par[j]) - p).lensq() < 1e-13) break;
		}
		if(j == par.size()) return false;
		eind[par[j]] = eind[i];
		ematch[eind[i]] = par[j];
	}
	nmatch.clear();
	Buffer<uint> fmatch(fs[1]);
	for(i=0; i<fsize; i++)
	{
		if(fslot[i] != 1) continue;
		const Vector4 p = mesh.getFaceAverage(i) + dir;
		const Buffer<uint> &par = mesh.getEdgeFaces(ematch[eind[mesh.getFaceEdges(i)[0]]]);
		for(j=0; j<par.size(); j++)
		{
			if(fslot[par[j]] != 3) continue;
			if((mesh.getFaceAverage(par[j]) - p).lensq() < 1e-13) break;
		}
		if(j == par.size()) return false;
		find[par[j]] = find[i];
		fmatch[find[i]] = par[j];
	}
	ematch.clear();
	for(i=0; i<bsize; i++)
	{
		if(bslot[i] != 1) continue;
		const Vector4 p = mesh.getBodyAverage(i) + dir;
		const Buffer<uint> &par = mesh.getFaceBodies(fmatch[find[mesh.getBodyFaces(i)[0]]]);
		for(j=0; j<par.size(); j++)
		{
			if(bslot[par[j]] != 3) continue;
			if((mesh.getBodyAverage(par[j]) - p).lensq() < 1e-13) break;
		}
		if(j == par.size()) return false;
		bind[par[j]] = bind[i];
	}
	fmatch.clear();

	// create mesh
	clear();
	const uint nstep = ns[1] + ns[2];
	const uint estep = es[1] + es[2];
	const uint fstep = fs[1] + fs[2];
	const uint bstep = bs[1] + bs[2];
	const uint qstep = qs[1] + qs[2];
	Buffer<uint> nbeg(5, 0);
	Buffer<uint> ebeg(5, 0);
	Buffer<uint> fbeg(5, 0);
	Buffer<uint> bbeg(5, 0);
	Buffer<uint> qbeg(5, 0);
	for(i=1; i<5; i++)
	{
		nbeg[i] = nbeg[i-1] + ns[i-1];
		ebeg[i] = ebeg[i-1] + es[i-1];
		fbeg[i] = fbeg[i-1] + fs[i-1];
		bbeg[i] = bbeg[i-1] + bs[i-1];
		qbeg[i] = qbeg[i-1] + qs[i-1];
	}

	// create nodes
	m_nsize = nsize + steps * nstep;
	resizeNodeBuffer(m_nsize);
	for(i=0; i<nsize; i++)
	{
		uint ii = nbeg[nslot[i]] + nind[i];
		if(nslot[i] == 0)
		{
			setNodePosition(ii, mesh.getNodePosition(i));
			setNodeWeight(ii, mesh.getNodeWeight(i));
			setNodeFlag(ii, mesh.getNodeFlag(i));
		}
		else if(nslot[i] <= 2)
		{
			for(j=0; j<=steps; j++)
			{
				setNodePosition(ii, mesh.getNodePosition(i) + j * dir);
				setNodeWeight(ii, mesh.getNodeWeight(i));
				setNodeFlag(ii, mesh.getNodeFlag(i));
				ii += nstep;
			}
		}
		else
		{
			ii += steps * nstep;
			setNodePosition(ii, mesh.getNodePosition(i) + steps * dir);
			setNodeWeight(ii, mesh.getNodeWeight(i));
			setNodeFlag(ii, mesh.getNodeFlag(i));
		}
	}

	// create edges
	m_esize = esize + steps * estep;
	resizeEdgeBuffer(m_esize);
	for(i=0; i<esize; i++)
	{
		uint ii = ebeg[eslot[i]] + eind[i];
		Buffer<uint> en = mesh.getEdgeNodes(i);
		for(k=0; k<en.size(); k++) en[k] = nbeg[nslot[en[k]]] + nind[en[k]];

		if(eslot[i] == 0)
		{
			m_e[ii].n = en;
			for(k=0; k<en.size(); k++) m_n[en[k]].e.push_back(ii);
			setEdgeFlag(ii, mesh.getEdgeFlag(i));
		}
		else if(eslot[i] <= 2)
		{
			for(j=0; j<=steps; j++)
			{
				m_e[ii].n = en;
				for(k=0; k<en.size(); k++) m_n[en[k]].e.push_back(ii);
				setEdgeFlag(ii, mesh.getEdgeFlag(i));
				for(k=0; k<en.size(); k++) en[k] += nstep;
				ii += estep;
			}
		}
		else
		{
			ii += steps * estep;
			for(k=0; k<en.size(); k++) en[k] += steps * nstep;
			m_e[ii].n = en;
			for(k=0; k<en.size(); k++) m_n[en[k]].e.push_back(ii);
			setEdgeFlag(ii, mesh.getEdgeFlag(i));
		}
	}

	// create faces
	m_fsize = fsize + steps * fstep;
	resizeFaceBuffer(m_fsize);
	for(i=0; i<fsize; i++)
	{
		uint ii = fbeg[fslot[i]] + find[i];
		Buffer<uint> fe = mesh.getFaceEdges(i);
		for(j=0; j<fe.size(); j++) fe[j] = ebeg[eslot[fe[j]]] + eind[fe[j]];

		if(fslot[i] == 0)
		{
			m_f[ii].e = fe;
			for(k=0; k<fe.size(); k++) m_e[fe[k]].f.push_back(ii);
			setFaceFlag(ii, mesh.getFaceFlag(i));
		}
		else if(fslot[i] <= 2)
		{
			for(j=0; j<=steps; j++)
			{
				m_f[ii].e = fe;
				for(k=0; k<fe.size(); k++) m_e[fe[k]].f.push_back(ii);
				setFaceFlag(ii, mesh.getFaceFlag(i));
				for(k=0; k<fe.size(); k++) fe[k] += estep;
				ii += fstep;
			}
		}
		else
		{
			ii += steps * fstep;
			for(k=0; k<fe.size(); k++) fe[k] += steps * estep;
			m_f[ii].e = fe;
			for(k=0; k<fe.size(); k++) m_e[fe[k]].f.push_back(ii);
			setFaceFlag(ii, mesh.getFaceFlag(i));
		}
	}

	// create bodies
	m_bsize = bsize + steps * bstep;
	resizeBodyBuffer(m_bsize);
	for(i=0; i<bsize; i++)
	{
		uint ii = bbeg[bslot[i]] + bind[i];
		Buffer<uint> bf = mesh.getBodyFaces(i);
		for(k=0; k<bf.size(); k++) bf[k] = fbeg[fslot[bf[k]]] + find[bf[k]];

		if(bslot[i] == 0)
		{
			m_b[ii].f = bf;
			for(k=0; k<bf.size(); k++) m_f[bf[k]].b.push_back(ii);
			setBodyFlag(ii, mesh.getBodyFlag(i));
		}
		else if(bslot[i] <= 2)
		{
			for(j=0; j<=steps; j++)
			{
				m_b[ii].f = bf;
				for(k=0; k<bf.size(); k++) m_f[bf[k]].b.push_back(ii);
				setBodyFlag(ii, mesh.getBodyFlag(i));
				for(k=0; k<bf.size(); k++) bf[k] += fstep;
				ii += bstep;
			}
		}
		else
		{
			ii += steps * bstep;
			for(k=0; k<bf.size(); k++) bf[k] += steps * fstep;
			m_b[ii].f = bf;
			for(k=0; k<bf.size(); k++) m_f[bf[k]].b.push_back(ii);
			setBodyFlag(ii, mesh.getBodyFlag(i));
		}
	}

	// create quads
	m_qsize = qsize + steps * qstep;
	resizeQuadBuffer(m_qsize);
	for(i=0; i<qsize; i++)
	{
		uint ii = qbeg[qslot[i]] + qind[i];
		Buffer<uint> qb = mesh.getQuadBodies(i);
		for(k=0; k<qb.size(); k++) qb[k] = bbeg[bslot[qb[k]]] + bind[qb[k]];

		if(qslot[i] == 0)
		{
			m_q[ii].b = qb;
			for(k=0; k<qb.size(); k++) m_b[qb[k]].q.push_back(ii);
			setQuadFlag(ii, mesh.getQuadFlag(i));
		}
		else if(qslot[i] <= 2)
		{
			for(j=0; j<=steps; j++)
			{
				m_q[ii].b = qb;
				for(k=0; k<qb.size(); k++) m_b[qb[k]].q.push_back(ii);
				setQuadFlag(ii, mesh.getQuadFlag(i));
				for(k=0; k<qb.size(); k++) qb[k] += bstep;
				ii += qstep;
			}
		}
		else
		{
			ii += steps * qstep;
			for(k=0; k<qb.size(); k++) qb[k] += steps * bstep;
			m_q[ii].b = qb;
			for(k=0; k<qb.size(); k++) m_b[qb[k]].q.push_back(ii);
			setQuadFlag(ii, mesh.getQuadFlag(i));
		}
	}
	return true;
}

void BuilderMesh::createIntersection(const Mesh &mesh, const Vector4 &v, const ddouble dot)
{
	uint i, j;
	clear();

	// calculate side (of the plane) for each node
	Buffer<bool> nside(mesh.getNodeSize());
	for(i=0; i<nside.size(); i++)
	{
		nside[i] = (v.dot(mesh.getNodePosition(i)) > dot);
	}

	// find edges which are intersect by the plane
	uint esize = 0;
	Buffer<uint> e(mesh.getEdgeSize());
	Buffer<uint> enew(e.size(), NONE);
	for(i=0; i<e.size(); i++)
	{
		const Buffer<uint> &en = mesh.getEdgeNodes(i);
		if(nside[en[0]] != nside[en[1]])
		{
			enew[i] = esize;
			e[esize++] = i;
		}
	}

	// add nodes at intersections of each edge and the plane
	resizeNodeBuffer(esize);
	for(i=0; i<esize; i++)
	{
		const Buffer<uint> &en = mesh.getEdgeNodes(e[i]);
		Vector4 p = mesh.getNodePosition(en[0]);
		const Vector4 d = mesh.getNodePosition(en[1]) - p;
		const ddouble pdotv = dot - p.dot(v);
		const ddouble ddotv = d.dot(v);
		if(pdotv * ddotv >= ddotv * ddotv) p += d;
		else if(pdotv * ddotv > 0.0) p += (dot - p.dot(v)) / ddotv * d;
		setNodeFlag(addNode(p), mesh.getEdgeFlag(e[i]));
	}

	// find faces which are intersect by the plane
	uint fsize = 0;
	Buffer<uint> f(mesh.getFaceSize());
	Buffer<uint> fnew(f.size(), NONE);
	for(i=0; i<f.size(); i++)
	{
		const Buffer<uint> &fe = mesh.getFaceEdges(i);
		for(j=0; j<fe.size(); j++)
		{
			if(enew[fe[j]] != NONE)
			{
				fnew[i] = fsize;
				f[fsize++] = i;
				break;
			}
		}
	}

	// add edges
	resizeEdgeBuffer(fsize);
	for(i=0; i<fsize; i++)
	{
		const Buffer<uint> &fe = mesh.getFaceEdges(f[i]);
		uint ens = 0;
		Buffer<uint> en(fe.size());
		for(j=0; j<fe.size(); j++)
		{
			if(enew[fe[j]] != NONE) en[ens++] = enew[fe[j]];
		}
		setEdgeFlag(addEdge(en[0], en[1]), mesh.getFaceFlag(f[i]));
	}

	// find bodies which are intersect by the plane
	uint bsize = 0;
	Buffer<uint> b(mesh.getBodySize());
	Buffer<uint> bnew(b.size(), NONE);
	for(i=0; i<b.size(); i++)
	{
		const Buffer<uint> &bf = mesh.getBodyFaces(i);
		for(j=0; j<bf.size(); j++)
		{
			if(fnew[bf[j]] != NONE)
			{
				bnew[i] = bsize;
				b[bsize++] = i;
				break;
			}
		}
	}

	// add faces
	resizeFaceBuffer(bsize);
	for(i=0; i<bsize; i++)
	{
		const Buffer<uint> &bf = mesh.getBodyFaces(b[i]);
		uint fes = 0;
		Buffer<uint> fe(bf.size());
		for(j=0; j<bf.size(); j++)
		{
			if(fnew[bf[j]] != NONE) fe[fes++] = fnew[bf[j]];
		}
		fe.resize(fes);
		setFaceFlag(addFace(fe), mesh.getBodyFlag(b[i]));
	}

	// find quads which are intersect by the plane
	uint qsize = 0;
	Buffer<uint> q(mesh.getQuadSize());
	for(i=0; i<q.size(); i++)
	{
		const Buffer<uint> &qb = mesh.getQuadBodies(i);
		for(j=0; j<qb.size(); j++)
		{
			if(bnew[qb[j]] != NONE)
			{
				q[qsize++] = i;
				break;
			}
		}
	}

	// add bodies
	resizeBodyBuffer(qsize);
	for(i=0; i<qsize; i++)
	{
		const Buffer<uint> &qb = mesh.getQuadBodies(q[i]);
		uint bfs = 0;
		Buffer<uint> bf(qb.size());
		for(j=0; j<qb.size(); j++)
		{
			if(bnew[qb[j]] != NONE) bf[bfs++] = bnew[qb[j]];
		}
		bf.resize(bfs);
		setBodyFlag(addBody(bf), mesh.getQuadFlag(q[i]));
	}
}

uint BuilderMesh::addNode(const Vector4 &p)
{
	// use detached slot if possible
	uint res;
	if(m_dns > 0) res = m_dn[--m_dns];
	else
	{
		// check if m_n is full -> resize the table
		res = m_nsize++;
		if(m_nsize > m_n.size()) resizeNodeBuffer(2 * m_nsize);
	}

	// create new node
	setNodePosition(res, p);
	return res;
}

uint BuilderMesh::addEdge(const uint n0, const uint n1)
{
	uint i;

	// check if edge already exists
	const Buffer<uint> &e = getNodeEdges(n0);
	for(i=0; i<e.size(); i++)
	{
		const Buffer<uint> &n = getEdgeNodes(e[i]);
		if(n[0] == n0 && n[1] == n1) return e[i];
		if(n[1] == n0 && n[0] == n1) return e[i];
	}

	// use detached slot if possible
	uint res;
	if(m_des > 0) res = m_de[--m_des];
	else
	{
		// check if m_e is full -> resize the table
		res = m_esize++;
		if(m_esize > m_e.size()) resizeEdgeBuffer(2 * m_esize);
	}

	// create new edge
	m_e[res].n.resize(2);
	m_e[res].n[0] = n0;
	m_e[res].n[1] = n1;
	m_n[n0].e.push_back(res);
	m_n[n1].e.push_back(res);
	return res;
}

uint BuilderMesh::addFace(const Buffer<uint> &e)
{
	uint i;

	// check if face already exists
	const Buffer<uint> &f = getEdgeFaces(e[0]);
	for(i=0; i<f.size(); i++)
	{
		if(e.isAnagram(getFaceEdges(f[i]))) return f[i];
	}

	// use detached slot if possible
	uint res;
	if(m_dfs > 0) res = m_df[--m_dfs];
	else
	{
		// check if m_f is full -> resize the table
		res = m_fsize++;
		if(m_fsize > m_f.size()) resizeFaceBuffer(2 * m_fsize);
	}

	// create new face
	m_f[res].e = e;
	for(i=0; i<e.size(); i++) m_e[e[i]].f.push_back(res);
	orderFaceEdges(res);
	return res;
}

uint BuilderMesh::addBody(const Buffer<uint> &f)
{
	uint i;

	// check if body already exists
	const Buffer<uint> &b = getFaceBodies(f[0]);
	for(i=0; i<b.size(); i++)
	{
		if(f.isAnagram(getBodyFaces(b[i]))) return b[i];
	}

	// use detached slot if possible
	uint res;
	if(m_dbs > 0) res = m_db[--m_dbs];
	else
	{
		// check if m_b is full -> resize the table
		res = m_bsize++;
		if(m_bsize > m_b.size()) resizeBodyBuffer(2 * m_bsize);
	}

	// create new body
	m_b[res].f = f;
	for(i=0; i<f.size(); i++) m_f[f[i]].b.push_back(res);
	orderBodyFaces(res);
	return res;
}

uint BuilderMesh::addQuad(const Buffer<uint> &b)
{
	uint i;

	// check if quad already exists
	const Buffer<uint> &q = getBodyQuads(b[0]);
	for(i=0; i<q.size(); i++)
	{
		if(b.isAnagram(getQuadBodies(q[i]))) return q[i];
	}

	// use detached slot if possible
	uint res;
	if(m_dqs > 0) res = m_dq[--m_dqs];
	else
	{
		// check if m_q is full -> resize the table
		res = m_qsize++;
		if(m_qsize > m_q.size()) resizeQuadBuffer(2 * m_qsize);
	}

	// create new quad
	m_q[res].b = b;
	for(i=0; i<b.size(); i++) m_b[b[i]].q.push_back(res);
	return res;
}

void BuilderMesh::removeNode(const uint n)
{
	uint i;

	// remove linked edges
	Buffer<uint> &e = m_n[n].e;
	for(i=e.size(); i-->0; ) removeEdge(e[i]);

	// replace this node by the last one
	--m_nsize;
	if(n != m_nsize)
	{
		setNodePosition(n, getNodePosition(m_nsize));
		setNodeFlag(n, getNodeFlag(m_nsize));
		setNodeFlag(m_nsize, 0);
		setNodeWeight(n, getNodeWeight(m_nsize));
		setNodeWeight(m_nsize, 0.0);

		Buffer<uint> &e = m_n[n].e;
		e.swap(m_n[m_nsize].e);
		for(i=e.size(); i-->0; ) m_e[e[i]].n.replaceFirst(m_nsize, n);
	}
}

void BuilderMesh::removeEdge(const uint e)
{
	uint i;

	// remove linked faces
	Buffer<uint> &f = m_e[e].f;
	for(i=f.size(); i-->0; ) removeFace(f[i]);

	// remove links from nodes
	Buffer<uint> &n = m_e[e].n;
	for(i=n.size(); i-->0; ) m_n[n[i]].e.eraseFirst(e);
	n.clear();

	// replace this edge by the last one
	--m_esize;
	if(e != m_esize)
	{
		setEdgeFlag(e, getEdgeFlag(m_esize));
		setEdgeFlag(m_esize, 0);

		Buffer<uint> &n = m_e[e].n;
		n.swap(m_e[m_esize].n);
		for(i=n.size(); i-->0; ) m_n[n[i]].e.replaceFirst(m_esize, e);

		Buffer<uint> &f = m_e[e].f;
		f.swap(m_e[m_esize].f);
		for(i=f.size(); i-->0; ) m_f[f[i]].e.replaceFirst(m_esize, e);
	}
}

void BuilderMesh::removeFace(const uint f)
{
	uint i;

	// remove linked bodies
	Buffer<uint> &b = m_f[f].b;
	for(i=b.size(); i-->0; ) removeBody(b[i]);

	// remove links from edges
	Buffer<uint> &e = m_f[f].e;
	for(i=e.size(); i-->0; ) m_e[e[i]].f.eraseFirst(f);
	e.clear();

	// replace this face by the last one
	--m_fsize;
	if(f != m_fsize)
	{
		setFaceFlag(f, getFaceFlag(m_fsize));
		setFaceFlag(m_fsize, 0);

		Buffer<uint> &e = m_f[f].e;
		e.swap(m_f[m_fsize].e);
		for(i=e.size(); i-->0; ) m_e[e[i]].f.replaceFirst(m_fsize, f);

		Buffer<uint> &b = m_f[f].b;
		b.swap(m_f[m_fsize].b);
		for(i=b.size(); i-->0; ) m_b[b[i]].f.replaceFirst(m_fsize, f);
	}
}

void BuilderMesh::removeBody(const uint b)
{
	uint i;

	// remove linked quads
	Buffer<uint> &q = m_b[b].q;
	for(i=q.size(); i-->0; ) removeQuad(q[i]);

	// remove links from faces
	Buffer<uint> &f = m_b[b].f;
	for(i=f.size(); i-->0; ) m_f[f[i]].b.eraseFirst(b);
	f.clear();

	// replace this body by the last one
	--m_bsize;
	if(b != m_bsize)
	{
		setBodyFlag(b, getBodyFlag(m_bsize));
		setBodyFlag(m_bsize, 0);

		Buffer<uint> &f = m_b[b].f;
		f.swap(m_b[m_bsize].f);
		for(i=f.size(); i-->0; ) m_f[f[i]].b.replaceFirst(m_bsize, b);

		Buffer<uint> &q = m_b[b].q;
		q.swap(m_b[m_bsize].q);
		for(i=q.size(); i-->0; ) m_q[q[i]].b.replaceFirst(m_bsize, b);
	}
}

void BuilderMesh::removeQuad(const uint q)
{
	uint i;

	// remove links from bodies
	Buffer<uint> &b = m_q[q].b;
	for(i=b.size(); i-->0; ) m_b[b[i]].q.eraseFirst(q);
	b.clear();

	// replace this quad by the last one
	--m_qsize;
	if(q != m_qsize)
	{
		setQuadFlag(q, getQuadFlag(m_qsize));
		setQuadFlag(m_qsize, 0);

		Buffer<uint> &b = m_q[q].b;
		b.swap(m_q[m_qsize].b);
		for(i=b.size(); i-->0; ) m_b[b[i]].q.replaceFirst(m_qsize, q);
	}
}

uint BuilderMesh::detachNode(const uint n)
{
	uint i;
	m_dn.gather(n, m_dns);
	setNodeFlag(n, 0);
	setNodeWeight(n, 0.0);

	// detach linked edges
	Buffer<uint> &e = m_n[n].e;
	for(i=e.size(); i-->0; ) detachEdge(e[i]);

	return n;
}

uint BuilderMesh::detachEdge(const uint e)
{
	uint i;
	m_de.gather(e, m_des);
	setEdgeFlag(e, 0);

	// detach linked faces
	Buffer<uint> &f = m_e[e].f;
	for(i=f.size(); i-->0; ) detachFace(f[i]);

	// remove links from nodes
	Buffer<uint> &n = m_e[e].n;
	for(i=n.size(); i-->0; ) m_n[n[i]].e.eraseFirst(e);
	n.clear();

	return e;
}

uint BuilderMesh::detachFace(const uint f)
{
	uint i;
	m_df.gather(f, m_dfs);
	setFaceFlag(f, 0);

	// detach linked bodies
	Buffer<uint> &b = m_f[f].b;
	for(i=b.size(); i-->0; ) detachBody(b[i]);

	// remove links from edges
	Buffer<uint> &e = m_f[f].e;
	for(i=e.size(); i-->0; ) m_e[e[i]].f.eraseFirst(f);
	e.clear();
	return f;
}

uint BuilderMesh::detachBody(const uint b)
{
	uint i;
	m_db.gather(b, m_dbs);
	setBodyFlag(b, 0);

	// detach linked quads
	Buffer<uint> &q = m_b[b].q;
	for(i=q.size(); i-->0; ) detachQuad(q[i]);

	// remove links from faces
	Buffer<uint> &f = m_b[b].f;
	for(i=f.size(); i-->0; ) m_f[f[i]].b.eraseFirst(b);
	f.clear();

	return b;
}

uint BuilderMesh::detachQuad(const uint q)
{
	uint i;
	m_dq.gather(q, m_dqs);
	setQuadFlag(q, 0);

	// remove links from bodies
	Buffer<uint> &b = m_q[q].b;
	for(i=b.size(); i-->0; ) m_b[b[i]].q.eraseFirst(q);
	b.clear();

	return q;
}

uint BuilderMesh::detachEdgeRecursive(const uint e)
{
	const Buffer<uint> n = getEdgeNodes(e);
	detachEdge(e);
	for(uint i=0; i<n.size(); i++)
	{
		if(getNodeEdges(n[i]).empty()) detachNode(n[i]);
	}
	return e;
}

uint BuilderMesh::detachFaceRecursive(const uint f)
{
	const Buffer<uint> e = getFaceEdges(f);
	detachFace(f);
	for(uint i=0; i<e.size(); i++)
	{
		if(getEdgeFaces(e[i]).empty()) detachEdgeRecursive(e[i]);
	}
	return f;
}

uint BuilderMesh::detachBodyRecursive(const uint b)
{
	const Buffer<uint> f = getBodyFaces(b);
	detachBody(b);
	for(uint i=0; i<f.size(); i++)
	{
		if(getFaceBodies(f[i]).empty()) detachFaceRecursive(f[i]);
	}
	return b;
}

uint BuilderMesh::detachQuadRecursive(const uint q)
{
	const Buffer<uint> b = getQuadBodies(q);
	detachQuad(q);
	for(uint i=0; i<b.size(); i++)
	{
		if(getBodyQuads(b[i]).empty()) detachBodyRecursive(b[i]);
	}
	return q;
}

void BuilderMesh::removeDetached()
{
	if(m_dns > 0)
	{
		m_dn.resize(m_dns);
		removeNodes(m_dn);
		m_dns = 0;
	}
	if(m_des > 0)
	{
		m_de.resize(m_des);
		removeEdges(m_de);
		m_des = 0;
	}
	if(m_dfs > 0)
	{
		m_df.resize(m_dfs);
		removeFaces(m_df);
		m_dfs = 0;
	}
	if(m_dbs > 0)
	{
		m_db.resize(m_dbs);
		removeBodies(m_db);
		m_dbs = 0;
	}
	if(m_dqs > 0)
	{
		m_dq.resize(m_dqs);
		removeQuads(m_dq);
		m_dqs = 0;
	}
}

void BuilderMesh::removeNodes(const Buffer<uint> &n)
{
	uint i, j;
	Buffer<uint> buf(n.size(), m_nsize);
	const uint size = m_nsize - n.size();
	for(i=0; i<buf.size(); i++)
	{
		if(n[i] >= size) buf[n[i] - size] = n[i];
	}
	for(i=0,j=0; i<buf.size(); i++)
	{
		if(n[i] >= size) continue;
		while(buf[j] != m_nsize) j++;
		buf[j] = n[i];
	}
	for(i=buf.size(); i-->0; ) removeNode(buf[i]);
}

void BuilderMesh::removeEdges(const Buffer<uint> &e)
{
	uint i, j;
	Buffer<uint> buf(e.size(), m_esize);
	const uint size = m_esize - buf.size();
	for(i=0; i<buf.size(); i++)
	{
		if(e[i] >= size) buf[e[i] - size] = e[i];
	}
	for(i=0,j=0; i<buf.size(); i++)
	{
		if(e[i] >= size) continue;
		while(buf[j] != m_esize) j++;
		buf[j] = e[i];
	}
	for(i=buf.size(); i-->0; ) removeEdge(buf[i]);
}

void BuilderMesh::removeFaces(const Buffer<uint> &f)
{
	uint i, j;
	Buffer<uint> buf(f.size(), m_fsize);
	const uint size = m_fsize - buf.size();
	for(i=0; i<buf.size(); i++)
	{
		if(f[i] >= size) buf[f[i] - size] = f[i];
	}
	for(i=0,j=0; i<buf.size(); i++)
	{
		if(f[i] >= size) continue;
		while(buf[j] != m_fsize) j++;
		buf[j] = f[i];
	}
	for(i=buf.size(); i-->0; ) removeFace(buf[i]);
}

void BuilderMesh::removeBodies(const Buffer<uint> &b)
{
	uint i, j;
	Buffer<uint> buf(b.size(), m_bsize);
	const uint size = m_bsize - buf.size();
	for(i=0; i<buf.size(); i++)
	{
		if(b[i] >= size) buf[b[i] - size] = b[i];
	}
	for(i=0,j=0; i<buf.size(); i++)
	{
		if(b[i] >= size) continue;
		while(buf[j] != m_bsize) j++;
		buf[j] = b[i];
	}
	for(i=buf.size(); i-->0; ) removeBody(buf[i]);
}

void BuilderMesh::removeQuads(const Buffer<uint> &q)
{
	uint i, j;
	Buffer<uint> buf(q.size(), m_qsize);
	const uint size = m_qsize - buf.size();
	for(i=0; i<buf.size(); i++)
	{
		if(q[i] >= size) buf[q[i] - size] = q[i];
	}
	for(i=0,j=0; i<buf.size(); i++)
	{
		if(q[i] >= size) continue;
		while(buf[j] != m_qsize) j++;
		buf[j] = q[i];
	}
	for(i=buf.size(); i-->0; ) removeQuad(buf[i]);
}

void BuilderMesh::fillNodeFlags(const uint flag, const UintGroup &oldflag)
{
	for(uint i=0; i<m_nsize; i++)
	{
		if(oldflag.includes(getNodeFlag(i))) setNodeFlag(i, flag);
	}
}
void BuilderMesh::fillEdgeFlags(const uint flag, const UintGroup &oldflag)
{
	for(uint i=0; i<m_esize; i++)
	{
		if(oldflag.includes(getEdgeFlag(i))) setEdgeFlag(i, flag);
	}
}
void BuilderMesh::fillFaceFlags(const uint flag, const UintGroup &oldflag)
{
	for(uint i=0; i<m_fsize; i++)
	{
		if(oldflag.includes(getFaceFlag(i))) setFaceFlag(i, flag);
	}
}
void BuilderMesh::fillBodyFlags(const uint flag, const UintGroup &oldflag)
{
	for(uint i=0; i<m_bsize; i++)
	{
		if(oldflag.includes(getBodyFlag(i))) setBodyFlag(i, flag);
	}
}
void BuilderMesh::fillQuadFlags(const uint flag, const UintGroup &oldflag)
{
	for(uint i=0; i<m_qsize; i++)
	{
		if(oldflag.includes(getQuadFlag(i))) setQuadFlag(i, flag);
	}
}
void BuilderMesh::fillFlags(const uint flag, const UintGroup &oldflag)
{
	fillNodeFlags(flag, oldflag);
	fillEdgeFlags(flag, oldflag);
	fillFaceFlags(flag, oldflag);
	fillBodyFlags(flag, oldflag);
	fillQuadFlags(flag, oldflag);
}

void BuilderMesh::fillBoundaryFlags(const uint flag, const UintGroup &oldflag)
{
	uint i, j, k, l;
	if(m_fsize == 0) // 1d
	{
		for(i=0; i<m_nsize; i++)
		{
			if(!oldflag.includes(getNodeFlag(i))) continue;
			if(getNodeEdges(i).size() >= 2) continue;
			setNodeFlag(i, flag);
		}
		return;
	}
	if(m_bsize == 0) // 2d
	{
		for(i=0; i<m_esize; i++)
		{
			if(!oldflag.includes(getEdgeFlag(i))) continue;
			if(getEdgeFaces(i).size() >= 2) continue;
			setEdgeFlag(i, flag);
			const Buffer<uint> &n = getEdgeNodes(i);
			for(j=0; j<n.size(); j++)
			{
				if(oldflag.includes(getNodeFlag(n[j]))) setNodeFlag(n[j], flag);
			}
		}
		return;
	}
	if(m_qsize == 0) // 3d
	{
		for(i=0; i<m_fsize; i++)
		{
			if(!oldflag.includes(getFaceFlag(i))) continue;
			if(getFaceBodies(i).size() >= 2) continue;
			setFaceFlag(i, flag);
			const Buffer<uint> &e = getFaceEdges(i);
			for(j=0; j<e.size(); j++)
			{
				if(!oldflag.includes(getEdgeFlag(e[j]))) continue;
				setEdgeFlag(e[j], flag);
				const Buffer<uint> &n = getEdgeNodes(e[j]);
				for(k=0; k<n.size(); k++)
				{
					if(oldflag.includes(getNodeFlag(n[k]))) setNodeFlag(n[k], flag);
				}
			}
		}
		return;
	}
	// 4d
	for(i=0; i<m_bsize; i++)
	{
		if(!oldflag.includes(getBodyFlag(i))) continue;
		if(getBodyQuads(i).size() >= 2) continue;
		setBodyFlag(i, flag);
		const Buffer<uint> &f = getBodyFaces(i);
		for(j=0; j<f.size(); j++)
		{
			if(!oldflag.includes(getFaceFlag(f[j]))) continue;
			setFaceFlag(f[j], flag);
			const Buffer<uint> &e = getFaceEdges(f[j]);
			for(k=0; k<e.size(); k++)
			{
				if(!oldflag.includes(getEdgeFlag(e[k]))) continue;
				setEdgeFlag(e[k], flag);
				const Buffer<uint> &n = getEdgeNodes(e[k]);
				for(l=0; l<n.size(); l++)
				{
					if(oldflag.includes(getNodeFlag(n[l]))) setNodeFlag(n[l], flag);
				}
			}
		}
	}
}

void BuilderMesh::fillFlags(const Vector4 &minp, const Vector4 &maxp, const uint flag, const UintGroup &oldflag)
{
	for(uint i=0; i<m_nsize; i++)
	{
		if(!oldflag.includes(getNodeFlag(i))) continue;
		const Vector4 p = getNodePosition(i);
		if(p.x < minp.x || maxp.x <= p.x) continue;
		if(p.y < minp.y || maxp.y <= p.y) continue;
		if(p.z < minp.z || maxp.z <= p.z) continue;
		if(p.t < minp.t || maxp.t <= p.t) continue;
		setNodeFlag(i, flag);
	}
	for(uint i=0; i<m_esize; i++)
	{
		if(!oldflag.includes(getEdgeFlag(i))) continue;
		const Vector4 p = getEdgeAverage(i);
		if(p.x < minp.x || maxp.x <= p.x) continue;
		if(p.y < minp.y || maxp.y <= p.y) continue;
		if(p.z < minp.z || maxp.z <= p.z) continue;
		if(p.t < minp.t || maxp.t <= p.t) continue;
		setEdgeFlag(i, flag);
	}
	for(uint i=0; i<m_fsize; i++)
	{
		if(!oldflag.includes(getFaceFlag(i))) continue;
		const Vector4 p = getFaceAverage(i);
		if(p.x < minp.x || maxp.x <= p.x) continue;
		if(p.y < minp.y || maxp.y <= p.y) continue;
		if(p.z < minp.z || maxp.z <= p.z) continue;
		if(p.t < minp.t || maxp.t <= p.t) continue;
		setFaceFlag(i, flag);
	}
	for(uint i=0; i<m_bsize; i++)
	{
		if(!oldflag.includes(getBodyFlag(i))) continue;
		const Vector4 p = getBodyAverage(i);
		if(p.x < minp.x || maxp.x <= p.x) continue;
		if(p.y < minp.y || maxp.y <= p.y) continue;
		if(p.z < minp.z || maxp.z <= p.z) continue;
		if(p.t < minp.t || maxp.t <= p.t) continue;
		setBodyFlag(i, flag);
	}
	for(uint i=0; i<m_qsize; i++)
	{
		if(!oldflag.includes(getQuadFlag(i))) continue;
		const Vector4 p = getQuadAverage(i);
		if(p.x < minp.x || maxp.x <= p.x) continue;
		if(p.y < minp.y || maxp.y <= p.y) continue;
		if(p.z < minp.z || maxp.z <= p.z) continue;
		if(p.t < minp.t || maxp.t <= p.t) continue;
		setQuadFlag(i, flag);
	}
}

void BuilderMesh::removeByFlags(const UintGroup &flag)
{
	uint i;
	for(i=m_qsize; i-->0; )
	{
		if(flag.includes(getQuadFlag(i))) removeQuad(i);
	}
	for(i=m_bsize; i-->0; )
	{
		if(flag.includes(getBodyFlag(i))) removeBody(i);
	}
	for(i=m_fsize; i-->0; )
	{
		if(flag.includes(getFaceFlag(i))) removeFace(i);
	}
	for(i=m_esize; i-->0; )
	{
		if(flag.includes(getEdgeFlag(i))) removeEdge(i);
	}
	for(i=m_nsize; i-->0; )
	{
		if(flag.includes(getNodeFlag(i))) removeNode(i);
	}
}

bool BuilderMesh::repeatMiddle(const Vector4 &pos, const Vector4 &dir, const uint steps)
{
	if(steps == 0) return true;
	Mesh mesh(m_dim);
	swap(mesh);
	if(createRepeated(mesh, pos, dir, steps)) return true;
	swap(mesh);
	return false;
}

void BuilderMesh::combine(const Mesh &mesh)
{
	uint i, j;

	const uint ns = getNodeSize();
	const uint nsize = mesh.getNodeSize();
	resizeNodeBuffer(ns + nsize);
	for(i=0; i<nsize; i++)
	{
		const uint n = addNode(mesh.getNodePosition(i));
		setNodeWeight(n, mesh.getNodeWeight(i));
		setNodeFlag(n, mesh.getNodeFlag(i));
	}
	const uint es = getEdgeSize();
	const uint esize = mesh.getEdgeSize();
	resizeEdgeBuffer(es + esize);
	for(i=0; i<esize; i++)
	{
		const Buffer<uint> &par = mesh.getEdgeNodes(i);
		const uint e = addEdge(ns + par[0], ns + par[1]);
		setEdgeFlag(e, mesh.getEdgeFlag(i));
	}
	const uint fs = getFaceSize();
	const uint fsize = mesh.getFaceSize();
	resizeFaceBuffer(fs + fsize);
	for(i=0; i<fsize; i++)
	{
		Buffer<uint> par = mesh.getFaceEdges(i);
		for(j=0; j<par.size(); j++) par[j] += es;
		const uint f = addFace(par);
		setFaceFlag(f, mesh.getFaceFlag(i));
	}
	const uint bs = getBodySize();
	const uint bsize = mesh.getBodySize();
	resizeBodyBuffer(bs + bsize);
	for(i=0; i<bsize; i++)
	{
		Buffer<uint> par = mesh.getBodyFaces(i);
		for(j=0; j<par.size(); j++) par[j] += fs;
		const uint b = addBody(par);
		setBodyFlag(b, mesh.getBodyFlag(i));
	}
	const uint qs = getQuadSize();
	const uint qsize = mesh.getQuadSize();
	resizeQuadBuffer(qs + qsize);
	for(i=0; i<qsize; i++)
	{
		Buffer<uint> par = mesh.getQuadBodies(i);
		for(j=0; j<par.size(); j++) par[j] += bs;
		const uint q = addQuad(par);
		setQuadFlag(q, mesh.getQuadFlag(i));
	}
}

void BuilderMesh::stretchLinear(const Vector4 &v, const uint steps, const UintGroup &flag, const uint flagMiddle, const uint flagEnd)
{
	if(steps == 0) return;
	const Vector4 d = v / ddouble(steps);

	// find nodes to duplicate
	uint i, j;
	uint nnsize = 0;
	Buffer<uint> nn(m_nsize);
	for(i=0; i<m_nsize; i++)
	{
		if(flag.includes(getNodeFlag(i))) nn[nnsize++] = i;
	}
	if(nnsize == 0) return;
	nn.resize(nnsize);

	// create new nodes
	const uint nsize = m_nsize;
	m_nsize += steps * nnsize;
	resizeNodeBuffer(m_nsize);
	for(i=0; i<nnsize; i++)
	{
		const Vector4 p = getNodePosition(nn[i]);
		const ddouble w = getNodeWeight(nn[i]);
		for(j=0; j<steps; j++)
		{
			const uint ii = nsize + nnsize * j + i;
			setNodePosition(ii, p + (j + 1) * d);
			setNodeWeight(ii, w);
		}
	}

	stretch(nn, steps, flag, flagMiddle, flagEnd);
}

void BuilderMesh::stretch(const Buffer<uint> &n, const uint steps, const UintGroup &flag, const uint flagMiddle, const uint flagEnd)
{
	uint i, j, k;
	const uint nnsize = n.size();
	const uint nsize = m_nsize - steps * nnsize;
	const uint esize = m_esize;
	const uint fsize = m_fsize;
	const uint bsize = m_bsize;
	const uint qsize = m_qsize;

	// find edges to stretch
	uint eesize = 0;
	Buffer<uint> ee(esize);
	for(i=0; i<esize; i++)
	{
		if(flag.includes(getEdgeFlag(i))) ee[eesize++] = i;
	}

	// find faces to stretch
	uint ffsize = 0;
	Buffer<uint> ff(fsize);
	for(i=0; i<fsize; i++)
	{
		if(flag.includes(getFaceFlag(i))) ff[ffsize++] = i;
	}

	// find bodies to stretch
	uint bbsize = 0;
	Buffer<uint> bb(bsize);
	for(i=0; i<bsize; i++)
	{
		if(flag.includes(getBodyFlag(i))) bb[bbsize++] = i;
	}

	// resize cell buffers
	m_esize = esize + steps * (nnsize + eesize);
	resizeEdgeBuffer(m_esize);
	m_fsize = fsize + steps * (eesize + ffsize);
	resizeFaceBuffer(m_fsize);
	m_bsize = bsize + steps * (ffsize + bbsize);
	resizeBodyBuffer(m_bsize);
	m_qsize = qsize + steps * bbsize;
	resizeQuadBuffer(m_qsize);

	// stretch nodes
	for(i=0; i<nnsize; i++)
	{
		const uint flag0 = getNodeFlag(n[i]);
		for(j=0; j<steps; j++)
		{
			const uint n1 = nsize + j * nnsize + i;
			const uint n0 = (j > 0 ? n1 - nnsize : n[i]);
			setNodeFlag(n1, flag0 + (j + 1 < steps ? flagMiddle : flagEnd));

			const uint ei = esize + j * nnsize + i;
			setEdgeFlag(ei, flag0 + flagMiddle);
			m_e[ei].n.resize(2);
			m_e[ei].n[0] = n0;
			m_e[ei].n[1] = n1;
			m_n[n0].e.push_back(ei);
			m_n[n1].e.push_back(ei);
		}
	}

	// stretch edges
	for(i=0; i<eesize; i++)
	{
		const uint flag0 = getEdgeFlag(ee[i]);
		for(j=0; j<steps; j++)
		{
			const uint e1 = esize + steps * nnsize + j * eesize + i;
			const uint e0 = (j > 0 ? e1 - eesize : ee[i]);
			Buffer<uint> en = getEdgeNodes(e0);
			Buffer<uint> fe(4);
			fe[1] = e0;
			fe[3] = e1;
			for(k=0; k<en.size(); k++)
			{
				if(j == 0) fe[2 * k] = getNodeEdges(en[k]).back();
				else fe[2 * k] = getNodeEdges(en[k])[1];
				en[k] = getEdgeNodes(fe[2 * k])[1];
			}
			setEdgeFlag(e1, flag0 + (j + 1 < steps ? flagMiddle : flagEnd));
			m_e[e1].n = en;
			m_n[en[0]].e.push_back(e1);
			m_n[en[1]].e.push_back(e1);

			const uint fi = fsize + j * eesize + i;
			setFaceFlag(fi, flag0 + flagMiddle);
			m_f[fi].e = fe;
			for(k=0; k<fe.size(); k++) m_e[fe[k]].f.push_back(fi);
		}
	}

	// stretch faces
	for(i=0; i<ffsize; i++)
	{
		const uint flag0 = getFaceFlag(ff[i]);
		for(j=0; j<steps; j++)
		{
			const uint f1 = fsize + steps * eesize + j * ffsize + i;
			const uint f0 = (j > 0 ? f1 - ffsize : ff[i]);
			Buffer<uint> fe = getFaceEdges(f0);
			Buffer<uint> bf(2 + fe.size());
			bf[0] = f0;
			bf.back() = f1;
			for(k=0; k<fe.size(); k++)
			{
				if(j == 0) bf[1 + k] = getEdgeFaces(fe[k]).back();
				else bf[1 + k] = getEdgeFaces(fe[k])[1];
				fe[k] = getFaceEdges(bf[1 + k])[3];
			}
			setFaceFlag(f1, flag0 + (j + 1 < steps ? flagMiddle : flagEnd));
			m_f[f1].e = fe;
			for(k=0; k<fe.size(); k++) m_e[fe[k]].f.push_back(f1);

			const uint bi = bsize + j * ffsize + i;
			setBodyFlag(bi, flag0 + flagMiddle);
			m_b[bi].f = bf;
			for(k=0; k<bf.size(); k++) m_f[bf[k]].b.push_back(bi);
		}
	}

	// stretch bodies
	for(i=0; i<bbsize; i++)
	{
		const uint flag0 = getBodyFlag(bb[i]);
		for(j=0; j<steps; j++)
		{
			const uint b1 = bsize + steps * ffsize + j * bbsize + i;
			const uint b0 = (j > 0 ? b1 - bbsize : bb[i]);
			Buffer<uint> bf = getBodyFaces(b0);
			Buffer<uint> qb(2 + bf.size());
			qb[0] = b0;
			qb[1] = b1;
			for(k=0; k<bf.size(); k++)
			{
				if(j == 0) qb[2 + k] = getFaceBodies(bf[k]).back();
				else qb[2 + k] = getFaceBodies(bf[k])[1];
				bf[k] = getBodyFaces(qb[2 + k]).back();
			}
			setBodyFlag(b1, flag0 + (j + 1 < steps ? flagMiddle : flagEnd));
			m_b[b1].f = bf;
			for(k=0; k<bf.size(); k++) m_f[bf[k]].b.push_back(b1);

			const uint qi = qsize + j * bbsize + i;
			setQuadFlag(qi, flag0 + flagMiddle);
			m_q[qi].b = qb;
			for(k=0; k<qb.size(); k++) m_b[qb[k]].q.push_back(qi);
		}
	}
}


