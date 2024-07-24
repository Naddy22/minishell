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
