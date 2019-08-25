/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vec_op_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:41:57 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/25 17:42:17 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		vec_length(t_vec v)
{
	return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

double		dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec		rt_mult_mtrx_vec(double mtrx[3][3], t_vec vec)
{
	t_vec	res;
	int		i;
	int		j;

	res = 0;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			res[i] += vec[j] * mtrx[i][j];
	}
	return (res);
}
