#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	init(envp);
	// char *s  = "";
	// while (s) 
	// {
	// 	s = readline("minishell> ");
	// 	printf("s = %s\n", s);
	// 	free(s);
	// }
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