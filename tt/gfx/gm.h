///////////////////////////////////////////////////////////////////////////
//
// graphics math constants and utility functions
//
// Reference:
//   Graphics Gems V, Chapter 7 - 7
//   libgm++: Graphics Math Library
//   Ferdi Scheepers and Stephen F May
//   15 June 1994
//
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <cmath>

//=========================================================================
// constants
//=========================================================================

const double gmEPSILON =   1.e-5;
const double gmPI =        3.14159265358979323846;
const double gm2PI =       6.28318530717958623200;
const double gmINVPI =     0.31830988618379069122;
const double gmPIDIV2 =    1.57079632679489655800;
const double gmPIDIV4 =    0.78539816339744827900;
const double gmINF =       1.e30;
const double gmDEGTORAD =  0.01745329251994329547;
const double gmRADTODEG = 57.29577951308232286465;

//=========================================================================

inline float gmAbs(float f) {
  return (f >= 0) ? f : -f;
}

inline float gmSign(float f) {
  return (f < 0) ? -1.f : 1.f;
}

inline float gmZSign(float f) {
  return (f > 0) ? 1.f : (f < 0) ? -1.f : 0.f;
}

//=========================================================================

inline float gmSqr(float f) {
  return f * f;
}

inline float gmCube(float f) {
  return f * f * f;
}

inline float gmInv(float f) {
  return 1.f / f;
}

//=========================================================================
// rounding
//=========================================================================

inline float gmTrunc(float f) {
  return float(int(f));
}

inline float gmRound(float f) {
  return (f >= 0) ? float(int(f + .5)) : float(- int(.5 - f));
}

inline float gmFloor(float f) {
  return (f == int(f)) ? f : (f > 0) ? float(int(f)) : float(int(f) - 1);
}

inline float gmCeil(float f) {
  return (f == int(f)) ? f : (f > 0) ? float(int(f) + 1) : float(int(f));
}

//=========================================================================
// degrees and radians
//=========================================================================

inline float gmDegrees(float f) {
  return float(f * gmRADTODEG);
}

inline float gmRadians(float f) {
  return float(f * gmDEGTORAD);
}

//=========================================================================
// comparison
//=========================================================================

inline bool gmIsZero(float f, float epsilon = gmEPSILON) {
  return (gmAbs(f) < epsilon);
}

// f ~= g
inline bool gmFuzEQ(float f, float g, float epsilon = gmEPSILON) {
  return (f <= g) ? (f >= g - epsilon) : (f <= g + epsilon);
}

// f ~>= g
inline bool gmFuzGEQ(float f, float g, float epsilon = gmEPSILON) {
  return (f >= g - epsilon);
}

// f ~<= g
inline bool gmFuzLEQ(float f, float g, float epsilon = gmEPSILON) {
  return (f <= g + epsilon);
}

//=========================================================================
// min & max
//=========================================================================

inline float gmMin(float f, float g) {
  return (f < g) ? f : g;
}

inline float gmMax(float f, float g) {
  return (f > g) ? f : g;
}

inline float gmMin3(float f, float g, float h) {
  return (f < g) ? gmMin(f, h) : gmMin(g, h);
}

inline float gmMax3(float f, float g, float h) {
  return (f > g) ? gmMax(f, h) : gmMax(g, h);
}

//=========================================================================

template<typename T>
inline void gmSwap(T& f, T& g) {
  T tmp = f;
  f = g;
  g = tmp;
}

inline float gmClamp(float val, float low, float high) {
	if (val < low)
		return low;
	else if (val > high)
		return high;
	else
		return val;
}

inline float gmLerp(float f, float l, float h) {
  return l + ((h - l) * f );
}

inline float gmSmooth(float f) {
  return (3.f - 2.f * f) * f * f;
}

//=========================================================================
// functions for integer parameters
//=========================================================================

inline int gmAbs_i(int f) {
  return (f >= 0) ? f : -f;
}

//=========================================================================
// min & max
//=========================================================================

inline int gmMin_i(int f, int g) {
  return (f < g) ? f : g;
}

inline int gmMax_i(int f, int g) {
  return (f > g) ? f : g;
}

inline int gmMin3_i(int f, int g, int h) {
  return (f < g) ? gmMin_i(f, h) : gmMin_i(g, h);
}

inline int gmMax3_i(int f, int g, int h) {
  return (f > g) ? gmMax_i(f, h) : gmMax_i(g, h);
}

//=========================================================================

inline int gmClamp_i(int val, int low, int high) {
	if (val < low)
		return low;
	else if (val > high)
		return high;
	else
		return val;
}

//=========================================================================

inline int gmCyclicPrev(int x, int front, int last) {
	return (x == front) ? last : x-1;
}

inline int gmCyclicNext(int x, int front, int last) {
	return (x == last) ? front : x+1;
}

inline int gmCyclicPrev3(int x) {
	return (x == 0) ? 2 : x-1;
}

inline int gmCyclicNext3(int x) {
	return (x == 2) ? 0 : x+1;
}

inline int gmMinAxis(float x, float y, float z) {
	if (x < y) {
		if (x < z) return 0;
		else       return 2;
	} else {
		if (y < z) return 1;
		else       return 2;
	}
}

inline int gmMaxAxis(float x, float y, float z) {
	if (x > y) {
		if (x > z) return 0;
		else       return 2;
	} else {
		if (y > z) return 1;
		else       return 2;
	}
}

