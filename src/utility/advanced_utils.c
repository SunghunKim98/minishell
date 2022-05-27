#include "../../include/minishell.h"

char	*advanced_strlcpy(char *line, int start)
{
	char	*new_line;

	new_line = (char *)malloc(sizeof(char) * (start + 1));
	if (new_line == NULL)
		exit(-1);
	ft_strlcpy(new_line, line, start + 1);
	return (new_line);
}

char	*advanced_strdup(char *line)
{
	char	*new_line;

	new_line = ft_strdup(line);
	if (!new_line)
		exit(-1);
	free(line);
	return (new_line);
}

char	*advanced_strdup_no_free(char *line)
{
	char	*new_line;

	new_line = ft_strdup(line);
	if (!new_line)
		exit(-1);
	return (new_line);
}

char	*advanced_itoa(int n)
{
	char	*new_line;

	new_line = ft_itoa(n);
	if (!new_line)
		exit(-1);
	return (new_line);
}
