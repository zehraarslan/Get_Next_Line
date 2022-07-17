/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarslan <zarslan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:52:29 by zarslan           #+#    #+#             */
/*   Updated: 2022/02/20 11:25:30 by zarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_main_line(char *main_line)
{
	int		i;
	int		c;
	char	*new_line;

	i = 0;
	while (main_line[i] != '\n' && main_line[i])
		i++;
	if (!main_line[i])
	{
		free (main_line);
		return (NULL);
	}
	new_line = (char *)malloc(sizeof(char) * ft_strlen(main_line) - i + 1);
	if (!new_line)
		return (NULL);
	i++;
	c = 0;
	while (main_line[i])
		new_line[c++] = main_line[i++];
	new_line[c] = '\0';
	free (main_line);
	return (new_line);
}

char	*out_line(char *main_line)
{
	char	*result_line;
	int		i;

	i = 0;
	if (!main_line[i])
		return (NULL);
	while (main_line[i] != '\n' && main_line[i])
		i++;
	result_line = (char *)malloc(sizeof(char) * i + 2);
	if (!result_line)
		return (NULL);
	i = 0;
	while (main_line[i] != '\n' && main_line[i])
	{
		result_line[i] = main_line[i];
		i++;
	}
	if (main_line[i] == '\n')
	{
		result_line[i] = '\n';
		i++;
	}
	result_line[i] = '\0';
	return (result_line);
}

char	*read_line(int fd, char *main_line)
{
	int		read_value;
	char	*part_line;

	read_value = 1;
	part_line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!part_line)
		return (NULL);
	while (!(ft_strchr(main_line, '\n')) && read_value != 0)
	{
		read_value = read(fd, part_line, BUFFER_SIZE);
		if (read_value == -1)
		{
			free (part_line);
			return (NULL);
		}
		part_line[read_value] = '\0';
		main_line = ft_strjoin(main_line, part_line);
	}
	free (part_line);
	return (main_line);
}

char	*get_next_line(int fd)
{
	static char	*main_line;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	main_line = read_line(fd, main_line);
	if (!main_line)
		return (NULL);
	return_line = out_line(main_line);
	main_line = next_main_line(main_line);
	return (return_line);
}
/*
int	main(void)
{
	int	fd;

	fd = open("text1.txt", O_RDONLY);
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
	printf("%s",get_next_line(fd));
}*/