/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:54:26 by namoisan          #+#    #+#             */
/*   Updated: 2024/01/04 13:34:02 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	result;

	i = 0;
	result = 0;
	if (src == NULL)
		return (0);
	while (src[i] != '\0' && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	while (src[result] != '\0')
		result++;
	return (result);
}

char	*ft_strjoin_dup(char *s1, char const *s2)
{
	char	*result;
	int		size;

	result = NULL;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)malloc(sizeof(char) * size);
	if (result == NULL)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	ft_bzero(result, size);
	ft_strlcpy_gnl(result, s1, ft_strlen(s1) + 1);
	ft_strlcat(result, s2, size);
	if (s1)
		free(s1);
	return (result);
}

char	*delete_buf_line(char *buf)
{
	int		i;
	char	*res;

	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	if (buf[i] == '\n')
		i++;
	if (buf[i] != '\0')
	{
		res = ft_strdup(&buf[i]);
		free(buf);
		return (res);
	}
	free(buf);
	return (NULL);
}

char	*fill_buffer(char *buf, int fd)
{
	int			read_bytes;
	char		tmp[BUFFER_SIZE + 1];

	read_bytes = 1;
	while ((!ft_strchr(buf, '\n') || !buf) && read_bytes > 0)
	{
		ft_bzero(tmp, BUFFER_SIZE + 1);
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		buf = ft_strjoin_dup(buf, tmp);
		if (buf == NULL)
			return (NULL);
	}
	if (!buf || read_bytes < 0 || buf[0] == 0)
	{
		if (buf != NULL)
			free(buf);
		buf = NULL;
		return (NULL);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	int			i;
	char		*line;

	buf = fill_buffer(buf, fd);
	if (!buf)
		return (NULL);
	i = 0;
	while (buf[i] != '\0' && (i == 0 || buf[i - 1] != '\n'))
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (line == NULL)
	{
		if (buf)
			free(buf);
		buf = NULL;
		return (NULL);
	}
	ft_strlcpy_gnl(line, buf, i);
	buf = delete_buf_line(buf);
	return (line);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int	fd;
// 	char *result;

// 	fd = 0;
// 	result = "Bouh";
// 	fd = open("simple.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while (result)
// 	{
// 		result = get_next_line(fd);
// 		printf("result :%s\n", result);
// 		if (result)
// 			free (result);
// 	}
// 	return (0);
// }
