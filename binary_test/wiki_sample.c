#include <stdio.h>

int	global_var;
int	global_var_init = 26;

static int static_var;
static int static_var_init = 25;

static int static_function()
{
	return (0);
}

int	global_function(int p)
{
	static int local_static_var;
	static int local_static_var_init = 5;
	
	local_static_var = p;
	
	return local_static_var_init \
		+ local_static_var;
}

void A()
{
	;
}

int	global_function2()
{
	int	x;
	int	y;
	return x+y;
}

void	non_mangled_function()
{
	;
}

int	main(void)
{
	global_var = 1;
	static_var = 2;
	printf("hello");

	return 0;
}