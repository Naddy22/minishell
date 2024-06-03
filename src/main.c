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


int	main(int argc, char **argv, char **envp) 
{
	t_data data;
	t_command *com;

	(void)argv;
	if (argc != 1)
	{
		printf("Error: too many arguments. Number accepted: 0.");
		return(FAIL);
	}
	ft_memset(&data, 0, sizeof(t_data));
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
		//test_print_token_list(data.tokens);
		if (make_cmds(&data) != SUCCESS)
		{
			free_all(&data);
			continue ;
		}
		printf("stocker dans cmd : %s\n", data.commands->cmd[0]);
		init_exec(&data);
		to_execute(&data);
		free_all(&data);
		i++;
	} 
	// return (dernier code erreur);
}

//EXECUTION
	// t_list	cmd;
	// t_list	cmd2;
	// t_cmd	mini;

	// (void)argc;
	// mini.max = 0;
	// cmd.cmd = ft_split("ls -la", ' ');
	// cmd.next = &cmd2;
	// cmd2.cmd = ft_split("grep -v src", ' ');
	// cmd2.next = NULL;
	// mini.cmdlst = &cmd;
	// mini.fd = ft_calloc(2, sizeof(int *));
	// mini.fd[0] = ft_calloc(1, sizeof(int[2]));
	// mini.fd[1] = ft_calloc(1, sizeof(int[2]));
	// mini.max = 1;
	// mini.pnb = 0;
	// pipe(mini.fd[0]); //
	// pipe(mini.fd[1]); //
	// ft_pipe(&mini, argv, envp);


	// return (0);
