#include "../../inc/minishell.h"

//Gestion des codes d'erreur ok

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_printf("%s\n", envp[i]);
		i++;
	}
}
