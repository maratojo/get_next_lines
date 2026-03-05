/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maratojo <maratojo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:21:36 by maratojo          #+#    #+#             */
/*   Updated: 2026/03/05 11:58:31 by maratojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*stock_(int fd, char *stock)
{
	char	*buffer;
	int		nbr_read;
	char *tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stock, '\n'))
	{
		nbr_read = read(fd, buffer, BUFFER_SIZE);
		if (nbr_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (nbr_read > 0)
		{
			buffer[nbr_read + 1] = '\0';
			tmp = ft_strjoin(stock, buffer);
			stock = tmp;
			free (buffer);
		}
	}
	return (stock);
}

static char *extract_line(char **stock)
{
	char	*line;
	char	*new_stock;
	char	*pos;

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

char *get_next_line(int fd)
{
	char *line;
	static char *stock;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	if(!stock)
	{
		stock = ft_strdup("");
		if (!stock)
			return (NULL);
	}
	stock = stock_(fd, stock);
	if (!stock)
	{
		free(stock);
		stock = NULL;
	}
	line = extract_line(&stock);
	if (!line)
	{
		free(line);
		line = NULL;
	}
	return (line);
}
