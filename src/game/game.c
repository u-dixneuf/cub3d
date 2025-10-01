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

static double	contact(t_ray *ray, double gx, double gy)
{
	double	rayvec[2];
	double	gridvec[2];
	double	product;
	double	scalar;

	rayvec[0] = cos(ray->r_angle * acos(-1) / 180);
	rayvec[1] = -sin(ray->r_angle * acos(-1) / 180);
	gridvec[0] = gx - ray->px;
	gridvec[1] = gy - ray->py;
	product = norme(rayvec) * norme(gridvec);
	scalar = scalarp(rayvec, gridvec);
	if (fabs(scalar - product) < EPS)
		return (norme(gridvec));
	return (-1);
}

static void	check_contact(t_ray *ray, double gX, double gY) // norminette
{
	double	pt_d;
	double	pos;

	pos = 0;
	while (pos != CSIZE + 1)
	{
		pt_d = contact(ray, gX * CSIZE + pos, gY * CSIZE);
		if (pt_d != -1 && (ray->c_dist == -1 || pt_d < ray->c_dist))
		{
			ray->c_dist = pt_d;
			ray->dir = 'S';
		}
		pt_d = contact(ray, gX * CSIZE, gY * CSIZE + pos);
		if (pt_d != -1 && (ray->c_dist == -1 || pt_d < ray->c_dist))
		{
			ray->c_dist = pt_d;
			ray->dir = 'E';
		}
		pt_d = contact(ray, gX * CSIZE + pos, (gY + 1) * CSIZE);
		if (pt_d != -1 && (ray->c_dist == -1 || pt_d < ray->c_dist))
		{
			ray->c_dist = pt_d;
			ray->dir = 'N';
		}
		pt_d = contact(ray, (gX + 1) * CSIZE, gY * CSIZE + pos);
		if (pt_d != -1 && (ray->c_dist == -1 || pt_d < ray->c_dist))
		{
			ray->c_dist = pt_d;
			ray->dir = 'W';
		}
		pos += 1;
	}
}

static void	fill_column(t_ray ray, t_cube *cube, int X)
{
	double	max_cdis;
	double	texture_s;
	int		Y;
	int		*color;
	double		diff_angle;

	max_cdis = sqrt(pow(cube->map.size_x * CSIZE, 2) +
		pow(cube->map.size_y * CSIZE, 2));
	diff_angle = (ray.r_angle - cube->map.angle) * acos(-1) / 180;
	texture_s = SIZE * (1 - ray.c_dist / max_cdis);
	/* debug */
	//printf("max_cdis = %lf, texture_s = %lf\n", max_cdis, texture_s);
	/* debug */
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
	int		gX;
	int		gY;

	ray.r_angle = cube->map.angle + (double)FOV / ((double)SIZE - 1) * (double)(SIZE / 2 - X);
	while (ray.r_angle >= 360)
		ray.r_angle -= 360;
	while (ray.r_angle < 360)
		ray.r_angle += 360;
	ray.px = (double)cube->map.pX * CSIZE + cube->map.posX;
	ray.py = (double)cube->map.pY * CSIZE + cube->map.posY;
	ray.c_dist = -1;
	ray.dir = '+';
	gY = 0;
	while (gY < cube->map.size_y)
	{
		gX = 0;
		while (gX < cube->map.size_x)
		{
			if (g(&cube->map, gX, gY) == '1')
				check_contact(&ray, gX, gY);
			gX += 1;
		}
		gY += 1;
	}
	fill_column(ray, cube, X);
}

int	game(t_cube	*cube)
{
	int	X;

	printf("rendering!\n");
	X = 0;
	while (X < SIZE)
	{
		draw_column(cube, X);
		X += 1;
	}
	mlx_put_image_to_window(cube->mlx.mlx_ptr, cube->mlx.win_ptr,
		cube->mlx.img_ptr, 0, 0);
	printf("done rendering!\n");
	return (0);
}
