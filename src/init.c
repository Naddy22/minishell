#include "../inc/minishell.h"

int	get_env(char **envp)
{
	int i;
	char **tmp;

	i = 0;
	while (envp[i])
		i++;
	tmp = ft_calloc(i + 1, sizeof(char *));
	if (tmp == NULL)
		return (FAIL);
	i = 0;
	while (envp[i])
	{
		tmp[i] = strdup(envp[i]);
		printf("%s\n", tmp[i]);
		i++;
	}
	return(SUCCESS);
}

int init(char **envp)
{
	if (get_env(envp) != SUCCESS)
		return (FAIL);
	return(SUCCESS);
}

// next step: gerer les $ en remplacant ce qu'il y a apres le $ si celui ci
// correspond à une variable d'environnement par ce qu'il y a apres le =
// faire attention a bien comparer en regardant si la str (ex: USER) fini
// par un = car parfois le debut peut être pareil.
// strjoin par la suite au texte deja commencé afin de remplacer tout en allouant
// la bonne taille (si le env n'existe pas, ca join juste rien avec rien)