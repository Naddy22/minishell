#include "../inc/minishell.h"

void test_print_token_list(t_list *tokens)
{
	t_list *current = tokens;
	int i;

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
	t_data data;

	(void)argc;
	(void)argv;
	memset(&data, 0, sizeof(t_data));
	init(&data, envp); // verifier si succes sinon quitte completement (exit failure)
	while (42)
	{
		if (read_user_cmd(&data) != SUCCESS)
			continue ;
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
		free_all(&data);
	}
	// return (dernier code erreur);
}
