/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:57:20 by mzary             #+#    #+#             */
/*   Updated: 2025/09/19 20:56:38 by mzary            ###   ########.fr       */
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
# include "mlx/mlx.h"
# include "mlx/mlx_int.h"

# define SCALE 10

typedef struct	s_npc
{
	int			xp;
	int			yp;
	int			xa;
	int			ya;
}	t_npc;

typedef struct	s_mlx
{
	int			size_x;
	int			size_y;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;

	char		*img_addr;
	int			bpx;
	int			sl;
	int			e;

	t_npc		*npc;
}	t_mlx;

typedef struct	s_map
{
	char		*path; // no need to free av[2]
	t_npc		*npc;
	int			filefd;
	int			count;

	char		*north; // need to free dup
	int			northfd; // need to close

	char		*south;
	int			southfd;

	char		*west;
	int			westfd;

	char		*east;
	int			eastfd;

	int			floor[3];
	int			ceiling[3];

	int			size_x;
	int			size_y;
}	t_map;

typedef struct	s_cube
{
	t_mlx		mlx;
	t_map		map;
	t_npc		npc;
}	t_cube;

/* tools */
int		cerror(char *message);
void	cmemset(void *p, int c, size_t n);

int		cstrchr(char *s, char *tofind);
size_t	cstrlen(char *s);
char	*cstrdup(char *s);
int		cstrcmp(char *s1, char *s2);

char	*getline(int fd);

int		mlxinit(t_mlx *mlx);
void	mlxdestroy(t_mlx *mlx);


/* map */
int		mapinit(t_map *map);
void	mapdestroy(t_map *map);

/* game */
int		game(t_cube	*cube);

#endif