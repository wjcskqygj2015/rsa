#ifndef BIG_INT_INIT
#define BIG_INT_INIT
#include"BigInt.h"
#include<cassert>

template<int bits>
const BigInt<bits> operator+(const BigInt<bits>& summand, const BigInt<bits>& addand)
{
	//Here X, Y is unsigned
	// - X + -Y = -(X+Y), OK
	// X+Y=(X+Y), OK
	if (summand.overflowFlag || addand.overflowFlag)
		assert("BigInt Addition are not allowed when overflowed");
	if (summand.signFlag == addand.signFlag)
	{
		BigInt<bits> sum;
		int totalRound = bits / intBits;
		unsigned int overflow = 0;
		unsigned int lastOverflow = 0;
		for (int i = 0; i < totalRound; i++)
		{
			sum.represent[i] = summand.represent[i] + addand.represent[i] + lastOverflow;
			overflow = BigInt<bits>::judgeOverflow(summand.represent[i], addand.represent[i]);
			overflow = overflow ? overflow : BigInt<bits>::judgeOverflow(summand.represent[i] + addand.represent[i], lastOverflow);
			lastOverflow = overflow;
		}
		sum.overflowFlag = overflow;
		sum.signFlag = summand.signFlag;
		return sum;
	}
	else
		return summand-(-addand);
}

template<int bits>
const BigInt<bits> operator-(const BigInt<bits>& minuend, const BigInt<bits>& subtrahend)
{
	//Here X, Y is unsigned
	// - X - -Y = -(X-Y), OK
	// X-Y=(X-Y), OK
	if (minuend.overflowFlag || subtrahend.overflowFlag)
		assert("BigInt Substraction are not allowed when overflowed");
	if (minuend.signFlag == subtrahend.signFlag)
	{
		BigInt<bits> diff;//difference
		int totalRound = bits / intBits;
		int borrow = 0;
		int lastBorrow = 0;
		for (int i = 0; i < totalRound; i++)
		{
			//borrowFlag
			diff.represent[i] = minuend.represent[i] - subtrahend.represent[i] - lastBorrow;
			borrow = minuend.represent[i] < subtrahend.represent[i];
			borrow = borrow ? borrow : ((minuend.represent[i] - subtrahend.represent[i]) < lastBorrow);
			lastBorrow = borrow;
		}
		//Here We need to care if still has borrow just means X<Y, and here X-Y will be FF...
		//So we need to shift all0
		if (borrow)
		{
			for (int i = 0; i < totalRound; i++)
				diff.represent[i] = (~diff.represent[i] + 1);
			diff.signFlag = false;//We now notify here false, and maybe change by then
		}
		diff.signFlag = (minuend.signFlag) ? diff.signFlag : !diff.signFlag;
		return diff;
	}
	else
		return minuend+(-subtrahend);
	
}

template<int bits>
const BigInt<2 * bits> operator*(const BigInt<bits>& multiplicand, const BigInt<bits>& factor)
{
	if (multiplicand.overflowFlag || factor.overflowFlag)
		assert("BigInt Multiplication are not allowed when overflowed");

	BigInt<2 * bits> prod;//product
	
//	prod.signFlag = (multiplicand.signFlag == factor.signFlag);
	assert("* Undefined");
	return prod;
}

template<int bits>
const BigInt<bits> operator/(const BigInt<2 * bits>& dividend, const BigInt<bits>& divisor)
{
//	if (dividend.overflowFlag || divisor.overflowFlag)
//		assert("BigInt Dividion are not allowed when overflowed");

	BigInt<bits> quot;//quotient
	assert("/ Undefined");
	return quot;
}

template<int bits>
const BigInt<bits> operator%(const BigInt<2 * bits>& dividend, const BigInt<bits>& divisor)
{
//	if (dividend.overflowFlag || divisor.overflowFlag)
//		assert("BigInt Modulation are not allowed when overflowed");
	BigInt<bits> rema;//remainder
	assert("% Undefined");
	return rema;
}

template<int bits>
const BigInt<bits> operator%(const BigInt<bits>& dividend, const BigInt<bits>& divisor)
{
//	if (divisor.overflowFlag)
//		assert("Divisor are not allowed when overflowed");
	//Here We could let diviend to have an overflow Flag
	BigInt<bits> rema;//remainder

	assert("% Undefined");

	return rema;
}

template<int bits>
int BigIntCompareHelper(const BigInt<bits>& a, const BigInt<bits>& b)
{
	const int intNum = BigInt<bits>::intNum;
	int sign = 0;
	int count = 0;
	for (int i = intNum - 1; i >= 0; i--)
	{
		if (a.represent[i] < b.represent[i])
		{
			sign = -1;
			break;
		}
		else if (a.represent[i]>b.represent[i])
		{
			sign = 1;
			break;
		}
		else if (a.represent[i] == 0 && b.represent[i] == 0)
		{
			count++;
		}
	}
	if (count == intNum) return 0;
	else if (a.signFlag > b.signFlag) return 1;
	else if (a.signFlag < b.signFlag) return -1;
	else if (a.overflowFlag == a.overflowFlag) return sign;
	else if (a.signFlag == false)
	{
		if (a.overflowFlag<b.overflowFlag)
			return -1;
		else//(a.overflowFlag<b.overflowFlag) 
			return 1;
	}
	else if (a.signFlag == true)
	{
		if (a.overflowFlag > b.overflowFlag)
			return 1;
		else //(a.overflowFlag < b.overflowFlag) 
			return -1;
	}
}
template<int bits>
bool operator<(const BigInt<bits>& a, const BigInt<bits>& b)
{
	return BigIntCompareHelper(a, b) == -1;
}

template<int bits>
bool operator<=(const BigInt<bits>& a, const BigInt<bits>& b)
{
	return BigIntCompareHelper(a, b) <= 0;
}

template<int bits>
bool operator>(const BigInt<bits>& a, const BigInt<bits>& b)
{
	return BigIntCompareHelper(a, b) == 1;
}

template<int bits>
bool operator>=(const BigInt<bits>& a, const BigInt<bits>& b)
{
	return BigIntCompareHelper(a, b) >= 0;
}
template<int bits>
bool operator==(const BigInt<bits>& a, const BigInt<bits>& b)
{
	return BigIntCompareHelper(a, b) == 0;
}
template<int bits>
bool operator!=(const BigInt<bits>& a, const BigInt<bits>& b)
{
	return BigIntCompareHelper(a, b) != 0;
}

#endif //BIG_INT_INIT