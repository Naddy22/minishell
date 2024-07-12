#include "../inc/minishell.h"

static void sig_handler_parent(int signum)
{
	(void)signum; // fix pour ne pas avoir 2 fois le prompts
}

static void sig_handler_hd(int signum)
{
	(void)signum;
}

static void sig_handler_main(int signum)
{
	(void)signum;
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_replace_line("\0", 0);
	rl_redisplay();
}

void	set_signal(t_sig_type type)
{
	if (type == MAIN)
	{
		signal(SIGINT, &sig_handler_main);
		signal(SIGQUIT, SIG_IGN); //SIG_IGN = ignore signal
	}
	else if (type == CHILD)
	{
		signal(SIGINT, SIG_DFL); //SIG_DFL = default signal handler
		signal(SIGQUIT, SIG_DFL);
	}
	else if (type == HERE_DOC)
	{
		signal(SIGINT, &sig_handler_hd);
		signal(SIGQUIT, SIG_IGN);
	}
	else if(type == PARENT)
	 {
		signal(SIGINT, &sig_handler_parent);
		signal(SIGQUIT, SIG_IGN);
	 }
}