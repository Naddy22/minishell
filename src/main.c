#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	t_data data;

	(void)argc;
	(void)argv;
	memset(&data, 0, sizeof(t_data));
	init(&data, envp);
	while (42)
	{
		if (read_user_cmd(&data) != SUCCESS)
			continue ;
		parsing(&data);
		// printf("%s\n", data.last_token->brut_cmd);
		printf("%s\n", data.tokens->brut_cmd);
		free_all(&data);
		free_tokenlist(&data.tokens);
	}
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