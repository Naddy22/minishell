#include "../../inc/minishell.h"

// next step: gerer les $ en remplacant ce qu'il y a apres le $ si celui ci
// correspond à une variable d'environnement par ce qu'il y a apres le =
// faire attention a bien comparer en regardant si la str (ex: USER) fini
// par un = car parfois le debut peut être pareil.
// strjoin par la suite au texte deja commencé afin de remplacer tout en allouant
// la bonne taille (si le env n'existe pas, ca join juste rien avec rien)

char *get_env_value(char **env_cpy, const char *var_name)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(var_name);
	while (env_cpy[i] != 0)
	{
		if (ft_strnstr(env_cpy[i], var_name, len) && env_cpy[i][len] == '=')
			return (env_cpy[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	add_dollar_value_to_str(t_data *data, const char *value)
{
	char *current;
	char *new;

	if (data->last_token->brut_cmd == NULL)
	{
		data->last_token->brut_cmd = ft_strdup(value);
		if (data->last_token->brut_cmd == NULL)
		{
			perror("Malloc");
			return (FAIL);
		}
	}
	else
	{
		current = data->last_token->brut_cmd;
		new = ft_strjoin(current, value);
		if (new == NULL)
		{
			perror("Malloc");
			return (FAIL);
		}
		ft_free_verif((void **)&data->last_token->brut_cmd);
		data->last_token->brut_cmd = new;
	}
	return (SUCCESS);
}

int	add_exit_status_to_token(t_data *data, size_t *i, int *start)
{
	char	*status_char;
	char	*current;
	char	*new;

	current = data->last_token->brut_cmd;
	status_char = ft_itoa(data->exit_status);
	if (status_char == NULL)
	{
		perror("Malloc");
		return (FAIL);	
	}
	new = ft_strjoin(current, status_char);
	if (new == NULL)
	{
		perror("Malloc");
		return (FAIL);
	}
	ft_free_verif((void **)&(data->last_token->brut_cmd));
	data->last_token->brut_cmd = new;
	ft_free_verif((void **)&status_char);
	(*i)++;
	*start = *i;
	return (SUCCESS);
}

char *process_variable_name(t_data *data, size_t *i, int *start, char *str)
{
	char *var_name;
	char *result;

	while((str[*i] && ft_isalnum(str[*i])) || str[*i] == '_')
		(*i)++;
	var_name = ft_substr(str, *start, *i - *start);
	if (var_name == NULL)
	{
		perror("Malloc");
		return (NULL);
	}
	result = get_env_value(data->cpy_env, var_name);
	if (result == NULL)
		result = "";
	ft_free_verif((void **)&var_name);
	return (result);
}

int	handle_dollar_expansion(t_data *data, size_t *i, int *start)
{
	char *result;
	char *str;

	if (data->last_token && data->last_token->previous && \
	data->last_token->previous->token_type == L2_REDIR)
	{
		(*i)++;
		return (SUCCESS);
	}
	str = data->parsing.last_user_cmd;
	(*i)++;
	if(ft_isspace(str[*i]) == TRUE || str[*i] == '\0')
		return (add_str_to_token(data, i, start));
	if(str[*i] == '?')
		return (add_exit_status_to_token(data, i, start));
	*start = *i;
	result = process_variable_name(data, i, start, str);
	if (result == NULL)
		return (FAIL);
	*start = *i;
	return (add_dollar_value_to_str(data, result));
}
