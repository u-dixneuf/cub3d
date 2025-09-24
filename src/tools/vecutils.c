/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:50:00 by mzary             #+#    #+#             */
/*   Updated: 2025/09/24 19:59:08 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

double	norme(double vec[2])
{
	double	norme;

	norme = vec[0] * vec[0] + vec[1] * vec[1];
	return (sqrt(norme));
}

double	scalarp(double a[2], double b[2])
{
	return (a[0] * b[0] + a[1] * b[1]);
}
