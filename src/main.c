#include "../inc/minishell.h"

void	test_print_token_list(t_list *tokens)
{
	t_list	*current = tokens;
	int		i;

	i = 0;
	while (current != NULL)
	{
		if (current->brut_cmd == NULL)
		{
			if (current->token_type == L1_REDIR)
				printf("Token %d: <\n", i);
			else if (current->token_type == L2_REDIR)
				printf("Token %d: <<\n", i);
			else if (current->token_type == R1_REDIR)
				printf("Token %d: >\n", i);
			else if (current->token_type == R2_REDIR)
				printf("Token %d: >>\n", i);
			else if (current->token_type == PIPE)
				printf("Token %d: |\n", i);
		}
		else
			printf("Token %d: %s\n", i, current->brut_cmd);
		current = current->next;
		i++;
	}
}

void	test_print_cmd(t_data *data)
{
	t_command *current_cmd;
	int i;
	int j = 1;

	current_cmd = data->commands;
	while (current_cmd != NULL)
	{
		i = 0;
		if (current_cmd->cmd)
		{
			while (current_cmd->cmd[i] != NULL)
			{
				printf("Cmd %d: %s\n", j, current_cmd->cmd[i]);
				i++;
			}
		}
		if (current_cmd->redir && current_cmd->redir->file_name)
			printf("Cmd %d: filename = \"%s\"\n", j, current_cmd->redir->file_name);
		current_cmd = current_cmd->next;
		j++;
	}
}

int main(int argc, char **argv, char **envp) 
{
	t_data	data;
	int		status;

	status = 0;
	(void)argv;
	if (argc != 1)
	{
		printf("Error: too many arguments. Number accepted: 0.");
		return (FAIL);
	}
	ft_memset(&data, 0, sizeof(t_data));
	if (init(&data, envp) == FAIL)
	{
		free_all(&data); // verifier si succes sinon quitte completement (exit failure)
		close(data.fdin_origin);
		close(data.fdout_origin);
		if (data.cpy_env) //TODO place at each exit point that exit minishell
			ft_free_table(data.cpy_env);
		if (data.cpy_env_orig) //TODO place at each exit point that exit minishell
			ft_free_table(data.cpy_env_orig);
		if (data.custom_env) //TODO place at each exit point that exit minishell
			ft_free_table(data.custom_env);
		return (FAIL);
	}
	while (42)
	{
		set_signal(MAIN);
		if (read_user_cmd(&data) != SUCCESS)
			continue ;
		set_signal(PARENT);
		if (parsing(&data) != SUCCESS)
		{
			free_all(&data);
			continue ;
		}
		test_print_token_list(data.tokens);
		if (make_cmds(&data) != SUCCESS)
		{
			free_all(&data);
			continue ;
		}
		test_print_cmd(&data);
		// printf("Nb_pipe: %d \n", data.nb_pipes);
		reset_exec(&data);
		to_execute(&data);
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
			dprintf(2, "to free and exit\n");
			//free_and_exit(mini, status);
		free_all(&data);
	}
	close(data.fdin_origin); //TODO place close and free in end_program
	close(data.fdout_origin);
	if (data.cpy_env) //TODO place at each exit point that exit minishell
		ft_free_table(data.cpy_env);
	if (data.cpy_env_orig) //TODO place at each exit point that exit minishell
		ft_free_table(data.cpy_env_orig);
	if (data.custom_env) //TODO place at each exit point that exit minishell
		ft_free_table(data.custom_env);
	// return (dernier code erreur);
}
