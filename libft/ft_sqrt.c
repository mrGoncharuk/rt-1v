/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:37:17 by mhonchar          #+#    #+#             */
/*   Updated: 2018/11/30 16:38:49 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_sqrt(double nb)
{
	double an;
	double sum;
	double eps;

	an = nb / 2;
	sum = (an + nb / an) / 2;
	eps = 0.000001;
	while (ft_abs(an - sum) >= eps)
	{
		an = sum;
		sum = (an + nb / an) / 2;
	}
	return (sum);
}
