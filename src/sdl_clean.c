/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:51:23 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/19 18:21:40 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "guimp.h"

void		ft_sdl_clean(t_sdls *app)
{
    cn_destroy_canvas(&(app->canvas));
    tb_destroy_toolbox(&(app->toolbox));
    SDL_Quit();
}