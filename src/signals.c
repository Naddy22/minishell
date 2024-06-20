#include "../../inc/minishell.h"

void	set_signal(sig_type type)
{
	if (type == MAIN)
	{
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == CHILD)
	{
		
	}
	else if (type == HERE_DOC)
	{
		signal(SIGQUIT, SIG_IGN);
	}
}