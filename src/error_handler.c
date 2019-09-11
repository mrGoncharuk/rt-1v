/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:20:36 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/11 17:53:36 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	err_show(const char *where, const char *msg)
{
	ft_putstr(where);
	ft_putendl(msg);
}

int		err_sdl(int err_code)
{
	if (err_code == ERR_INIT)
		err_show("Could not initialize SDL: ", SDL_GetError());
	else if (err_code == ERR_WIN_CREATE)
		err_show("Could not create window: ", SDL_GetError());
	else if (err_code == ERR_RENDERER_CREATE)
		err_show("Could not create renderer: ", SDL_GetError());
	else if (err_code == ERR_IMG_LOAD)
		err_show("Unable to load image: ", SDL_GetError());
	exit(0);
	return (1);
}

int		err_sdl_load(int err_code, const char *path)
{
	if (err_code == ERR_IMG_LOAD)
	{
		err_show("Unable to load image: ", SDL_GetError());
		err_show("File path: ", path);
	}
	else if (err_code == ERR_CREATE_TEX_FROM_SURF)
	{
		err_show("Unable to create texture: ", SDL_GetError());
		err_show("File path: ", path);
	}
	return (0);
}
