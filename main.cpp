#include"BigInt.h"
using namespace std;
int main()
{
	BigInt<512> a, b,c;
	a = BigInt<512>::getRandom();
	b = BigInt<512>::getRandom();
	//c = a+b;
	cout << a+b;

}