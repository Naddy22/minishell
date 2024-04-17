#include "../inc/minishell.h"

int main() 
{
	char *s  = "";
	while (s) 
	{
		s = readline("> ");
		printf("s = %s\n", s);
		free(s);
	}
}