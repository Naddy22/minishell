#include "../../inc/minishell.h"

/*

-Identifier si quote simple ou double
-lire jusqu'a rencontrer la prochaine meme quotes
-si $USER envelopper de " on remplace pas la valeur d'env, sinon on lit le tout et à 
la fin on stocke/joint le tout dans le même token word actuel
-si quotes pas fermer c'est erreur de syntaxe

*/

int	handle_simple_quote(t_data *data, size_t *i, int *start)
{
	char *str;

	str = data->parsing.last_user_cmd;
	(*i)++;
	*start = *i;
	while (str[*i] != '\'')
	{
		if (str[*i] == '\0')
		{
			ft_putstr_fd("Error: quote is not close", 2);
			data->exit_status = 258;
			return (FAIL);
		}
		(*i)++;
	}
	if (add_str_to_token(data, i, start) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

int	handle_dollar_in_dquote(t_data *data, size_t *i, int *start)
{
	if (add_str_to_token(data, i, start) != SUCCESS)
		return (FAIL);
	if (handle_dollar_expansion(data, i, start) != SUCCESS)
		return (FAIL);
	*start = *i;
	return (SUCCESS);
}

int	handle_double_quote(t_data *data, size_t *i, int *start)
{
	char *str;

	str = data->parsing.last_user_cmd;
	(*i)++;
	*start = *i;
	while (str[*i] != '"')
	{
		if (str[*i] == '\0')
		{
			ft_putstr_fd("Error: quote is not close", 2);
			data->exit_status = 258;
			return (FAIL);
		}
		else if (str[*i] == '$')
		{
			handle_dollar_in_dquote(data, i, start);
			continue ;
		}
		(*i)++;
	}
	if (add_str_to_token(data, i, start) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

int	handle_quotes(t_data *data, size_t *i, int *start)
{
	char *str;

	str = data->parsing.last_user_cmd;
	if (add_str_to_token(data, i, start) != SUCCESS)
		return (FAIL);
	if (str[*i] == '\'')
	{
		if (handle_simple_quote(data, i, start) != SUCCESS)
			return (FAIL);
	}
	if (str[*i] == '"')
	{
		if (handle_double_quote(data, i, start) != SUCCESS)
			return (FAIL);
	}
	(*i)++;
	*start = *i;
	return (SUCCESS);
}
