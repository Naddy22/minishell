#include "../inc/minishell.h"

int	get_err_code(int exit_code)
{
	unsigned char	r_val;

	r_val = exit_code;
	if (WIFEXITED(exit_code))
		r_val = WEXITSTATUS(exit_code);
	else if (WIFSIGNALED(exit_code))
		r_val = (128 + WTERMSIG(exit_code));
	return (r_val);
}

void	free_error(t_data *data, char *error)
{
	free_all(data);
	printf("%s\n", error);
}


// void	free_error(t_data *data)
// {
// 	free_all(&data->parsing.last_user_cmd);
// 	strerror(errno);
// }