#include "../../inc/minishell.h"

char *get_str(char *str, size_t *start, size_t *i)
{
	char *result;

	result = ft_substr(str, *start, *i - *start);
	if (result == NULL)
	{
		perror("Malloc");
		return (NULL);
	}
	*start = *i;
	return (result);
}

char *dollars_parse(char *str, size_t *start, size_t *i)
{
	char *result;

	(*i)++;

}

char	*parsing_heredoc(char *str)
{
	char *result;
	size_t i;
	size_t start;
	char *tmp;

	i = 0;
	start = i;
	result = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			tmp = get_str(str, &start, &i);
			
		}
		i++;
	}
	tmp = get_str(str, &start, &i);
	result = tmp;
	return (result);
}

// char	*parsing_heredoc(char *str)
// {
// 	char *result;
// 	size_t i;
// 	size_t start;
// 	char *tmp;

// 	i = 0;
// 	start = i;
// 	result = NULL;
// 	while (str[i] != '\0' && str[i] != '$')
// 		i++;
// 	tmp = ft_substr(str, start, i - start);
// 	if (tmp == NULL)
// 	{
// 		perror("Malloc");
// 		return (NULL);
// 	}
// 	if (str[i] == '\0')
// 		result = tmp;
// 	if (str[i] == '$')
// 	{
// 		result = dollar_parse(str, &start, &i);
// 	}
// 	return (result);
// }
