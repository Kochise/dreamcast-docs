/*      
   Tiki
        
   vector.h

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_VECTOR_H
#define __TIKI_VECTOR_H

#include <assert.h>
#include "tikimath.h"

namespace Tiki {
namespace Math {

class Matrix;
class Vector3;

/// A C++ friendly wrapper for the point_t / vector_t struct. Note that
/// the 'w' value is not actually a fourth dimension but rather a scaling
/// factor for a homogeneous coordinate. i.e. the real vector/point expressed
/// by <x,y,z,w> is actually <x/w,y/w,z/w>.
class Vector {
public:
	Vector(float ix, float iy, float iz, float iw = 1.0f)
		: x(ix), y(iy), z(iz), w(iw) { }
	Vector() { }

	/// Return one of the vector elements array-style
	float operator[](int i) const {
		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else if (i == 2)
			return z;
		else if (i == 3)
			return w;
		else {
			Debug::printf("Point::operator[] Invalid index\n");
			assert( false );
			return 0.0f;
		}
	}

	/// Copy a Vector3 into a Vector
	Vector & operator=(const Vector3 & other);

	/// Compare two vectors for equality
	bool operator==(const Vector & other) const {
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	/// Compare two vectors for inequality
	bool operator!=(const Vector & other) const {
		return !(*this == other);
	}

	/// Add two vectors
	Vector operator+(const Vector & other) const {
		return Vector(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	/// Subtract two vectors
	Vector operator-(const Vector & other) const {
		return Vector(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	/// Unary minus
	Vector operator-() const {
		return Vector(-x, -y, -z);
	}

	/// Multiply by a scalar
	Vector operator*(float s) const {
		return Vector(x * s, y * s, z * s, w * s);
	}

	/// Inline add two vectors
	Vector & operator+=(const Vector & other) {
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	/// Inline subtract two vectors
	Vector & operator-=(const Vector & other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	// Inline multiply by a scalar
	Vector & operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	/// Zero this vector out.
	void zero() {
		x = y = z = w = 0;
	}

	/// Dot product with another vector.
	/// NOTE: Only takes x,y,z into account.
	float dot(const Vector & other) const {
		return (x * other.x)
			+ (y * other.y)
			+ (z * other.z);
	}

	/// Cross product with another vector
	/// NOTE: Only takes x,y,z into account.
	Vector cross(const Vector & other) const {
		return Vector(
			y * other.z - z*other.y,
			z * other.x - x*other.z,
			x * other.y - y*other.x);
	}

	/// Get the length/magnitude of the vector
	float length() const {
		return fsqrt(x*x+y*y+z*z);
	}

	/// Returns 1.0/length()
	/// WARNING: Could cause a div-zero error.
	float rlength() const {
		return frsqrt(x*x+y*y+z*z);
	}

	/// Normalize this vector in place.
	Vector & normalizeSelf() {
		float l = rlength();
		x = x * l;
		y = y * l;
		z = z * l;
		w = w * l;
		return *this;
	}

	/// Normalize this vector and return a new one.
	Vector normalize() const {
		float l = rlength();
		return Vector(
			x * l,
			y * l,
			z * l,
			w * l);
	}

	/// Multiply this vector with a matrix.
	Vector operator*(const Matrix & mat) const;

	/// Operator *= to multiply with a matrix.
	Vector & operator*=(const Matrix & mat);

public:
	float	x, y, z, w;
};

}
}

// Suck it over into the main namespace as well.
namespace Tiki {
	using Math::Vector;
}

#endif	// __TIKI_VECTOR_H

