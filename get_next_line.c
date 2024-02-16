/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarunota <jarunota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:27:55 by jarunota          #+#    #+#             */
/*   Updated: 2024/02/16 13:49:31 by jarunota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

//free memory allocated for the backup buffer (*backup)

static char	*ft_clear_backup(char **backup)
{
	free(*backup);
	*backup = NULL;
	return (NULL);
}

//reads from the file descriptor fd into the buffer buf

static char	*ft_read(int fd, char *buf, char **backup)
{
	int		bytes;
	char	*temp;

	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1 && backup)
			return (ft_clear_backup(backup));
		if (bytes < 1)
			break ;
		buf[bytes] = '\0';
		if (!(*backup))
			*backup = ft_strdup("");
		temp = *backup;
		*backup = ft_strjoin(temp, buf);
		ft_clear_backup(&temp);
		if (!(*backup))
			return (ft_clear_backup(backup));
		if (ft_strchr(*backup, '\n'))
			break ;
	}
	return (*backup);
}

static char	*ft_get_new_line(char *line)
{
	int		i;
	char	*temp;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	temp = ft_substr(line, i + 1, -1);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
		ft_clear_backup(&line);
	return (temp);
}

static char	*ft_cut_line(char *line)
{
	int		i;
	char	*new;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	new = ft_strdup(line);
	free(line);
	if (!new)
		return (NULL);
	line = ft_substr(new, 0, i + 1);
	free(new);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
	{
		if (backup)
			return (ft_clear_backup(&backup));
		return (NULL);
	}
	line = ft_read(fd, buf, &backup);
	free(buf);
	backup = ft_get_new_line(line);
	line = ft_cut_line(line);
	if (!line)
	{
		if (backup)
			return (ft_clear_backup(&backup));
		return (NULL);
	}
	return (line);
}
