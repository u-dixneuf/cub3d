/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:15:07 by mzary             #+#    #+#             */
/*   Updated: 2025/09/24 21:01:38 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static double	contact(t_ray *ray, double	rx, double ry)
{
	double	rayvec[2];
	double	rvec[2];
	double	product;

	rayvec[0] = cos(ray->r_angle);
	rayvec[1] = -sin(ray->r_angle);
	rvec[0] = rx - ray->px;
	rvec[1] = ry - ray->py;
	product = norme(rayvec) * norme(rvec);
	if (fabs(scalarp(rayvec, rvec) - product) < EPS)
		return (norme(rvec));
	return (-1);
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
		pos = pos + INCR;
	}
}

static void	fill_column(t_ray ray, t_cube *cube, int X)
{
	double	max_cdis;
	double	texture_s;
	int		Y;
	int		*color;

	max_cdis = sqrt(pow(cube->map.size_x * CSIZE, 2) +
		pow(cube->map.size_y * CSIZE, 2));
	texture_s = SIZE * (1 - ray.c_dist / max_cdis); // fix
	Y = 0;
	while (Y < SIZE)
	{
		color = (int *)(cube->mlx.img_addr + Y * cube->mlx.sl + X * cube->mlx.bpx / 8);
		if (Y <= SIZE / 2 - texture_s / 2)
			*color = mlx_get_color_value(cube->mlx.mlx_ptr, CEILING);
		else if (Y >= SIZE / 2 + texture_s / 2)
			*color = mlx_get_color_value(cube->mlx.mlx_ptr, FLOOR);
		else if (ray.dir == 'N')
			*color = mlx_get_color_value(cube->mlx.mlx_ptr, NORTH);
		else if (ray.dir == 'S')
			*color = mlx_get_color_value(cube->mlx.mlx_ptr, SOUTH);
		else if (ray.dir == 'W')
			*color = mlx_get_color_value(cube->mlx.mlx_ptr, WEST);
		else if (ray.dir == 'E')
			*color = mlx_get_color_value(cube->mlx.mlx_ptr, EAST);
		Y += 1;
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
	fill_column(ray, cube, X);
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
	mlx_put_image_to_window(cube->mlx.mlx_ptr, cube->mlx.win_ptr,
		cube->mlx.img_ptr, 0, 0);
	mlx_loop(cube->mlx.mlx_ptr);
	return (0);
}
