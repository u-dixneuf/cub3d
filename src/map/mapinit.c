/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:11:18 by mzary             #+#    #+#             */
/*   Updated: 2025/09/22 16:00:11 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	mapinit(t_cube *cube)
{
	int		index;

	index = cstrchr(cube->map.path, ".cub");
	if (index == -1 || index != cstrlen(cube->map.path) - 4)
		return (cerror("wrong extension!"), 1);
	cube->map.filefd = open(cube->map.path, O_RDONLY);
	if (cube->map.filefd == -1)
		return (cerror("error opening file!"), 1);
	if (parsedata(&cube->map))
		return (1);
	return (parsegrid(cube));
}
