#include "../../inc/minishell.h"

char	*get_env_value(char **env_cpy, const char *var_name)
{
	size_t	i;
	size_t	len;

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

static int	add_dollar_value_to_str(t_data *data, const char *value)
{
	if (ft_strchr(value, ' ')) //faire fonction qui va faire un split, remplir le token en court par le premier mot et creer un nouveau token pour chaque mot suivant
	{
		if (split_expanded_value(data, value) == FAIL)
			return (FAIL);
	}
	else
		if (add_value_to_brut_cmd(data, value) == FAIL)
			return (FAIL);
	return (SUCCESS);
}

static int	add_exit_status_to_token(t_data *data, size_t *i, int *start)
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

char	*process_variable_name(t_data *data, size_t *i, int *start, char *str)
{
	char	*var_name;
	char	*result;

	*start = *i; //fait pour remettre start sur la premiere lettre du nom de variable d'environnement
	while ((str[*i] && ft_isalnum(str[*i])) || str[*i] == '_')
		(*i)++;
	if (str[*i] == '$' && !ft_isalnum(str[*i - 1])) //!ft_isalnum ajouté pour pas que ca entre si $USER$USER
	{
		result = "$"; //mis pour avoir un $ si $$ ecrit
		(*i)++;
		return (result);
	}
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
	char	*result;
	char	*str;

	if (data->last_token && data->last_token->previous && \
	data->last_token->previous->token_type == L2_REDIR)
	{
		(*i)++;
		return (SUCCESS);
	}
	str = data->parsing.last_user_cmd;
	(*i)++;
	if (!ft_isalnum(str[*i]) && !ft_isspecial(str[*i], 1)) //ajout de isalnum pour que rien ne soit interpreté si ce n'est pas une lettre ou chiffre
		return (add_str_to_token(data, i, start));
	if (ft_isspace(str[*i]) == TRUE || str[*i] == '\0')
		return (add_str_to_token(data, i, start));
	if (str[*i] == '?')
		return (add_exit_status_to_token(data, i, start));
	result = process_variable_name(data, i, start, str);
	if (result == NULL)
		return (FAIL);
	*start = *i;
	if (result[0] == '\0' && (!data->last_token->brut_cmd || \
		data->last_token->brut_cmd[0] == '\0') && str[*i] == '\0') //Condition pour pas que ca aille dedans si ma commande a deja commencé a etre rempli (ex: coucou$A), ajout de \0 car mon brut est forcement créer
		return (ft_reset_1token(data, &data->last_token));
	return (add_dollar_value_to_str(data, result));
}

//next step: splitter la fonction add_dollar_value_to_str
