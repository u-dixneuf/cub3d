/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 20:15:54 by mzary             #+#    #+#             */
/*   Updated: 2025/09/21 14:23:40 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	cstrchr(char *s, char *tofind)
{
	int	index;
	int	j;

	index = 0;
	while (s && s[index])
	{
		j = 0;
		while (tofind && tofind[j] && tofind[j] == s[index + j])
			j += 1;
		if (!tofind[j])
			return (index);
		index += 1;
	}
	return (-1);
}

size_t	cstrlen(char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len += 1;
	return (len);
}

char	*cstrdup(char *s)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(sizeof(char) * (cstrlen(s) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		dup[i] = s[i];
		i += 1;
	}
	dup[i] = 0;
	return (dup);
}

int	cstrcmp(char *s1, char *s2) // looks good to me
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i += 1;
	return (s1[i] - s2[i]);
}

int	cstrncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
