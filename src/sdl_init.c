/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:16:47 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 19:15:33 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_sdl_init(t_sdls *app)
{
	int		x;
	int		y;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		err_sdl(ERR_INIT);
	cn_create_canvas(&(app->canvas));
	SDL_GetWindowPosition(app->canvas.wn.win, &x, &y);
	app->flags.running = true;
	app->flags.rot_x = false;
	app->flags.rot_y = false;
	app->flags.state_changed = true;
}
