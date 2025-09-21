/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsedata.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:38:47 by mzary             #+#    #+#             */
/*   Updated: 2025/09/21 16:44:05 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	filldata(t_map *map, char *line, char c)
{
	char	*path;

	while (*line == 32)
		line += 1;
	if (!*line || *line == '\n')
		return (cerror("path not found!"), 1);
	if (line[cstrlen(line) - 1] == '\n')
		line[cstrlen(line) - 1] = 0;
	path = cstrdup(line);
	if (!path)
		return (cerror("malloc error!"), 1);
	if ((c == 'N' && map->northpath)
		|| (c == 'S' && map->southpath)
		|| (c == 'W' && map->westpath)
		|| (c == 'E' && map->eastpath))
		return (cerror("duplicate element!"), free(path), 1);
	if (c == 'N')
		map->northpath = path;
	else if (c == 'S')
		map->southpath = path;
	else if (c == 'W')
		map->westpath = path;
	else
		map->eastpath = path;
	return (0);
}

static int	fillcolor(t_map *map, char *line, char c)
{
	char	**split;

	while (*line == 32)
		line += 1;
	if (!*line || *line == '\n')
		return (cerror("path not found!"), 1);
	if (line[cstrlen(line) - 1] == '\n')
		line[cstrlen(line) - 1] = 0;
}

int	parsedata(t_map *map)
{
	char	*line;
	int		fail;

	while (map->count != 6 && !fail) // infinite loop scenario!
	{
		line = cgetline(map->filefd);
		if (!line)
			return (cerror("malloc error!"), 1);
		fail = 0;
		if (!cstrncmp(line, "NO ", 3)
			|| !cstrncmp(line, "SO ", 3)
			|| !cstrncmp(line, "WE ", 3)
			|| !cstrncmp(line, "EA ", 3))
			fail = filldata(map, line + 3, line[0]);
		else if (!cstrncmp(line, "F ", 2)
			|| !cstrncmp(line, "C ", 2))
			fail = fillcolor(map, line + 2, line[0]);
		else if (!*line || !spaceline(line))
			fail = cerror("missing element(s)!");
		map->count += !fail * !spaceline(line);
		free(line);
	}
	return (fail);
}
