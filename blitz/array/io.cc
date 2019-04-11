/***************************************************************************
 * blitz/array/io.cc  Input/output of arrays.
 *
 * $Id$
 *
 * Copyright (C) 1997-2011 Todd Veldhuizen <tveldhui@acm.org>
 *
 * This file is a part of Blitz.
 *
 * Blitz is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Blitz is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with Blitz.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Suggestions:          blitz-devel@lists.sourceforge.net
 * Bugs:                 blitz-support@lists.sourceforge.net    
 *
 * For more information, please see the Blitz++ Home Page:
 *    https://sourceforge.net/projects/blitz/
 *
 ****************************************************************************/
#ifndef BZ_ARRAYIO_CC
#define BZ_ARRAYIO_CC

#ifndef BZ_ARRAY_H
 #error <blitz/array/io.cc> must be included via <blitz/array.h>
#endif

BZ_NAMESPACE(blitz)

// This version of operator<< is updated on August 2005
// by Sergei Mingaleev <mingaleev@gmail.com>.
// Also, the corresponding operator>> is updated.

// Update on April 2019
// by Andrey Baranov <armath123@gmail.com>.

template<typename T, int N>
inline void write(ostream &os, const Array<T, N> &x) {
	cout << "Error: operator<< for " << N << "D Array is not supported!" << endl;
	BZASSERT("ERROR!");
}

template<typename T, int N>
inline void read(istream &is, Array<T, N> &x) {
	cout << "Error: read() for " << N << "D Array is not supported!" << endl;
	BZASSERT("ERROR!");
}

template<typename T>
inline void write(ostream &os, const Array<T, 4> &x) {

	for (int i1 = x.lbound(0); i1 <= x.ubound(0); ++ i1)
	for (int i2 = x.lbound(1); i2 <= x.ubound(1); ++ i2)
	for (int i3 = x.lbound(2); i3 <= x.ubound(2); ++ i3) {
		for (int i4 = x.lbound(3); i4 <= x.ubound(3); ++ i4) {
			os << x(i1, i2, i3, i4) << " ";
		}
		if (i1 != x.ubound(0) || i2 != x.ubound(1) ||
		    i3 != x.ubound(2)) {
			os << endl << "  ";
		}
	}
}

template<typename T>
inline void read(istream &is, Array<T, 4> &x) {

	for (int i1 = x.lbound(0); i1 <= x.ubound(0); ++ i1)
	for (int i2 = x.lbound(1); i2 <= x.ubound(1); ++ i2)
	for (int i3 = x.lbound(2); i3 <= x.ubound(2); ++ i3)
	for (int i4 = x.lbound(3); i4 <= x.ubound(3); ++ i4) {
		BZPRECHECK(
		!is.bad(),
		"Premature end of input while scanning Array"
		);
		is >> x(i1, i2, i3, i4);
	}
}

template<typename T>
inline void write(ostream &os, const Array<T, 3> &x) {

	for (int i1 = x.lbound(0); i1 <= x.ubound(0); ++ i1)
	for (int i2 = x.lbound(1); i2 <= x.ubound(1); ++ i2) {
		for (int i3 = x.lbound(2); i3 <= x.ubound(2); ++ i3) {
			os << x(i1, i2, i3) << " ";
		}
		if (i1 != x.ubound(0) || i2 != x.ubound(1)) {
			os << endl << "  ";
		}
	}
}

template<typename T>
inline void read(istream &is, Array<T, 3> &x) {

	for (int i1 = x.lbound(0); i1 <= x.ubound(0); ++ i1)
	for (int i2 = x.lbound(1); i2 <= x.ubound(1); ++ i2)
	for (int i3 = x.lbound(2); i3 <= x.ubound(2); ++ i3) {
		BZPRECHECK(
		!is.bad(),
		"Premature end of input while scanning Array"
		);
		is >> x(i1, i2, i3);
	}
}

template<typename T>
inline void write(ostream &os, const Array<T, 2> &x) {

	for (int i1 = x.lbound(0); i1 <= x.ubound(0); ++ i1) {
		for (int i2 = x.lbound(1); i2 <= x.ubound(1); ++ i2) {
			os << x(i1, i2) << " ";
		}
		if (i1 != x.ubound(0)) {
			os << endl << "  ";
		}
	}
}

template<typename T>
inline void read(istream &is, Array<T, 2> &x) {

	for (int i1 = x.lbound(0); i1 <= x.ubound(0); ++ i1)
	for (int i2 = x.lbound(1); i2 <= x.ubound(1); ++ i2) {
		BZPRECHECK(
		!is.bad(),
		"Premature end of input while scanning Array"
		);
		is >> x(i1, i2);
	}
}

template<typename T>
inline void write(ostream &os, const Array<T, 1> &x) {

	for (int i1 = x.lbound(0); i1 <= x.ubound(0); ++ i1) {
		os << x(i1) << " ";
	}
}

template<typename T>
inline void read(istream &is, Array<T, 1> &x) {
	for (int i1 = x.lbound(0); i1 <= x.ubound(0); ++ i1) {
		BZPRECHECK(
		!is.bad(),
		"Premature end of input while scanning Array"
		);
		is >> x(i1);
	}
}

/*
 *  Output
 */

template<typename T_numtype, int N_rank>
ostream& operator<<(ostream &os, const Array<T_numtype, N_rank> &x) {

	// Write the extent vector: this is separated by 'x's, e.g.
	// (1, 10) x (-4, 4) x (-5, 5)

	for (int i = 0; i < N_rank; ++ i) {
		os << "(" << x.lbound(i) << "," << x.ubound(i) << ")";
		if (i != N_rank-1) os << " x ";
	}
	os << endl << "[ ";
	write(os, x);
	os << "]" << endl;
	return os;
}

/*
 *  Input
 */

template<typename T_numtype, int N_rank>
istream& operator>>(istream &is, Array<T_numtype, N_rank> &x) {

	TinyVector<int, N_rank> lower_bounds, upper_bounds, extent;
	char sep;

	// Read the extent vector: this is separated by 'x's, e.g.
	// (1, 10) x (-4, 4) x (-5, 5) 

	for (int i = 0; i < N_rank; ++ i) {
		is >> sep;
		BZPRECHECK(!is.bad(), "Premature end of input while scanning Array");
		BZPRECHECK(sep == '(', "Format error while scanning input Array \n -- expected '(' opening Array extents");
		is >> lower_bounds(i);
		is >> sep;
		BZPRECHECK(sep == ',', "Format error while scanning input Array \n -- expected ',' between Array extents");
		is >> upper_bounds(i);
		is >> sep;
		BZPRECHECK(sep == ')', "Format error while scanning input Array \n -- expected ',' closing Array extents");
		if (i != N_rank-1) {
			is >> sep;
			BZPRECHECK(
			sep == 'x', "Format error while scanning input Array \n (expected 'x' between Array extents)"
			);
		}
	}
	is >> sep;
	BZPRECHECK(sep == '[', "Format error while scanning input Array \n (expected '[' before beginning of Array data)");

	for (int i = 0; i < N_rank; ++ i)
		extent(i) = upper_bounds(i) - lower_bounds(i) + 1;
	x.resize(extent);
	x.reindexSelf(lower_bounds);
	read(is, x);
	is >> sep;
	BZPRECHECK(sep == ']', "Format error while scanning input Array \n (expected ']' after end of Array data)");
	return is;
}

BZ_NAMESPACE_END

#endif // BZ_ARRAYIO_CC
