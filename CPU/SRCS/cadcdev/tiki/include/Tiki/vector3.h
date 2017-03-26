/*      
   Tiki
        
   vector3.h

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_VECTOR3_H
#define __TIKI_VECTOR3_H

#include <assert.h>
#include "tikimath.h"

namespace Tiki {
namespace Math {

class Matrix;

/// This is a leaner, meaner version of Vector with no W component.
class Vector3 {
public:
	Vector3(float ix, float iy, float iz)
		: x(ix), y(iy), z(iz) { }
	Vector3() { }

	/// Return one of the vector elements array-style
	float operator[](int i) const {
		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else if (i == 2)
			return z;
		else {
			Debug::printf("Point::operator[] Invalid index\n");
			assert( false );
			return 0.0f;
		}
	}

	/// Compare two vectors for equality
	bool operator==(const Vector3 & other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	/// Compare two vectors for inequality
	bool operator!=(const Vector3 & other) const {
		return !(*this == other);
	}

	/// Add two vectors
	Vector3 operator+(const Vector3 & other) const {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	/// Subtract two vectors
	Vector3 operator-(const Vector3 & other) const {
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	/// Unary minus
	Vector3 operator-() const {
		return Vector3(-x, -y, -z);
	}

	/// Multiply by a scalar
	Vector3 operator*(float s) const {
		return Vector3(x * s, y * s, z * s);
	}

	/// Inline add two vectors
	Vector3 & operator+=(const Vector3 & other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	/// Inline subtract two vectors
	Vector3 & operator-=(const Vector3 & other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	// Inline multiply by a scalar
	Vector3 & operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	/// Zero this vector out.
	void zero() {
		x = y = z = 0;
	}

	/// Dot product with another vector.
	/// NOTE: Only takes x,y,z into account.
	float dot(const Vector3 & other) const {
		return (x * other.x)
			+ (y * other.y)
			+ (z * other.z);
	}

	/// Cross product with another vector
	/// NOTE: Only takes x,y,z into account.
	Vector3 cross(const Vector3 & other) const {
		return Vector3(
			y * other.z - z*other.y,
			z * other.x - x*other.z,
			x * other.y - y*other.x);
	}

	/// Get the length/magnitude of the vector
	float length() const {
		return fsqrt(x*x+y*y+z*z);
	}

	/// Returns 1.0/length()
	float rlength() const {
		return frsqrt(x*x+y*y+z*z);
	}

	/// Normalize this vector in place.
	Vector3 & normalizeSelf() {
		float l = rlength();
		x = x * l;
		y = y * l;
		z = z * l;
		return *this;
	}

	/// Normalize this vector and return a new one.
	Vector3 normalize() const {
		float l = rlength();
		return Vector3(
			x * l,
			y * l,
			z * l);
	}

	/// Multiply this vector with a matrix.
	Vector3 operator*(const Matrix & mat) const;

	/// Operator *= to multiply with a matrix.
	Vector3 & operator*=(const Matrix & mat);

public:
	float	x, y, z;
};

}
}

// Suck it over into the main namespace as well.
namespace Tiki {
	using Math::Vector3;
}

#endif	// __TIKI_VECTOR3_H

