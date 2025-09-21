/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:00:25 by mzary             #+#    #+#             */
/*   Updated: 2025/09/21 17:50:38 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cube	cube;

	cmemset((void *)&cube, 0, sizeof(t_cube));
	if (ac != 2)
		return (cerror("invalid args!"));
	cube.map.path = av[1];
	cube.map.npc = &cube.npc;
	if (mapinit(&cube.map)) // HERE
		return (mapdestroy(&cube.map), 1); // double error message, remove?
	cube.mlx.size_x = cube.map.size_x;
	cube.mlx.size_y = cube.map.size_y;
	cube.mlx.npc = &cube.npc;
	if (mlxinit(&cube.mlx))
		return (mapdestroy(&cube.map),
			mlxdestroy(&cube.mlx),
			cerror("mlxinit fail!"));
	return (game(&cube));
}
