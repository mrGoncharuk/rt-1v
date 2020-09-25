/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:40:08 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/20 10:25:29 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_channel	anti_aliasing_(Uint32 *pixels, t_channel tmp, int x)
{
	t_channel	rgb;

	rgb.r = (((pixels[x + tmp.r + 1] >> 16) & 0xFF) + ((pixels[x
		+ tmp.r] >> 16) & 0xFF) + ((pixels[x + tmp.r - 1] >> 16) &
			0xFF) + ((pixels[x + tmp.b] >> 16) & 0xFF) +
				((pixels[x + tmp.g + 1] >> 16) & 0xFF)) / 5;
	rgb.g = (((pixels[x + tmp.r + 1] >> 8) & 0xFF) + ((pixels[x +
		tmp.r] >> 8) & 0xFF) + ((pixels[x + tmp.r - 1] >> 8) & 0xFF)
			+ ((pixels[x + tmp.b] >> 8) & 0xFF) + ((pixels[x +
				tmp.g + 1] >> 8) & 0xFF)) / 5;
	rgb.b = (((pixels[x + tmp.r + 1]) & 0xFF) + (pixels[x + tmp.r]
		& 0xFF) + (pixels[x + tmp.r - 1] & 0xFF) + (pixels[x +
			tmp.b] & 0xFF) + (pixels[x + tmp.g + 1] & 0xFF)) / 5;
	return (rgb);
}

void				anti_aliasing(Uint32 *pixels, int intensive)
{
	int			i;
	int			y;
	int			x;
	t_channel	rgb;
	t_channel	tmp;

	i = -1;
	while (++i <= intensive)
	{
		y = 1;
		while (++y < CH - 2)
		{
			tmp.r = (y) * CW;
			tmp.g = (y + 1) * CW;
			tmp.b = (y - 1) * CW;
			x = 0;
			while (++x < CW - 2)
			{
				rgb = anti_aliasing_(pixels, tmp, x);
				pixels[x + tmp.r] = rt_channel_color_to_uint(rgb);
			}
		}
	}
}
