/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsedata.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:38:47 by mzary             #+#    #+#             */
/*   Updated: 2025/09/22 21:31:24 by mzary            ###   ########.fr       */
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
		return (cerror("duplicate element!"), cfree((void **)&path), 1);
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

static int	checkcolor(char *s)
{
	size_t	i;
	int		color;

	i = 0;
	while (s[i])
	{
		if (s[i] >'9' || s[i] < '0')
			return (-1);
		i += 1;
	}
	color = catoi(s);
	if (color < 0 || color > 255)
		return (-1);
	return (color);
}

static int	fillcheck(t_map *map, char **split, char c)
{
	int	colors[3];
	int	i;

	if ((c == 'F' && map->fset) || (c == 'C' && map->cset))
			return (cerror("duplicate color!"), 1);
	i = -1;
	while (++i < 3)
		colors[i] = checkcolor(split[i]);
	if (colors[0] == -1 || colors[1] == -1 || colors[2] == -1)
			return (cerror("invalid color!"), 1);
	i = -1;
	while (++i < 3)
	{
		if (c == 'F')
			map->floor[i] = colors[i];
		else
			map->ceiling[i] = colors[i];
		i += 1;
	}
	if (c == 'F')
		map->fset = true;
	else
		map->cset = true;
	return (0);
}

static int	fillcolor(t_map *map, char *line, char c)
{
	char	**split;
	size_t	count;

	while (*line == 32)
		line += 1;
	if (!*line || *line == '\n')
		return (cerror("path not found!"), 1);
	if (line[cstrlen(line) - 1] == '\n')
		line[cstrlen(line) - 1] = 0;
	split = csplit(line, ',');
	if (!split)
		return (cerror("malloc error!"), 1);
	count = 0;
	while (split[count])
		count += 1;
	if (count != 3)
		return (freesplit(split), cerror("color error!"), 1);
	if (fillcheck(map, split, c))
		return (freesplit(split), 1);
	return (freesplit(split), 0);
}

int	parsedata(t_map *map)
{
	char	*line;
	int		fail;

	fail = 0;
	while (map->count != 6 && !fail)
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
		cfree((void **)&line);
	}
	return (fail);
}
