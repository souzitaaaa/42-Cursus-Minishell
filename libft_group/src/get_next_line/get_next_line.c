/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:15:28 by dinoguei          #+#    #+#             */
/*   Updated: 2023/02/15 13:37:00 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_file(int fd, char *backup)
{
	int		read_bytes;
	char	*buffer;
	char	*temp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(backup, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(backup);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		temp = ft_strjoin(backup, buffer);
		free(backup);
		backup = temp;
	}
	free(buffer);
	return (backup);
}

char	*get_line(char *backup)
{
	char	*line;
	size_t	pos;

	if (!(*backup))
		return (NULL);
	pos = 0;
	while (backup[pos] && backup[pos] != '\n')
		pos++;
	line = malloc(sizeof(char) * (pos + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, backup, pos + 1);
	if (backup[pos] == '\n')
		line[pos++] = '\n';
	line[pos] = '\0';
	return (line);
}

char	*remove_read(char *backup)
{
	size_t	pos;
	size_t	pos2;
	char	*new_backup;

	pos = 0;
	pos2 = 0;
	while (backup[pos] && backup[pos] != '\n')
		pos++;
	if (!backup[pos])
	{
		free(backup);
		return (NULL);
	}
	new_backup = malloc(sizeof(char) * ft_strlen(backup) - pos + 1);
	if (!new_backup)
		return (NULL);
	pos++;
	while (backup[pos])
		new_backup[pos2++] = backup[pos++];
	new_backup[pos2] = '\0';
	free(backup);
	return (new_backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	if (backup == NULL)
	{
		backup = malloc(sizeof(char) * 1);
		if (!backup)
			return (NULL);
		backup[0] = '\0';
	}
	backup = read_file(fd, backup);
	if (!backup)
		return (NULL);
	line = get_line(backup);
	backup = remove_read(backup);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*prt;
	fd = open("teste.txt", O_RDONLY);
	prt = get_next_line(fd);
	printf("\nFunc Return: %s\n", prt);
	free(prt);
	prt = get_next_line(fd);
	printf("\nFunc Return: %s\n", prt);
	free(prt);
	close(fd);
}
*/
