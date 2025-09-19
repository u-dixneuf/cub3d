/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:29:19 by mzary             #+#    #+#             */
/*   Updated: 2025/09/19 20:10:02 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mlxhooks(t_mlx *mlx)
{
	// ◦ The left and right arrow keys of the keyboard must allow you to look left and
	// right in the maze.
	// ◦ The W, A, S, and D keys must allow you to move the point of view through
	// the maze.
	// ◦ Pressing ESC must close the window and quit the program cleanly.
	// ◦ Clicking on the red cross on the window’s frame must close the window and
	// quit the program cleanly.
	mlxloop(mlx->mlx_ptr);
	return (0);
}

int	mlxinit(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (1);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			mlx->size_x, mlx->size_y, "cub3d");
	if (!mlx->win_ptr)
		return (1);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr,
			mlx->size_x,
			mlx->size_y);
	if (!mlx->img_ptr)
		return (1);
	mlx->img_addr = mlx_get_data_addr(mlx->img_ptr,
			&mlx->bpx, &mlx->sl, &mlx->e);
	if (!mlx->img_addr)
		return (1);
	return (mlxhooks(mlx));
}

