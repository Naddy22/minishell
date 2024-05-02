#include "../../inc/minishell.h"

// next step: gerer les $ en remplacant ce qu'il y a apres le $ si celui ci
// correspond à une variable d'environnement par ce qu'il y a apres le =
// faire attention a bien comparer en regardant si la str (ex: USER) fini
// par un = car parfois le debut peut être pareil.
// strjoin par la suite au texte deja commencé afin de remplacer tout en allouant
// la bonne taille (si le env n'existe pas, ca join juste rien avec rien)

void	find_token(t_data *data, int *i, int *start_token)
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
}

int	parsing(t_data *data)
{
	int start;

	start = 0;
	data->parsing.i = 0;
	data->nb_pipes = 0;
	find_token(data, &data->parsing.i, &start);
}