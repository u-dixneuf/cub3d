/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsegrid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:19:46 by mzary             #+#    #+#             */
/*   Updated: 2025/09/22 17:42:57 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	parsegrid(t_cube *cube)
{
	t_grid	*grid;
	
	grid = NULL;
	if (!getgrid(&grid, cube->map.filefd))
		return (freegrid(grid), 1);
	if (!checkgrid(grid, cube))
	return (0);
}
