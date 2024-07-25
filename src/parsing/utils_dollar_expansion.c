#include "../../inc/minishell.h"

int	add_value_to_brut_cmd(t_data *data, const char *value)
{
	char *new;
	char *current_tmp;

	if (data->last_token->brut_cmd == NULL)
	{
		data->last_token->brut_cmd = ft_strdup(value);
		if (data->last_token->brut_cmd == NULL)
			return (error_fail("Malloc"));
	}
	else
	{
		current_tmp = data->last_token->brut_cmd;
		new = ft_strjoin(current_tmp, value);
		if (new == NULL)
			return (error_fail("Malloc"));
		ft_free_verif((void **)&data->last_token->brut_cmd);
		data->last_token->brut_cmd = new;
	}
	return (SUCCESS);
}

int	split_expanded_value(t_data *data, const char *value)
{
	size_t i;
	int start;
	char **split;

	i = 1;
	start = 0;
	split = ft_split(value, ' ');
	if (split == NULL)
		return (error_fail("Malloc"));
	if (add_value_to_brut_cmd(data, split[0]) == FAIL)
		return (FAIL);
	while (split[i])
	{
		if (create_token(data, &i, &start, WORD) != SUCCESS)
			return (error_fail("Malloc"));
		data->last_token->brut_cmd = ft_strdup(split[i]);
		if (data->last_token->brut_cmd == NULL)
			return (error_fail("Malloc"));
		i++;
	}
	ft_free_table(split);
	return (SUCCESS);
}