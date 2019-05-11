#include "testsuite.h"
#include <blitz/array.h>
#include <sstream>

BZ_USING_NAMESPACE(blitz)

template <int N>
bool cmp_size(const Array<int, N> &A, const Array<int, N> &B) {
	for (int kk = 0; kk < 1; ++ kk) {
		if (A.lbound(kk) != B.lbound(kk)) return false;
		if (A.ubound(kk) != B.ubound(kk)) return false;
	}
	return true;
}

bool cmp(const Array<int, 4> &A, const Array<int, 4> &B) {
	if (!cmp_size(A, B)) return false;
	for (int i1 = A.lbound(0); i1 <= A.ubound(0); ++ i1)
	for (int i2 = A.lbound(1); i2 <= A.ubound(1); ++ i2)
	for (int i3 = A.lbound(2); i3 <= A.ubound(2); ++ i3)
	for (int i4 = A.lbound(3); i4 <= A.ubound(3); ++ i4) {
		if (A(i1, i2, i3, i4) != B(i1, i2, i3, i4)) {
			return false;
		}
	}
	return true;
}

bool cmp(const Array<int, 3> &A, const Array<int, 3> &B) {
	if (!cmp_size(A, B)) return false;
	for (int i1 = A.lbound(0); i1 <= A.ubound(0); ++ i1)
	for (int i2 = A.lbound(1); i2 <= A.ubound(1); ++ i2)
	for (int i3 = A.lbound(2); i3 <= A.ubound(2); ++ i3) {
		if (A(i1, i2, i3) != B(i1, i2, i3)) {
			return false;
		}
	}
	return true;
}

bool cmp(const Array<int, 2> &A, const Array<int, 2> &B) {
	if (!cmp_size(A, B)) return false;
	for (int i1 = A.lbound(0); i1 <= A.ubound(0); ++ i1)
	for (int i2 = A.lbound(1); i2 <= A.ubound(1); ++ i2) {
		if (A(i1, i2) != B(i1, i2)) {
			return false;
		}
	}
	return true;
}

bool cmp(const Array<int, 1> &A, const Array<int, 1> &B) {
	if (!cmp_size(A, B)) return false;
	for (int i1 = A.lbound(0); i1 <= A.ubound(0); ++ i1) {
		if (A(i1) != B(i1)) {
			return false;
		}
	}
	return true;
}

template <int N>
bool run(Array<int, N> &A, Array<int, N> &B) {
	typename Array<int, N>::iterator iter, last = A.end();
	int i = 0;
	for (iter = A.begin(); iter != last; ++ iter) {
		*iter = i ++;
	}
	std::stringstream S;
	S << A;
	cout << A << endl;
	S >> B;
	cout << B << endl;
	return cmp(A, B);
}

int main() {

	Array<int, 4> A4(3, 4, 5, 6), B4;//(3, 4, 5, 6);
	Array<int, 3> A3(3, 4, 5), B3;//(3, 4, 5);
	Array<int, 2> A2(3, 4), B2;//(3, 4);
	Array<int, 2> A1(3), B1;//(3);

	BZTEST(run(A4, B4));
	BZTEST(run(A3, B3));
	BZTEST(run(A2, B2));
	BZTEST(run(A1, B1));

	return 0;
}
