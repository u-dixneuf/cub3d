/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:57:20 by mzary             #+#    #+#             */
/*   Updated: 2025/09/23 17:32:06 by mzary            ###   ########.fr       */
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

# define SCALE	10
# define FOV	60
# define PI		3.14159

typedef struct	s_mlx
{
	int			size_x;
	int			size_y;
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