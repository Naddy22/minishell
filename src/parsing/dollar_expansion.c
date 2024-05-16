#include "../../inc/minishell.h"

// next step: gerer les $ en remplacant ce qu'il y a apres le $ si celui ci
// correspond à une variable d'environnement par ce qu'il y a apres le =
// faire attention a bien comparer en regardant si la str (ex: USER) fini
// par un = car parfois le debut peut être pareil.
// strjoin par la suite au texte deja commencé afin de remplacer tout en allouant
// la bonne taille (si le env n'existe pas, ca join juste rien avec rien)

int add_dollar_expansion(t_data *data, size_t *i, int *start)
{
	char *var_name;
	char *str;

	*start = ++(*i);
	str = data->parsing.last_user_cmd;
	
	while((str[*i] && ft_isalnum(str[*i])) || str[*i] == '_')
		(*i)++;
	var_name = ft_substr(str, start, *i - *start);
	if (var_name == NULL)
	{
		perror("Malloc : ");
		return (FAIL);
	}
}