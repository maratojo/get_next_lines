/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maratojo <maratojo@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:04:27 by maratojo          #+#    #+#             */
/*   Updated: 2026/03/05 16:41:55 by maratojo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
# include <fcntl.h>
# include "get_next_line.h"
int main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	// printf("%s", line);
	// free(line);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(42);
	}
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}
