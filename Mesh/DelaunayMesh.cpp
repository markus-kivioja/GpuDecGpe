#include "DelaunayMesh.hpp"
#include <iostream>

const ddouble MINLENGTHSQ = 1e-13; // limit for minimal edge length
const ddouble ORTOGONALSQ = 1e-13; // limit for linear dependency
const ddouble RADIUSSCALE = 1.0000000001;

DelaunayMesh::DelaunayMesh(const uint dim)
: BuilderMesh(dim)
{

}

void DelaunayMesh::clear()
{
	BuilderMesh::clear();
}

void DelaunayMesh::createHexagonGrid(const Vector2 &minp, const Vector2 &maxp, const ddouble h)
{
	const Vector2 d(h, h / sqrt(3.0));
	const uint xsize = uint((maxp.x - minp.x) / d.x + 0.999);
	const uint ysize = uint((maxp.y - minp.y) / d.y + 0.999);

	const uint xs = (xsize < 3 ? xsize : 3);
	const uint ys = (ysize < 3 ? ysize : 3);

	const Vector2 p0 = 0.5 * (maxp + minp - Vector2(xsize * d.x, ysize * d.y));
	const Vector2 p1 = p0 + Vector2(xs * d.x, ys * d.y);
	createTriangleGrid(p0, p1, h / 3.0, true);

	// generate nodes
	uint xi, yi;
	uint node = 0;
	for(yi=0; yi<ys; yi++)
	{
		const ddouble py = p0.y + d.y * yi;
		for(xi=0; xi<xs; xi++)
		{
			const ddouble px = p0.x + d.x * xi;
			if(yi > 0 && xi > 0)
			{
				node = findNodeAt(Vector4(px, py,0,0), 1e-13, node);
				if(node != NONE) eraseNode(node);
			}
			node = findNodeAt(Vector4(px+0.5*d.x, py+0.5*d.y,0,0), 1e-13, node);
			if(node != NONE) eraseNode(node);
		}
	}
	const Vector4 pp(p0 + 0.99999*d, 0.0, 0.0);
	if(xsize > xs) repeatMiddle(pp, Vector4(d.x,0,0,0), xsize - xs);
	if(ysize > ys) repeatMiddle(pp, Vector4(0,d.y,0,0), ysize - ys);
}

void DelaunayMesh::createSnubSquareGrid(const Vector2 &minp, const Vector2 &maxp, const ddouble h)
{
	const uint xsize = uint((maxp.x - minp.x) / h + 0.5);
	const uint ysize = uint((maxp.y - minp.y) / h + 0.5);

	const uint xs = (xsize < 3 ? xsize : 3);
	const uint ys = (ysize < 3 ? ysize : 3);

	const ddouble SQ3 = sqrt(3.0);
	const ddouble l = h / (SQ3 + 1);
	const Vector2 p0 = 0.5 * (minp + maxp - Vector2(xsize * h, ysize * h));
	const Vector2 p1 = p0 + Vector2(xs * h, ys * h);

	createGrid(Vector4(p0,0,0), Vector4(p1,0,0), h);

	// generate nodes
	uint node = 0;
	uint xi, yi;
	for(yi=0; yi<=ys; yi++)
	{
		const ddouble py = p0.y + h * yi;
		for(xi=1; xi<=xs; xi++)
		{
			const ddouble px = p0.x + h * xi;
			if(yi > 0)
			{
				node = insertNode(Vector4(px - 0.5 * h, py - 0.5 * h, 0,0), 0.0, node);
				node = insertNode(Vector4(px - 0.5 * h-l, py - 0.5 * h, 0,0), 0.0, node);
				node = insertNode(Vector4(px - 0.5 * (h + l), py - 0.5 * l, 0,0), 0.0, node);
				node = insertNode(Vector4(px - 0.5 * (h + l), py - h + 0.5 * l, 0,0), 0.0, node);
				node = insertNode(Vector4(px - 0.5 * l, py - 0.5 * (h - l), 0,0), 0.0, node);
				node = insertNode(Vector4(px - 0.5 * l, py - 0.5 * (h + l), 0,0), 0.0, node);

				if(xi == 1) node = insertNode(Vector4(px - h, py - 0.5 * h, 0,0), 0.0, node);
				if(xi == xs)
				{
					node = insertNode(Vector4(px, py - l, 0,0), 0.0, node);
					node = insertNode(Vector4(px, py - h + l, 0,0), 0.0, node);
				}
			}
			node = insertNode(Vector4(px - l, py, 0,0), 0.0, node);
			if(yi == 0 || yi == ys) node = insertNode(Vector4(px - 0.5 * (h + l), py, 0,0), 0.0, node);
		}
	}
	const Vector4 pp(p0 + 0.99999*Vector2(h,h), 0.0, 0.0);
	if(xsize > xs) repeatMiddle(pp, Vector4(h,0,0,0), xsize - xs);
	if(ysize > ys) repeatMiddle(pp, Vector4(0,h,0,0), ysize - ys);
}

void DelaunayMesh::createTetrilleGrid(const Vector2 &minp, const Vector2 &maxp, const ddouble h)
{
	const Vector2 d(h, h * sqrt(3.0));
	const uint xsize = uint((maxp.x - minp.x) / d.x + 0.999);
	const uint ysize = uint((maxp.y - minp.y) / d.y + 0.999);

	const uint xs = (xsize < 3 ? xsize : 3);
	const uint ys = (ysize < 3 ? ysize : 3);

	const Vector2 p0 = 0.5 * (maxp + minp - Vector2(xsize * d.x, ysize * d.y));
	const Vector2 p1 = p0 + Vector2(xs * d.x, ys * d.y);
	createTriangleGrid(p0, p1, 0.5 * h, true);

	// generate nodes
	uint node = 0;
	uint xi, yi;
	for(yi=0; yi<ys; yi++)
	{
		const ddouble py = p0.y + d.y * yi;
		for(xi=0; xi<xs; xi++)
		{
			const ddouble px = p0.x + d.x * xi;
			if(xi > 0)
			{
				node = insertNode(Vector4(px, py + d.y / 6.0, 0,0), 0.0, node);
				node = insertNode(Vector4(px, py + d.y * 5.0 / 6.0, 0,0), 0.0, node);
			}
			node = insertNode(Vector4(px + 0.5 * d.x, py + d.y / 3.0, 0,0), 0.0, node);
			node = insertNode(Vector4(px + 0.5 * d.x, py + d.y * 2.0 / 3.0, 0,0), 0.0, node);
		}
	}
	const Vector4 pp(p0 + 0.99999*d, 0.0, 0.0);
	if(xsize > xs) repeatMiddle(pp, Vector4(d.x,0,0,0), xsize - xs);
	if(ysize > ys) repeatMiddle(pp, Vector4(0,d.y,0,0), ysize - ys);
}

void DelaunayMesh::createFccGrid(const Vector3 &minp, const Vector3 &maxp, const ddouble h)
{
	const uint xsize = uint((maxp.x - minp.x) / h - 1e-8) + 1;
	const uint ysize = uint((maxp.y - minp.y) / h - 1e-8) + 1;
	const uint zsize = uint((maxp.z - minp.z) / h - 1e-8) + 1;

	const uint xs = (xsize < 3 ? xsize : 3);
	const uint ys = (ysize < 3 ? ysize : 3);
	const uint zs = (zsize < 3 ? zsize : 3);

	const Vector3 p0 = 0.5 * (maxp + minp - Vector3(xsize * h, ysize * h, zsize * h));
	const Vector3 p1 = p0 + Vector3(xs * h, ys * h, zs * h);

	createGrid(Vector4(p0,0), Vector4(p1,0), h);

	uint node = 0;
	uint xi, yi, zi;
	for(zi=0; zi<=zs; zi++)
	{
		const ddouble pz = p0.z + h * zi;
		for(yi=0; yi<=ys; yi++)
		{
			const ddouble py = p0.y + h * yi;
			for(xi=0; xi<=xs; xi++)
			{
				const ddouble px = p0.x + h * xi;
				if(xi < xs && yi < ys) node = insertNode(Vector4(px + 0.5 * h, py + 0.5 * h, pz, 0), 0.0, node);
				if(xi < xs && zi < zs) node = insertNode(Vector4(px + 0.5 * h, py, pz + 0.5 * h, 0), 0.0, node);
				if(yi < ys && zi < zs) node = insertNode(Vector4(px, py + 0.5 * h, pz + 0.5 * h, 0), 0.0, node);
			}
		}
	}
	const Vector4 pp(p0 + 0.99999 * Vector3(h, h, h), 0.0);
	if(xsize > xs) repeatMiddle(pp, Vector4(h,0,0,0), xsize - xs);
	if(ysize > ys) repeatMiddle(pp, Vector4(0,h,0,0), ysize - ys);
	if(zsize > zs) repeatMiddle(pp, Vector4(0,0,h,0), zsize - zs);
}

void DelaunayMesh::createBccGrid(const Vector3 &minp, const Vector3 &maxp, const ddouble h)
{
	const uint xsize = uint((maxp.x - minp.x) / h - 1e-8) + 1;
	const uint ysize = uint((maxp.y - minp.y) / h - 1e-8) + 1;
	const uint zsize = uint((maxp.z - minp.z) / h - 1e-8) + 1;

	const uint xs = (xsize < 3 ? xsize : 3);
	const uint ys = (ysize < 3 ? ysize : 3);
	const uint zs = (zsize < 3 ? zsize : 3);

	const Vector3 p0 = 0.5 * (maxp + minp - Vector3(xsize * h, ysize * h, zsize * h));
	const Vector3 p1 = p0 + Vector3(xs * h, ys * h, zs * h);

	createGrid(Vector4(p0,0), Vector4(p1,0), h);

	uint node = 0;
	uint xi, yi, zi;
	for(zi=0; zi<=zs; zi++)
	{
		const ddouble pz = p0.z + h * zi;
		for(yi=0; yi<=ys; yi++)
		{
			const ddouble py = p0.y + h * yi;
			for(xi=0; xi<=xs; xi++)
			{
				const ddouble px = p0.x + h * xi;
				if(xi < xs && yi < ys && zi < zs) node = insertNode(Vector4(px + 0.5 * h, py + 0.5 * h, pz + 0.5 * h, 0), 0.0, node);
				if(xi < xs && yi < ys && (zi == 0 || zi == zs)) node = insertNode(Vector4(px + 0.5 * h, py + 0.5 * h, pz, 0), 0.0, node);
				if(xi < xs && zi < zs && (yi == 0 || yi == ys)) node = insertNode(Vector4(px + 0.5 * h, py, pz + 0.5 * h, 0), 0.0, node);
				if(zi < zs && yi < ys && (xi == 0 || xi == xs)) node = insertNode(Vector4(px, py + 0.5 * h, pz + 0.5 * h, 0), 0.0, node);
				if(xi < xs && (yi == 0 || yi == ys || zi == 0 || zi == zs)) node = insertNode(Vector4(px + 0.5 * h, py, pz, 0), 0.0, node);
				if(yi < ys && (xi == 0 || xi == xs || zi == 0 || zi == zs)) node = insertNode(Vector4(px, py + 0.5 * h, pz, 0), 0.0, node);
				if(zi < zs && (yi == 0 || yi == ys || xi == 0 || xi == xs)) node = insertNode(Vector4(px, py, pz + 0.5 * h, 0), 0.0, node);
			}
		}
	}

	const Vector4 pp(p0 + 0.99999 * Vector3(h, h, h), 0.0);
	if(xsize > xs) repeatMiddle(pp, Vector4(h,0,0,0), xsize - xs);
	if(ysize > ys) repeatMiddle(pp, Vector4(0,h,0,0), ysize - ys);
	if(zsize > zs) repeatMiddle(pp, Vector4(0,0,h,0), zsize - zs);
}

void DelaunayMesh::createTruncatedOctahedraGrid(const Vector3 &minp, const Vector3 &maxp, const ddouble h)
{
	const uint xsize = uint((maxp.x - minp.x) / h - 1e-8) + 1;
	const uint ysize = uint((maxp.y - minp.y) / h - 1e-8) + 1;
	const uint zsize = uint((maxp.z - minp.z) / h - 1e-8) + 1;

	const uint xs = (xsize < 3 ? xsize : 3);
	const uint ys = (ysize < 3 ? ysize : 3);
	const uint zs = (zsize < 3 ? zsize : 3);

	const Vector3 p0 = 0.5 * (maxp + minp - Vector3(xsize * h, ysize * h, zsize * h));
	const Vector3 p1 = p0 + Vector3(xs * h, ys * h, zs * h);

	createGrid(Vector4(p0,0), Vector4(p1,0), h);

	uint node = 0;
	uint xi, yi, zi;
	for(zi=0; zi<=zs; zi++)
	{
		const ddouble pz = p0.z + h * zi;
		for(yi=0; yi<=ys; yi++)
		{
			const ddouble py = p0.y + h * yi;
			for(xi=0; xi<=xs; xi++)
			{
				const ddouble px = p0.x + h * xi;
				if(xi > 0 && yi > 0 && zi > 0)
				{
					node = insertNode(Vector4(px - 0.5 * h, py - 0.5 * h, pz - 0.5 * h, 0), 0.0, node);
					node = insertNode(Vector4(px - 0.25 * h, py - 0.5 * h, pz - 0.75 * h, 0), 0.0, node);
					node = insertNode(Vector4(px - 0.75 * h, py - 0.75 * h, pz - 0.5 * h, 0), 0.0, node);
					node = insertNode(Vector4(px - 0.75 * h, py - 0.25 * h, pz - 0.5 * h, 0), 0.0, node);
					node = insertNode(Vector4(px - 0.25 * h, py - 0.5 * h, pz - 0.25 * h, 0), 0.0, node);
				}
				if(yi > 0 && zi > 0) node = insertNode(Vector4(px, py - 0.5 * h, pz - 0.5 * h, 0), 0.0, node);
				if(xi > 0 && yi > 0)
				{
					node = insertNode(Vector4(px - 0.25 * h, py - 0.25 * h, pz, 0), 0.0, node);
					node = insertNode(Vector4(px - 0.25 * h, py - 0.75 * h, pz, 0), 0.0, node);
				}
				if(xi > 0 && zi > 0)
				{
					node = insertNode(Vector4(px - 0.75 * h, py, pz - 0.75 * h, 0), 0.0, node);
					node = insertNode(Vector4(px - 0.75 * h, py, pz - 0.25 * h, 0), 0.0, node);
				}
				if(xi > 0) node = insertNode(Vector4(px - 0.5 * h, py, pz, 0), 0.0, node);
			}
		}
	}

	const Vector4 pp(p0 + 0.99999 * Vector3(h, h, h), 0.0);
	if(xsize > xs) repeatMiddle(pp, Vector4(h,0,0,0), xsize - xs);
	if(ysize > ys) repeatMiddle(pp, Vector4(0,h,0,0), ysize - ys);
	if(zsize > zs) repeatMiddle(pp, Vector4(0,0,h,0), zsize - zs);
}

void DelaunayMesh::createA15Grid(const Vector3 &minp, const Vector3 &maxp, const ddouble h)
{
	const uint xsize = uint((maxp.x - minp.x) / h - 1e-8) + 1;
	const uint ysize = uint((maxp.y - minp.y) / h - 1e-8) + 1;
	const uint zsize = uint((maxp.z - minp.z) / h - 1e-8) + 1;

	const uint xs = (xsize < 3 ? xsize : 3);
	const uint ys = (ysize < 3 ? ysize : 3);
	const uint zs = (zsize < 3 ? zsize : 3);

	const Vector3 p0 = 0.5 * (maxp + minp - Vector3(xsize * h, ysize * h, zsize * h));
	const Vector3 p1 = p0 + Vector3(xs * h, ys * h, zs * h);

	createGrid(Vector4(p0,0), Vector4(p1,0), h);

	const ddouble bias = 0.25;
	const ddouble weight = 0.0;

	const ddouble a = 0.5 - bias;
	const ddouble b = 0.5 + bias;
	const ddouble w = weight * h * h;

	uint node = 0;
	uint xi, yi, zi;
	for(zi=0; zi<=zs; zi++)
	{
		const ddouble pz = p0.z + h * zi;
		for(yi=0; yi<=ys; yi++)
		{
			const ddouble py = p0.y + h * yi;
			for(xi=0; xi<=xs; xi++)
			{
				const ddouble px = p0.x + h * xi;
				if(xi < xs && yi < ys && zi < zs) node = insertNode(Vector4(px + 0.5 * h, py + 0.5 * h, pz + 0.5 * h, 0), 0.0, node);

				if(xi < xs && yi < ys)
				{
					if(zi == 0 || zi == zs)
					{
						node = insertNode(Vector4(px + h / 3.0, py + h / 3.0, pz, 0), 0.0, node);
						node = insertNode(Vector4(px + 2*h / 3.0, py + h / 3.0, pz, 0), 0.0, node);
						node = insertNode(Vector4(px + h / 3.0, py + 2*h / 3.0, pz, 0), 0.0, node);
						node = insertNode(Vector4(px + 2*h / 3.0, py + 2*h / 3.0, pz, 0), 0.0, node);
					}
					else
					{
						node = insertNode(Vector4(px + 0.5 * h, py + a * h, pz, 0), w, node);
						node = insertNode(Vector4(px + 0.5 * h, py + b * h, pz, 0), w, node);
					}
				}
				if(xi < xs && zi < zs)
				{
					if(yi == 0 || yi == ys)
					{
						node = insertNode(Vector4(px + h / 3.0, py, pz + h / 3.0, 0), 0.0, node);
						node = insertNode(Vector4(px + 2*h / 3.0, py, pz + h / 3.0, 0), 0.0, node);
						node = insertNode(Vector4(px + h / 3.0, py, pz + 2*h / 3.0, 0), 0.0, node);
						node = insertNode(Vector4(px + 2*h / 3.0, py, pz + 2*h / 3.0, 0), 0.0, node);
					}
					else
					{
						node = insertNode(Vector4(px + a * h, py, pz + 0.5 * h, 0), w, node);
						node = insertNode(Vector4(px + b * h, py, pz + 0.5 * h, 0), w, node);
					}
				}
				if(zi < zs && yi < ys)
				{
					if(xi == 0 || xi == xs)
					{
						node = insertNode(Vector4(px, py + h / 3.0, pz + h / 3.0, 0), 0.0, node);
						node = insertNode(Vector4(px, py + 2*h / 3.0, pz + h / 3.0, 0), 0.0, node);
						node = insertNode(Vector4(px, py + h / 3.0, pz + 2*h / 3.0, 0), 0.0, node);
						node = insertNode(Vector4(px, py + 2*h / 3.0, pz + 2*h / 3.0, 0), 0.0, node);
					}
					else
					{
						node = insertNode(Vector4(px, py + 0.5 * h, pz + a * h, 0), w, node);
						node = insertNode(Vector4(px, py + 0.5 * h, pz + b * h, 0), w, node);
					}

				}
				if(xi < xs && (yi == 0 || yi == ys || zi == 0 || zi == zs))
				{
					node = insertNode(Vector4(px + h / 3.0, py, pz, 0), 0.0, node);
					node = insertNode(Vector4(px + 2*h / 3.0, py, pz, 0), 0.0, node);
				}
				if(yi < ys && (xi == 0 || xi == xs || zi == 0 || zi == zs))
				{
					node = insertNode(Vector4(px, py + h / 3.0, pz, 0), 0.0, node);
					node = insertNode(Vector4(px, py + 2*h / 3.0, pz, 0), 0.0, node);
				}
				if(zi < zs && (yi == 0 || yi == ys || xi == 0 || xi == xs))
				{
					node = insertNode(Vector4(px, py, pz + h / 3.0, 0), 0.0, node);
					node = insertNode(Vector4(px, py, pz + 2*h / 3.0, 0), 0.0, node);
				}
			}
		}
	}

	const Vector4 pp(p0 + 0.99999 * Vector3(h, h, h), 0.0);
	if(xsize > xs) repeatMiddle(pp, Vector4(h,0,0,0), xsize - xs);
	if(ysize > ys) repeatMiddle(pp, Vector4(0,h,0,0), ysize - ys);
	if(zsize > zs) repeatMiddle(pp, Vector4(0,0,h,0), zsize - zs);
}

void DelaunayMesh::createC15Grid(const Vector3 &minp, const Vector3 &maxp, const ddouble h)
{
	const uint xsize = uint((maxp.x - minp.x) / h - 1e-8) + 1;
	const uint ysize = uint((maxp.y - minp.y) / h - 1e-8) + 1;
	const uint zsize = uint((maxp.z - minp.z) / h - 1e-8) + 1;

	const uint xs = (xsize < 3 ? xsize : 3);
	const uint ys = (ysize < 3 ? ysize : 3);
	const uint zs = (zsize < 3 ? zsize : 3);

	const Vector3 p0 = 0.5 * (maxp + minp - Vector3(xsize * h, ysize * h, zsize * h));
	const Vector3 p1 = p0 + Vector3(xs * h, ys * h, zs * h);

	createGrid(Vector4(p0,0), Vector4(p1,0), h);

	uint node = 0;
	uint xi, yi, zi;
	for(zi=0; zi<=zs; zi++)
	{
		const ddouble pz = p0.z + zi * h;
		for(yi=0; yi<=ys; yi++)
		{
			const ddouble py = p0.y + yi * h;
			for(xi=0; xi<=xs; xi++)
			{
				const ddouble px = p0.x + xi * h;

				if(yi < ys && zi < zs)
				{
					node = insertNode(Vector4(px, py + 0.5 * h, pz + 0.5 * h, 0), 0.0, node);
					if(xi == 0 || xi == xs)
					{
						node = insertNode(Vector4(px, py + 0.25 * h, pz + 0.25 * h, 0), 0.0, node);
						node = insertNode(Vector4(px, py + 0.25 * h, pz + 0.75 * h, 0), 0.0, node);
						node = insertNode(Vector4(px, py + 0.75 * h, pz + 0.25 * h, 0), 0.0, node);
						node = insertNode(Vector4(px, py + 0.75 * h, pz + 0.75 * h, 0), 0.0, node);
						node = insertNode(Vector4(px, py + 0.5 * h, pz + 0.25 * h, 0), 0.0, node);
						node = insertNode(Vector4(px, py + 0.5 * h, pz + 0.75 * h, 0), 0.0, node);
						node = insertNode(Vector4(px, py + 0.25 * h, pz + 0.5 * h, 0), 0.0, node);
						node = insertNode(Vector4(px, py + 0.75 * h, pz + 0.5 * h, 0), 0.0, node);
					}
				}
				if(xi < xs && zi < zs)
				{
					node = insertNode(Vector4(px + 0.5 * h, py, pz + 0.5 * h, 0), 0.0, node);
					if(yi == 0 || yi == ys)
					{
						node = insertNode(Vector4(px + 0.25 * h, py, pz + 0.25 * h, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.25 * h, py, pz + 0.75 * h, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.75 * h, py, pz + 0.25 * h, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.75 * h, py, pz + 0.75 * h, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.5 * h, py, pz + 0.25 * h, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.5 * h, py, pz + 0.75 * h, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.25 * h, py, pz + 0.5 * h, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.75 * h, py, pz + 0.5 * h, 0), 0.0, node);
					}
				}
				if(xi < xs && yi < ys)
				{
					node = insertNode(Vector4(px + 0.5 * h, py + 0.5 * h, pz, 0), 0.0, node);
					if(zi == 0 || zi == zs)
					{
						node = insertNode(Vector4(px + 0.25 * h, py + 0.25 * h, pz, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.25 * h, py + 0.75 * h, pz, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.75 * h, py + 0.25 * h, pz, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.75 * h, py + 0.75 * h, pz, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.5 * h, py + 0.25 * h, pz, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.5 * h, py + 0.75 * h, pz, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.25 * h, py + 0.5 * h, pz, 0), 0.0, node);
						node = insertNode(Vector4(px + 0.75 * h, py + 0.5 * h, pz, 0), 0.0, node);
					}
				}

				if(xi < xs && (yi == 0 || yi == ys || zi == 0 || zi == zs))
				{
					node = insertNode(Vector4(px + 0.25 * h, py, pz, 0), 0.0, node);
					node = insertNode(Vector4(px + 0.5 * h, py, pz, 0), 0.0, node);
					node = insertNode(Vector4(px + 0.75 * h, py, pz, 0), 0.0, node);
				}
				if(yi < ys && (xi == 0 || xi == xs || zi == 0 || zi == zs))
				{
					node = insertNode(Vector4(px, py + 0.25 * h, pz, 0), 0.0, node);
					node = insertNode(Vector4(px, py + 0.5 * h, pz, 0), 0.0, node);
					node = insertNode(Vector4(px, py + 0.75 * h, pz, 0), 0.0, node);
				}
				if(zi < zs && (yi == 0 || yi == ys || xi == 0 || xi == xs))
				{
					node = insertNode(Vector4(px, py, pz + 0.25 * h, 0), 0.0, node);
					node = insertNode(Vector4(px, py, pz + 0.5 * h, 0), 0.0, node);
					node = insertNode(Vector4(px, py, pz + 0.75 * h, 0), 0.0, node);
				}
				if(xi < xs && yi < ys && zi < zs)
				{
					node = insertNode(Vector4(px + 0.25 * h, py + 0.75 * h, pz + 0.75 * h, 0), 0.0, node);
					node = insertNode(Vector4(px + 0.75 * h, py + 0.25 * h, pz + 0.75 * h, 0), 0.0, node);
					node = insertNode(Vector4(px + 0.75 * h, py + 0.75 * h, pz + 0.25 * h, 0), 0.0, node);
					node = insertNode(Vector4(px + 0.25 * h, py + 0.25 * h, pz + 0.25 * h, 0), 0.0, node);

					if(xi > 0 && zi < zs-1) node = insertNode(Vector4(px + 0.125 * h, py + 0.375 * h, pz + 0.875 * h, 0), 0.0, node);
					if(xi > 0 && yi > 0) node = insertNode(Vector4(px + 0.125 * h, py + 0.125 * h, pz + 0.625 * h, 0), 0.0, node);
					if(yi > 0 && zi < zs-1) node = insertNode(Vector4(px + 0.375 * h, py + 0.125 * h, pz + 0.875 * h, 0), 0.0, node);
					node = insertNode(Vector4(px + 0.375 * h, py + 0.375 * h, pz + 0.625 * h, 0), 0.0, node);

					if(xi > 0 && yi < ys-1) node = insertNode(Vector4(px + 0.125 * h, py + 0.875 * h, pz + 0.375 * h, 0), 0.0, node);
					if(zi > 0 && yi < ys-1) node = insertNode(Vector4(px + 0.375 * h, py + 0.875 * h, pz + 0.125 * h, 0), 0.0, node);
					node = insertNode(Vector4(px + 0.375 * h, py + 0.625 * h, pz + 0.375 * h, 0), 0.0, node);
					if(xi > 0 && zi > 0) node = insertNode(Vector4(px + 0.125 * h, py + 0.625 * h, pz + 0.125 * h, 0), 0.0, node);

					if(yi > 0 && zi > 0) node = insertNode(Vector4(px + 0.625 * h, py + 0.125 * h, pz + 0.125 * h, 0), 0.0, node);
					if(xi < xs-1 && zi > 0) node = insertNode(Vector4(px + 0.875 * h, py + 0.375 * h, pz + 0.125 * h, 0), 0.0, node);
					node = insertNode(Vector4(px + 0.625 * h, py + 0.375 * h, pz + 0.375 * h, 0), 0.0, node);
					if(yi > 0 && xi < xs-1) node = insertNode(Vector4(px + 0.875 * h, py + 0.125 * h, pz + 0.375 * h, 0), 0.0, node);

					node = insertNode(Vector4(px + 0.625 * h, py + 0.625 * h, pz + 0.625 * h, 0), 0.0, node);
					if(xi < xs-1 && zi < zs-1) node = insertNode(Vector4(px + 0.875 * h, py + 0.625 * h, pz + 0.875 * h, 0), 0.0, node);
					if(xi < xs-1 && yi < ys-1) node = insertNode(Vector4(px + 0.875 * h, py + 0.875 * h, pz + 0.625 * h, 0), 0.0, node);
					if(yi < ys-1 && zi < zs-1) node = insertNode(Vector4(px + 0.625 * h, py + 0.875 * h, pz + 0.875 * h, 0), 0.0, node);
				}
			}
		}
	}

	const Vector4 pp(p0 + 0.99999 * Vector3(h, h, h), 0.0);
	if(xsize > xs) repeatMiddle(pp, Vector4(h,0,0,0), xsize - xs);
	if(ysize > ys) repeatMiddle(pp, Vector4(0,h,0,0), ysize - ys);
	if(zsize > zs) repeatMiddle(pp, Vector4(0,0,h,0), zsize - zs);
}

void DelaunayMesh::createZGrid(const Vector3 &minp, const Vector3 &maxp, const ddouble h)
{
	const Vector3 d(h, h * sqrt(3.0), h);
	const uint xsize = uint((maxp.x - minp.x) / d.x + 0.99999);
	const uint ysize = uint((maxp.y - minp.y) / d.y + 0.99999);
	const uint zsize = uint((maxp.z - minp.z) / d.z + 0.99999);

	const uint xs = (xsize < 3 ? xsize : 3);
	const uint ys = (ysize < 3 ? ysize : 3);
	const uint zs = (zsize < 3 ? zsize : 3);

	const Vector3 p0 = 0.5 * (maxp + minp - Vector3(xsize * d.x, ysize * d.y, zsize * d.z));
	const Vector3 p1 = p0 + Vector3(xs * d.x, ys * d.y, zs * d.z);
	createTriangleGrid(Vector2(p0.x, p0.y), Vector2(p1.x, p1.y), h, true);
	move(Vector4(0,0,p0.z,0));
	stretchLinear(Vector4(0,0,p1.z-p0.z,0), 2*zs);

	uint node = 0;
	uint xi, yi, zi;
	for(zi=0; zi<zs; zi++)
	{
		const ddouble pz = p0.z + d.z * zi;
		for(yi=0; yi<ys; yi++)
		{
			const ddouble py = p0.y + d.y * yi;
			for(xi=0; xi<xs; xi++)
			{
				const ddouble px = p0.x + d.x * xi;
				node = insertNode(Vector4(px + 0.25 * d.x, py + 0.25 * d.y, pz + 0.75 * d.z, 0), 0.0, node);
				node = insertNode(Vector4(px + 0.25 * d.x, py + 0.75 * d.y, pz + 0.75 * d.z, 0), 0.0, node);
				node = insertNode(Vector4(px + 0.75 * d.x, py + 0.25 * d.y, pz + 0.75 * d.z, 0), 0.0, node);
				node = insertNode(Vector4(px + 0.75 * d.x, py + 0.75 * d.y, pz + 0.75 * d.z, 0), 0.0, node);
				node = insertNode(Vector4(px + 0.5 * d.x, py + 1.0 / 6.0 * d.y, pz + 0.25 * d.z, 0), 0.0, node);
				node = insertNode(Vector4(px + 0.5 * d.x, py + 5.0 / 6.0 * d.y, pz + 0.25 * d.z, 0), 0.0, node);
				if(xi > 0)
				{
                    node = insertNode(Vector4(px, py + 0.5 * d.y, pz + 0.75 * d.z, 0), 0.0, node);
                    node = insertNode(Vector4(px, py + 1.0 / 3.0 * d.y, pz + 0.25 * d.z, 0), 0.0, node);
					node = insertNode(Vector4(px, py + 2.0 / 3.0 * d.y, pz + 0.25 * d.z, 0), 0.0, node);
				}
				if(yi > 0)
				{
                    node = insertNode(Vector4(px + 0.5 * d.x, py, pz + 0.75 * d.z, 0), 0.0, node);
				}
			}
		}
	}
	const Vector4 pp(p0 + 0.99999 * d, 0.0);
	if(xsize > xs) repeatMiddle(pp, Vector4(d.x,0,0,0), xsize - xs);
	if(ysize > ys) repeatMiddle(pp, Vector4(0,d.y,0,0), ysize - ys);
	if(zsize > zs) repeatMiddle(pp, Vector4(0,0,d.z,0), zsize - zs);
}


ddouble DelaunayMesh::getRadiusSq(const Vector4 &p, const Buffer<uint> &n) const
{
	ddouble sq = 0.0;
	for(uint i=0; i<n.size(); i++) sq += getRadiusSq(p, n[i]);
	return sq / ddouble(n.size());
}

bool DelaunayMesh::isInSphere(const Vector4 &p, const ddouble sq, const Buffer<uint> &n) const
{
	const ddouble safeSq = RADIUSSCALE * sq;
	for(uint i=0; i<n.size(); i++)
	{
		if(getRadiusSq(p, n[i]) > safeSq) return false;
	}
	return true;
}

bool DelaunayMesh::isOutsideSphere(const Vector4 &p, const ddouble sq, const Buffer<uint> &n) const
{
	const ddouble safeSq = sq / RADIUSSCALE;
	for(uint i=0; i<n.size(); i++)
	{
		if(getRadiusSq(p, n[i]) < safeSq) return false;
	}
	return true;
}

uint DelaunayMesh::findNode(const Vector4 &p, uint curr) const
{
	// check starter node
	if(curr >= m_nsize) return NONE;

	// travel and find the nearest node
	ddouble currsq = getRadiusSq(p, curr);
	while(true)
	{
		const uint prev = curr;
		const Buffer<uint> &e = getNodeEdges(prev);
		for(uint i=0; i<e.size(); i++)
		{
			const uint next = getEdgeOtherNode(e[i], prev);
			const ddouble nextsq = getRadiusSq(p, next);

			if(nextsq < currsq)
			{
				curr = next;
				currsq = nextsq;
			}
		}
		if(prev == curr) return curr;
	}
}

bool DelaunayMesh::findCell(const Vector4 &p, uint &curr) const
{
	if(m_nsize == 0) return false;
	if(m_esize == 0) // 0-dimensional mesh
	{
		if(curr >= m_nsize) curr = 0;
		return (getNodePosition(curr) - p).lensq() < ORTOGONALSQ;
	}
	uint i;
	if(m_fsize == 0) // 1-dimensional mesh
	{
		if(curr >= m_esize) curr = 0;
		uint prev = NONE;
		while(true)
		{
			const Vector4 p1 = getEdgeAverage(curr);
			const Buffer<uint> &n = getEdgeNodes(curr);
			for(i=0; i<n.size(); i++)
			{
				if(n[i] == prev) continue;
				const Vector4 p0 = getNodePosition(n[i]);
				const Vector4 v = p - p0;
				if(v.lensq() < ORTOGONALSQ || v.dot(p1 - p0) > 0.0) continue;

				const Buffer<uint> &e = getNodeEdges(n[i]);
				if(e.size() < 2)
				{
					curr = n[i];
					return false;
				}
				if(e[0] == curr) curr = e[1];
				else curr = e[0];
				prev = n[i];
				break;
			}
			if(i == n.size()) return true;
		}
	}
	if(m_bsize == 0) // 2-dimensional mesh
	{
		if(curr >= m_fsize) curr = 0;
		uint prev = NONE;
		while(true)
		{
			const Vector4 p1 = getFaceAverage(curr);
			const Buffer<uint> &e = getFaceEdges(curr);
			for(i=0; i<e.size(); i++)
			{
				if(e[i] == prev) continue;
				const Vector4 p0 = getEdgeAverage(e[i]);
				const Vector4 v = getEdgeOrthogonal(e[i], p - p0);
				if(v.lensq() < ORTOGONALSQ || v.dot(p1 - p0) > 0.0) continue;

				const Buffer<uint> &f = getEdgeFaces(e[i]);
				if(f.size() < 2)
				{
					curr = e[i];
					return false;
				}
				if(f[0] == curr) curr = f[1];
				else curr = f[0];
				prev = e[i];
				break;
			}
			if(i == e.size()) return true;
		}
	}
	if(m_qsize == 0) // 3-dimensional mesh
	{
		if(curr >= m_bsize) curr = 0;
		uint prev = NONE;
		while(true)
		{
			const Vector4 p1 = getBodyAverage(curr);
			const Buffer<uint> &f = getBodyFaces(curr);
			for(i=0; i<f.size(); i++)
			{
				if(f[i] == prev) continue;
				const Vector4 p0 = getFaceAverage(f[i]);
				const Vector4 v = getFaceOrthogonal(f[i], p - p0);
				if(v.lensq() < ORTOGONALSQ || v.dot(p1 - p0) > 0.0) continue;

				const Buffer<uint> &b = getFaceBodies(f[i]);
				if(b.size() < 2)
				{
					curr = f[i];
					return false;
				}
				if(b[0] == curr) curr = b[1];
				else curr = b[0];
				prev = f[i];
				break;
			}
			if(i == f.size()) return true;
		}
	}
	// 4-dimensional mesh
	if(curr >= m_qsize) curr = 0;
	uint prev = NONE;
	while(true)
	{
		const Vector4 p1 = getQuadAverage(curr);
		const Buffer<uint> &b = getQuadBodies(curr);
		for(i=0; i<b.size(); i++)
		{
			if(b[i] == prev) continue;
			const Vector4 p0 = getBodyAverage(b[i]);
			const Vector4 v = getBodyOrthogonal(b[i], p - p0);
			if(v.lensq() < ORTOGONALSQ || v.dot(p1 - p0) > 0.0) continue;

			const Buffer<uint> &q = getBodyQuads(b[i]);
			if(q.size() < 2)
			{
				curr = b[i];
				return false;
			}
			if(q[0] == curr) curr = q[1];
			else curr = q[0];
			prev = b[i];
			break;
		}
		if(i == b.size()) return true;
	}
}


uint DelaunayMesh::insertNode(const Vector4 &p, const ddouble w, uint nearNode)
{
	uint i, j, k, l;

	// Check if the node already exists
	nearNode = findNode(p, nearNode);
	if(nearNode != NONE && (getNodePosition(nearNode) - p).lensq() < MINLENGTHSQ) return nearNode;

	// Create new node
	const uint node = addNode(p);

	if(w != 0.0) setNodeWeight(node, w);
	if(nearNode == NONE) return node; // this is the first node

	if(m_esize == 0) // 0-dimensional convex mesh (only one node exists)
	{
		addEdge(nearNode, node);
		return node;
	}

	if(m_fsize == 0) // 1-dimensional convex mesh (mesh on a straight line)
	{
		const Vector4 d = getNodePosition(nearNode) - p;
		uint curr = getNodeEdges(nearNode)[0];
		if(getEdgeOrthogonal(curr, d).lensq() > ORTOGONALSQ) // the new node increase the mesh dimension to 2
		{
			increaseDimension();
			return node;
		}
		if(findCell(p, curr)) // insert node inside the mesh. replace curr with two edges
		{
			const Buffer<uint> en = getEdgeNodes(curr);
			detachEdge(curr);
			for(j=0; j<en.size(); j++) addEdge(en[j], node);
		}
		else // insert node outside of the mesh
		{
			addEdge(curr, node);
		}
		return node;
	}

	if(m_bsize == 0) // 2-dimensional convex mesh (mesh on a plane)
	{
		const Vector4 d = getNodePosition(nearNode) - p;
		uint curr = getEdgeFaces(getNodeEdges(nearNode)[0])[0];
		if(getFaceOrthogonal(curr, d).lensq() > ORTOGONALSQ) // the new node increase the mesh dimension to 3
		{
			increaseDimension();
			return node;
		}
		uint fes = 0;
		Buffer<uint> fe;
		if(findCell(p, curr)) // insert node inside the mesh.
		{
			fe = getFaceEdges(curr);
			fes = fe.size();
			detachFace(curr);
		}
		else // insert node outside of the mesh
		{
			fe.gather(curr, fes);
			Buffer<uint> fn = getEdgeNodes(curr);
			uint fns = fn.size();
			while(fns > 0)
			{
				const Buffer<uint> &ne = getNodeEdges(fn[0]);
				for(i=0; i<ne.size(); i++)
				{
					const Buffer<uint> &ef = getEdgeFaces(ne[i]);
					if(ef.size() != 1) continue; // ne[i] is not on boundary
					if(fe.includes(ne[i], fes)) continue; // ne[i] is already on the list fe

					// the unique next boundary edge is found
					const Vector4 p0 = getEdgeAverage(ne[i]);
					const Vector4 v = getEdgeOrthogonal(ne[i], p - p0);
					const Buffer<uint> &en = getEdgeNodes(ne[i]);
					if(v.lensq() > ORTOGONALSQ && v.dot(getFaceAverage(ef[0]) - p0) < 0.0)
					{
						fe.gather(ne[i], fes);
						for(j=0; j<en.size(); j++) fn.gatherOrUngather(en[j], fns);
						break;
					}
					for(j=0; j<en.size(); j++) fn.ungather(en[j], fns);
					break;
				}
			}
		}

		// remove recursively
		for(i=0; i<fes; i++)
		{
			const Buffer<uint> &ef = getEdgeFaces(fe[i]);
			if(getEdgeOrthogonal(fe[i], p - getEdgeAverage(fe[i])).lensq() > ORTOGONALSQ) // p is linearly independent of edge
			{
				if(ef.empty()) continue; // fe[i] is a boundary edge

				const Vector4 fp = getFacePosition(ef[0]);
				const ddouble fsq = getRadiusSq(fp, getEdgeNodes(fe[i]));
				if(!isInSphere(fp, fsq, node)) continue; // node is outside the face radius
			}

			// remove edge ->
			const Buffer<uint> efe = (ef.empty() ? Buffer<uint>(1, fe[i]) : getFaceEdges(ef[0]));
			for(j=0; j<efe.size(); j++)
			{
				if(fe.gatherOrUngather(efe[j], fes)) continue;
				if(i + 1 != 0) i--;
				detachEdgeRecursive(efe[j]);
			}
		}

		// insert faces
		for(i=0; i<fes; i++)
		{
			const Buffer<uint> en = getEdgeNodes(fe[i]);
			Buffer<uint> ee(en.size() + 1);
			for(j=0; j<en.size(); j++) ee[j] = addEdge(en[j], node);
			ee[j] = fe[i];
			fe[i] = addFace(ee);
		}
		for(i=0; i<fes; i++) mergeFace(fe[i]);

		// remove unnecessary edges
		removeDetached();
		return node;
	}

	if(m_qsize == 0) // 3-dimensional convex mesh
	{
		const Vector4 d = getNodePosition(nearNode) - p;
		uint curr = getFaceBodies(getEdgeFaces(getNodeEdges(nearNode)[0])[0])[0];
		if(getBodyOrthogonal(curr, d).lensq() > ORTOGONALSQ) // the new node increase the mesh dimension to 4
		{
			increaseDimension();
			return node;
		}
		uint bfs = 0;
		Buffer<uint> bf;
		if(findCell(p, curr)) // insert node inside the mesh.
		{
			bf = getBodyFaces(curr);
			bfs = bf.size();
			detachBody(curr);
		}
		else // insert node outside of the mesh
		{
			bf.gather(curr, bfs);
			Buffer<uint> be = getFaceEdges(curr);
			uint bes = be.size();
			while(bes > 0)
			{
				const Buffer<uint> &ef = getEdgeFaces(be[0]);
				for(i=0; i<ef.size(); i++)
				{
					const Buffer<uint> &fb = getFaceBodies(ef[i]);
					if(fb.size() != 1) continue; // ef[i] is not on boundary
					if(bf.includes(ef[i], bfs)) continue; // ef[i] is already on the list bf

					// the unique next boundary face is found
					const Vector4 p0 = getFaceAverage(ef[i]);
					const Vector4 v = getFaceOrthogonal(ef[i], p - p0);
					const Buffer<uint> &fe = getFaceEdges(ef[i]);
					if(v.lensq() > ORTOGONALSQ && v.dot(getBodyAverage(fb[0]) - p0) < 0.0)
					{
						bf.gather(ef[i], bfs);
						for(j=0; j<fe.size(); j++) be.gatherOrUngather(fe[j], bes);
						break;
					}
					for(j=0; j<fe.size(); j++) be.ungather(fe[j], bes);
					break;
				}
			}
		}

		// remove recursively
		for(i=0; i<bfs; i++)
		{
			const Buffer<uint> &fb = getFaceBodies(bf[i]);
			if(getFaceOrthogonal(bf[i], p - getFaceAverage(bf[i])).lensq() > ORTOGONALSQ) // p is linearly independent of face
			{
				if(fb.empty()) continue; // bf[i] is a boundary face

				const Vector4 bp = getBodyPosition(fb[0]);
				const ddouble bsq = getRadiusSq(bp, getFaceNodes(bf[i]));
				if(!isInSphere(bp, bsq, node)) continue; // node is outside the body radius
			}

			// remove face ->
			const Buffer<uint> fbf = (fb.empty() ? Buffer<uint>(1, bf[i]) : getBodyFaces(fb[0]));
			for(j=0; j<fbf.size(); j++)
			{
				if(bf.gatherOrUngather(fbf[j], bfs)) continue;
				if(i + 1 != 0) i--;
				detachFaceRecursive(fbf[j]);
			}
		}

		// insert bodies
		for(i=0; i<bfs; i++)
		{
			const Buffer<uint> fe = getFaceEdges(bf[i]);
			Buffer<uint> ff(fe.size() + 1);
			for(j=0; j<fe.size(); j++)
			{
				const Buffer<uint> en = getEdgeNodes(fe[j]);
				Buffer<uint> ee(en.size() + 1);
				for(k=0; k<en.size(); k++) ee[k] = addEdge(en[k], node);
				ee[k] = fe[j];
				ff[j] = addFace(ee);
			}
			ff[j] = bf[i];
			bf[i] = addBody(ff);
		}
		for(i=0; i<bfs; i++) mergeBody(bf[i]);

		// remove unnecessary faces and edges
		removeDetached();
		return node;
	}

	// 4-dimensional mesh
	uint curr = getBodyQuads(getFaceBodies(getEdgeFaces(getNodeEdges(nearNode)[0])[0])[0])[0];
	uint qbs = 0;
	Buffer<uint> qb;
	if(findCell(p, curr)) // insert node inside the mesh.
	{
		qb = getQuadBodies(curr);
		qbs = qb.size();
		removeQuad(curr);
	}
	else // insert node outside of the mesh
	{
		qb.gather(curr, qbs);
		Buffer<uint> qf = getBodyFaces(curr);
		uint qfs = qf.size();
		while(qfs > 0)
		{
			const Buffer<uint> &fb = getFaceBodies(qf[0]);
			for(i=0; i<fb.size(); i++)
			{
				const Buffer<uint> &bq = getBodyQuads(fb[i]);
				if(bq.size() != 1) continue; // fb[i] is not on boundary
				if(qb.includes(fb[i], qbs)) continue; // fb[i] is already on the list qb

				// the unique next boundary body is found
				const Vector4 p0 = getBodyAverage(fb[i]);
				const Vector4 v = getBodyOrthogonal(fb[i], p - p0);
				const Buffer<uint> &bf = getBodyFaces(fb[i]);
				if(v.lensq() > ORTOGONALSQ && v.dot(getQuadAverage(bq[0]) - p0) < 0.0)
				{
					qb.gather(fb[i], qbs);
					for(j=0; j<bf.size(); j++) qf.gatherOrUngather(bf[j], qfs);
					break;
				}
				for(j=0; j<bf.size(); j++) qf.ungather(bf[j], qfs);
				break;
			}
		}
	}

	// remove recursively
	for(i=0; i<qbs; i++)
	{
		const Buffer<uint> &bq = getBodyQuads(qb[i]);
		if(getBodyOrthogonal(qb[i], p - getBodyAverage(qb[i])).lensq() > ORTOGONALSQ) // p is linearly independent of body
		{
			if(bq.empty()) continue; // qb[i] is a boundary body

			const Vector4 qp = getQuadPosition(bq[0]);
			const ddouble qsq = getRadiusSq(qp, getBodyNodes(qb[i]));
			if(!isInSphere(qp, qsq, node)) continue; // node is outside the quad radius
		}

		// remove body ->
		const Buffer<uint> bqb = (bq.empty() ? Buffer<uint>(1, qb[i]) : getQuadBodies(bq[0]));
		for(j=0; j<bqb.size(); j++)
		{
			if(qb.gatherOrUngather(bqb[j], qbs)) continue;
			if(i + 1 != 0) i--;
			detachBodyRecursive(bqb[j]);
		}
	}

	// insert quads
	for(i=0; i<qbs; i++)
	{
		const Buffer<uint> bf = getBodyFaces(qb[i]);
		Buffer<uint> bb(bf.size() + 1);
		for(j=0; j<bf.size(); j++)
		{
			const Buffer<uint> fe = getFaceEdges(bf[j]);
			Buffer<uint> ff(fe.size() + 1);
			for(k=0; k<fe.size(); k++)
			{
				const Buffer<uint> en = getEdgeNodes(fe[k]);
				Buffer<uint> ee(en.size() + 1);
				for(l=0; l<en.size(); l++) ee[l] = addEdge(en[l], node);
				ee[l] = fe[k];
				ff[k] = addFace(ee);
			}
			ff[k] = bf[j];
			bb[j] = addBody(ff);
		}
		bb[j] = qb[i];
		qb[i] = addQuad(bb);
	}
	for(i=0; i<qbs; i++) mergeQuad(qb[i]);

	removeDetached();
	return node;
}
/*
bool DelaunayMesh::eraseNode(const uint n)
{
	uint i, j, k;
	if(n >= m_nsize) return false;

	if(m_esize == 0) // 0-dimensional convex mesh (only one node exists)
	{
		removeNode(n);
		return true;
	}

	if(m_fsize == 0) // 1-dimensional convex mesh (mesh on a straight line)
	{
		const Buffer<uint> &ne = getNodeEdges(n);
		if(ne.size() >= 2) addEdge(getEdgeOtherNode(ne[0], n), getEdgeOtherNode(ne[1], n));
		removeNode(n);
		return true;
	}

	if(m_bsize == 0)
	{
		// remove node and store hole boundary
		uint es = 0;
		Buffer<uint> e;
		const Buffer<uint> nf = getNodeFaces(n);
		for(i=0; i<nf.size(); i++)
		{
			const Buffer<uint> &fe = getFaceEdges(nf[i]);
			for(j=0; j<fe.size(); j++) e.gatherOrUngather(fe[j], es);
		}
		const Buffer<uint> &ne = getNodeEdges(n);
		for(i=0; i<ne.size(); i++) e.ungather(ne[i], es);
		detachNode(n);

		// fill the hole by faces
		uint fs = 0;
		Buffer<uint> f;
		for(i=1; i<es; i++)
		{
			for(j=0; j<i; j++)
			{
				const uint in = getEdgeIntersection(e[i], e[j]);
				if(in == NONE) continue;

				const Vector4 ip = getEdgeAverage(e[i]);
				const Vector4 jp = getEdgeAverage(e[j]);
				const Vector4 iv = getEdgeOrthogonal(e[i], jp - ip);
				if(iv.lensq() < ORTOGONALSQ) continue;
				const Buffer<uint> &ief = getEdgeFaces(e[i]);
				if(!ief.empty() && iv.dot(getFaceAverage(ief[0]) - ip) > 0.0) continue;
				const Vector4 jv = getEdgeOrthogonal(e[j], ip - jp);
				if(jv.lensq() < ORTOGONALSQ) continue;
				const Buffer<uint> &jef = getEdgeFaces(e[j]);
				if(!jef.empty() && jv.dot(getFaceAverage(jef[0]) - jp) > 0.0) continue;

				// check if e[i] and e[j] combines a face
				const SymmMatrix4 &met = getMetric();
				const Vector4 p0 = getEdgePosition(e[i]);
				const Vector4 v0 = met * getEdgeVector(e[i]);
				const Vector4 v1 = met * getEdgeVector(e[j]);
				SymmMatrix4 mA = SymmMatrix4(v0) + SymmMatrix4(v1);
				const Vector4 vB = v1 * v1.dot(getEdgePosition(e[j]) - p0);
				const TwoVector4 fv(v0, v1);
				mA += SymmMatrix4(fv.wedgeX()) + SymmMatrix4(fv.wedgeY()) + SymmMatrix4(fv.wedgeZ()) + SymmMatrix4(fv.wedgeT());
				const Vector4 fp = p0 + mA.inverse() * vB;
				const ddouble fsq = getRadiusSq(fp, in);
				for(k=0; k<es && (k == i || k == j || isOutsideSphere(fp, fsq, getEdgeNodes(e[k]))); k++);
				if(k < es) continue;

				// create convex face
				const uint face = addConvexFace(e[i], e[j]);
				f.gather(face, fs);

				// change the hole boundary
				const Buffer<uint> &fe = getFaceEdges(face);
				for(k=0; k<fe.size(); k++) e.gatherOrUngather(fe[k], es);
				i = 0;
			}
		}
		for(i=0; i<fs; i++) mergeFace(f[i]);
		removeDetached();
		return true;
	}

	if(m_qsize == 0)
	{
		const Vector4 np = getNodePosition(n);
		std::cout << "node " << np.x << " " << np.y << " " << np.z << std::endl;

		// remove node and store hole boundary
		uint fs = 0;
		Buffer<uint> f;
		const Buffer<uint> nb = getNodeBodies(n);
		for(i=0; i<nb.size(); i++)
		{
			const Buffer<uint> &bf = getBodyFaces(nb[i]);
			for(j=0; j<bf.size(); j++) f.gatherOnce(bf[j], fs);
		}
		const Buffer<uint> nf = getNodeFaces(n);
		for(i=0; i<nf.size(); i++) f.ungather(nf[i], fs);
		detachNode(n);

		// fill the hole by bodies
		uint bs = 0;
		Buffer<uint> b;
		for(i=1; i<fs; i++)
		{
			for(j=0; j<i; j++)
			{
				// try to form a body by f[i] and f[j]
				// check if f[i] and f[j] links common edge but no common body
				const uint ie = getFaceIntersection(f[i], f[j]);
				if(ie == NONE) continue;
				const Buffer<uint> &ifb = getFaceBodies(f[i]);
				const Buffer<uint> &jfb = getFaceBodies(f[j]);
				if(getCommon(ifb, jfb) != NONE) continue;

				// check if the body is convex
				const Vector4 ip = getFaceAverage(f[i]);
				const Vector4 jp = getFaceAverage(f[j]);
				const Vector4 iv = getFaceOrthogonal(f[i], jp - ip);
				if(iv.lensq() < ORTOGONALSQ) continue;
				if(!ifb.empty() && iv.dot(getBodyAverage(ifb[0]) - ip) > 0.0) continue;
				const Vector4 jv = getFaceOrthogonal(f[j], ip - jp);
				if(jv.lensq() < ORTOGONALSQ) continue;
				if(!jfb.empty() && jv.dot(getBodyAverage(jfb[0]) - jp) > 0.0) continue;

				// check if the circum-circle of the body includes no other points
				const SymmMatrix4 &met = getMetric();
				const Vector4 p = getEdgePosition(ie);
				const Vector4 v = getEdgeVector(ie);
				SymmMatrix4 mA(met * v);
				Vector4 vB(0,0,0,0);
				const Buffer<uint> &fe0 = getFaceEdges(f[i]);
				for(k=0; k<fe0.size(); k++)
				{
					if(fe0[k] == ie) continue;
					const Vector4 vi = met * getEdgeVector(fe0[k]);
					mA += SymmMatrix4(vi);
					vB += vi * vi.dot(getEdgePosition(fe0[k]) - p);
				}
				const Buffer<uint> &fe1 = getFaceEdges(f[j]);
				for(k=0; k<fe1.size(); k++)
				{
					if(fe1[k] == ie) continue;
					const Vector4 vi = met * getEdgeVector(fe1[k]);
					mA += SymmMatrix4(vi);
					vB += vi * vi.dot(getEdgePosition(fe1[k]) - p);
				}
				mA += SymmMatrix4(TwoVector4(ip-p, jp-p).wedge(v));
				const Vector4 bp = p + mA.inverse() * vB;
				const ddouble bsq = getRadiusSq(bp, getEdgeNodes(ie));
				for(k=0; k<fs && (k == i || k == j || isOutsideSphere(bp, bsq, getFaceNodes(f[k]))); k++);
				if(k < fs) continue;

				const uint body = addConvexBody(f[i], f[j]);
				b.gather(body, bs);

				// change the hole boundary
				const Buffer<uint> &bf = getBodyFaces(body);
				for(k=0; k<bf.size(); k++) f.gatherOrUngather(bf[k], fs);
				i = 0;
			}
		}
		//for(i=0; i<bs; i++) mergeBody(b[i]);
		removeDetached();
		return true;
	}
}
*/
bool DelaunayMesh::eraseNode(const uint n)
{
	uint i, j, k;
	if(n >= m_nsize) return false;

	if(m_esize == 0) // 0-dimensional convex mesh (only one node exists)
	{
		removeNode(n);
		return true;
	}

	if(m_fsize == 0) // 1-dimensional convex mesh (mesh on a straight line)
	{
		const Buffer<uint> &ne = getNodeEdges(n);
		if(ne.size() >= 2) addEdge(getEdgeOtherNode(ne[0], n), getEdgeOtherNode(ne[1], n));
		removeNode(n);
		return true;
	}

	const Vector4 np = getNodePosition(n);
	if(m_bsize == 0)
	{
		// remove node and store hole boundary
		uint es = 0;
		Buffer<uint> e;
		const Buffer<uint> nf = getNodeFaces(n);
		for(i=0; i<nf.size(); i++)
		{
			const Buffer<uint> &fe = getFaceEdges(nf[i]);
			for(j=0; j<fe.size(); j++) e.gatherOnce(fe[j], es);
		}
		const Buffer<uint> &ne = getNodeEdges(n);
		for(i=0; i<ne.size(); i++) e.ungather(ne[i], es);
		detachNode(n);

		// store boundary nodes
		uint nns = 0;
		Buffer<uint> nn;
		for(i=0; i<es; i++)
		{
			const Buffer<uint> &en = getEdgeNodes(e[i]);
			for(j=0; j<en.size(); j++) nn.gatherOnce(en[j], nns);
		}

		// create new mesh
		uint node = 0;
		DelaunayMesh mesh(m_dim);
		mesh.setMetric(m_met);
		for(i=0; i<nns; i++) node = mesh.insertNode(getNodePosition(nn[i]), getNodeWeight(nn[i]), node);
		if(mesh.getNodeSize() != nns) std::cout << "erase failed: epsilon limits may be too large" << std::endl;

		// remove elements outside
		uint fs = 0;
		Buffer<uint> f;
		for(i=0; i<es; i++)
		{
			const Vector4 p = getEdgeAverage(e[i]);
			for(j=0; (p - mesh.getEdgeAverage(j)).lensq() > MINLENGTHSQ; j++);
			mesh.setEdgeFlag(j, 1);

			const Vector4 v = getEdgeOrthogonal(e[i], np - p);
			const Buffer<uint> &ef = mesh.getEdgeFaces(j);
			for(k=0; k<ef.size(); k++)
			{
				if(v.dot(mesh.getFaceAverage(ef[k]) - p) > 0.0) f.gatherOnce(ef[k], fs);
			}
		}
		for(i=0; i<fs; i++) // try to spread out removable area
		{
			mesh.setFaceFlag(f[i], 1);
			const Buffer<uint> &fe = mesh.getFaceEdges(f[i]);
			for(j=0; j<fe.size(); j++)
			{
				if(mesh.getEdgeFlag(fe[j]) > 0) continue;
				mesh.setEdgeFlag(fe[j], 1);

				const Buffer<uint> &ef = mesh.getEdgeFaces(fe[j]);
				for(k=0; k<ef.size(); k++) f.gatherOnce(ef[k], fs);
			}
		}
		mesh.fillNodeFlags(1);
		mesh.removeByFlags(0);

		// copy elements from mesh
		Buffer<uint> ee(mesh.getEdgeSize());
		for(i=0; i<ee.size(); i++)
		{
			const Buffer<uint> &en = mesh.getEdgeNodes(i);
			ee[i] = addEdge(nn[en[0]], nn[en[1]]);
		}
		for(i=0; i<mesh.getFaceSize(); i++)
		{
			const Buffer<uint> fe = mesh.getFaceEdges(i);
			for(j=0; j<fe.size(); j++) fe[j] = ee[fe[j]];
			addFace(fe);
		}
		removeDetached();

/*
		// remove node and store hole boundary
		uint es = 0;
		Buffer<uint> e;
		const Buffer<uint> nf = getNodeFaces(n);
		for(i=0; i<nf.size(); i++)
		{
			const Buffer<uint> &fe = getFaceEdges(nf[i]);
			for(j=0; j<fe.size(); j++) e.gatherOrUngather(fe[j], es);
		}
		const Buffer<uint> &ne = getNodeEdges(n);
		for(i=0; i<ne.size(); i++) e.ungather(ne[i], es);
		detachNode(n);

		// fill the hole by faces
		uint fs = 0;
		Buffer<uint> f;
		for(i=1; i<es; i++)
		{
			for(j=0; j<i; j++)
			{
				const uint in = getEdgeIntersection(e[i], e[j]);
				if(in == NONE) continue;

				const Vector4 ip = getEdgeAverage(e[i]);
				const Vector4 jp = getEdgeAverage(e[j]);
				const Vector4 iv = getEdgeOrthogonal(e[i], jp - ip);
				if(iv.lensq() < ORTOGONALSQ) continue;
				const Buffer<uint> &ief = getEdgeFaces(e[i]);
				if(!ief.empty() && iv.dot(getFaceAverage(ief[0]) - ip) > 0.0) continue;
				const Vector4 jv = getEdgeOrthogonal(e[j], ip - jp);
				if(jv.lensq() < ORTOGONALSQ) continue;
				const Buffer<uint> &jef = getEdgeFaces(e[j]);
				if(!jef.empty() && jv.dot(getFaceAverage(jef[0]) - jp) > 0.0) continue;

				// check if e[i] and e[j] combines a face
				const SymmMatrix4 &met = getMetric();
				const Vector4 p0 = getEdgePosition(e[i]);
				const Vector4 v0 = met * getEdgeVector(e[i]);
				const Vector4 v1 = met * getEdgeVector(e[j]);
				SymmMatrix4 mA = SymmMatrix4(v0) + SymmMatrix4(v1);
				const Vector4 vB = v1 * v1.dot(getEdgePosition(e[j]) - p0);
				const TwoVector4 fv(v0, v1);
				mA += SymmMatrix4(fv.wedgeX()) + SymmMatrix4(fv.wedgeY()) + SymmMatrix4(fv.wedgeZ()) + SymmMatrix4(fv.wedgeT());
				const Vector4 fp = p0 + mA.inverse() * vB;
				const ddouble fsq = getRadiusSq(fp, in);
				for(k=0; k<es && (k == i || k == j || isOutsideSphere(fp, fsq, getEdgeNodes(e[k]))); k++);
				if(k < es) continue;

				// create convex face
				const uint in = getEdgeIntersection(e0, e1);
				Buffer<uint> ee(3);
				ee[0] = e0;
				ee[1] = e1;
				ee[2] = addEdge(getEdgeOtherNode(e0, in), getEdgeOtherNode(e1, in));
				return addFace(ee);

				const uint face = addConvexFace(e[i], e[j]);
				f.gather(face, fs);

				// change the hole boundary
				const Buffer<uint> &fe = getFaceEdges(face);
				for(k=0; k<fe.size(); k++) e.gatherOrUngather(fe[k], es);
				i = 0;
			}
		}
		for(i=0; i<fs; i++) mergeFace(f[i]);
		removeDetached();
*/		return true;
	}

	if(m_qsize == 0)
	{
		// remove node and store hole boundary
		uint fs = 0;
		Buffer<uint> f;
		const Buffer<uint> nb = getNodeBodies(n);
		for(i=0; i<nb.size(); i++)
		{
			const Buffer<uint> &bf = getBodyFaces(nb[i]);
			for(j=0; j<bf.size(); j++) f.gatherOnce(bf[j], fs);
		}
		const Buffer<uint> nf = getNodeFaces(n);
		for(i=0; i<nf.size(); i++) f.ungather(nf[i], fs);
		detachNode(n);

		// store boundary nodes
		uint nns = 0;
		Buffer<uint> nn;
		for(i=0; i<fs; i++)
		{
			const Buffer<uint> fn = getFaceNodes(f[i]);
			for(j=0; j<fn.size(); j++) nn.gatherOnce(fn[j], nns);
		}

		// create new mesh
		uint node = 0;
		DelaunayMesh mesh(m_dim);
		mesh.setMetric(m_met);
		for(i=0; i<nns; i++) node = mesh.insertNode(getNodePosition(nn[i]), getNodeWeight(nn[i]), node);
		if(mesh.getNodeSize() != nns) std::cout << "erase failed: epsilon limits may be too large" << std::endl;

		// remove elements outside
		uint bs = 0;
		Buffer<uint> b;
		for(i=0; i<fs; i++)
		{
			const Vector4 p = getFaceAverage(f[i]);
			for(j=0; (p - mesh.getFaceAverage(j)).lensq() > MINLENGTHSQ; j++);
			mesh.setFaceFlag(j, 1);

			const Vector4 v = getFaceOrthogonal(f[i], np - p);
			const Buffer<uint> &fb = mesh.getFaceBodies(j);
			for(k=0; k<fb.size(); k++)
			{
				if(v.dot(mesh.getBodyAverage(fb[k]) - p) > 0.0) b.gatherOnce(fb[k], bs);
			}
		}
		for(i=0; i<bs; i++) // try to spread out removable area
		{
			mesh.setBodyFlag(b[i], 1);
			const Buffer<uint> &bf = mesh.getBodyFaces(b[i]);
			for(j=0; j<bf.size(); j++)
			{
				const Buffer<uint> &fe = mesh.getFaceEdges(bf[j]);
				for(k=0; k<fe.size(); k++) mesh.setEdgeFlag(fe[k], 1);

				if(mesh.getFaceFlag(bf[j]) > 0) continue;
				mesh.setFaceFlag(bf[j], 1);

				const Buffer<uint> &fb = mesh.getFaceBodies(bf[j]);
				for(k=0; k<fb.size(); k++) b.gatherOnce(fb[k], bs);
			}
		}
		mesh.fillNodeFlags(1);
		mesh.removeByFlags(0);

		// copy elements from mesh
		Buffer<uint> ee(mesh.getEdgeSize());
		for(i=0; i<ee.size(); i++)
		{
			const Buffer<uint> &en = mesh.getEdgeNodes(i);
			ee[i] = addEdge(nn[en[0]], nn[en[1]]);
		}
		Buffer<uint> ff(mesh.getFaceSize());
		for(i=0; i<ff.size(); i++)
		{
			const Buffer<uint> fe = mesh.getFaceEdges(i);
			for(j=0; j<fe.size(); j++) fe[j] = ee[fe[j]];
			ff[i] = addFace(fe);
		}
		for(i=0; i<mesh.getBodySize(); i++)
		{
			const Buffer<uint> bf = mesh.getBodyFaces(i);
			for(j=0; j<bf.size(); j++) bf[j] = ff[bf[j]];
			addBody(bf);
		}
		removeDetached();
		return true;
	}


	// remove node and store hole boundary
	uint bs = 0;
	Buffer<uint> b;
	const Buffer<uint> nq = getNodeQuads(n);
	for(i=0; i<nq.size(); i++)
	{
		const Buffer<uint> &qb = getQuadBodies(nq[i]);
		for(j=0; j<qb.size(); j++) b.gatherOnce(qb[j], bs);
	}
	const Buffer<uint> nb = getNodeBodies(n);
	for(i=0; i<nb.size(); i++) b.ungather(nb[i], bs);
	detachNode(n);

	// store boundary nodes
	uint nns = 0;
	Buffer<uint> nn;
	for(i=0; i<bs; i++)
	{
		const Buffer<uint> bn = getBodyNodes(b[i]);
		for(j=0; j<bn.size(); j++) nn.gatherOnce(bn[j], nns);
	}

	// create new mesh
	uint node = 0;
	DelaunayMesh mesh(m_dim);
	mesh.setMetric(m_met);
	for(i=0; i<nns; i++) node = mesh.insertNode(getNodePosition(nn[i]), getNodeWeight(nn[i]), node);
	if(mesh.getNodeSize() != nns) std::cout << "erase failed: epsilon limits may be too large" << std::endl;

	// remove elements outside
	uint qs = 0;
	Buffer<uint> q;
	for(i=0; i<bs; i++)
	{
		const Vector4 p = getBodyAverage(b[i]);
		for(j=0; (p - mesh.getBodyAverage(j)).lensq() > MINLENGTHSQ; j++);
		mesh.setBodyFlag(j, 1);

		const Vector4 v = getBodyOrthogonal(b[i], np - p);
		const Buffer<uint> &bq = mesh.getBodyQuads(j);
		for(k=0; k<bq.size(); k++)
		{
			if(v.dot(mesh.getQuadAverage(bq[k]) - p) > 0.0) q.gatherOnce(bq[k], qs);
		}
	}
	for(i=0; i<qs; i++) // try to spread out removable area
	{
		mesh.setQuadFlag(q[i], 1);
		const Buffer<uint> &qb = mesh.getQuadBodies(q[i]);
		for(j=0; j<qb.size(); j++)
		{
			const Buffer<uint> &bf = mesh.getBodyFaces(qb[j]);
			for(k=0; k<bf.size(); k++) mesh.setFaceFlag(bf[k], 1);
			const Buffer<uint> be = mesh.getBodyEdges(qb[j]);
			for(k=0; k<be.size(); k++) mesh.setEdgeFlag(be[k], 1);

			if(mesh.getBodyFlag(qb[j]) > 0) continue;
			mesh.setBodyFlag(qb[j], 1);

			const Buffer<uint> &bq = mesh.getBodyQuads(qb[j]);
			for(k=0; k<bq.size(); k++) q.gatherOnce(bq[k], qs);
		}
	}
	mesh.fillNodeFlags(1);
	mesh.removeByFlags(0);

	// copy elements from mesh
	Buffer<uint> ee(mesh.getEdgeSize());
	for(i=0; i<ee.size(); i++)
	{
		const Buffer<uint> &en = mesh.getEdgeNodes(i);
		ee[i] = addEdge(nn[en[0]], nn[en[1]]);
	}
	Buffer<uint> ff(mesh.getFaceSize());
	for(i=0; i<ff.size(); i++)
	{
		const Buffer<uint> fe = mesh.getFaceEdges(i);
		for(j=0; j<fe.size(); j++) fe[j] = ee[fe[j]];
		ff[i] = addFace(fe);
	}
	Buffer<uint> bb(mesh.getBodySize());
	for(i=0; i<bb.size(); i++)
	{
		const Buffer<uint> bf = mesh.getBodyFaces(i);
		for(j=0; j<bf.size(); j++) bf[j] = ff[bf[j]];
		bb[i] = addBody(bf);
	}
	for(i=0; i<mesh.getQuadSize(); i++)
	{
		const Buffer<uint> qb = mesh.getQuadBodies(i);
		for(j=0; j<qb.size(); j++) qb[j] = bb[qb[j]];
		addQuad(qb);
	}
	removeDetached();
	return true;
}


void DelaunayMesh::increaseDimension()
{
	uint i, j;
	const uint nsize = m_nsize - 1;
	const uint esize = m_esize;
	const uint fsize = m_fsize;
	const uint bsize = m_bsize;

	for(i=0; i<nsize; i++)
	{
		addEdge(i, nsize);
	}
	for(i=0; i<esize; i++)
	{
		const Buffer<uint> &en = getEdgeNodes(i);
		Buffer<uint> fe(en.size() + 1);
		for(j=0; j<en.size(); j++) fe[j] = esize + en[j];
		fe[j] = i;
		addFace(fe);
	}
	for(i=0; i<fsize; i++)
	{
		const Buffer<uint> &fe = getFaceEdges(i);
		Buffer<uint> bf(fe.size() + 1);
		for(j=0; j<fe.size(); j++) bf[j] = fsize + fe[j];
		bf[j] = i;
		addBody(bf);
	}
	for(i=0; i<bsize; i++)
	{
		const Buffer<uint> &bf = getBodyFaces(i);
		Buffer<uint> qb(bf.size() + 1);
		for(j=0; j<bf.size(); j++) qb[j] = bsize + bf[j];
		qb[j] = i;
		addQuad(qb);
	}
}

/*uint DelaunayMesh::addConvexFace(const uint e0, const uint e1)
{
	const uint in = getEdgeIntersection(e0, e1);
	Buffer<uint> ee(3);
	ee[0] = e0;
	ee[1] = e1;
	ee[2] = addEdge(getEdgeOtherNode(e0, in), getEdgeOtherNode(e1, in));
	return addFace(ee);
}

uint DelaunayMesh::addConvexBody(const uint f0, const uint f1)
{
	uint i, j, k;
	uint fs = 2;
	Buffer<uint> f(fs);
	f[0] = f0;
	f[1] = f1;

	// gather boundary edges
	uint es = 0;
	Buffer<uint> e;
	for(i=0; i<fs; i++)
	{
		const Buffer<uint> &fe = getFaceEdges(f[i]);
		for(j=0; j<fe.size(); j++) e.gatherOrUngather(fe[j], es);
	}
	const Vector4 p = getEdgeAverage(getFaceIntersection(f0, f1));

	for(i=1; i<es; i++)
	{
		for(j=0; j<i; j++)
		{
			const uint in = getEdgeIntersection(e[i], e[j]);
			if(in == NONE) continue; // edges are not linked

			uint face = getCommon(getEdgeFaces(e[i]), getEdgeFaces(e[j]));
			if(face == NONE) // common face not found
			{
				// compute base vectors for the new face
				const Vector4 evi = getEdgeVector(e[i]);
				const ddouble esqi = evi.lensq();
				Vector4 evj = getEdgeVector(e[j]);
				evj -= evj.dot(evi) / esqi * evi;
				const ddouble esqj = evj.lensq();

				const Vector4 ip = getNodePosition(in);
				Vector4 v = ip - p;
				v -= v.dot(evi) / esqi * evi + v.dot(evj) / esqj * evj;
				const ddouble limit = sqrt(v.lensq() * ORTOGONALSQ);

				// check the convexity
				for(k=0; k<es; k++)
				{
					if(k == i || k == j) continue;
					const Buffer<uint> &en = getEdgeNodes(e[k]);
					if(v.dot(getNodePosition(en[0]) - ip) > limit) break; // node is on the wrong side
					if(v.dot(getNodePosition(en[1]) - ip) > limit) break; // node is on the wrong side
				}
				if(k < es) continue; // the new face would break convexity

				// create new face connecting e[i] and e[j]
				face = addConvexFace(e[i], e[j]);
			}
			else if(f.includes(face, fs)) continue; // common face is included already

			// insert face and update boundary edges
			f.gather(face, fs);
			const Buffer<uint> &fe = getFaceEdges(face);
			for(k=0; k<fe.size(); k++) e.gatherOrUngather(fe[k], es);
			i = 0;
		}
	}
	f.resize(fs);
//if(es != 0) std::cout << "should be zero " << es << " " << fs << std::endl;
	return addBody(f);
}
*/
uint DelaunayMesh::mergeFace(const uint f)
{
	uint i, j;
	Buffer<uint> &e = m_f[f].e;
	uint es = e.size();
	if(es < 3) return f; // f is detached already
	bool merged = false;
	for(i=0; i<es; i++) m_e[e[i]].f.eraseFirst(f); // temporally uncontact f from edges
	const Buffer<uint> &fb = getFaceBodies(f);
	Vector4 fp(0,0,0,0);
	ddouble fsq = 0.0;
	if(fb.empty())
	{
		fp = getFacePosition(f);
		fsq = getRadiusSq(fp, getFaceNodes(f));
	}
	for(i=0; i<es; i++)
	{
		const Buffer<uint> &ef = getEdgeFaces(e[i]);
		if(ef.size() != 1) continue; // no unique face to merge

		if(fb.empty())
		{
			if(!isInSphere(fp, fsq, getFaceNodes(ef[0]))) continue;
		}
		else
		{
			Buffer<uint> &efb = m_f[ef[0]].b;
			if(!fb.isAnagram(efb)) continue;
			if(fb.size() == 1 && getFaceOrthogonal(f, getFaceAverage(ef[0]) - getEdgeAverage(e[i])).lensq() > ORTOGONALSQ) continue;
			for(j=0; j<fb.size(); j++) m_b[fb[j]].f.eraseFirst(ef[0]); // uncontact ef[0] from bodies
			efb.clear();
		}

		// merge face ->
		const Buffer<uint> fe = getFaceEdges(ef[0]);
		for(j=0; j<fe.size(); j++)
		{
			if(e.gatherOrUngather(fe[j], es)) continue;
			if(i + 1 != 0) i--;
			detachEdgeRecursive(fe[j]);
		}
		merged = true;
		e.resize(es);
	}

	for(i=0; i<es; i++) m_e[e[i]].f.push_back(f); // contact f by edges
	if(!merged) return f; // face is unchanged
	orderFaceEdges(f);
	for(j=0; j<fb.size(); j++) orderBodyFaces(fb[j]);
	return f;
}

uint DelaunayMesh::mergeBody(const uint b)
{
	uint i, j;
	Buffer<uint> &f = m_b[b].f;
	uint fs = f.size();
	if(fs < 4) return b; // b is detached already
	bool merged = false;
	for(i=0; i<fs; i++) m_f[f[i]].b.eraseFirst(b); // temporally uncontact b from faces
	const Buffer<uint> &bq = getBodyQuads(b);
	Vector4 bp(0,0,0,0);
	ddouble bsq = 0.0;
	if(bq.empty())
	{
		bp = getBodyPosition(b);
		bsq = getRadiusSq(bp, getBodyNodes(b));
	}
	for(i=0; i<fs; i++)
	{
		const Buffer<uint> &fb = getFaceBodies(f[i]);
		if(fb.size() != 1) continue; // no unique body to merge

		if(bq.empty())
		{
			if(!isInSphere(bp, bsq, getBodyNodes(fb[0]))) continue;
		}
		else
		{
			Buffer<uint> &fbq = m_b[fb[0]].q;
			if(!bq.isAnagram(fbq)) continue;
			if(bq.size() == 1 && getBodyOrthogonal(b, getBodyAverage(fb[0]) - getFaceAverage(f[i])).lensq() > ORTOGONALSQ) continue;
			for(j=0; j<bq.size(); j++) m_q[bq[j]].b.eraseFirst(fb[0]); // uncontact fb[0] from quads
			fbq.clear();
		}

		// merge body ->
		const Buffer<uint> bf = getBodyFaces(fb[0]);
		for(j=0; j<bf.size(); j++)
		{
			if(f.gatherOrUngather(bf[j], fs)) continue;
			if(i + 1 != 0) i--;
			detachFaceRecursive(bf[j]);
		}
		merged = true;
		f.resize(fs);
	}
	for(i=0; i<fs; i++) m_f[f[i]].b.push_back(b); // contact b by faces
	if(!merged) return b; // body is unchanged
	orderBodyFaces(b);
	const Buffer<uint> ff = f;
	for(i=0; i<ff.size(); i++) mergeFace(ff[i]);
	return b;
}

uint DelaunayMesh::mergeQuad(const uint q)
{
	uint i, j;
	Buffer<uint> &b = m_q[q].b;
	uint bs = b.size();
	if(bs < 5) return q; // q is detached already
	bool merged = false;
	const Vector4 qp = getQuadPosition(q);
	const ddouble qsq = getRadiusSq(qp, getQuadNodes(q));
	for(i=0; i<bs; i++) m_b[b[i]].q.eraseFirst(q); // temporally uncontact q from bodies
	for(i=0; i<bs; i++)
	{
		const Buffer<uint> &bq = getBodyQuads(b[i]);
		if(bq.size() != 1) continue; // no unique quad to merge

		if(!isInSphere(qp, qsq, getQuadNodes(bq[0]))) continue;

		// merge quad ->
		const Buffer<uint> qb = getQuadBodies(bq[0]);
		for(j=0; j<qb.size(); j++)
		{
			if(b.gatherOrUngather(qb[j], bs)) continue;
			if(i + 1 != 0) i--;
			detachBodyRecursive(qb[j]);
		}
		merged = true;
		b.resize(bs);
	}
	for(i=0; i<bs; i++) m_b[b[i]].q.push_back(q); // contact q by bodies
	if(!merged) return q; // quad is unchanged

	const Buffer<uint> bb = b;
	for(i=0; i<bb.size(); i++) mergeBody(bb[i]);
	return q;
}

void DelaunayMesh::transform(const Matrix4 &mat)
{
	Mesh::transform(mat);
	//m_met *= (mat * mat.transpose()).getSymmetric().inverse();
}

