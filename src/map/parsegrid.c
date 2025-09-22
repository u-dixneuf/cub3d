/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsegrid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:19:46 by mzary             #+#    #+#             */
/*   Updated: 2025/09/22 21:43:38 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static bool	closedgrid(char *grid, int sx, int sy)
{
	// The map must be closed/surrounded by walls, if not the program must return
	// an error.
	return (true);
}

static void	getplayer(int x, int y, char dir, t_map *map)
{
	map->pX = x;
	map->pY = y;
	if (dir == 'N')
		map->angle = PI / 2;
	else if (dir == 'S')
		map->angle = -PI / 2;
	else if (dir == 'W')
		map->angle = PI;
	else
		map->angle = 0;
	map->grid[map->size_x * y + x] = '0';
}

static void	fillgrid(t_grid *grid, t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->size_y)
	{
		x = -1;
		while (grid->line[++x])
		{
			if (grid->line[x] == '1' || grid->line[x] == '0')
				map->grid[map->size_x * y + x] = grid->line[x];
			else if (grid->line[x] == 32)
				map->grid[map->size_x * y + x] = '+';
			else
				getplayer(x, y, grid->line[x], map);
		}
		while (x < map->size_x)
		{
			map->grid[map->size_x * y + x] = '+';
			x += 1;
		}
		grid = grid->next;
	}
}

static bool	transgrid(t_grid *grid, t_map *map)
{
	t_grid	*node;

	node = grid;
	while (node)
	{
		map->size_y += 1;
		if (cstrlen(node->line) > map->size_x)
			map->size_x = cstrlen(node->line);
		node = node->next;
	}
	map->grid = (char *)malloc(map->size_x * map->size_y);
	if (!map->grid)
		return (cerror("malloc fail!"), false);
	fillgrid(grid, map);
	if (!closedgrid(map->grid, map->size_x, map->size_y))
		return (cfree((void **)&map->grid), false);
	return (true);
}

int	parsegrid(t_map *map)
{
	t_grid	*grid;

	grid = NULL;
	if (!getgrid(&grid, map->filefd)
		|| !checkgrid(grid, map))
		return (freegrid(grid), 1);
	// transform grid into 2D char array and get player positions and angles
	if (!transgrid(grid, map))
		return (freegrid(grid), 1);
	return (freegrid(grid), 0);
}
