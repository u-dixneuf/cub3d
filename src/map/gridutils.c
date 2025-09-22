/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gridutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:10:50 by mzary             #+#    #+#             */
/*   Updated: 2025/09/22 17:40:47 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static bool	getlinecheck(char **line, int fd)
{
	*line = cgetline(fd);
	if (!*line)
		return (cerror("malloc fail!"), false);
	return (true);
}

bool	getgrid(t_grid **grid, int fd)
{
	char	*line;

	if (!getlinecheck(&line, fd))
		return (false);
	while (spaceline(line))
	{
		free(line);
		if (!getlinecheck(&line, fd))
			return (false);
	}
	if (!*line)
		return (free(line), cerror("missing map!"), false);
	while (*line)
	{
		*grid = ccalloc(sizeof(t_grid));
		if (!*grid)
			return (free(line), cerror("malloc fail!"), false);
		if (line[cstrlen(line) - 1] == '\n')
			line[cstrlen(line) - 1] = 0;
		(*grid)->line = line;
		grid = &(*grid)->next;
		if (!getlinecheck(&line, fd))
			return (false);
	}
	return (free(line), true);
}

void	freegrid(t_grid	*grid)
{
	t_grid	*next;

	while (grid)
	{
		next = grid->next;
		free(grid->line);
		free(grid);
		grid = next;
	}
}
