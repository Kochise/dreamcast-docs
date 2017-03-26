/*
   Tiki

   matrix.h

   Copyright (C)2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_MATRIX_H
#define __TIKI_MATRIX_H

#include "vector.h"

namespace Tiki {
namespace Math {

/// A C++ friendly wrapper for the matrix_t struct
class Matrix {
public:
	Matrix();
	Matrix(const Matrix & other);
	Matrix(const float * values);

	Matrix & operator=(const Matrix & other);

	/// Set us to the identity matrix
	void identity();

	/// Do an arbitrary rotation on the matrix
	void rotate(float angle, const Vector & axis);

	/// Do a scale operation on the matrix
	void scale(const Vector & scale);

	/// Do a translation operation on the matrix
	void translate(const Vector & delta);

	/// Do a look-at operation on the matrix (i.e. camera)
	void lookAt(const Vector & pos, const Vector & lookAt, const Vector & up);

	/// Compare two matrices for equality
	bool operator==(const Matrix & other) const;

	/// Compare two matrices for inequality
	bool operator!=(const Matrix & other) const {
		return !(*this == other);
	}

	/// Add two matrices
	Matrix operator+(const Matrix & other) const;

	/// Subtract two matrices
	Matrix operator-(const Matrix & other) const;

	/// Unary minus
	Matrix operator-() const;

	/// Inline add two matrices
	Matrix & operator+=(const Matrix & other) {
		*this = *this + other;
		return *this;
	}

	/// Inline subtract two matrices
	Matrix & operator-=(const Matrix & other) {
		*this = *this - other;
		return *this;
	}

	/// Matrix multiply (aka mat_apply)
	Matrix operator*(const Matrix & other) const;

public:
	float		matrix[4][4];
};

}
}

// Suck it over into the main namespace as well. 
namespace Tiki {
	using Math::Matrix;
}

#endif	// __TIKI_MATRIX_H

