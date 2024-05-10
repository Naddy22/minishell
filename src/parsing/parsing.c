#include "../../inc/minishell.h"

// next step: gerer les $ en remplacant ce qu'il y a apres le $ si celui ci
// correspond à une variable d'environnement par ce qu'il y a apres le =
// faire attention a bien comparer en regardant si la str (ex: USER) fini
// par un = car parfois le debut peut être pareil.
// strjoin par la suite au texte deja commencé afin de remplacer tout en allouant
// la bonne taille (si le env n'existe pas, ca join juste rien avec rien)

void	find_token(t_data *data, size_t *i, int *start_token)
{
	char *cmd;

	cmd = data->parsing.last_user_cmd;
	while (cmd[*i] == '<' || cmd[*i] == '>' || cmd[*i] == '|' || cmd[*i] == ' ')
	{
		if (cmd[*i] == ' ')
			(*i)++;
		else
			create_token_pipe_redir();
	}
	if (cmd[*i] == '\0')
		return ;
	create_token(data, i, start_token, WORD);
}
int	get_char(t_data *data, char *str, int *i, int *start)
{
	if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>' || str[*i] == ' ')
	{

	}
	else if (str[*i] == '$')
	{

	}
	else if (str[*i] == '\'' || str[*i] == '"')
	{

	}
	else
		(*i)++;
}

void	add_str_to_token(t_data *data, size_t *i, int *start)
{
	char *token;
	char *tmp;
	char *str;

	str = data->parsing.last_user_cmd;
	token = data->last_token->brut_cmd;
	tmp = ft_substr(str, *start, *i - *start);
	if (tmp == NULL)
		free_error(data, "Error malloc substr in str to token");
	data->last_token->brut_cmd = ft_strjoin(token, tmp);
	ft_free_verif((void *)&token);
	ft_free_verif((void *)&tmp);
	if (data->last_token->brut_cmd == NULL)
		free_error(data, "Error malloc substr in str to token");
}

void	parsing(t_data *data)
{
	int start;

	start = 0;
	data->parsing.i = 0;
	data->nb_pipes = 0; 
	find_token(data, &data->parsing.i, &start);
	while (data->parsing.last_user_cmd[data->parsing.i] != '\0')
	{
		get_char(data, data->parsing.last_user_cmd, &data->parsing.i, &start);
	}
}
