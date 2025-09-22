/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:00:25 by mzary             #+#    #+#             */
/*   Updated: 2025/09/22 17:44:57 by mzary            ###   ########.fr       */
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
	if (mapinit(&cube)) // HERE
		return (mapdestroy(&cube.map), 1); // double error message, remove?
	// need size_x size_y in mlx struct
	if (mlxinit(&cube))
		return (mapdestroy(&cube.map),
			mlxdestroy(&cube.mlx),
			cerror("mlxinit fail!"));
	return (game(&cube));
}
