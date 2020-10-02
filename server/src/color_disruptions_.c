/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_disruptions_.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:55:55 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/20 12:53:27 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_channel			disruption_1(t_vec p, t_vec center)
{
	int			u;
	int			v;
	t_channel	color;

	p -= center;
	p = normalize(p);
	u = 0;
	v = 0;
	u = ((sin(p.x * M_PI * 1) + 1) * 10) * 4;
	u *= ((cos(p.x * M_PI * 1) + 1) * 10) * 4;
	color = (t_channel){(u) & 0xFF, (u >> 2) & 0xFF, (u >> 4) & 0xFF};
	return (color);
}

t_channel			disruption_2(t_vec p, t_vec center)
{
	int			u;
	int			v;
	t_channel	color;

	p -= center;
	p = normalize(p);
	u = 0;
	v = 0;
	u = ((sin(p.x * 2 * M_PI * 5) + 1) * 10);
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10;
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10;
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10;
	v = (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	v += (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	v += (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	v += (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	if (v)
		u *= v;
	color = (t_channel){(u >> 16) & 0xFF, (u) & 0xFF, ((u) & 0xFF)};
	if (color.r == 0 && color.b == 0 && color.g == 0)
		color = (t_channel){0, 0, 0};
	return (color);
}

t_channel			disruption_3(t_vec p, t_vec center)
{
	int			u;
	int			v;
	t_channel	color;

	p -= center;
	p = normalize(p);
	u = 0;
	v = 0;
	u = ((cos(p.x * M_PI * 10) + 1) * 10) * 10;
	color = (t_channel){(u >> 5) & 0xFF, (u) & 0xFF, (u >> 2) & 0xFF};
	return (color);
}

t_channel			disruption_4(t_vec p, t_vec center)
{
	int			u;
	int			v;
	t_channel	color;

	p -= center;
	p = normalize(p);
	u = 0;
	v = 0;
	u = ((sin(p.x * 2 * M_PI * 5) + 1) * 10);
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10;
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10;
	u += (sin(p.x * 2 * M_PI * 5) + 1) * 10;
	v = (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	v += (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	v += (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	v += (cos(p.y * 2 * M_PI * 5) + 1) * 10;
	if (v)
		u *= v;
	color = (t_channel){(u << 2) & 0xFF, (u >> 8) & 0xFF, ((u >> 16) & 0xFF)};
	if (color.r == 0 && color.b == 0 && color.g == 0)
		color = (t_channel){0, 255, 255};
	return (color);
}
