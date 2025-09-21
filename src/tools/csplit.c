/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csplit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:23:00 by mzary             #+#    #+#             */
/*   Updated: 2025/09/21 17:48:19 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	if (size)
	{
		while (i < size - 1 && *(src + i) != '\0')
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
	src_len = 0;
	while (src[src_len])
		src_len += 1;
	return (src_len);
}

static int	s_count(char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

void	freesplit(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		free(splits[i]);
		i++;
	}
	free(splits);
}

static int	ft_splits(char *s, char c, char **splits, int count)
{
	int	i;
	int	st;
	int	split;

	i = 0;
	split = 0;
	while (split < count)
	{
		while (s[i] && s[i] == c)
			i++;
		st = i;
		while (s[i] && s[i] != c)
			i++;
		splits[split] = (char *)malloc(sizeof(char) * (i - st + 1));
		if (splits[split] == NULL)
		{
			freesplit(splits);
			return (0);
		}
		ft_strlcpy(splits[split], s + st, i - st + 1);
		split++;
	}
	splits[count] = NULL;
	return (1);
}

char	**csplit(char *s, char c)
{
	char	**splits;
	int		count;

	if (!s)
		return (NULL);
	count = s_count(s, c);
	splits = (char **)malloc(sizeof(char *) * (count + 1));
	if (splits == NULL)
		return (NULL);
	if (!ft_splits(s, c, splits, count))
		return (NULL);
	return (splits);
}
