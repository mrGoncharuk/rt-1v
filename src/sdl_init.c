/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmolyboh <dmolyboh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:16:47 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/20 10:15:06 by dmolyboh         ###   ########.fr       */
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
	app->flags.state_changed = true;
	app->flags.running = true;
	app->flags.rot_x = false;
	app->flags.rot_y = false;
	app->flags.rot_x_min = false;
	app->flags.rot_y_min = false;
	app->flags.left = false;
	app->flags.right = false;
	app->flags.forward = false;
	app->flags.backward = false;
	app->flags.sepia = false;
	app->flags.white = false;
	app->flags.gray = false;
	app->flags.cartoon = false;
	app->flags.aliasing = false;
	app->flags.clear = false;
}
