/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsegrid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:19:46 by mzary             #+#    #+#             */
/*   Updated: 2025/09/21 17:57:17 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	parsegrid(t_map *map)
{
	/* debug */
	printf("path: %s\n", map->path);
	printf("filefd: %d\n", map->filefd);
	printf("count %d\n", map->count);
	printf("northpath: %s\n", map->northpath);
	printf("southpath: %s\n", map->southpath);
	printf("westpath: %s\n", map->westpath);
	printf("eastpath: %s\n", map->eastpath);
	printf("floor [%d][%d][%d]\n", map->floor[0], map->floor[1], map->floor[2]);
	printf("ceiling [%d][%d][%d]\n", map->ceiling[0], map->ceiling[1], map->ceiling[2]);
	/* debug */
	return (0);
}
