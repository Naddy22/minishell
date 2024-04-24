#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	(void)argc;
	(void)argv;
	init(envp);
	while (42)
	{
		
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