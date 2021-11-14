#include "Random.hpp"

const uint MT_M = 397;
const uint LAST_31BITS = 2147483647;
const uint THE_32ND_BIT = 2147483648;
const uint EVEN_ODD[2] = {0, 2567483615};
const ddouble UINT2DOUBLE = 1.0 / 4294967296.0;
const ddouble INT2DOUBLE = 1.0 / 2147483648.0;

uint Random::ms_seed = 0;

void Random::init(const uint seed)
{
  m_mt[0] = seed;
  for(m_i=1; m_i<MT_N; m_i++)
  {
//    m_mt[m_i] = (69069 * m_mt[m_i-1]) & 0xffffffff;
    m_mt[m_i] = (1812433253 * (m_mt[m_i-1] ^ (m_mt[m_i-1] >> 30)) + m_i);
  }
  m_iGaus = 2;
}

uint Random::getUint()
{
/*
  // Using antithetic variates
  if(m_i >= 2 * MT_N)
  {
    generateNumbers();
    m_i = 0;
  }

  uint y = m_mt[m_i < MT_N ? m_i : m_i - MT_N];
  y ^=  y >> 11;
  y ^= (y << 7) & 2636928640;
  y ^= (y << 15) & 4022730752;
  y ^=  y >> 18;

  if(m_i++ < MT_N) return y;
  return 0xffffffff - y;
*/

  if(m_i >= MT_N)
  {
    generateNumbers();
    m_i = 0;
  }

  uint y = m_mt[m_i++];
  y ^=  y >> 11;
  y ^= (y << 7) & 2636928640;
  y ^= (y << 15) & 4022730752;
  y ^=  y >> 18;
  return y;
}

ddouble Random::getUniform()
{
  return UINT2DOUBLE * getUint();
}

ddouble Random::getExponential()
{
  return -log(1.0 - UINT2DOUBLE * getUint());
}

ddouble Random::getGaussian()
{
  if(m_iGaus >= 2)
  {
    generateGaussians();
    m_iGaus = 0;
  }
  return m_gaus[m_iGaus++];
}

Vector2 Random::getUniformCircle()
{
  Vector2 v;
  do
  {
    v.x = INT2DOUBLE * int(getUint());
    v.y = INT2DOUBLE * int(getUint());
  } while(v.lensq() > 1.0);
  return v;
}

Vector3 Random::getUniformSphere()
{
  Vector3 v;
  do
  {
    v.x = INT2DOUBLE * int(getUint());
    v.y = INT2DOUBLE * int(getUint());
    v.z = INT2DOUBLE * int(getUint());
  } while(v.lensq() > 1.0);
  return v;

}

inline void Random::generateNumbers()
{
  uint i = 0;
  while(i < MT_N - MT_M)
  {
    const uint y = (THE_32ND_BIT & m_mt[i]) | (LAST_31BITS & m_mt[i+1]);
    m_mt[i] = (m_mt[i + MT_M] ^ (y >> 1) ^ EVEN_ODD[y & 1]);
    i++;
  }
  while(i < MT_N - 1)
  {
    const uint y = (THE_32ND_BIT & m_mt[i]) | (LAST_31BITS & m_mt[i+1]);
    m_mt[i] = (m_mt[i + MT_M - MT_N] ^ (y >> 1) ^ EVEN_ODD[y & 1]);
    i++;
  }
  const uint y = (THE_32ND_BIT & m_mt[i]) | (LAST_31BITS & m_mt[0]);
  m_mt[i] = m_mt[MT_M-1] ^ (y >> 1) ^ EVEN_ODD[y & 1];
}

inline void Random::generateGaussians()
{
  const ddouble r = sqrt(2.0 * getExponential()),
              a = PIx2 * getUniform();

  m_gaus[0] = r * cos(a);
  m_gaus[1] = r * sin(a);
}

