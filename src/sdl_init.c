/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:16:47 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/19 20:18:53 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

void		ft_sdl_init(t_sdls *app)
{
	int		x;
	int		y;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		err_sdl(ERR_INIT);

	cn_create_canvas(&(app->canvas));
	SDL_GetWindowPosition(app->canvas.wn.win, &x, &y);
	tb_create_toolbox(&(app->toolbox), x - CN_WIDTH / 2 - TB_WIDTH, y - CN_HEIGHT / 2 - TB_HEIGHT);
	app->flags.running = true;
    //printf("sprite: %p\n", win->buttons->sprite);
}
