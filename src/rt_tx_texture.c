/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_tx_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:42:03 by dshereme          #+#    #+#             */
/*   Updated: 2019/09/20 18:01:00 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool			load_texture(t_rt *rtv, char *text_path)
{
	static	int			texture_numb;

	rtv->texture[texture_numb] = SDL_LoadBMP(text_path);
	if (rtv->texture[texture_numb] == NULL)
	{
		while (texture_numb >= 0)
		{
			SDL_FreeSurface(rtv->texture[texture_numb]);
			rtv->texture[texture_numb] = NULL;
			texture_numb--;
		}
		rt_clean(rtv);
		return (false);
	}
	texture_numb++;
	return (true);
}

bool				load_textures(t_rt *rtv)
{
	int					i;
	char				*leaks;
	char				*s;

	leaks = NULL;
	i = -1;
	while (++i < TEXTURES_COUNT)
	{
		s = ft_itoa(i);
		leaks = ft_strjoin("./textures/", s);
		if (s)
			free(s);
		s = ft_strjoin(leaks, ".bmp");
		if (leaks)
			free(leaks);
		if ((load_texture(rtv, s)) == false)
		{
			if (s)
				free(s);
			return (false);
		}
		if (s)
			free(s);
	}
	return (true);
}

static Uint32		get_texel(void *pixels, int idx)
{
	unsigned	char	*pix;
	Uint32				red;
	Uint32				green;
	Uint32				blue;

	pix = (unsigned char*)pixels;
	blue = pix[idx];
	green = pix[idx + 1] << 8;
	red = pix[idx + 2] << 16;
	return (red | green | blue);
}

static	t_channel	color_to_vec(int rgb)
{
	Uint32				red;
	Uint32				green;
	Uint32				blue;

	red = (rgb >> 16) & 0xFF;
	green = (rgb >> 8) & 0xFF;
	blue = (rgb) & 0xFF;
	return ((t_channel){red, green, blue});
}

t_channel			texture_mapping(t_rt *rtv, t_vec p, t_objects *ob)
{
	int					u;
	int					v;
	t_channel			color;
	Uint32				int_color;

	p -= ob->centre;
	p = normalize(p);
	u = (0.5 + atan2(p.z, p.x) / (2.0 * M_PI))
	* rtv->texture[ob->texture]->w;
	v = rtv->texture[ob->texture]->h - ((0.5 - asin(p.y) / M_PI) *
	rtv->texture[ob->texture]->h);
	int_color = get_texel(rtv->texture[ob->texture]->pixels,
	(v * rtv->texture[ob->texture]->w + u) * 3);
	color = color_to_vec(int_color);
	return (color);
}
