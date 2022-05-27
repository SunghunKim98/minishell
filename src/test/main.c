#include "../../include/minishell.h"

int main(void)
{
	unsigned char c;
	c = (unsigned char)ft_atoi("2147483648");
	printf("%d\n", c);
	return (0);
}