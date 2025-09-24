/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:15:07 by mzary             #+#    #+#             */
/*   Updated: 2025/09/24 18:36:22 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static double	contact(t_ray *ray, double	rx, double ry)
{

}

static void	check_contact(t_ray *ray, int rX, int rY) // norminette
{
	double	pt_d;
	double	pos;

	pos = 0;
	while (fabs(pos - CSIZE) > EPS)
	{
		pt_d = contact(ray, rX + pos, rY);
		if (pt_d != -1 && (ray->c_dist == -1 || pt_d < ray->c_dist))
		{
			ray->c_dist = pt_d;
			ray->dir = 'S';
		}
		pt_d = contact(ray, rX, rY + pos);
		if (pt_d != -1 && (ray->c_dist == -1 || pt_d < ray->c_dist))
		{
			ray->c_dist = pt_d;
			ray->dir = 'W';
		}
		pt_d = contact(ray, rX + pos, rY + CSIZE);
		if (pt_d != -1 && (ray->c_dist == -1 || pt_d < ray->c_dist))
		{
			ray->c_dist = pt_d;
			ray->dir = 'N';
		}
		pt_d = contact(ray, rX + CSIZE, rY + pos);
		if (pt_d != -1 && (ray->c_dist == -1 || pt_d < ray->c_dist))
		{
			ray->c_dist = pt_d;
			ray->dir = 'E';
		}
		pos += INCR;
	}
}

static void	draw_column(t_cube *cube, int X)
{
	t_ray	ray;
	double	texture_size;
	int		rX;
	int		rY;

	ray.r_angle = cube->map.angle + (FOV / SIZE) * (SIZE / 2 - X);
	while (ray.r_angle >= 2 * PI)
		ray.r_angle -= 2 * PI;
	ray.px = (double)cube->map.pX * CSIZE + cube->map.posX;
	ray.py = (double)cube->map.pY * CSIZE + cube->map.posY;
	ray.c_dist = -1;
	rY = 0;
	while (rY < cube->map.size_y)
	{
		rX = 0;
		while (rX < cube->map.size_x)
		{
			if (g(&cube->map, rX, rY) == '1')
				check_contact(&ray, rX, rY);
			rX += 1;
		}
		rY += 1;
	}
	// get texture_size (0 <= ts <= SIZE)
	// fill 0<=y<= SIZE / 2 - TS / 2 with ceiling color
	// fill SIZE/2 - TS/2<=y<=SIZE/2 + TS/2 with texture
	// fill SIZE/2 + TS/2<=y<=SIZE with floor color
}

int	game(t_cube	*cube)
{
	int	X;

	X = 0;
	while (X < SIZE)
	{
		draw_column(cube, X);
		X += 1;
	}
	return (0);
}
