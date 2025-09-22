/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsegrid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:19:46 by mzary             #+#    #+#             */
/*   Updated: 2025/09/22 20:13:00 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static bool	transgrid(t_grid *grid, t_map *map)
{
	return (true);
}

int	parsegrid(t_map *map)
{
	t_grid	*grid;

	grid = NULL;
	if (!getgrid(&grid, map->filefd)
		|| !checkgrid(grid, map))
		return (freegrid(grid), 1);
	// transform grid into 2D int array and get player positions and angles
	if (!transgrid(grid, map))
		return (freegrid(grid), 1);
	return (freegrid(grid), 0);
}
