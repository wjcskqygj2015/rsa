#ifndef BIG_INT
#define BIG_INT
#include<iostream>
#include<iomanip>
#include<random>

namespace BigIntSeries
{
	extern std::random_device rd;
}

const int bitsPerByte = 8;
const int intBits = sizeof(int)* bitsPerByte;

template<int bits>
class BigInt;

template<int bits>
const BigInt<bits> operator+(const BigInt<bits>& summand, const BigInt<bits>& addand);

template<int bits>
const BigInt<bits> operator-(const BigInt<bits>& minuend, const BigInt<bits>& subtrahend);

template<int bits>
const BigInt<2 * bits> operator*(const BigInt<bits>& multiplicand, const BigInt<bits>& factor);

template<int bits>
const BigInt<bits> operator/(const BigInt<2 * bits>& dividend, const BigInt<bits>& divisor);

template<int bits>
const BigInt<bits> operator%(const BigInt<2 * bits>& dividend, const BigInt<bits>& divisor);

template<int bits>
const BigInt<bits> operator%(const BigInt<bits>& dividend, const BigInt<bits>& divisor);

template<int bits>
bool operator<(const BigInt<bits>& a, const BigInt<bits>& b);

template<int bits>
bool operator<=(const BigInt<bits>& a, const BigInt<bits>& b);

template<int bits>
bool operator>(const BigInt<bits>& a, const BigInt<bits>& b);

template<int bits>
bool operator>=(const BigInt<bits>& a, const BigInt<bits>& b);

template<int bits>
bool operator==(const BigInt<bits>& a, const BigInt<bits>& b);

template<int bits>
bool operator!=(const BigInt<bits>& a, const BigInt<bits>& b);

//-1	a<b 
//0		a==b 
//1		a>b 
template<int bits>
int BigIntCompareHelper(const BigInt<bits>& a, const BigInt<bits>& b);

template<int bits>
class BigInt
{
public:
	static const int intNum = bits / intBits;
private:
	unsigned int represent[intNum];
	bool signFlag;//true means +; false means -
	bool overflowFlag; //true means overflow happend
public:
	
	static const BigInt<bits> getRandom()
	{
		BigInt<bits> temp;
		for (int i = 0; i < intNum; i++)
			temp.represent[i] = BigIntSeries::rd();
		return temp;
	}
	friend BigInt<2 * bits>;
	friend BigInt<bits/2>;
	BigInt(char* init, int base=16);
	BigInt() :signFlag(true), overflowFlag(false)
	{
		memset(represent, 0, bits / bitsPerByte);
	}
	explicit BigInt(const BigInt<2 * bits>& from)
	{
		for (int i = 0; i < bits / intBits; i++)
			represent[i] = from.represent[i];
	}
	explicit operator BigInt<2 * bits>()const
	{
		BigInt<2 * bits> temp;
		for (int i = 0; i < bits / intBits; i++)
			temp.represent[i] = this->represent[i];
		return temp;
	}

	//true means Overflow while false means not
	static inline bool judgeOverflow(unsigned int a, unsigned int b)
	{
		return a > ~b;
		//because a+b>0xFFFFFFFF means overflow return true
		//a>0xFFFFFFFF-b=~b;
	}

	
	friend const BigInt<bits> operator+ <>(const BigInt<bits>& summand, const BigInt<bits>& addand);
	friend const BigInt<bits> operator- <>(const BigInt<bits>& minuend, const BigInt<bits>& subtrahend);
	friend const BigInt<2*bits> operator* <>(const BigInt<bits>& multiplicand, const BigInt<bits>& factor);
	friend const BigInt<bits> operator/ <>(const BigInt<2*bits>& dividend, const BigInt<bits>& divisor);
	friend const BigInt<bits> operator% <>(const BigInt<2*bits>& dividend, const BigInt<bits>& divisor);
	//beacause always in this branch means You are using sum or diff to have module;
	friend const BigInt<bits> operator% <>(const BigInt<bits>& dividend, const BigInt<bits>& divisor);
	friend int BigIntCompareHelper(const BigInt<bits>& a, const BigInt<bits>& b);
	friend bool operator< <>(const BigInt<bits>& a, const BigInt<bits>& b);
	friend bool operator<= <>(const BigInt<bits>& a, const BigInt<bits>& b);
	friend bool operator> <>(const BigInt<bits>& a, const BigInt<bits>& b);
	friend bool operator>= <>(const BigInt<bits>& a, const BigInt<bits>& b);
	friend bool operator== <>(const BigInt<bits>& a, const BigInt<bits>& b);
	friend bool operator!= <>(const BigInt<bits>& a, const BigInt<bits>& b);
	friend std::ostream& operator<< (std::ostream& out, const BigInt<bits>& num)
	{
		for (int i = 0; i < bits / intBits; i++)
			out << std::setfill('0') << std::setw(8) << std::hex << std::uppercase << num.represent[i] << ' ';
		out << std::endl;
		return out;
	}
	const BigInt<bits> operator-(void)const
	{
		BigInt<bits> temp = *this;
		temp.signFlag = !(temp.signFlag);
		return temp;
	}

};

#endif //BIG_INT

