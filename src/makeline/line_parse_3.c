#include "../../include/minishell.h"

int		check_char_special(char ch)
{
	if (ch == '\"' || ch == '\'' || ch == ' ' || ch == '|'
		|| ch == '\0' || ch == '>' || ch == '<')
		return (1);
	else
		return (0);
}

t_env	*check_env_list(char *key, t_data *p_data)
{
	t_env	*p;

	p = p_data->env_deq->head;
	while (p)
	{
		if (!ft_strncmp(key, p->key, ft_strlen(key) + 1))
			return (p);
		p = p->next;
	}
	return (0);
}

char	*get_env_by_key(char *key, t_data *p_data)
{
	t_env	*p;
	char	*env_value;

	p = check_env_list(key, p_data);
	if (!p)
		return (0);
	env_value = advanced_strdup_no_free(p->value);
	return (env_value);
}

char	*parse_env_after_dollar(char **line, int *i, t_data *p_data)
{
	char	*k_env;
	char	*v_env;
	int		idx;

	idx = *i;
	while (!check_char_special((*line)[*i]))
		(*i)++;
	k_env = advanced_strlcpy((*line + idx), (*i - idx));
	v_env = get_env_by_key(k_env, p_data);
	free(k_env);
	return (v_env);
}
