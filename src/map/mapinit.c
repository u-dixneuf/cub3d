/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:11:18 by mzary             #+#    #+#             */
/*   Updated: 2025/09/21 14:38:45 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mapinit(t_map *map)
{
	int		index;

	index = cstrchr(map->path, ".cub");
	if (index == -1 || index != cstrlen(map->path) - 4)
		return (cerror("wrong extension!"), 1);
	map->filefd = open(map->path, O_RDONLY);
	if (map->filefd == -1)
		return (cerror("error opening file!"), 1);
	if (parsedata(map))
		return (1);
	return (parsegrid(map));
}
