#ifndef _TYPES_HPP_INCLUDED_
#define _TYPES_HPP_INCLUDED_

#ifdef _WIN32
#include <windows.h>
#define SPRINT sprintf_s
#endif
#ifdef __linux__
#include <sys/time.h>
#include <memory>
#include <cstring>
#include <cstdlib>
#define SPRINT snprintf
#endif

#include "Matrix4.hpp"

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long long ullong;

static const uint NONE = uint(-1);
static const ddouble PI = 3.1415926535897932385;
static const ddouble PIx2 = 6.2831853071795864770;
static const ddouble PI_2 = 1.5707963267948966193;
static const ddouble PI_3 = 1.0471975511965977462;
static const ddouble PI_4 = 0.7853981633974483096;
static const ddouble PIx3_2 = 4.7123889803846898578;
static const ddouble RAD2DEG = 57.295779513082320875;
static const ddouble DEG2RAD = 0.0174532925199432958;


#endif //_TYPES_HPP_INCLUDED_
