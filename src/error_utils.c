#include "../inc/minishell.h"

int	get_err_code(int exit_code)
{
	unsigned char	r_val;

	if (exit_code == 256)
		return (1);
	r_val = exit_code;
	if (WIFEXITED(exit_code))
		r_val = WEXITSTATUS(exit_code);
	else if (WIFSIGNALED(exit_code))
		r_val = (128 + WTERMSIG(exit_code));
	return (r_val);
}

int error_fail(char *err_msg)
{
	perror(err_msg);
	return (FAIL);
}
