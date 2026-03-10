/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maratojo <maratojo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:21:36 by maratojo          #+#    #+#             */
/*   Updated: 2026/03/09 08:25:12 by maratojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*stock_read(int fd, char *stock)
{
	char	*buffer;
	int		nbr_read;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	nbr_read = 1;
	while (nbr_read > 0 && !ft_strchr(stock, '\n'))
	{
		nbr_read = read(fd, buffer, BUFFER_SIZE);
		if (nbr_read == -1)
		{
			free(stock);
			free(buffer);
			return (NULL);
		}
		buffer[nbr_read] = '\0';
		tmp = ft_strjoin(stock, buffer);
		free(stock);
		stock = tmp;
	}
	free(buffer);
	return (stock);
}

static char	*extract_line(char **stock)
{
	char	*line;
	char	*new_stock;
	char	*pos;

	if (!*stock || !**stock)
	{
		free(*stock);
		*stock = NULL;
		return (NULL);
	}
	pos = ft_strchr(*stock, '\n');
	if (pos)
	{
		line = ft_substr(*stock, 0, pos - *stock + 1);
		new_stock = ft_strdup(pos + 1);
		free (*stock);
		*stock = new_stock;
	}
	else
	{
		line = ft_strdup(*stock);
		free(*stock);
		*stock = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stock)
	{
		stock = ft_strdup("");
		if (!stock)
			return (NULL);
	}
	stock = stock_read(fd, stock);
	if (!stock)
		return (NULL);
	line = extract_line(&stock);
	return (line);
}
#include <stdio.h>
#include <fcntl.h>
int main()
{
	char *line;
	int fd;
	fd = open("test.txt", O_RDONLY);

	line = get_next_line(fd);
	printf("1: %s", line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}

	// free(line);
	close(fd);

}
