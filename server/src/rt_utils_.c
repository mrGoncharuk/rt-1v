/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:12:30 by dmolyboh          #+#    #+#             */
/*   Updated: 2019/09/19 17:16:09 by dmolyboh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		save_image(const char *file_name, SDL_Renderer *renderer)
{
	SDL_Surface	*surface;

	surface = SDL_CreateRGBSurface(0, CW, CH, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(renderer, NULL, surface->format->format,
	surface->pixels, surface->pitch);
	IMG_SavePNG(surface, file_name);
	SDL_FreeSurface(surface);
}

double		deg_to_rad(double angle)
{
	return ((M_PI * angle) / 180);
}
