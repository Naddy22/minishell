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
		read_user_cmd(&data);
		
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