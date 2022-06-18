#include "stdafx.h"

#include <stack>
int main()
{
	std::stack<int> stac;
	stac.push(3);
	std::stack<int> stack(stac);
}

