#include "curry.h"
#include <stdio.h>

long add(long x, long y)
{
	return x + y;
}

int main()
{
	t_2 addf = (void*)add;
	// curry can curry itself
	t_curryg cg = curry(curry, (void*)addf).p;
	t_1 add10 = cg(10l).p;
	long k = add10(4l).v;
	eat(cg);
	eat(add10);
	printf("10 + 4 = %ld\n", k);
}
