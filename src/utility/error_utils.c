#include "../../include/minishell.h"

char	*error_util0()
{
	printf("\033[1A");
	printf("\033[10C");
	printf(" exit\n");
	return (0);
}

void	error_util1()
{
	printf("\033[1A");
	printf("\033[10C");
	printf(" exit\n");
	exit(-1);
}