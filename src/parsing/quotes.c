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
			perror("Error: quote is not close");
			return (FAIL);
		}
		(*i)++;
	}
	add_str_to_token(data, i, start);
	(*i)++;
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
			perror("Error: quote is not close");
			return (FAIL);
		}
		else if (str[*i] == '$')
		{
			add_str_to_token(data, i, start);
			handle_dollar_expansion(data, i, start);
			*start = *i;
			continue ;
		}
		(*i)++;
	}
	add_str_to_token(data, i, start);
	(*i)++;
	*start = *i;
	return (SUCCESS);
}

void	handle_quotes(t_data *data, size_t *i, int *start)
{
	char *str;

	str = data->parsing.last_user_cmd;
	add_str_to_token(data, i, start);
	if (str[*i] == '\'')
		handle_simple_quote(data, i, start);
	if (str[*i] == '"')
		handle_double_quote(data, i, start);
}
