/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:26:08 by namoisan          #+#    #+#             */
/*   Updated: 2024/01/24 12:00:46 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_free_table(char **table)
{
	int	i;

	i = 0;
	if (table)
	{
		while (table[i])
		{
			free(table[i]);
			i++;
		}
		free(table);
		table = NULL;
	}
}

static int	count_words(const char *s, char c)
{
	int	sep_count;
	int	start;

	sep_count = 0;
	start = 0;
	while (s[start])
	{
		while (s[start] == c)
			start++;
		if (s[start])
		{
			sep_count++;
			while (s[start] != c && s[start])
				start++;
		}
	}
	return (sep_count);
}

static char	*ft_allocate_and_copy_substring(char const *s, int start, int end)
{
	char	*substring;

	substring = malloc(sizeof(char) * (end - start + 1));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, &s[start], end - start + 1);
	return (substring);
}

static char	*find_and_copy_next_word(const char *s, char c, int *start)
{
	int	end;
	int	temp_start;

	temp_start = *start;
	while (s[temp_start] == c)
		temp_start++;
	end = temp_start;
	while (s[end] != c && s[end])
		end++;
	*start = end;
	return (ft_allocate_and_copy_substring(s, temp_start, end));
}

char	**ft_split(char const *s, char c)
{
	int		table_id;
	int		start;
	char	**table;
	int		sep_count;

	table_id = 0;
	start = 0;
	sep_count = count_words(s, c);
	table = malloc(sizeof(char *) * (sep_count + 1));
	if (!table || s == NULL)
		return (NULL);
	while (s[start] && table_id < sep_count)
	{
		table[table_id] = find_and_copy_next_word(s, c, &start);
		if (!table[table_id])
		{
			ft_free_table(table);
			return (NULL);
		}
		table_id++;
	}
	table[table_id] = NULL;
	return (table);
}

// int	main(int argc, char **argv)
// {
// 	char	**result;
// 	int		i;

// 	if (argc != 2)
// 		return (1);
// 	result = ft_split(argv[1], '.');
// 	if (result == NULL)
// 	{
// 		printf("Erreur d'allocation de mémoire.\n");
// 		return (1);
// 	}
// 	i = 0;
// 	while (result[i])
// 	{
// 		printf("Mot %d: %s\n", i, result[i]);
// 		i++;
// 	}
// 	return (0);
// }
