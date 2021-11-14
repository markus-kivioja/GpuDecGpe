#include "VortexState.hpp"
#include <fstream>
#include <iostream>

VortexState::VortexState()
{
	setKappa(2);
	setG(0.0);
	setDimensions(100, 0.1, 0.0, 1, 1.0);
}

void VortexState::setDimensions(const uint rsize, const ddouble rstep, const ddouble rplug, const uint zsize, const ddouble zstep)
{
	m_rsize = (rsize > 1 ? rsize : 1);
	m_rstep = (rstep > 1e-13 ? rstep : 1e-13);
	m_rplug = (rplug > 0.0 ? rplug : 0.0);
	m_zsize = (zsize > 1 ? zsize : 1);
	m_zstep = (zstep > 1e-13 ? zstep : 1e-13);

	// create initial state
	m_mu = 1.0;
	m_f.resize(m_rsize * m_zsize);
	ddouble prob = 0.0;
	uint ii = 0;
	for(uint i=0; i<m_rsize; i++)
	{
		const ddouble fr = 1.0 - cos(i * PIx2 / ddouble(m_rsize));
		const ddouble r = m_rplug + i * m_rstep;
		uint times = 1;
		for(uint j=0; j<m_zsize; j++, ii++)
		{
			m_f[ii] = (1.0 + cos(j * PI / ddouble(m_zsize))) * fr;
			prob += times * m_f[ii] * m_f[ii] * r;
			times = 2;
		}
	}
	prob *= PIx2 * m_rstep * m_zstep;
	const ddouble scale = 1.0 / sqrt(prob);
	for(ii=0; ii<m_f.size(); ii++) m_f[ii] *= scale;
}

void VortexState::setRange(const ddouble rmin, const ddouble rmax, const ddouble zmax, const ddouble rstep, const ddouble zstep)
{
	const uint rsize = uint((rmax - rmin) / rstep + 0.5);
	const uint zsize = uint(zmax / zstep + 0.5);
	setDimensions(rsize, (rmax - rmin) / ddouble(rsize), rmin, zsize, zmax / ddouble(zsize));
}

bool VortexState::load(const std::string &path)
{
	std::ifstream fs(path.c_str(), std::ios::binary | std::ios::in);
	if(fs.fail() != 0) return false;

	// physical parameters
	fs.read((char*)&m_kappa, sizeof(uint)); // quantum number
	fs.read((char*)&m_g, sizeof(ddouble));  // effective interaction strength

	// dimensions
	fs.read((char*)&m_rsize, sizeof(uint)); // number of r-instances
	fs.read((char*)&m_zsize, sizeof(uint)); // number of z-instances
	fs.read((char*)&m_rplug, sizeof(ddouble)); // lowest value of radius
	fs.read((char*)&m_rstep, sizeof(ddouble)); // radial step length
	fs.read((char*)&m_zstep, sizeof(ddouble)); // z-step length

	// solution
	fs.read((char*)&m_mu, sizeof(ddouble)); // angular frequency for time
	m_f.resize(m_rsize * m_zsize);
	fs.read((char*)&m_f[0], sizeof(ddouble) * m_f.size()); // function f(r,z)

	fs.close();
	return true;
}

bool VortexState::save(const std::string &path) const
{
	std::ofstream fs(path.c_str(), std::ios::binary | std::ios_base::trunc);
	if(fs.fail() != 0) return false;

	// physical parameters
	fs.write((char*)&m_kappa, sizeof(uint)); // quantum number
	fs.write((char*)&m_g, sizeof(ddouble));  // effective interaction strength

	// dimensions
	fs.write((char*)&m_rsize, sizeof(uint)); // number of r-instances
	fs.write((char*)&m_zsize, sizeof(uint)); // number of z-instances
	fs.write((char*)&m_rplug, sizeof(ddouble)); // lowest value of radius
	fs.write((char*)&m_rstep, sizeof(ddouble)); // radial step length
	fs.write((char*)&m_zstep, sizeof(ddouble)); // z-step length

	// solution
	fs.write((char*)&m_mu, sizeof(ddouble)); // angular frequency for time
	fs.write((char*)&m_f[0], sizeof(ddouble) * m_f.size()); // function f(r,z)

	fs.close();
	return true;
}

void VortexState::initialize(const VortexState &state)
{
	m_mu = state.getMu();
	uint ii = 0;
	for(uint i=0; i<m_rsize; i++)
	{
		const ddouble r = m_rplug + i * m_rstep;
		for(uint j=0; j<m_zsize; j++) m_f[ii++] = state.getFunction(r, j * m_zstep);
	}
}

void VortexState::iterateSolution(ddouble (*potential)(const ddouble, const ddouble), const uint maxiters, const ddouble eps)
{
	uint i, j, k, ii;
	const ddouble PIx2drdz = PIx2 * m_rstep * m_zstep;
	const ddouble kk = 0.5 * ddouble(m_kappa * m_kappa);
	const ddouble laplr = 0.5 / (m_rstep * m_rstep);
	const ddouble laplz = (m_zsize > 1 ? 0.5 / (m_zstep * m_zstep) : 0.0);

	// set function to zero at r = m_rplug
	for(j=0; j<m_zsize; j++) m_f[j] = 0.0;

	// iterate solution by relaxation method
	for(k=0; k<maxiters; k++)
	{
		ddouble diff = 0.0;
		for(i=1,ii=m_zsize; i<m_rsize; i++)
		{
			const ddouble r = m_rplug + i * m_rstep;
			const ddouble lapl = kk / (r * r) + 2.0 * (laplr + laplz);
			const ddouble gradr = 0.25 / (r * m_rstep);
			ddouble dv = PIx2drdz * r;
			for(j=0; j<m_zsize; j++, ii++)
			{
				const ddouble pot = potential(r, j * m_zstep) + m_g * m_f[ii] * m_f[ii];

				const ddouble fiir = (i + 1 < m_rsize ? m_f[ii + m_zsize] : 0.0);
				const ddouble frii = m_f[ii - m_zsize];
				const ddouble fiiz = (j + 1 < m_zsize ? m_f[ii + 1] : 0.0);
				const ddouble fzii = (j > 0 ? m_f[ii - 1] : fiiz);

				ddouble dfii = m_f[ii];
				m_f[ii] = (gradr * (frii - fiir) - laplr * (frii + fiir) - laplz * (fzii + fiiz)) / (m_mu - lapl - pot);
				dfii -= m_f[ii];
				diff += dfii * dfii * dv;
				if(j == 0) dv *= 2.0;
			}
		}

		ddouble prob = 0.0;
		ddouble prob2 = 0.0;
		for(i=1,ii=m_zsize; i<m_rsize; i++)
		{
			const ddouble r = m_rplug + i * m_rstep;
			const ddouble lapl = kk / (r * r) + 2.0 * (laplr + laplz);
			const ddouble gradr = 0.25 / (r * m_rstep);
			ddouble dv = PIx2drdz * r;
			for(j=0; j<m_zsize; j++, ii++)
			{
				const ddouble pot = potential(r, j * m_zstep) + m_g * m_f[ii] * m_f[ii];

				const ddouble fiir = (i + 1 < m_rsize ? m_f[ii + m_zsize] : 0.0);
				const ddouble frii = m_f[ii - m_zsize];
				const ddouble fiiz = (j + 1 < m_zsize ? m_f[ii + 1] : 0.0);
				const ddouble fzii = (j > 0 ? m_f[ii - 1] : fiiz);

				prob += m_f[ii] * m_f[ii] * dv;
				prob2 += ((pot + lapl) * m_f[ii] + gradr * (frii - fiir) - laplr * (frii + fiir) - laplz * (fzii + fiiz)) * m_f[ii] * dv;
				if(j == 0) dv *= 2.0;
			}
		}
		m_mu = prob2 / prob;
		const ddouble scale = 1.0 / sqrt(prob);
		for(ii=m_zsize; ii<m_f.size(); ii++) m_f[ii] *= scale;

		if(k % 1000 == 0) std::cout << "iter=" << k << " diff=" << diff << " prob=" << prob << std::endl;
		if(diff < eps) break;
	}

	// make f non-negative
	ddouble sum = 0.0;
	for(ii=m_zsize; ii<m_f.size(); ii++) sum += m_f[ii];
	if(sum < 0.0)
	{
		for(ii=m_zsize; ii<m_f.size(); ii++) m_f[ii] = -m_f[ii];
	}

	// print statistics
	std::cout << "mu = " << m_mu << std::endl;
	std::cout << "error = " << integrateFunctionError(potential) << std::endl;
/*	const ddouble fmax = searchFunctionMax();
	std::cout << "function max = " << fmax << std::endl;
	std::cout << "min radius = " << searchMinR(1e-6 * fmax) << std::endl;
	std::cout << "max radius = " << searchMaxR(1e-6 * fmax) << std::endl;
	std::cout << "max z = " << searchMaxZ(1e-6 * fmax) << std::endl;
	const ddouble curv = integrateCurvature();
	std::cout << "curvature = " << curv << std::endl;
	std::cout << "effective wavelength = " << PIx2 / sqrt(curv) << std::endl;
*/}

Complex VortexState::getPhase(const ddouble time) const
{
	const ddouble phase = time * m_mu;
	return Complex(cos(phase), -sin(phase));
}

Complex VortexState::getPsi(const Vector3 &p) const
{
	const ddouble r = sqrt(p.x * p.x + p.y * p.y);
	if(r < 1e-30) return Complex(0.0, 0.0);
	Complex c(getFunction(r, p.z), 0.0);
	const Complex n(p.x / r, p.y / r);
	for(uint j=0; j<m_kappa; j++) c *= n;
	return c;
}

Complex VortexState::getPsi(const ddouble r, const ddouble phi, const ddouble z) const
{
	const ddouble f = getFunction(r, z);
	return Complex(f * cos(m_kappa * phi), f * sin(m_kappa * phi));
}

ddouble VortexState::getFunction(const ddouble r, const ddouble z) const
{
	const ddouble rr = (r - m_rplug) / m_rstep;
	if(rr < 0.0) return 0.0; // radius is smaller than m_rplug
	const uint ir = uint(rr);
	if(ir >= m_rsize) return 0.0; // radius is out of boundaries
	const ddouble dr = rr - ddouble(ir);

	const ddouble zz = fabs(z) / m_zstep;
	const uint iz = uint(zz);
	if(iz >= m_zsize) return 0.0; // z is out of boundaries
	const ddouble dz = zz - ddouble(iz);

	const uint ii = ir * m_zsize + iz;
	const ddouble fiir = (ir + 1 < m_rsize ? m_f[ii + m_zsize] : 0.0);
	const ddouble fiiz = (iz + 1 < m_zsize ? m_f[ii + 1] : 0.0);
	const ddouble fiirz = (ii + m_zsize + 1 < m_f.size() ? m_f[ii + m_zsize + 1] : 0.0);
	return (1.0 - dz) * ((1.0 - dr) * m_f[ii] + dr * fiir) + dz * ((1.0 - dr) * fiiz + dr * fiirz);
}

ddouble VortexState::integrateFunctionError(ddouble (*potential)(const ddouble, const ddouble)) const
{
	uint i, j, ii;
	const ddouble PIx2drdz = PIx2 * m_rstep * m_zstep;
	const ddouble kk = 0.5 * ddouble(m_kappa * m_kappa);
	const ddouble laplr = 0.5 / (m_rstep * m_rstep);
	const ddouble laplz = (m_zsize > 1 ? 0.5 / (m_zstep * m_zstep) : 0.0);
	ddouble error = 0.0;
	for(i=1,ii=m_zsize; i<m_rsize; i++)
	{
		const ddouble r = m_rplug + i * m_rstep;
		const ddouble lapl = kk / (r * r) + 2.0 * (laplr + laplz);
		const ddouble gradr = 0.25 / (r * m_rstep);
		ddouble dv = PIx2drdz * r;
		for(j=0; j<m_zsize; j++, ii++)
		{
			const ddouble pot = potential(r, j * m_zstep) + m_g * m_f[ii] * m_f[ii];

			const ddouble fiir = (i + 1 < m_rsize ? m_f[ii + m_zsize] : 0.0);
			const ddouble frii = m_f[ii - m_zsize];
			const ddouble fiiz = (j + 1 < m_zsize ? m_f[ii + 1] : 0.0);
			const ddouble fzii = (j > 0 ? m_f[ii - 1] : fiiz);

			const ddouble df = (pot + lapl - m_mu) * m_f[ii] + gradr * (frii - fiir) - laplr * (frii + fiir) - laplz * (fzii + fiiz);
			error += df * df * dv;
			if(j == 0) dv *= 2.0;
		}
	}
	return error;
}

ddouble VortexState::integrateCurvature() const
{
	uint i, j, ii;
	const ddouble PIx2drdz = PIx2 * m_rstep * m_zstep;
	const ddouble kk = ddouble(m_kappa * m_kappa);
	const ddouble laplr = 1.0 / (m_rstep * m_rstep);
	const ddouble laplz = (m_zsize > 1 ? 1.0 / (m_zstep * m_zstep) : 0.0);
	ddouble curv = 0.0;
	for(i=1,ii=m_zsize; i<m_rsize; i++)
	{
		const ddouble r = m_rplug + i * m_rstep;
		const ddouble lapl = kk / (r * r) + 2.0 * (laplr + laplz);
		const ddouble gradr = 0.5 / (r * m_rstep);
		ddouble dv = PIx2drdz * r;
		for(j=0; j<m_zsize; j++, ii++)
		{
			const ddouble fiir = (i + 1 < m_rsize ? m_f[ii + m_zsize] : 0.0);
			const ddouble frii = m_f[ii - m_zsize];
			const ddouble fiiz = (j + 1 < m_zsize ? m_f[ii + 1] : 0.0);
			const ddouble fzii = (j > 0 ? m_f[ii - 1] : fiiz);

			const ddouble iicurv = lapl * m_f[ii] + gradr * (frii - fiir) - laplr * (frii + fiir) - laplz * (fzii + fiiz);
			curv += iicurv * m_f[ii] * dv;
			if(j == 0) dv *= 2.0;
		}
	}
	return curv;
}

ddouble VortexState::searchFunctionMax() const
{
	ddouble maxf = 0.0;
	for(uint ii=0; ii<m_f.size(); ii++)
	{
		if(m_f[ii] > maxf) maxf = m_f[ii];
	}
	return maxf;
}

ddouble VortexState::searchMinR(const ddouble eps) const
{
	for(uint ii=0; ii<m_f.size(); ii++)
	{
		if(m_f[ii] > eps) return m_rplug + (ii / m_zsize) * m_rstep;
	}
	return 1e30;
}

ddouble VortexState::searchMaxR(const ddouble eps) const
{
	for(uint ii=m_f.size(); ii-->0; )
	{
		if(m_f[ii] > eps) return m_rplug + (ii / m_zsize) * m_rstep;
	}
	return 0.0;
}

ddouble VortexState::searchMaxZ(const ddouble eps) const
{
	for(uint j=m_zsize; j-->0; )
	{
		uint ii = j;
		for(uint i=0; i<m_rsize; i++)
		{
			if(m_f[ii] > eps) return j * m_zstep;
			ii += m_zsize;
		}
	}
	return 0.0;
}

