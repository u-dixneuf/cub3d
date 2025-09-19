/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:29:19 by mzary             #+#    #+#             */
/*   Updated: 2025/09/19 18:39:27 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
}
