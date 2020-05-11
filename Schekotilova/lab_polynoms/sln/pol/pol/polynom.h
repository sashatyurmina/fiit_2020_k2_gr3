#pragma once
#include "Monom.h"
#include <string>

using namespace std;

class Polynom
{
private:
	TList<unsigned int, float>* monoms;
public:
	Polynom();
	Polynom(const string&);
	Polynom(const Polynom&);
	Polynom(TList<unsigned int, float>*);
	~Polynom() { delete monoms; }

	void SortingDegs();
	void SimularTerms();
	Polynom operator+(const Polynom&);
	Polynom operator-(const Polynom&);
	Polynom operator*(const Polynom&);
	bool operator==(const Polynom&) const;
	const Polynom& operator=(const Polynom&);
	Polynom operator-() const;
	Polynom operator*(const TNode<unsigned int, float>&);//polynom*monom
	friend ostream& operator<<(ostream& out, const Polynom&);
};

Polynom::Polynom()
{
	monoms = new TList<unsigned int, float>();
}

Polynom::Polynom(const string& str)
{
	monoms = new TList<unsigned int, float>();
	string s = str;
	float pData = 1;
	int key = 0, i = 0;
	bool is_x = false, is_y = false, is_z = false;
	while (i < s.length())
	{
		do
		{
			if (s[i] == '^')
			{
				i++;
				continue;
			}
			if (isdigit(s[i]) && !is_x && !is_y && !is_z)
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
				pData *= (float)(atof(c.c_str()));
				continue;
			}
			if (s[i] == 'x')
			{
				i++;
				is_x = true;
				is_y = false;
				is_z = false;
			}
			if (is_x == true && (s[i] == 'y' || s[i] == 'z' || s[i] == ' '))
			{
				is_x = false;
				key += 100;
			}
			if (is_x == true && isdigit(s[i]))
			{
				if (isdigit(s[i + 1])) throw "error809 (incorrect key (> 9))";
				key += ((int)s[i] - 48) * 100;
				is_x = false;
				i++;
				continue;
			}
			if ((i + 1) == s.length() && is_x == true)
			{
				is_x = false;
				key += 100;
				i++;
			}
			if (s[i] == 'y')
			{
				i++;
				is_x = false;
				is_y = true;
				is_z = false;
			}
			if (is_y == true && (s[i] == 'x' || s[i] == 'z' || s[i] == ' '))
			{
				is_y = false;
				key += 10;
			}
			if ((is_y == true) && (isdigit(s[i])))
			{
				if (isdigit(s[i + 1])) throw "error809 (incorrect key (> 9))";
				key += ((int)s[i] - 48) * 10;
				is_y = false;
				i++;
				continue;
			}
			if (((i + 1) == s.length()) && (is_y == true))
			{
				is_y = false;
				key += 10;
				i++;
			}
			if (s[i] == 'z')
			{
				i++;
				is_x = false;
				is_y = false;
				is_z = true;
			}
			if ((i + 1) == s.length() && is_z == true)
			{
				is_z = false;
				key += 1;
				i++;
				continue;
			}
			if ((is_z == true) && !(isdigit(s[i])))
			{
				is_z = false;
				key += 1;
			}
			if ((is_z == true) && (isdigit(s[i])))
			{
				if (isdigit(s[i + 1])) throw "error809 (incorrect key (> 9))";
				key += ((int)s[i] - 48);
				is_z = false;
				i++;
				continue;
			}
			if ((s[i] == ' ') && (is_z == true))
			{
				is_z = false;
				key += 1;
			}
			if (s[i] == '+')
			{
				i++;
				continue;
			}
			if (s[i] == '-')
			{
				i++;
				pData *= (-1);
				continue;
			}
			if (s[i] == ' ')
			{
				i++;
				continue;
			}
		} while (!(s[i] == '+' || s[i] == '-') && i != s.length() && !is_x || !is_y || !is_z);
		monoms->InsertEnd(key, pData);
		pData = 1;
		key = 0;
	}
	SimularTerms();
	SortingDegs();
}

Polynom::Polynom(const Polynom& tmp)
{
	monoms = new TList<unsigned int, float>(*tmp.monoms);
}

Polynom::Polynom(TList<unsigned int, float>* list)
{
	list->Reset();
	while (!list->IsEnded())
	{
		if (list->getCurr()->key < 0 || list->getCurr()->key > 999)
			throw "error8859 (some key is wrong)";
		list->Next();
	}
	monoms = new TList<unsigned int, float>(*list);

	SimularTerms();
	SortingDegs();
}

void Polynom::SortingDegs()
{
	if (monoms->getFirst() == nullptr || monoms->getFirst()->pNext == nullptr) return;
	monoms->Reset();
	TNode<unsigned int, float>* node = monoms->getFirst(), * nnode = monoms->getFirst()->pNext;
	TNode<unsigned int, float>* prev_node = monoms->getFirst(), * tmp;
	while (node->pNext != nullptr)
	{
		while (nnode != nullptr)
		{
			if (node->key < nnode->key)
			{
				if (prev_node == node)
					monoms->pFirst = nnode;
				else
					prev_node->pNext = nnode;
				node->pNext = nnode->pNext;
				nnode->pNext = node;
				tmp = node;
				node = nnode;
				nnode = tmp;
			}
			prev_node = node;
			node = node->pNext;
			nnode = nnode->pNext;
		}
	}
}

void Polynom::SimularTerms()
{
	monoms->Reset();
	if (monoms->getCurr() == nullptr)
		return;
	while (!monoms->IsEnded())
	{
		TNode<unsigned int, float>* tmp = monoms->getFirst();
		TNode<unsigned int, float>* temp = monoms->getCurr();
		while (tmp->key != temp->key)
			tmp = tmp->pNext;
		if (tmp == temp)
		{
			monoms->Next();
			continue;
		}
		monoms->getCurr()->pData = monoms->getCurr()->pData + tmp->pData;
		monoms->Remove(tmp->key);
		monoms->Next();
	}
	monoms->Reset();
}

Polynom Polynom::operator+(const Polynom& polynom)
{
	if (monoms->IsEmpty()) return polynom;
	if (polynom.monoms->IsEmpty()) return (*this);
	Polynom result;
	polynom.monoms->Reset();
	monoms->Reset();
	while ((!polynom.monoms->IsEnded()) && (!monoms->IsEnded()))
	{
		if (monoms->getCurr()->key < polynom.monoms->getCurr()->key)
		{
			result.monoms->InsertEnd(monoms->getCurr()->key, monoms->getCurr()->pData);
			monoms->Next();
		}
		else if (monoms->getCurr()->key > polynom.monoms->getCurr()->key)
		{
			result.monoms->InsertEnd(polynom.monoms->getCurr()->key, polynom.monoms->getCurr()->pData);
			polynom.monoms->Next();
		}
		else
		{
			if ((monoms->getCurr()->pData + polynom.monoms->getCurr()->pData) != 0)
			{
				result.monoms->InsertEnd(monoms->getCurr()->key, monoms->getCurr()->pData + polynom.monoms->getCurr()->pData);
			}
			monoms->Next();
			polynom.monoms->Next();
		}
	}
	while (!monoms->IsEnded())
	{
		result.monoms->InsertEnd(monoms->getCurr()->key, monoms->getCurr()->pData);
		monoms->Next();
	}
	while (!polynom.monoms->IsEnded())
	{
		result.monoms->InsertEnd(polynom.monoms->getCurr()->key, polynom.monoms->getCurr()->pData);
		polynom.monoms->Next();
	}
	result.monoms->Reset();
	result.SortingDegs();
	result.SimularTerms();
	return result;
}

Polynom Polynom::operator-(const Polynom& polynom)
{
	return *this + (-polynom);
}

Polynom Polynom::operator*(const Polynom& polynom)
{
	Polynom result;
	monoms->Reset();
	while (!monoms->IsEnded())
	{
		polynom.monoms->Reset();
		while (!polynom.monoms->IsEnded())
		{
			TNode<unsigned int, float>* res;
			res = *monoms->getCurr() * (*polynom.monoms->getCurr());
			result.monoms->InsertEnd(res->key, res->pData);
			polynom.monoms->Next();
		}
		monoms->Next();
	}
	result.SimularTerms();
	result.SortingDegs();
	return result;
}

bool Polynom::operator==(const Polynom& polynom) const
{
	while (!polynom.monoms->IsEnded() || !monoms->IsEnded())
	{
		if (monoms->getCurr() != polynom.monoms->getCurr())
			return false;
	}
	if (!polynom.monoms->IsEnded() || !monoms->IsEnded())
		return false;
	else
		return true;
}

const Polynom& Polynom::operator=(const Polynom& polynom)
{
	if (*this == polynom)
		return *this;
	if (!monoms->IsEnded())
	{
		delete monoms;
	}
	monoms = new TList<unsigned int, float>(*polynom.monoms);
	return *this;
}

Polynom Polynom::operator-() const
{
	Polynom result(*this);
	while (!result.monoms->IsEnded())
	{
		result.monoms->getCurr()->pData *= -1;
		result.monoms->Next();
	}
	result.monoms->Reset();
	return result;
}

Polynom  Polynom::operator*(const TNode<unsigned int, float>& monom)
{
	if (monom.pData == 0)
		return monoms;
	Polynom result;
	TNode<unsigned int, float>* mon = new TNode<unsigned int, float>(monom);
	while (!monoms->IsEnded())
	{
		result.monoms->InsertEnd(monoms->getCurr()->key, mon->pData * monoms->getCurr()->pData);
		monoms->Next();
	}
	SimularTerms();
	SortingDegs();
	return result;
}

ostream& operator<<(ostream& out, const Polynom& polynom)
{
	unsigned int d;
	float coeff;
	polynom.monoms->Reset();
	if (polynom.monoms->IsEnded())
	{
		out << "0";
		return out;
	}
	while (!polynom.monoms->IsEnded())
	{
		d = polynom.monoms->getCurr()->key;
		coeff = polynom.monoms->getCurr()->pData;
		int d_x = d / 100;
		int d_y = (d % 100) / 10;
		int d_z = d % 10;
		if (coeff == 0)
		{
			polynom.monoms->Next();
			continue;
		}
		else
		{
			if (coeff != 1 && coeff != -1)
			{
				if (coeff > 0)
					out << "+" << coeff;
				if (coeff < 0)
					out << coeff;
			}
			if (coeff == -1)
				out << "-";
			if (coeff == 1)
				out << "+";
			if (d_x == 1)
				out << "x";
			if (d_y == 1)
				out << "y";
			if (d_z == 1)
				out << "z";
			if (d_x > 0 && d_x != 1)
				out << "x^" << d_x;
			if (d_y > 0 && d_y != 1)
				out << "y^" << d_y;
			if (d_z > 0 && d_z != 1)
				out << "z^" << d_z;
		}
		polynom.monoms->Next();
	}
	return out;
}