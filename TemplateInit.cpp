#include "BigInt.cpp"

#pragma warning (disable:4172)

namespace BigIntSeries
{
	std::random_device rd;
}

template BigInt<512>;
template const BigInt<512> operator+(const BigInt<512>& summand, const BigInt<512>& addand);
template const BigInt<512> operator-(const BigInt<512>& minuend, const BigInt<512>& subtrahend);
template const BigInt<1024> operator*(const BigInt<512>& multiplicand, const BigInt<512>& factor);
template const BigInt<512> operator/(const BigInt<1024>& dividend, const BigInt<512>& divisor);
template const BigInt<512> operator%(const BigInt<1024>& dividend, const BigInt<512>& divisor);

template BigInt<1024>;
template const BigInt<1024> operator+(const BigInt<1024>& summand, const BigInt<1024>& addand);
template const BigInt<1024> operator-(const BigInt<1024>& minuend, const BigInt<1024>& subtrahend);
template const BigInt<2048> operator*(const BigInt<1024>& multiplicand, const BigInt<1024>& factor);
template const BigInt<1024> operator/(const BigInt<2048>& dividend, const BigInt<1024>& divisor);
template const BigInt<1024> operator%(const BigInt<2048>& dividend, const BigInt<1024>& divisor);

template BigInt<2048>;
template const BigInt<2048> operator+(const BigInt<2048>& summand, const BigInt<2048>& addand);
template const BigInt<2048> operator-(const BigInt<2048>& minuend, const BigInt<2048>& subtrahend);