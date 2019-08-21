/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:04:41 by mhonchar          #+#    #+#             */
/*   Updated: 2019/07/23 20:23:37 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"

void		ft_pp_img(t_canvas *canv, int x, int y, Uint32 color)
{
	if ((x >= 0 && x < canv->w) && (y >= 0 && y < canv->h))
		canv->pixels[canv->w * y + x] = color;
}

void		ft_draw_low_line(t_canvas *canv, t_vector2 p0, t_vector2 p1,
			t_vector2 deltap)
{
	t_vector2		p;
	int				d;
	int				yi;

	yi = 1;
	if (deltap.y < 0)
	{
		yi = -1;
		deltap.y = -deltap.y;
	}
	d = 2 * deltap.y - deltap.x;
	p.y = p0.y;
	p.x = p0.x;
	while (p.x <= p1.x)
	{
		ft_pp_img(canv, p.x, p.y, canv->draw_color);
		if (d > 0)
		{
			p.y += yi;
			d -= 2 * deltap.x;
		}
		d += 2 * deltap.y;
		p.x++;
	}
}

void		ft_draw_high_line(t_canvas *canv, t_vector2 p0, t_vector2 p1,
			t_vector2 deltap)
{
	t_vector2		p;
	int				d;
	int				xi;

	xi = 1;
	if (deltap.x < 0)
	{
		xi = -1;
		deltap.x = -deltap.x;
	}
	d = 2 * deltap.x - deltap.y;
	p.y = p0.y;
	p.x = p0.x;
	while (p.y <= p1.y)
	{
		ft_pp_img(canv, p.x, p.y, canv->draw_color);
		if (d > 0)
		{
			p.x = p.x + xi;
			d = d - 2 * deltap.y;
		}
		d = d + 2 * deltap.x;
		p.y++;
	}
}

t_vector2	ft_calc_delta(t_vector2 p0, t_vector2 p1)
{
	t_vector2	deltap;

	deltap.x = p1.x - p0.x;
	deltap.y = p1.y - p0.y;
	return (deltap);
}

void		ft_draw_line(t_canvas *canv, t_vector2 p0, t_vector2 p1)
{
	if (abs(p1.y - p0.y) < abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			ft_draw_low_line(canv, p1, p0, ft_calc_delta(p1, p0));
		else
			ft_draw_low_line(canv, p0, p1, ft_calc_delta(p0, p1));
	}
	else
	{
		if (p0.y > p1.y)
			ft_draw_high_line(canv, p1, p0, ft_calc_delta(p1, p0));
		else
			ft_draw_high_line(canv, p0, p1, ft_calc_delta(p0, p1));
	}
}