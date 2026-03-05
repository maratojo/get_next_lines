/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maratojo <maratojo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:08:03 by maratojo          #+#    #+#             */
/*   Updated: 2026/03/05 21:14:37 by maratojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stock[1024];

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stock[fd])
	{
		stock[fd] = ft_strdup("");
		if (!stock[fd])
			return (NULL);
	}
	stock[fd] = stock_read(fd, stock[fd]);
	if (!stock[fd])
		return (NULL);
	line = extract_line(&stock[fd]);
	return (line);
}
