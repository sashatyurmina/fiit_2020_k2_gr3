#pragma once
#include "TList.h"
#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Polynom
{
private:
	TList<unsigned int, double>* monoms;

	int Priority(string sign_); // для конструктора полином от строки
	bool SignComparison(string sign, const stack<string> &tmp);
public:
	Polynom();
	Polynom(const Monom& monom);
	Polynom(const TList<unsigned int, double>& list);
	Polynom(const Polynom& polynom);
	~Polynom();
	Polynom(const string& exspression);

	Polynom& operator=(const Polynom& polynom);
	bool operator==(const Polynom& polynom) const;

	Polynom operator+(const Polynom& polynom) const;
	Polynom operator+(const Monom& monom);

	Polynom operator-() const;

	Polynom operator-(const Polynom& polynom) const;
	Polynom operator-(const Monom& monom);

	Polynom operator*(const Polynom& polynom) const;
	Polynom operator*(const Monom& monom) const;

	friend ostream& operator<<(ostream& out, const Polynom& polynom);
	friend istream& operator>>(istream& in, Polynom& polynom);
};

Polynom::Polynom()
{
	monoms = new TList<unsigned int, double>();
}

Polynom::Polynom(const Monom& monom)
{
	monoms = new TList<unsigned int, double>();
	monoms->InsertBegin(monom.key, monom.data);
}

Polynom::Polynom(const TList<unsigned int, double>& list)
{
	TList<unsigned int, double>* tmp = new TList<unsigned int, double>(list);
	tmp->Reset();
	unsigned int min_key, current_key;
	TNode<unsigned int, double>* min_node;
	TNode<unsigned int, double>* current_node;
	int cnt = 0;

	//Сортировка
	tmp->Reset();
	while (!tmp->IsEnded())
	{
		min_key = tmp->GetCurrent()->key;
		current_key = tmp->GetCurrent()->key;
		min_node = tmp->GetCurrent();
		current_node = tmp->GetCurrent();

		tmp->Next();
		if (tmp->IsEnded())
			break;
		while (!tmp->IsEnded())
		{
			if (min_key > tmp->GetCurrent()->key)
			{
				min_key = tmp->GetCurrent()->key;
				min_node = tmp->GetCurrent();
			}
			tmp->Next();
		}
		if (min_key != current_key)
		{
			Monom monom(*(tmp->Search(min_node)));
			*(tmp->Search(min_node)) = *(tmp->Search(current_node));
			*(tmp->Search(current_node)) = monom;
		}

		cnt++;
		tmp->Reset();
		for (int i = 0; i < cnt; i++)
			tmp->Next();
	}

	//Приводятся подобные
	tmp->Reset();
	while (!tmp->IsEnded())
	{
		TNode<unsigned int, double>* node = tmp->GetCurrent();
		tmp->Next();
		if (tmp->IsEnded())
			break;
		while ((!tmp->IsEnded()) && (node->key == tmp->GetCurrent()->key))
		{
			node->data = node->data + tmp->GetCurrent()->data;
			tmp->Remove(tmp->GetCurrent());
		}
	}

	monoms = new TList<unsigned int, double>(*tmp);
	delete tmp;
}

Polynom::Polynom(const Polynom& polynom)
{
	monoms = new TList<unsigned int, double>(*polynom.monoms);
}

Polynom::~Polynom()
{
	delete monoms;
}

bool Polynom::operator==(const Polynom& polynom) const
{
	Polynom polynom1(*this);
	Polynom polynom2(polynom);
	polynom1.monoms->Reset();
	polynom2.monoms->Reset();

	while ((!polynom1.monoms->IsEnded() && !polynom2.monoms->IsEnded()) &&
		((*polynom1.monoms->GetCurrent()) == (*polynom2.monoms->GetCurrent())))
	{
		polynom1.monoms->Next();
		polynom2.monoms->Next();
	}
	if (polynom1.monoms->IsEnded() && polynom2.monoms->IsEnded())
		return true;
	return false;
}

Polynom& Polynom::operator=(const Polynom& polynom)
{
	if (*this == polynom)
	{
		return *this;
	}
	delete monoms;
	monoms = new TList<unsigned int, double>(*polynom.monoms);
	return *this;
}

// Данный оператор позволяет создавать полиномы отсортированными
// по возрастанию, а также не имеющих подобных
Polynom Polynom::operator+(const Monom& monom)
{
	if (this->monoms->IsEmpty())
	{
		return Polynom(monom);
	}

	monoms->Reset();
	while (!monoms->IsEnded() && (monoms->GetCurrent()->key < monom.key))
		monoms->Next();
	if (monoms->IsEnded()) // дошли до конца, и все мономы меньше нового
	{
		monoms->InsertEnd(monom.key, monom.data);
		monoms->Reset();
		return *this;
	}
	if (monoms->GetCurrent()->key > monom.key)
	{
		monoms->InsertBefore(monoms->GetCurrent()->key, monom.key, monom.data);
	}
	if (monoms->GetCurrent()->key == monom.key)
	{ // прибавляем как подобный
		if ((monoms->GetCurrent()->data + monom.data) != 0.0)
			monoms->GetCurrent()->data =
			monoms->GetCurrent()->data + monom.data;
		else
			monoms->Remove(monoms->GetCurrent()->key);
	}
	monoms->Reset();
	return *this;
}

Polynom Polynom::operator+(const Polynom& polynom) const
{
	Polynom sum;
	Polynom polynom1(*this);
	Polynom polynom2(polynom);
	polynom1.monoms->Reset();
	polynom2.monoms->Reset();

	while (!polynom1.monoms->IsEnded() && !polynom2.monoms->IsEnded())
	{
		Monom m1(*polynom1.monoms->GetCurrent());
		Monom m2(*polynom2.monoms->GetCurrent());
		if (m1.key < m2.key)
		{
			sum = sum + m1;
			polynom1.monoms->Next();
		}
		else if (m1.key > m2.key)
		{
			sum = sum + m2;
			polynom2.monoms->Next();
		}
		else if (m1.key == m2.key)
		{
			if (m1.data + m2.data != 0)
			{
				Monom sumMonoms = m1 + m2;
				sum = sum + sumMonoms;
			}
			polynom1.monoms->Next();
			polynom2.monoms->Next();
		}
	}

	while (!polynom1.monoms->IsEnded())
	{
		Monom m1(*polynom1.monoms->GetCurrent());
		sum = sum + m1;
		polynom1.monoms->Next();
	}

	while (!polynom2.monoms->IsEnded())
	{
		Monom m2(*polynom2.monoms->GetCurrent());
		sum = sum + m2;
		polynom2.monoms->Next();
	}
	sum.monoms->Reset();
	return sum;
}

Polynom Polynom::operator-() const
{
	Polynom tmp(*this);
	tmp.monoms->Reset();
	while (!tmp.monoms->IsEnded())
	{
		*tmp.monoms->GetCurrent() = -(*tmp.monoms->GetCurrent());
		tmp.monoms->Next();
	}
	return tmp;
}

Polynom Polynom::operator-(const Monom& monom)
{
	Monom tmp(monom);        // создаём копию монома, так как менять
	return (*this + (-tmp)); // передаваемый не можем из-за const
}

Polynom Polynom::operator-(const Polynom& polynom) const
{
	Polynom tmp(polynom);
	return (*this + (-tmp));
}

Polynom Polynom::operator*(const Monom& monom) const
{
	Polynom result;
	if (monom.data == 0.0)
		return result;
	Polynom polynom(*this);
	polynom.monoms->Reset();
	while (!polynom.monoms->IsEnded())
	{
		Monom tmp = Monom(*polynom.monoms->GetCurrent());
		tmp = tmp * monom;
		if (tmp.data != 0.0)
			result = result + tmp;
		polynom.monoms->Next();
	}
	return result;
}

Polynom Polynom::operator*(const Polynom& polynom) const
{
	Polynom result;
	Polynom polynom1(*this);
	Polynom polynom2(polynom);
	polynom2.monoms->Reset();
	while (!polynom2.monoms->IsEnded())
	{
		Monom tmp = Monom(*polynom2.monoms->GetCurrent());
		result = result + polynom1 * tmp;
		polynom2.monoms->Next();
	} // подобные при умножении (которые например пол-cя при сумм-нии
	// рез-тов от умн-ий одного пол-ма на разные мономы) прив-ся в сумме пол-ов
	return result;
}

ostream& operator<<(ostream& out, const Polynom& polynom)
{
	if (polynom.monoms->IsEmpty())
	{
		out << " 0  (your polynom is empty)";
		return out;
	}
	Polynom tmp(polynom);
	tmp.monoms->Reset();
	while (!tmp.monoms->IsEnded())
	{
		out << *(tmp.monoms->GetCurrent());
		tmp.monoms->Next();
	}

	return out;
}

istream& operator>>(istream& in, Polynom& polynom)
{
	string str;
	cout << " Enter expression with polynomials in string:\n ";
	getline(cin, str);
	polynom = Polynom(str);

	return in;
}

int Polynom::Priority(string sign_)
{
	if (sign_.empty())
		throw Exception(" Error, string is empty\n");
	char sign = sign_[0]; // с таким присваиванием работает, но нужно 
	switch (sign) // знать наверняка, что по 0 индексу лежит операция,
	{             // возможны ошибки
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	default:
		return 0;
	}
}

bool Polynom::SignComparison(string sign, const stack<string> &tmp)
{
	if (Priority(sign) <= Priority(tmp.top()))
		return true;

	return false;
}

Polynom::Polynom(const string& exspression_)
{
	stack<string> stack1;
	stack<string> stack2;
	if (exspression_[0] == '\0')
		throw Exception(" Error, string is empty\n");
	string exspression;
	for (int i = 0; i < exspression_.length(); i++) // избавляемся от пробелов
	{
		if (exspression_[i] != ' ')
			exspression = exspression + exspression_[i];
	}

	for (int i = 0; i < exspression.length(); i++)
	{
		if (!(('0' <= exspression[i] && exspression[i] <= '9') ||
			exspression[i] == '(' || exspression[i] == ')' ||
			exspression[i] == '+' || exspression[i] == '-' ||
			exspression[i] == '*' || exspression[i] == '^' ||
			exspression[i] == 'x' || exspression[i] == 'y' ||
			exspression[i] == 'z'))
			throw Exception(" Error, incorrecting symbol or low register!\n");
	}
	int cnt1 = 0;
	int cnt2 = 0;
	for (int i = 0; i < exspression.length(); i++)
	{
		if (exspression[i] == '(')
			cnt1++;
		if (exspression[i] == ')')
			cnt2++;

		if (cnt2 > cnt1)
			throw Exception(" Error,  ) meets before (");
	}
	if (cnt1 != cnt2)
		throw Exception(" Error,  number ( and ) isn't equal");
	if (exspression[0] == '*' || exspression[0] == '^')
		throw Exception(" Error, You began with * or ^\n");
	for (int i = 0; i < exspression.length() - 1; i++)
	{
		if ((exspression[i] == '+' || exspression[i] == '-' ||
			exspression[i] == '*') && (exspression[i + 1] == '+' ||
				exspression[i + 1] == '-' || exspression[i + 1] == '*'))
			throw Exception(" Error, 2 or more operations go together\n");
	}

	int check = 1;
	for (int i = 0; i < exspression.length(); i++)
	{
		int start = i;
		if (('0' <= exspression[i] && exspression[i] <= '9') ||
			exspression[i] == 'x' || exspression[i] == 'y' ||
			exspression[i] == 'z')
		{
			if (check == 1)
				check = 0;
			int end;
			string for_monom;
			i++;
			while ((i < exspression.length()) && (exspression[i] != '+') &&
				(exspression[i] != '-') && (exspression[i] != '*') &&
				(exspression[i] != ')'))
				i++;
			end = i - 1; // должны сохранить позицию посл-го эл-та на 1 меньше
			for_monom = exspression.substr(start, end - start + 1);
			if (check == 2) // знак у первого монома '-'
			{
				for_monom.insert(0, "-");
				check = 0;
			}
			stack1.push(for_monom);
			i--;
			continue;
		}

		if (exspression[i] == '(')
		{
			string str;
			str = str + exspression[i];
			stack2.push(str);
			continue;
		}
		if (exspression[i] == ')')
		{
			int flag = 0;
			while (!stack2.empty())
			{
				if (stack2.top() != "(")
				{
					stack1.push(stack2.top());
					stack2.pop();
					continue;
				}
				stack2.pop();
				flag = 1;
				break;
			}
			if ((stack2.empty()) && (flag != 1))
				throw Exception(" Wasn't found '('\n");
			continue;
		}

		if (exspression[i] == '+' || exspression[i] == '-' ||
			exspression[i] == '*')
		{
			if (check == 1) // если знак перед первым мономом
			{
				if (exspression[i] == '*')
					throw Exception(" Error, operation '*' before 1 monom\n");
				if (exspression[i] == '-')
					check = 2;
				continue;
			}
			if (stack2.empty())
			{
				string str;
				str = str + exspression[i];
				stack2.push(str);
			}
			else
			{
				string str;
				str = str + exspression[i];
				if (SignComparison(str, stack2)) // true if <=
				{
					while (!stack2.empty())
					{
						if (Priority(str) == Priority(stack2.top()))
						{
							stack1.push(stack2.top());
							stack2.pop();
							break;
						}
						if (stack2.top() == "(")
						{
							break;
						}

						stack1.push(stack2.top());
						stack2.pop();
					}
					stack2.push(str);
				}
				else
					stack2.push(str);
				continue;
			}
		}
		else
			throw Exception(" Error, incorrect enter, try again\n");
	}

	while (!stack2.empty())
	{
		stack1.push(stack2.top());
		stack2.pop();
	}

	stack<string> stack3;
	while (!stack1.empty()) // делаю swap
	{
		stack3.push(stack1.top());
		stack1.pop();
	}
	stack<Polynom> result;

	while (!stack3.empty())
	{
		if (stack3.top().find_first_of("xyz^0123456789.") != stack3.top().npos)
		{ // выполнится, если это моном
			Monom mon = Monom(stack3.top());
			Polynom pol(mon);
			result.push(pol);
			if (!stack3.empty())
				stack3.pop();
			else
				throw Exception
				(" Error, stack is empty, you cannot do pop()\n");
		}
		else if (stack3.top().find_first_of("+-*") != stack3.top().npos)
		{
			Polynom p1 = result.top();
			if (!result.empty())
				result.pop();
			else
				throw Exception
				(" Error, stack is empty, you cannot do pop() !\n");

			Polynom p2 = result.top();
			if (!result.empty())
				result.pop();
			else
				throw Exception
				(" Error, stack is empty, you cannot do pop() !!\n");

			char sign = stack3.top()[0]; // с таким присваиванием работает,
			stack3.pop(); // но нужно знать наверняка, что по 0 индексу
			switch (sign) // лежит операция, возможны ошибки!
			{
			case '+':
			{
				result.push(p2 + p1);
				break;
			}
			case '-':
			{
				result.push(p2 - p1);
				break;
			}
			case '*':
			{
				result.push(p2 * p1);
				break;
			}
			default:
				throw Exception(" Error, it can't be\n");
			}
		}
		else
			throw Exception(" Error, there are incorrect symbols in string\n");
	}

	monoms = new TList<unsigned int, double>(*result.top().monoms);
}

// в данном конструкторе работает только сложение и вычитание мономов в строке
//Polynom::Polynom(const string& exspression)
//{
//    string line = exspression;
//    Polynom result;
//    while (line.length())
//    {
//        int start, end;
//        string for_monom;
//        for (int i = 0; i < line.length(); i++)
//        {
//            if (line[i] == ' ') // пропускаем пробелы
//                continue;
//            if ((line[i] == '+') || (line[i] == '-') || 
//                ('0' <= line[i] && line[i] <= '9') || (line[i] == 'x') || 
//                (line[i] == 'y') || (line[i] == 'z'))
//            {
//                start = i;
//                i++;
//                while ((i < line.length()) && (line[i] != '+') && 
//                    (line[i] != '-'))
//                    i++;
//                end = i - 1; // должны сохр-ть поз-ю посл-го эл-та на 1 меньше
//                break;
//            }
//            else
//                throw Exception(" Error, incorrect enter or symbol\n");
//        }
//        for_monom = line.substr(start, end - start + 1);
//        result = result + Monom(for_monom);
//        if ((end + 1) == line.length())
//        {
//            break;
//        }
//        line = line.substr(end + 1, line.length() - end - 1);
//    }
//    monoms = new TList<unsigned int, double>(*result.monoms);
//}