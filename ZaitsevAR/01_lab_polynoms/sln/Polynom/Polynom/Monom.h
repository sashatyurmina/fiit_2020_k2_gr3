#pragma once
#include "Exception.h"
#include "TNode.h"
#include <iostream>
#include <string>

using namespace std;

#define MAX_KEY 999
#define MAX_DEGREE 9
#define Monom TNode<unsigned int, double>


template<>
struct Monom
{
	unsigned int key;
	double data;
	Monom* pNext;

	TNode();
	TNode(int key, double data);
	TNode(double data); // Нужен для умножения монома на константу
	TNode(const Monom& monom);
	TNode(const string& monom);
	~TNode();

	bool operator==(const Monom& monom) const;
	const Monom& operator=(const Monom& monom);

	Monom operator-() const; // унарный минус

	Monom operator+(const Monom& monom);
	Monom operator-(const Monom& monom);
	Monom operator*(const Monom& monom);

	friend ostream& operator<<(ostream& out, const Monom& monom);
};


Monom::TNode()
{
	key = 0;
	data = 0.0;
	pNext = nullptr;
}

Monom::TNode(int key, double data)
{
	if (key > MAX_KEY)
		throw Exception(" Error, key more than 999\n");
	this->key = key;
	this->data = data;
	pNext = nullptr;
}

Monom::TNode(double data)
{
	key = 0;
	this->data = data;
	pNext = nullptr;
}

Monom::TNode(const Monom& monom)
{
	key = monom.key;
	data = monom.data;
	pNext = nullptr;
}

Monom::~TNode()
{
	pNext = nullptr;
}

bool Monom::operator==(const Monom& monom) const
{
	return ((this->key == monom.key) && (this->data == monom.data));
}

const Monom& Monom::operator=(const Monom& monom)
{
	if (*this == monom)
		return *this;
	key = monom.key;
	data = monom.data;
	return *this;
}

Monom Monom::operator-() const
{
	return Monom(key, -data);
}

Monom Monom::operator+(const Monom& monom)
{
	if (key != monom.key)
		throw Exception(" Error of addition, degrees are different\n");
	return Monom(key, data + monom.data);
}

Monom Monom::operator-(const Monom& monom)
{
	if (key != monom.key)
		throw Exception(" Error of subtraction, degrees are different\n");
	return Monom(key, data - monom.data);
}

Monom Monom::operator*(const Monom& monom)
{
	if ((key / 100 + monom.key / 100 > MAX_DEGREE)
		|| ((key % 100) / 10 + (monom.key % 100) / 10 > MAX_DEGREE)
		|| (key % 10 + monom.key % 10 > MAX_DEGREE))
		throw Exception
		(" Error of multiplication, monom doesn't exist, degree > MAX_DEGREE\n");
	return Monom(key + monom.key, data * monom.data);
}

Monom::TNode(const string& monom)
{
	unsigned int _key;
	double _data;

	string new_monom;
	for (int i = 0; i < monom.length(); i++) // отбрасываем лишние символы
	{
		if ((monom[i] != ' ') && (monom[i] != '*'))
			new_monom.push_back(monom[i]);
	}

	int x_degree = 0;
	int y_degree = 0;
	int z_degree = 0;
	string coef;
	char sign = '+'; // '+' ~ 43, '-' ~ 45

	// Определяем знак

	int j = 0;
	if (new_monom[j] == '+' || new_monom[j] == '-')
		if (('0' <= new_monom[j + 1] && new_monom[j + 1] <= '9')
			|| (new_monom[j + 1] == 'x') || (new_monom[j + 1] == 'y')
			|| (new_monom[j + 1] == 'z'))
		{
			sign = new_monom[j];
			j++;
		}
		else
			throw Exception(" Error, incorrect enter after '+' or '-'!\n");

	// выделяем коэфициент и сохраняем его в отдельной строке

	if ((new_monom[j] == 'x') || (new_monom[j] == 'y') || (new_monom[j] == 'z'))
		coef.push_back('1'); // в таком случае коэфициент у монома равен 1
	else
		while ((new_monom[j] != 'x') && (new_monom[j] != 'y')
			&& (new_monom[j] != 'z') && (j < new_monom.length()))
			coef.push_back(new_monom[j++]);

	// а теперь сохраняем в переменной коэфициент из строки

	// в случае, если не найдём символ из приведённых,
	// значение должно равняться npos (-1) (см. ниже)
	if ((!coef.empty()) && (coef.find_first_not_of("0123456789.") == coef.npos))
		_data = stod(coef) * (44 - (int)sign); // stod извлекает из строки число
	else
		throw Exception
		(" Error, monom doesn't exist, incorrect enter or incorrect coefficient\n");

	// далее работаем со степенями у переменных x,y,z

	for (int i = j; i < new_monom.length(); i++)
	{
		switch (new_monom[i])
		{
		case 'x':
		{
			if (new_monom[i + 1] == '^')
				if ('0' <= new_monom[i + 2] && new_monom[i + 2] <= '9')
					if (x_degree + new_monom[i + 2] - '0' > MAX_DEGREE)
						throw Exception
						(" Error, monom doesn't exist, degree > MAX_DEGREE!\n");
					else
					{
						x_degree += new_monom[i + 2] - '0';
						i += 2;
					}
				else
					throw Exception(" Error, after ^ must be digit (0 - 9)\n");
			else if ((new_monom[i + 1] == 'y') || (new_monom[i + 1] == 'z')
				|| (i + 1 >= new_monom.length()))
				if (x_degree + 1 > MAX_DEGREE)
					throw Exception
					(" Error, monom doesn't exist, degree > MAX_DEGREE\n");
				else
					x_degree++;
			else
				throw Exception(" Error, monom doesn't exist\n");
			break;
		}
		case 'y':
		{
			if (new_monom[i + 1] == '^')
				if ('0' <= new_monom[i + 2] && new_monom[i + 2] <= '9')
					if (y_degree + new_monom[i + 2] - '0' > MAX_DEGREE)
						throw Exception
						(" Error, monom doesn't exist, degree > MAX_DEGREE!!\n");
					else
					{
						y_degree += new_monom[i + 2] - '0';
						i += 2;
					}
				else
					throw Exception(" Error, after ^ must be digit (0 - 9)\n");
			else if ((new_monom[i + 1] == 'x') || (new_monom[i + 1] == 'z')
				|| (i + 1 >= new_monom.length()))
				if (y_degree + 1 > MAX_DEGREE)
					throw Exception
					(" Error, monom doesn't exist, degree > MAX_DEGREE\n");
				else
					y_degree++;
			else
				throw Exception(" Error, monom doesn't exist\n");
			break;
		}
		case 'z':
		{
			if (new_monom[i + 1] == '^')
				if ('0' <= new_monom[i + 2] && new_monom[i + 2] <= '9')
					if (z_degree + new_monom[i + 2] - '0' > MAX_DEGREE)
						throw Exception
						(" Error, monom doesn't exist, degree > MAX_DEGREE!!!\n");
					else
					{
						z_degree += new_monom[i + 2] - '0';
						i += 2;
					}
				else
					throw Exception(" Error, after ^ must be digit (0 - 9)\n");
			else if ((new_monom[i + 1] == 'x') || (new_monom[i + 1] == 'y')
				|| (i + 1 >= new_monom.length()))
				if (z_degree + 1 > MAX_DEGREE)
					throw Exception
					(" Error, monom doesn't exist, degree > MAX_DEGREE\n");
				else
					z_degree++;
			else
				throw Exception(" Error, monom doesn't exist\n");
			break;
		}
		default:
			throw Exception(" Error, monom doesn't exist, incorrect enter!\n");
			break;
		}
	}
	_key = x_degree * 100 + y_degree * 10 + z_degree;

	key = _key;
	data = _data;
}

ostream& operator<<(ostream& out, const Monom& monom)
{
	if (monom.data == 0.0)
	{
		out << " 0  (your monom is empty)";
		return out;
	}
	if (monom.data < 0.0)
		out << " -";
	if (monom.data > 0.0)
		out << " +";
	if ((abs(monom.data) != 1.0) || (monom.key == 0))
		out << " " << abs(monom.data);

	if (monom.key / 100 == 1)
	{
		if (abs(monom.data) == 1)
			out << " x";
		else
			out << " * x";
	}
	else if (monom.key / 100 != 0)
	{
		if (abs(monom.data) == 1)
			out << " x^" << monom.key / 100;
		else
			out << " * x^" << monom.key / 100;
	}

	if ((monom.key % 100) / 10 == 1)
	{
		if ((monom.key / 100 == 0) && (abs(monom.data) == 1))
			out << " y";
		else
			out << " * y";
	}
	else if ((monom.key % 100) / 10 != 0)
	{
		if ((monom.key / 100 == 0) && (abs(monom.data) == 1))
			out << " y^" << (monom.key % 100) / 10;
		else
			out << " * y^" << (monom.key % 100) / 10;
	}

	if (monom.key % 10 == 1)
	{
		if ((monom.key / 100 == 0) && ((monom.key % 100) / 10 == 0)
			&& (abs(monom.data) == 1))
			out << " z";
		else
			out << " * z";
	}
	else if (monom.key % 10 != 0)
	{
		if ((monom.key / 100 == 0) && ((monom.key % 100) / 10 == 0)
			&& (abs(monom.data) == 1))
			out << " z^" << monom.key % 10;
		else
			out << " * z^" << monom.key % 10;
	}

	return out;
}