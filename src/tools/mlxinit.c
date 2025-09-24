/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:29:19 by mzary             #+#    #+#             */
/*   Updated: 2025/09/24 20:24:03 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	mlxhooks(t_cube *cube)
{
	// ◦ The left and right arrow keys of the keyboard must allow you to look left and
	// right in the maze.
	// ◦ The W, A, S, and D keys must allow you to move the point of view through
	// the maze.
	// ◦ Pressing ESC must close the window and quit the program cleanly.
	// ◦ Clicking on the red cross on the window’s frame must close the window and
	// quit the program cleanly.
	//mlx_loop(cube->mlx.mlx_ptr);
	return (0);
}

int	mlxinit(t_cube *cube)
{
	cube->mlx.mlx_ptr = mlx_init();
	if (!cube->mlx.mlx_ptr)
		return (1);
	cube->mlx.win_ptr = mlx_new_window(cube->mlx.mlx_ptr,
			SIZE, SIZE, "cub3d");
	if (!cube->mlx.win_ptr)
		return (1);
	cube->mlx.img_ptr = mlx_new_image(cube->mlx.mlx_ptr,
			SIZE,
			SIZE);
	if (!cube->mlx.img_ptr)
		return (1);
	cube->mlx.img_addr = mlx_get_data_addr(cube->mlx.img_ptr,
			&cube->mlx.bpx, &cube->mlx.sl, &cube->mlx.e);
	if (!cube->mlx.img_addr)
		return (1);
	return (mlxhooks(cube));
}
