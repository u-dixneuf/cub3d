/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cerror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 18:10:35 by mzary             #+#    #+#             */
/*   Updated: 2025/09/23 18:04:38 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	cerror(char *message)
{
	size_t	i;

	write(STDERR_FILENO, "Error\n", 6);
	i = 0;
	while (message && message[i])
	{
		write(STDERR_FILENO, message + i, 1);
		i += 1;
	}
	if (message)
		write(STDERR_FILENO, "\n", 1);
	return (1);
}

void	cmemset(void *p, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(p + i) = (unsigned char)c;
		i++;
	}
}

void	*ccalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	cmemset(ptr, 0, size);
	return (ptr);
}

bool	cfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
	return (true);
}

bool	cclose(int *fd)
{
	if (fd && *fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	return (true);
}
