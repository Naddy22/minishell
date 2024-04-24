#include "../inc/minishell.h"

int	get_env(t_data *data, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	data->cpy_env = ft_calloc(i + 1, sizeof(char *));
	if (data->cpy_env == NULL)
		return (FAIL);
	i = 0;
	while (envp[i])
	{
		data->cpy_env[i] = strdup(envp[i]);
		printf("%s\n", data->cpy_env[i]);
		i++;
	}
	return(SUCCESS);
}

int init(t_data *data, char **envp)
{
	if (get_env(data, envp) != SUCCESS)
		return (FAIL);
	return(SUCCESS);
}

// next step: gerer les $ en remplacant ce qu'il y a apres le $ si celui ci
// correspond à une variable d'environnement par ce qu'il y a apres le =
// faire attention a bien comparer en regardant si la str (ex: USER) fini
// par un = car parfois le debut peut être pareil.
// strjoin par la suite au texte deja commencé afin de remplacer tout en allouant
// la bonne taille (si le env n'existe pas, ca join juste rien avec rien)