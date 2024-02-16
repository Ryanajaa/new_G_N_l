/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarunota <jarunota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:27:55 by jarunota          #+#    #+#             */
/*   Updated: 2024/02/16 15:42:42 by jarunota         ###   ########.fr       */
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

/*	reading from a file descriptor (fd) into a buffer (buf) 
	with a specified size (BUFFER_SIZE). It continues reading until
	it reaches the end of the file or encounters an error
	The content read from the file is then appended to a backup buffer.*/

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

/*	This function extracts the remaining content 
	of a line AFTER A NEW LINE*/

static char	*ft_gnl(char *line)
{
	int		i;
	char	*remain_line;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	remain_line = ft_substr(line, i + 1, -1);
	if (!remain_line)
		return (NULL);
	if (remain_line[0] == '\0')
		ft_clear_backup(&line);
	return (remain_line);
}

/*	This function extracts a line of text from the 
	input line up to the FIRST NEWLINE character.*/

static char	*ft_extract(char *line)
{
	int		i;
	char	*temp_line;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	temp_line = ft_strdup(line);
	free(line);
	if (!temp_line)
		return (NULL);
	line = ft_substr(temp_line, 0, i + 1);
	free(temp_line);
	if (!line)
		return (NULL);
	return (line);
}

/*	it just the begin..... */

char	*get_next_line(int fd)
{
	char		*buf;
	char		*current_line;
	static char	*backup_buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
	{
		if (backup_buf)
			return (ft_clear_backup(&backup_buf));
		return (NULL);
	}
	current_line = ft_read(fd, buf, &backup_buf);
	free(buf);
	backup_buf = ft_gnl(current_line);
	current_line = ft_extract(current_line);
	if (!current_line)
	{
		if (backup_buf)
			return (ft_clear_backup(&backup_buf));
		return (NULL);
	}
	return (current_line);
}

// #define BUFFER_SIZE 1

// char *get_next_line(int fd);

// int main(void) {
//     int fd;
//     char *line;

//     // Open the file for reading
//     fd = open("test.txt", O_RDONLY);
//     if (fd < 0) {
//         perror("Error opening file");
//         return 1;
//     }

//     // Read lines from the file using get_next_line
//     while ((line = get_next_line(fd)) != NULL) {
//         printf("%s\n", line);
//         free(line);
//     }

//     // Close the file
//     close(fd);

//     return 0;
// }