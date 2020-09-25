/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_disruptions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:17:45 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/20 16:02:53 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_channel			noise_text(t_vec p, t_vec center)
{
	t_channel	color;
	Uint32		new_pixel;
	int			u;
	int			v;

	p -= center;
	p = normalize(p);
	u = 0;
	v = 0;
	u = ((sin(p.x * 2 * M_PI * 5) + 1) * 10000000) * 4;
	v = ((cos(p.x * 2 * M_PI * 5) + 1) * 10000000) * 4;
	if (v)
		u *= v;
	color = (t_channel){(u >> 16) & 0xFF, (u >> 8) & 0xFF, (u & 0xFF)};
	color.b = (color.r + color.g + color.b) / 3.0f;
	color.g = color.b;
	color.r = color.g;
	new_pixel = 0xFF000000 | ((Uint32)color.r << 16) |
		((Uint32)color.g << 8) | ((Uint32)color.b);
	color = (t_channel){(new_pixel >> 16) & 0xFF,
				(new_pixel >> 8) & 0xFF, (new_pixel & 0xFF)};
	return (color);
}

t_channel			wave_chechboard(t_vec p)
{
	float		u;
	double		v;
	t_channel	color;

	u = floor(sin(p.x)) + floor(sin(p.y)) + floor(sin(p.z));
	u = modf(u * 0.5, &v);
	u = u * 3;
	color = (t_channel){((int)u >> 16) & 0xFF, ((int)u >> 16) & 0xFF,
						(((int)u >> 16) & 0xFF)};
	return (color);
}
