#include "../../inc/minishell.h"

char *get_exit_status(t_data *data, size_t *start, size_t *i)
{
	char	*status_char;

	status_char = ft_itoa(data->exit_status);
	if (status_char == NULL)
	{
		perror("Malloc");
		return (NULL);	
	}
	(*i)++;
	*start = *i;
	return (status_char);
}

char *get_str(char *str, size_t *start, size_t *i)
{
	char *result;

	result = ft_substr(str, *start, *i - *start);
	if (result == NULL)
	{
		perror("Malloc");
		return (NULL);
	}
	*start = *i;
	return (result);
}

char *dollars_parse(t_data *data, char *str, size_t *start, size_t *i)
{
	char *result;

	(*i)++;
	if (!ft_isalnum(str[*i]) && str[*i] != '_' && str[*i] != '$' && str[*i] != '?')
		return (get_str(str, start, i));
	if(ft_isspace(str[*i]) == TRUE || str[*i] == '\0')
		return (get_str(str, start, i));
	if(str[*i] == '?')
		return (get_exit_status(data, start, i));
	result = process_variable_name(data, i, (int *)start, str);
	if (result == NULL)
		return (NULL);
	*start = *i;
	return (result);
}

char	*parsing_heredoc(t_data *data, char *str)
{
	char *result;
	size_t i;
	size_t start;
	char *tmp;
	char *dollar_exp;

	i = 0;
	start = i;
	result = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			tmp = get_str(str, &start, &i);
			dollar_exp = dollars_parse(data, str, &start, &i);
			result = ft_strjoin(tmp, dollar_exp);
			if (str[i] == '$') //essaie d'ajouter ca mais pour le moment ecrit toujours juste nadege quand $USER$USER au lieu de nadegenadege
				continue ;
		} //si else marche plus pour $USER$USER, sans le else marche pas pour $U$USER
		i++;
	}
	tmp = get_str(str, &start, &i);
	if (result)
		data->parsing.hered_print = ft_strjoin(result, tmp);
	else
		data->parsing.hered_print = tmp;
	return (data->parsing.hered_print);
}
