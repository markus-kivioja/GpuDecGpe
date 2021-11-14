#ifndef _VORTEXSTATE_HPP_INCLUDED_
#define _VORTEXSTATE_HPP_INCLUDED_

/*
	- To create, save, and load vortex states
	- Vortex state of formula \Psi(r, \phi, z, t) = f(r,z) e^{i \kappa \phi - i \mu t}
	- To satisfy Gross-Pitaevskii equation: i \partial_t \Psi = ( -0.5 \nabla^2 + V + g |\Psi|^2 ) \Psi, where V is given potential.
	- Normalized by \int |\Psi|^2 = 1.
	- Covers both two- and three-dimensional vortex solutions
*/

#include "../Types/Buffer.hpp"
#include "../Types/Complex.hpp"
#include <string>

class VortexState
{
public:
	VortexState();
	virtual ~VortexState() { }

	// physical parameters
	void setKappa(const uint kappa) { m_kappa = kappa; }
	uint getKappa() const { return m_kappa; }

	void setG(const ddouble g) { m_g = g; }
	ddouble getG() const { return m_g; }

	// set dimensions
	void setDimensions(const uint rsize, const ddouble rstep, const ddouble rplug = 0.0, const uint zsize = 1, const ddouble zstep = 1.0);
	void setRange(const ddouble rmin, const ddouble rmax, const ddouble zmax, const ddouble rstep, const ddouble zstep);

	// load and save binary file
	bool load(const std::string &path);
	bool save(const std::string &path) const;

	// initialize and iterate vortex solution
	void initialize(const VortexState &state);
	void iterateSolution(ddouble (*potential)(const ddouble, const ddouble), const uint maxiters = 100000, const ddouble eps = 1e-28);

	// get vortex solution
	ddouble getMu() const { return m_mu; }
	Complex getPhase(const ddouble time) const;
	Complex getPsi(const Vector3 &p) const;
	Complex getPsi(const ddouble r, const ddouble phi, const ddouble z) const;
	ddouble getFunction(const ddouble r, const ddouble z) const;

	// search and integrate variables
	ddouble searchFunctionMax() const; // search maximal value of the function f
	ddouble searchMinR(const ddouble eps) const; // search for minimal radius, where function f exceeds eps
	ddouble searchMaxR(const ddouble eps) const; // search for maximal radius, where function f exceeds eps
	ddouble searchMaxZ(const ddouble eps) const; // search for maximal z, where function exceeds eps
	ddouble integrateFunctionError(ddouble (*potential)(const ddouble, const ddouble)) const; // integrates error |( -0.5 \nabla^2 + V + g |\Psi|^2  - \mu) \Psi|^2
	ddouble integrateCurvature() const; // integrates mean of relative Laplacian (-\nabla^2 \Psi)^* \Psi

private:

	// physical parameters
	uint m_kappa; // quantum number
	ddouble m_g; // effective interaction strength

	// dimensions
	uint m_rsize; // number of r-instances
	uint m_zsize; // number of z-instances
	ddouble m_rplug; // lowest value of radius
	ddouble m_rstep; // radial step length
	ddouble m_zstep; // z-step length

	// solution
	ddouble m_mu; // angular frequency for time
	Buffer<ddouble> m_f; // function f(r,z)
};

#endif //_VORTEXSTATE_HPP_INCLUDED_
