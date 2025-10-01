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

int key_handler(int key, void *vcube)
{
	t_cube *cube = (t_cube *)vcube;
	if (key == 65307) // ESC
		exit(0);
	else if (key == 65361) // <-
		cube->map.angle += 1;
	else if (key == 65363) // ->
		cube->map.angle -= 1;
	else if (key == 119) // W
	{
		if (cube->map.posY != 0)
			cube->map.posY -= 1;
		else if (cube->map.pY != 0)
		{
			cube->map.pY -= 1;
			cube->map.posY = CSIZE;
		}
	}
	else if (key == 115) // S
	{
		if (cube->map.posY != CSIZE)
			cube->map.posY += 1;
		else if (cube->map.pY != cube->map.size_y - 1)
		{
			cube->map.pY += 1;
			cube->map.posY = 0;
		}
	}
	else if (key == 97) // A
	{
		if (cube->map.posX != 0)
			cube->map.posX -= 1;
		else if (cube->map.pX != 0)
		{
			cube->map.pX -= 1;
			cube->map.posX = CSIZE;
		}
	}
	else if (key == 100) // D
	{
		if (cube->map.posX != CSIZE)
			cube->map.posX += 1;
		else if (cube->map.pX != cube->map.size_x - 1)
		{
			cube->map.pX += 1;
			cube->map.posX = 0;
		}
	}
	game(cube);
	return (0);
}

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
	mlx_key_hook(cube->mlx.win_ptr, key_handler, cube);
	mlx_loop(cube->mlx.mlx_ptr);
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
