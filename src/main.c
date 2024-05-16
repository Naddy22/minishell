#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	t_data data;

	(void)argc;
	(void)argv;
	memset(&data, 0, sizeof(t_data));
	init(&data, envp); // verifier si succes sinon quitte completement (exit failure)
	while (42)
	{
		if (read_user_cmd(&data) != SUCCESS)
			continue ;
		parsing(&data);
		printf("last : %s\n", data.last_token->brut_cmd);
		printf("final : %s\n", data.tokens->brut_cmd);
		free_all(&data);
		free_tokenlist(&data.tokens);
	}
	// return (dernier code erreur);
}

// int main() 
// {
// 	char *s  = "";
// 	while (s) 
// 	{
// 		s = readline("minishell> ");
// 		printf("s = %s\n", s);
// 		free(s);
// 	}
// }