#include "../../inc/minishell.h"

int	read_user_cmd(t_data *data)
{
	char *rl_buffer;
	char *current_cmd;

	rl_buffer = readline("minishell>");
	if (rl_buffer == NULL) //càd que ctrl+D à été fait
	{
		//quitte tout
		printf("exit");
		//free tout
		rl_clear_history();
		exit(EXIT_SUCCESS);
	}
	else
	{
		current_cmd = ft_strtrim(rl_buffer, " ");
		if (current_cmd = NULL)
		{
			free(rl_buffer);
			free_error(data, "strtrim failed");
			rl_clear_history();
			exit(EXIT_FAILURE);
		}
	}
	//si current_cmd != null: faire ft qui va va strtrim pour enlever les
	//espace au debut et fin et si il reste plus rien apres la suppression
	//des espaces c'est que j'ai une ligne vide (rl_on_new_line pour remettre
	//le prompt, remplacer la ligne par une chaine vite afin de supprimer de
	//la memoire de readline et free aussi last_user_cmd etc). Sinon j'utilise
	//add history et mets à jour last cmd.

	//traiter le cas si la cmd est juste 'entrée' (si non null et vide) ->
	//remettre prompt (rl on new line et rl replace line(?)), free last user et
	//le remettre à null (devrait se refaire tout seule car main = boucle infini)

	//free si la moindre erreur et current cmd a la fin
}
