#include "../../include/minishell.h"

char	**malloc_double_char(int size)
{
	char	**p;
	int		i;

	p = (char**)malloc(sizeof(char*) * (size + 1));
	if (p == NULL)
	{
		printf("Malloc Error\n");
		exit(1);
	}
	i = -1;
	while (++i < size + 1)
		p[i] = 0;
	return (p);
}

char	*malloc_single_char(int size)
{
	char	*p;
	int		i;

	p = (char*)malloc(sizeof(char) * (size + 1));
	if (p == NULL)
	{
		printf("Malloc Error\n");
		exit(1);
	}
	i = -1;
	while (++i < size + 1)
		p[i] = 0;
	return (p);
}
