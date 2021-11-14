#ifndef _RANDOM_HPP_INCLUDED_
#define _RANDOM_HPP_INCLUDED_

/*
  Generates pseudorandom numbers.
  Uses Mersenne Twister (MT 19937) algorithm.

  MT 19937 has the following desirable properties:

  1. It was designed to have a colossal period of 2^19937 - 1 (the creators of the algorithm
      proved this property). This period explains the origin of the name: it is a Mersenne prime,
      and some of the guarantees of the algorithm depend on internal use of Mersenne primes.
      In practice, there is little reason to use larger ones. [citation needed]

  2. It has a very high order of dimensional equidistribution (see linear congruential generator).
      Note that this means, by default, that there is negligible serial correlation between
      successive values in the output sequence.

  3. It is faster than all but the most statistically unsound generators.

  4. It passes numerous tests for statistical randomness, including the stringent Diehard tests.
*/

#include "Types.hpp"

const uint MT_N = 624;

class Random
{
private:
  Random(const Random &rhs) { *this = rhs; }
  Random &operator = (const Random &rhs) { return *this; }

public:
  Random() { init(++ms_seed); }
  Random(const uint seed) { init(seed); }
  virtual ~Random() {}

  // Initialise the generator from a seed
  void init(const uint seed);

  // Returns pseudorandom 32-bit unsigned int.
  uint getUint();

  // Returns pseudorandom number of uniform distribution [0,1[.
  ddouble getUniform();

  // Returns pseudorandom number of exponentian distr. exp(-x), x > 0.
  ddouble getExponential();

  // Returns pseudorandom number of standard normal distr. exp(-0.5*x^2)/sqrt(dPIx2), x > 0.
  ddouble getGaussian();

  // Returns pseudorandom uniformly distributed vector where x^2 + y^2 <= 1.0.
  Vector2 getUniformCircle();

  // Returns pseudorandom uniformly distributed vector where x^2 + y^2 + z^2 <= 1.0.
  Vector3 getUniformSphere();

  // Sets static seed where Random objects can be generated.
  static void setStaticSeed(const uint seed) { ms_seed = seed; }

private:
  inline void generateNumbers();
  inline void generateGaussians();

  uint m_mt[MT_N]; // state vector
  uint m_i;          // index into mt

  ddouble m_gaus[2];
  uint m_iGaus;

  static uint ms_seed;
};

#endif //_RANDOM_HPP_INCLUDED_
