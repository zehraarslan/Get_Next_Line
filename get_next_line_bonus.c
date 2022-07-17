/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zarslan <zarslan@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:52:29 by zarslan           #+#    #+#             */
/*   Updated: 2022/02/20 11:49:52 by zarslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*main_line[2048];
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	main_line[fd] = read_line(fd, main_line[fd]);
	if (!main_line[fd])
		return (NULL);
	return_line = out_line(main_line[fd]);
	main_line[fd] = next_main_line(main_line[fd]);
	return (return_line);
}
/*
int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;
	int	i;

	fd1 = open("text1.txt", O_RDONLY);
	fd2 = open("text2.txt", O_RDONLY);
	fd3 = open("text3.txt", O_RDONLY);

	i = 0;
	char *c1 = get_next_line(fd1);
	while (c1)
    {
        printf("%s", c1);
    	c1 = get_next_line(fd1); 
		i++;       
    }
	printf("\n");
	i = 0;
	char *c2 = get_next_line(fd2);
	while (c2)
    {
        printf("%s", c2);
    	c2 = get_next_line(fd2);
		i++;        
    }
	printf("\n");
	i = 0;
	char *c3 = get_next_line(fd3);
	while (c3)
    {
        printf("%s", c3);
    	c3 = get_next_line(fd3);
		i++;   
    }
}*/