#include "Polinom.h"
#include <string>

using namespace std;

Polinom::Polinom()
{
	polinom = new TList<unsigned int, double>();
}

Polinom::Polinom(const string& str)
{
	polinom = new TList<unsigned int, double>();
	string s = str;
	double coeff = 1;
	int degree = 0;
	int i = 0;
	bool _x = false;
	bool _y = false;
	bool _z = false;
	while (i < s.length())
	{
		do
		{
			if (s[i] == '^')
			{
				i++;
				continue;
			}
			if (isdigit(s[i]) && !_x && !_y && !_z)
			{
				string c;
				while (isdigit(s[i]))
				{
					if (s[i + 1] == '.')
					{
						c += s[i];
						c += s[i + 1];
						i = i + 2;
					}
					else
					{
						c += s[i];
						i++;
					}
				}
				coeff *= (double)(atof(c.c_str()));
				continue;
			}
			if (s[i] == 'x')
			{
				i++;
				_x = true;
				_y = false;
				_z = false;
			}
			if ((_x == true) && ((s[i] == 'y') || (s[i] == 'z') || (s[i] == ' ')))
			{
				_x = false;
				degree += 100;
			}
			if ((_x == true) && (isdigit(s[i])))
			{
				if (isdigit(s[i + 1]))
					throw "Degree should be no more then 9";
				degree += ((int)s[i] - 48) * 100;
				_x = false;
				i++;
				continue;
			}
			if (((i + 1) == s.length()) && (_x == true))
			{
				_x = false;
				degree += 100;
				i++;
			}
			if (s[i] == 'y')
			{
				i++;
				_x = false;
				_y = true;
				_z = false;
			}
			if ((_y == true) && ((s[i] == 'x') || (s[i] == 'z') || (s[i] == ' ')))
			{
				_y = false;
				degree += 10;
			}
			if ((_y == true) && (isdigit(s[i])))
			{
				if (isdigit(s[i + 1]))
					throw "Degree should be no more then 9";
				degree += ((int)s[i] - 48) * 10;
				_y = false;
				i++;
				continue;
			}
			if (((i + 1) == s.length()) && (_y == true))
			{
				_y = false;
				degree += 10;
				i++;
			}
			if (s[i] == 'z')
			{
				i++;
				_x = false;
				_y = false;
				_z = true;
			}
			if (((i + 1) == s.length()) && (_z == true))
			{
				_z = false;
				degree += 1;
				i++;
				continue;
			}
			if ((_z == true) && !(isdigit(s[i])))
			{
				_z = false;
				degree += 1;
			}
			if ((_z == true) && (isdigit(s[i])))
			{
				if (isdigit(s[i + 1]))
					throw "Degree should be no more then 9";
				degree += ((int)s[i] - 48);
				_z = false;
				i++;
				continue;
			}
			if ((s[i] == ' ') && (_z == true))
			{
				_z = false;
				degree += 1;
			}
			if (s[i] == '+')
			{
				i++;
				continue;
			}
			if (s[i] == '-')
			{
				i++;
				coeff *= (-1);
				continue;
			}
			if (s[i] == ' ')
			{
				i++;
				continue;
			}
		} while (!((s[i] == '+') || (s[i] == '-')) && (i != s.length()) && (!_x || !_y || !_z));
		polinom->InsertEnd(degree, coeff);
		coeff = 1;
		degree = 0;
	}
	Simplification();
	OrganizeL();
}

Polinom::Polinom(const Polinom& tmp)
{
	polinom = new TList<unsigned int, double>(*tmp.polinom);
}

Polinom::Polinom(TList<unsigned int, double>* list)
{
	list->Reset();
	while (!list->IsEnded())
	{
		if (list->GetCurrent()->degree > 999 || list->GetCurrent()->degree < 0)
			throw"One of polynom's degree is wrong";
		list->Next();
	}
	polinom = new TList<unsigned int, double>(*list);
	Simplification();
	OrganizeL();
}

Polinom::~Polinom()
{
	delete polinom;
}

Polinom Polinom::operator+(const Polinom& pol)
{
	if (polinom->IsEmpty())
		return pol;
	if (pol.polinom->IsEmpty())
		return (*this);
	Polinom result;
	pol.polinom->Reset();
	polinom->Reset();
	while ((!pol.polinom->IsEnded()) && (!polinom->IsEnded()))
	{
		if (polinom->GetCurrent()->degree < pol.polinom->GetCurrent()->degree)
		{
			result.polinom->InsertEnd(polinom->GetCurrent()->degree, polinom->GetCurrent()->coeff);
			polinom->Next();
		}
		else if (polinom->GetCurrent()->degree > pol.polinom->GetCurrent()->degree)
		{
			result.polinom->InsertEnd(pol.polinom->GetCurrent()->degree, pol.polinom->GetCurrent()->coeff);
			pol.polinom->Next();
		}
		else
		{
			if ((polinom->GetCurrent()->coeff + pol.polinom->GetCurrent()->coeff) != 0)
			{
				result.polinom->InsertEnd(polinom->GetCurrent()->degree, polinom->GetCurrent()->coeff + pol.polinom->GetCurrent()->coeff);
			}
			polinom->Next();
			pol.polinom->Next();
		}
	}
	while (!polinom->IsEnded())
	{
		result.polinom->InsertEnd(polinom->GetCurrent()->degree, polinom->GetCurrent()->coeff);
		polinom->Next();
	}
	while (!pol.polinom->IsEnded())
	{
		result.polinom->InsertEnd(pol.polinom->GetCurrent()->degree, pol.polinom->GetCurrent()->coeff);
		pol.polinom->Next();
	}
	result.polinom->Reset();
	result.OrganizeL();
	result.Simplification();
	return result;
}

Polinom Polinom::operator-() const
{
	Polinom result(*this);
	while (!result.polinom->IsEnded())
	{
		result.polinom->GetCurrent()->coeff *= -1;
		result.polinom->Next();
	}
	result.polinom->Reset();
	return result;
}

Polinom Polinom::operator-(const Polinom& pol)
{
	return *this + (-pol);
}

Polinom  Polinom::operator*(const TNode<unsigned int, double>& monom)
{
	if (monom.coeff == 0)
		return polinom;
	Polinom result;
	TNode<unsigned int, double>* mon = new TNode<unsigned int, double>(monom);
	while (!polinom->IsEnded())
	{
		result.polinom->InsertEnd(polinom->GetCurrent()->degree, mon->coeff * polinom->GetCurrent()->coeff);
		polinom->Next();
	}
	Simplification();
	OrganizeL();
	return result;
}

Polinom Polinom::operator*(const Polinom& pol)
{
	Polinom result;
	polinom->Reset();
	while (!polinom->IsEnded())
	{
		pol.polinom->Reset();
		while (!pol.polinom->IsEnded())
		{
			TNode<unsigned int, double>* res;
			res = *polinom->GetCurrent() * *pol.polinom->GetCurrent();
			result.polinom->InsertEnd(res->degree, res->coeff);
			pol.polinom->Next();
		}
		polinom->Next();
	}
	result.Simplification();
	result.OrganizeL();
	return result;
}

bool Polinom::operator==(const Polinom& pol) const
{
	while (!pol.polinom->IsEnded() || !polinom->IsEnded())
	{
		if (polinom->GetCurrent() != pol.polinom->GetCurrent())
			return false;
	}
	if (!pol.polinom->IsEnded() || !polinom->IsEnded())
		return false;
	else
		return true;
}

const Polinom& Polinom::operator=(const Polinom& pol)
{
	if (*this == pol)
		return *this;
	if (!polinom->IsEnded())
	{
		delete polinom;
	}
	polinom = new TList<unsigned int, double>(*pol.polinom);
	return *this;
}

void Polinom::OrganizeL()
{
	if ((polinom->GetFirst() == nullptr) || (polinom->GetFirst()->pNext == nullptr))
		return;
	polinom->Reset();
	TNode<unsigned int, double>* node = polinom->GetFirst();
	TNode<unsigned int, double>* node_1 = polinom->GetFirst()->pNext;
	TNode<unsigned int, double>* prev_node = polinom->GetFirst(), *tmp;
	while (node->pNext != nullptr)
	{
		while (node_1 != nullptr)
		{
			if (node->degree < node_1->degree)
			{
				if (prev_node == node)
					polinom->pFirst = node_1;
				else
					prev_node->pNext = node_1;
				node->pNext = node_1->pNext;
				node_1->pNext = node;
				tmp = node;
				node = node_1;
				node_1 = tmp;
			}
			prev_node = node;
			node = node->pNext;
			node_1 = node_1->pNext;
		}
	}
}

void Polinom::Simplification()
{
	polinom->Reset();
	if (polinom->GetCurrent() == nullptr)
		return;
	while (!polinom->IsEnded())
	{
		TNode<unsigned int, double>* tmp = polinom->GetFirst();
		TNode<unsigned int, double>* tmp_1 = polinom->GetCurrent();
		while (tmp->degree != tmp_1->degree)
			tmp = tmp->pNext;
		if (tmp == tmp_1)
		{
			polinom->Next();
			continue;
		}
		polinom->GetCurrent()->coeff += tmp->coeff;
		polinom->Remove(tmp->degree);
		polinom->Next();
	}
	polinom->Reset();
}

ostream& operator<<(ostream& out, const Polinom& pol)
{
	unsigned int deg;
	double coef;
	pol.polinom->Reset();
	if (pol.polinom->IsEnded())
	{
		out << "0";
		return out;
	}
	while (!pol.polinom->IsEnded())
	{
		deg = pol.polinom->GetCurrent()->degree;
		coef = pol.polinom->GetCurrent()->coeff;
		int deg_x = deg / 100;
		int deg_y = (deg % 100) / 10;
		int deg_z = deg % 10;
		if (coef == 0)
		{
			pol.polinom->Next();
			continue;
		}
		else
		{
			if (coef != 1 && coef != -1)
			{
				if (coef > 0)
					out << "+" << coef;
				if (coef < 0)
					out << coef;
			}
			if (coef == -1)
				out << "-";
			if (coef == 1)
				out << "+";
			if (deg_x == 1)
				out << "x";
			if (deg_y == 1)
				out << "y";
			if (deg_z == 1)
				out << "z";
			if (deg_x > 0 && deg_x != 1)
				out << "x^" << deg_x;
			if (deg_y > 0 && deg_y != 1)
				out << "y^" << deg_y;
			if (deg_z > 0 && deg_z != 1)
				out << "z^" << deg_z;
		}
		pol.polinom->Next();
	}
	return out;
}
