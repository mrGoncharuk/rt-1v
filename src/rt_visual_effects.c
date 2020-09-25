/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_visual_effects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:24:36 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/20 16:21:59 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	sepia_image(Uint32 *pixels, Uint32 *pixels_copy)
{
	Uint32		i;
	Uint32		tmp;
	t_channel	rgb;

	i = -1;
	while (CW * CH > (++i))
	{
		tmp = pixels[i];
		rgb.r = (((tmp >> 16) & 0xFF) * 0.393) + ((tmp >> 8 & 0xFF) * 0.769) +
		((tmp & 0xFF) * 0.189);
		rgb.g = (((tmp >> 16) & 0xFF) * 0.349) + ((tmp >> 8 & 0xFF) * 0.686) +
		((tmp & 0xFF) * 0.168);
		rgb.b = (((tmp >> 16) & 0xFF) * 0.272) + ((tmp >> 8 & 0xFF) * 0.534) +
		((tmp & 0xFF) * 0.131);
		pixels_copy[i] = rt_channel_color_to_uint(rt_enlightenment(rgb, 1));
	}
}

void	gray_rad(Uint32 *pixels, Uint32 *pixels_copy)
{
	int			i;
	Uint32		rgb;

	i = -1;
	while (CW * CH > (++i))
	{
		rgb = 0.290 * ((pixels[i] >> 16) & 0xFF) + 0.59 *
			((pixels[i] >> 8) & 0xFF) + 0.11 * (pixels[i] & 0xFF);
		pixels_copy[i] = rt_channel_color_to_uint((t_channel){rgb, rgb, rgb});
	}
}

void	white_rad(Uint32 *pixels, Uint32 *pixels_copy)
{
	int			i;
	Uint32		rgb;
	t_channel	rez;

	i = -1;
	while (CW * CH > (++i))
	{
		rgb = 0.299 * ((pixels[i] >> 16) & 0xFF) + 0.587 *
			((pixels[i] >> 8) & 0xFF) + 0.114 * (pixels[i] & 0xFF);
		rez.r = (((255 - rgb) < 0) ? 0 : (255 - rgb));
		rez.g = (((255 - rgb) < 0) ? 0 : (255 - rgb));
		rez.b = (((255 - rgb) < 0) ? 0 : (255 - rgb));
		pixels_copy[i] = rt_channel_color_to_uint(rez);
	}
}

void	cartoon(Uint32 *pixels, Uint32 *pixels_copy)
{
	int			i;
	t_channel	rez;

	i = -1;
	while (CW * CH > (++i))
	{
		rez.r = (((pixels[i] >> 16) & 0xFF) / 20) * 20;
		rez.g = (((pixels[i] >> 8) & 0xFF) / 20) * 20;
		rez.b = (((pixels[i]) & 0xFF) / 20) * 20;
		pixels_copy[i] = rt_channel_color_to_uint(rez);
	}
}
