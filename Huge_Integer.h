#pragma once
#include <fstream>
#include <iostream>
using namespace std;

class HugeInt
{
	bool isNeg;
	int Size;
	int* Nums;
	HugeInt QuantityWiseSub(const HugeInt& I2)const;
	HugeInt QuantityWiseAdd(const HugeInt& I2)const;
	bool QuantityWiseLesser(const HugeInt& I2)const;
	bool QuantityWiseGreater(const HugeInt& I2)const;
	bool QuantityWiseEqual(const HugeInt& I2)const;
	void shrink();
	HugeInt identity()const;
	HugeInt NULLHI()const;
public:
	
	HugeInt(ifstream& rdr);
	HugeInt(int i);
	HugeInt(const HugeInt& I1);
	HugeInt();
	int operator[](int i)const 
	{
		if (i < this->Size)
			return Nums[i];
		return 0;
	}
	int& operator[](int i)
	{
		if (i < this->Size)
			return Nums[i];
	}
	friend ostream& operator << (ostream&, const HugeInt I);
	friend istream& operator >> (istream&, HugeInt& I);
	bool operator <(const HugeInt& I2)const;
	bool operator <=(const HugeInt& I2)const;
	bool operator >(const HugeInt& I2)const;
	bool operator >=(const HugeInt& I2)const;
	bool operator ==(const HugeInt& I2)const;
	void operator =(const HugeInt& I2);
	HugeInt operator +(const HugeInt& I2)const;
	const HugeInt& operator +=(const HugeInt& I2);
	HugeInt operator -()const;
	HugeInt operator -(const HugeInt& I2)const;
	const HugeInt& operator -=(const HugeInt& I2);
	void operator --();
	void operator ++();
	HugeInt operator *(const HugeInt& I2)const;
	const HugeInt& operator *=(const HugeInt& I2);
	HugeInt operator /(const HugeInt& I2)const;
	const HugeInt& operator /=(const HugeInt& I2);
	HugeInt operator %(const HugeInt& I2)const;
	const HugeInt& operator %=(const HugeInt& I2);

	~HugeInt();
};

