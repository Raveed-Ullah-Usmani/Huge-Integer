#include <fstream>
#include <cstring>
#include "Huge_Integer.h"
using namespace std;
HugeInt HugeInt::identity()const
{
	HugeInt I(1);
	I.Nums = new int[I.Size];
	I.isNeg = false;
	I.Nums[0] = 1;
	return I;
}
HugeInt HugeInt::NULLHI()const
{
	HugeInt I(1);
	I.Nums = new int[I.Size];
	I.isNeg = false;
	I.Nums[0] = 0;
	return I;
}
int maxof(int x, int y)
{
	if (x > y)
	{
		return x;
	}
	return y;
}
HugeInt::HugeInt(const HugeInt& I1)
{
	this->Size = I1.Size;
	this->isNeg = I1.isNeg;
	this->Nums = new int[this->Size];
	for (int i = 0; i < this->Size; i++)
	{
		(* this)[i] = I1[i];
	}
}
HugeInt::HugeInt(int i)
{
	this->Size = i;
	this->Nums = new int[this->Size];
}
HugeInt::HugeInt(ifstream& rdr)
{
	string N;
	rdr >> N;

	int i = 0;
	if (N[i] == '+' || N[i] == '-')
	{
		isNeg = ((N[i] == '-') ? true : false);
		i++;
	}
	this->Size = N.length() - i;
	Nums = new int[this->Size];
	for (int ni = 0; ni < this->Size; ni++, i++)
	{
		Nums[this->Size - 1 - ni] = N[i] - 48;
	}
}
HugeInt::HugeInt()
{
	this->Size = 0;
	this->isNeg = 0;
	this->Nums = NULL;
}
void HugeInt::shrink()
{
	if (this->Size == 1)
	{
		return;
	}
	int count = 0;
	for (int i = this->Size - 1; i >= 1; i--)
	{
		if ((*this)[i] != 0)
		{
			break;
		}
		count++;
	}
	if (count == 0)
	{
		return;
	}
	HugeInt R(this->Size - count);
	R.isNeg = this->isNeg;
	for (int i = 0; i < R.Size; i++)
	{
		R[i] = (*this)[i];
	}
	(*this) = R;

}
ostream& operator<< (ostream&, const HugeInt I)
{
	cout << (I.isNeg ? "-" : "+");
	for (int i = 0; i < I.Size; i++)
	{
		cout << I.Nums[I.Size - 1 - i];
	}
	return cout;
}
istream& operator >> (istream&, HugeInt& I)
{
	string N;
	cin >> N;
	int i = 0;
	if (N[i] == '+' || N[i] == '-')
	{
		I.isNeg = ((N[i] == '-') ? true : false);
		i++;
	}
	I.Size = N.length() - i;
	I.Nums = new int[I.Size];
	for (int ni = 0; ni < I.Size; ni++, i++)
	{
		I.Nums[I.Size - 1 - ni] = N[i] - 48;
	}
	return cin;
}
HugeInt HugeInt::QuantityWiseSub(const HugeInt& I2)const
{
	HugeInt R(this->Size);
	int c = 0;
	//if (this->Size > I2.Size)
	{
		for (int i = 0; i < R.Size; i++)
		{
			int S = (*this)[i] - I2[i] - c;
			if (S < 0)
			{
				S += 10;
				c = 1;

			}
			else
			{
				c = 0;
			}
			R[i] = S;
		}
	}
	return R;
}
HugeInt HugeInt::QuantityWiseAdd(const HugeInt& I2)const
{
	HugeInt R(this->Size + 1);
	int c = 0;
	//if (this->Size > I2.Size)
	{
		for (int i = 0; i < R.Size; i++)
		{
			int S = (*this)[i] + I2[i] + c;
			if (S >= 10)
			{
				S %= 10;
				c = 1;

			}
			else
			{
				c = 0;
			}
			R[i] = S;
		}
	}
	return R;
}
bool HugeInt::QuantityWiseLesser(const HugeInt& I2)const
{
	if (this->Size > I2.Size)
	{
		return false;
	}
	if (this->Size < I2.Size)
	{
		return true;
	}
	for (int i = this->Size - 1; i >= 0; i--)
	{
		if ((*this)[i] > I2[i])
		{
			return false;
		}
		else if ((*this)[i] < I2[i])
		{
			return true;
		}
	}
	return false;

}
bool HugeInt::QuantityWiseGreater(const HugeInt& I2)const
{
	return I2.QuantityWiseLesser(*this);
}
bool HugeInt::QuantityWiseEqual(const HugeInt& I2)const
{
	return this->QuantityWiseLesser(I2) == false && this->QuantityWiseGreater(I2) == false;
}
bool HugeInt::operator <(const HugeInt& I2)const
{
	if (this->isNeg == true && I2.isNeg == false)
	{
		return true;
	}
	if (this->isNeg == false && I2.isNeg == true)
	{
		return false;
	}
	if (this->Size < I2.Size)
	{
		if (this->isNeg == true)
		{
			return false;
		}
		return true;
	}
	if (this->Size > I2.Size)
	{
		if (this->isNeg == true)
		{
			return true;
		}
		return false;
	}
	for (int i = this->Size - 1; i >= 0; i--)
	{
		if ((*this)[i] > I2[i])
		{
			if (this->isNeg == true)
			{
				return true;
			}
			return false;
		}
		if ((*this)[i] < I2[i])
		{
			if (this->isNeg == true)
			{
				return false;
			}
			return true;
		}
	}
	return false;
}
bool HugeInt::operator <=(const HugeInt& I2)const
{
	return *this < I2 || *this == I2;
}
bool HugeInt::operator >(const HugeInt& I2)const
{
	return I2 < *this;
}
bool HugeInt::operator >=(const HugeInt& I2)const
{
	return *this > I2 || *this == I2;
}
bool HugeInt::operator ==(const HugeInt& I2)const
{
	return I2 < *this == false && I2>*this == false;
}
void HugeInt::operator =(const HugeInt& I2)
{
	delete[]this->Nums;
	this->isNeg = I2.isNeg;
	this->Size = I2.Size;
	this->Nums = new int[this->Size];
	for (int i = 0; i < this->Size; i++)
	{
		(*this)[i] = I2[i];
	}
}
HugeInt HugeInt::operator +(const HugeInt& I2)const
{
	HugeInt R;
	if (this->isNeg == I2.isNeg)
	{
		if ((*this). QuantityWiseGreater(I2))
		{
			R = (*this).QuantityWiseAdd(I2);
			R.isNeg = this->isNeg;

		}
		else
		{
			R = I2.QuantityWiseAdd(*this);
			R.isNeg = I2.isNeg;
		}
	}
	else
	{
		if ((*this).QuantityWiseGreater(I2))
		{
			R = (*this).QuantityWiseSub(I2);
			R.isNeg = this->isNeg;

		}
		else
		{
			R = I2.QuantityWiseSub(*this);
			R.isNeg = I2.isNeg;
		}
	}
	R.shrink();
	if (R.QuantityWiseEqual(NULLHI()))
	{
		R.isNeg = false;
	}
	return R;
}
HugeInt HugeInt:: operator -()const
{
	HugeInt temp = *this;
	temp.isNeg = !this->isNeg;
	return temp;
}
HugeInt HugeInt::operator -(const HugeInt& I2)const
{
	HugeInt R;
	HugeInt temp = -I2;
	R = *this + temp;
	/*if ((*this).QuantityWiseGreater(I2))
	{
		R.isNeg = this->isNeg;
	}
	else
	{
		R.isNeg = I2.isNeg;
	}*/
	return R;
}
const HugeInt& HugeInt::operator +=(const HugeInt& I2)
{
	*this = *this + I2;
	return *this;
}
const HugeInt& HugeInt::operator -=(const HugeInt& I2)
{
	*this = *this - I2;
	return *this;
}
void HugeInt::operator --()
{
	*this -= identity();
}
void HugeInt::operator ++()
{
	*this += identity();
}
HugeInt HugeInt::operator *(const HugeInt& I2)const
{
	HugeInt R;
	R = NULLHI();
	HugeInt A = (*this);
	A.isNeg = false;
	HugeInt B = I2;
	B.isNeg = false;
	HugeInt Zero = NULLHI();
	HugeInt TR = A;
	HugeInt c = identity();
	while ((B > Zero))
	{
		HugeInt temp = c + c;
		while (temp <= B)
		{
			TR += TR;
			c += c;
			temp = c + c;
		}
		B -= c;
		R += TR;
		TR = A;
		c = identity();

	}
	if (this->isNeg == I2.isNeg)
	{
		R.isNeg = false;
	}
	else
	{
		R.isNeg = true;
	}
	return R;
}
const HugeInt& HugeInt::operator *=(const HugeInt& I2)
{
	*this = *this * I2;
	return *this;
}
HugeInt HugeInt::operator /(const HugeInt& I2)const
{
	HugeInt Zero = NULLHI();
	if (I2.QuantityWiseEqual(Zero))
	{
		throw 0;
	}
	if (this->QuantityWiseLesser(I2))
	{
		return Zero;
	}
	HugeInt R;
	R = NULLHI();
	HugeInt A = I2;
	A.isNeg = false;
	HugeInt B = (*this);
	B.isNeg = false;
	HugeInt TR = A;
	HugeInt c = identity();
	while ((B > Zero))
	{
		HugeInt temp = TR + TR;
		while (temp <= B)
		{
			TR += TR;
			c += c;
			temp = TR + TR;
		}
		B -= TR;
		R += c;
		//if (B < I2)
		if (B < A)
		{
			break;
		}
		TR = A;
		c = identity();

	}
	if (this->isNeg == I2.isNeg)
	{
		R.isNeg = false;
	}
	else
	{
		R.isNeg = true;
	}
	return R;
}
const HugeInt& HugeInt::operator /=(const HugeInt& I2)
{
	*this = *this / I2;
	return *this;
}
HugeInt HugeInt::operator %(const HugeInt& I2)const
{
	HugeInt Zero = NULLHI();
	if (this->QuantityWiseLesser(I2))
	{
		return *this;
	}
	HugeInt R;
	R = NULLHI();
	HugeInt A = I2;
	A.isNeg = false;
	HugeInt B = (*this);
	B.isNeg = false;
	HugeInt TR = A;
	HugeInt c = identity();
	while ((B > Zero))
	{
		HugeInt temp = TR + TR;
		while (temp <= B)
		{
			TR += TR;
			c += c;
			temp = TR + TR;
		}
		B -= TR;
		R += c;
		if (B < A)
		{
			break;
		}
		TR = A;
		c = identity();

	}
	B.isNeg = false;
	return B;
}
const HugeInt& HugeInt::operator %=(const HugeInt& I2)
{
	*this = *this % I2;
	return *this;
}
HugeInt::~HugeInt()
{
	delete[] this->Nums;
}