/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tb_toolbox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:11:48 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/19 20:22:56 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toolbox.h"

// void		tb_load_butons(t_toolbox *tb)
// {
	
// }

void		tb_create_toolbox(t_toolbox *tb, int x, int y)
{
	wn_init(&(tb->wn), "ToolBox",  (SDL_Rect) {x, y, TB_WIDTH, TB_HEIGHT}, SDL_WINDOW_SHOWN);
	// tb_load_butons(tb);
}

void		tb_destroy_toolbox(t_toolbox *tb)
{
	wn_destroy(&(tb->wn));
}