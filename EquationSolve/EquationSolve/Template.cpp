#include "stdafx.h"

#include "Solve3.h"


#include "stdafx.h"
#include <iostream>

struct Base
{
	int x = 1;
	Base() = default;
	Base(const Base& other)
		: x(other.x)
	{
		std::cout << "Copying Base from " << &other << " to " << this << "\n";
	}
	virtual void WhoAmI() const { std::cout << "Base " << this << "\n"; }
	virtual ~Base()
	{
		if (std::uncaught_exception())
		{
			std::cout << "Deleting " << this << " during stack unwinding\n";
		}
		else
		{
			std::cout << "Deleting " << this << " during normal execution\n";
		}
	}
};

struct Derived : Base
{
	int y = 2;
	Derived() = default;
	Derived(const Derived& other)
		: Base(other)
		, y(other.y)
	{
		std::cout << "Copying Derived from " << &other << " to " << this << "\n";
	}
	void WhoAmI() const override { std::cout << "Derived " << this << "\n"; }
};

int main()
{
	long a = 10;
	a = pow(a, 6);
	std::cout <<a <<' '<< ((a % 35)* (a % 35)%35);
	/*try
	{
		{
			Derived d0;
		}
		Derived d;
		d.x = 555;
		std::cout << "Throwing " << &d << "\n";
		throw d;
	}
	catch (Base& b)
	{
		b.WhoAmI();
	}
	return 0;*/
}

/*int main()
{
    std::cout << Solve3(1, 1, 1, -3).roots[1] << std::endl;
    std::cout << "Hello World!\n";
}*/

