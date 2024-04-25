#include "../../inc/minishell.h"

int	read_user_cmd(t_data *data)
{
	char *current_cmd;

	current_cmd = readline("minishell>");
	if (current_cmd == NULL) //càd que ctrl+D à été fait
	{
		//quitte tout
		printf("exit");
		//free tout
		rl_clear_history();
		exit(EXIT_SUCCESS);
	}
	//si current_cmd != null: faire ft qui va va strtrim pour enlever les
	//espace au debut et fin et si il reste plus rien apres la suppression
	//des espaces c'est que j'ai une ligne vide (rl_on_new_line pour remettre
	//le prompt, remplacer la ligne par une chaine vite afin de supprimer de
	//la memoire de readline et free aussi last_user_cmd etc). Sinon je compare
	//current cmd avec last cmd car si differente j'utilise add history et mets à
	//jour last cmd.

	//traiter le cas si la cmd est juste 'entrée' (si non null et vide) ->
	//remettre prompt (rl on new line et rl replace line(?)), free last user et
	//le remettre à null

	//free si la moindre erreur et current cmd a la fin
}