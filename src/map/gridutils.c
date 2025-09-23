/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gridutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:10:50 by mzary             #+#    #+#             */
/*   Updated: 2025/09/23 17:20:56 by mzary            ###   ########.fr       */
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
		cfree((void **)&line);
		if (!getlinecheck(&line, fd))
			return (false);
	}
	if (!*line)
		return (cfree((void **)&line), cerror("missing map!"), false);
	while (*line)
	{
		*grid = ccalloc(sizeof(t_grid));
		if (!*grid)
			return (cfree((void **)&line), cerror("malloc fail!"), false);
		if (line[cstrlen(line) - 1] == '\n')
			line[cstrlen(line) - 1] = 0;
		(*grid)->line = line;
		grid = &(*grid)->next;
		if (!getlinecheck(&line, fd))
			return (false);
	}
	return (cfree((void **)&line), true);
}

void	freegrid(t_grid	*grid)
{
	t_grid	*next;

	while (grid)
	{
		next = grid->next;
		cfree((void **)&grid->line);
		cfree((void **)&grid);
		grid = next;
	}
}

bool	checkgrid(t_grid *grid, t_map *map)
{
	int		i;
	bool	dset;
	char	c;

	dset = false;
	while (grid)
	{
		if (!*grid->line || spaceline(grid->line))
			return (cerror("empty line in map!"), false);
		i = -1;
		while (grid->line[++i])
		{
			c = grid->line[i];
			if ((c == 'N' || c == 'S' || c == 'W' || c == 'E') && dset)
				return (cerror("cannot reset direction!"), false);
			else if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
				dset = true;
			else if (c != '0' && c != '1' && c != 32)
				return (cerror("invalid character in map!"), false);
		}
		grid = grid->next;
	}
	if (!dset)
		return (cerror("direction not set!"), false);
	return (true);
}

char	g(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->size_x
		|| y < 0 || y >= map->size_y)
		return ('+');
	return (map->grid[y * map->size_x + x]);
}
