/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgetline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:42:43 by mzary             #+#    #+#             */
/*   Updated: 2025/09/21 16:45:12 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*cgetline(int fd) // minimalistic getline, can copy the Libft one
{
	char	line[1000];
	size_t	i;

	cmemset((void *)line, 0, 1000);
	i = 0;
	while (read(fd, &line[i], 1) && line[i] != '\n')
		i += 1;
	return (cstrdup(line));
}

int	spaceline(char *line)
{
	size_t	i;

	i = 0;
	if (!*line)
		return (0);
	while (line[i])
	{
		if (!(line[i] == 32 || (line[i] >= 9 && line[i] <= 13 )))
			return (0);
		i += 1;
	}
	return (1);
}
