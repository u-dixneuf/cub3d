/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:57:20 by mzary             #+#    #+#             */
/*   Updated: 2025/09/24 20:54:35 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <stdbool.h>
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

# define SIZE	601
# define FOV	60
# define CSIZE	400
# define EPS	0.001

// debugpos
# define CEILING 0xffffff // white
# define FLOOR	0xff00ea // purple
# define NORTH	0x12de1c // green
# define SOUTH	0xff2f00 // red
# define WEST	0x07d5f5 // blue
# define EAST	0xf6ff00 // yellow
// debug

typedef struct	s_mlx
{
	void		*mlx_ptr; // need to free these
	void		*win_ptr;
	void		*img_ptr;

	char		*img_addr;
	int			bpx;
	int			sl;
	int			e;
}	t_mlx;

typedef struct	s_map
{
	char		*path; // no need to free av[2]
	int			filefd; // need to close at mapdestroy
	int			count;

	char		*northpath; // need to free these
	char		*southpath;
	char		*westpath;
	char		*eastpath;

	int			floor[3];
	bool		fset;
	int			ceiling[3];
	bool		cset;

	char		*grid;
	int			size_x;
	int			size_y;

	int			pX;
	int			pY;
	double		posX;
	double		posY;
	double		angle;
}	t_map;

typedef struct	s_cube
{
	t_mlx		mlx;
	t_map		map;
}	t_cube;

typedef struct	s_grid
{
	char			*line;
	struct s_grid	*next;
}	t_grid;

typedef struct	s_ray
{
	double	r_angle;
	double	px;
	double	py;

	double	c_dist;
	char	dir;
}	t_ray;

/* tools */
int		cerror(char *message);
void	cmemset(void *p, int c, size_t n);
void	*ccalloc(size_t size);
bool	cfree(void **p);
bool	cclose(int *fd);

int		catoi(char *nptr);

char	**csplit(char *s, char c);
void	freesplit(char **splits);

int		cstrchr(char *s, char *tofind);
size_t	cstrlen(char *s);
char	*cstrdup(char *s);
int		cstrcmp(char *s1, char *s2);
int		cstrncmp(char *s1, char *s2, size_t n);

char	*cgetline(int fd);
int		spaceline(char *line);

int		mlxinit(t_cube *cube);
void	mlxdestroy(t_mlx *mlx);

double	norme(double vec[2]);
double	scalarp(double a[2], double b[2]);

/* map */
int		mapinit(t_cube *cube);
void	mapdestroy(t_map *map);

int		parsedata(t_map *map);
int		parsegrid(t_map *map);

bool	getgrid(t_grid **grid, int fd);
void	freegrid(t_grid	*grid);
bool	checkgrid(t_grid *grid, t_map *map);
char	g(t_map *map, int x, int y);

/* game */
int		game(t_cube	*cube);

#endif
