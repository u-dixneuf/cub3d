/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:42:43 by mzary             #+#    #+#             */
/*   Updated: 2025/09/19 20:52:26 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*getline(int fd) // minimalistic getline, can copy the Libft one
{
	char	line[1000];
	size_t	i;

	cmemset((void *)line, 0, 1000);
	i = 0;
	while (read(fd, &line[i], 1) && line[i] != '\n')
		i += 1;
	line[i] = 0; // in case it's '\n'
	return (cstrdup(line));
}
