/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapdestroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:11:22 by mzary             #+#    #+#             */
/*   Updated: 2025/09/23 18:06:56 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	mapdestroy(t_map *map)
{
	cclose(map->filefd);
	cfree((void **)&map->northpath);
	cfree((void **)&map->southpath);
	cfree((void **)&map->westpath);
	cfree((void **)&map->eastpath);
	cfree((void **)&map->grid);
}
