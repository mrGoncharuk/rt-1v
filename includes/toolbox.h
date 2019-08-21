/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 19:20:35 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/19 20:10:37 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLBOX_H
# define TOOLBOX_H

# include "libui.h"

# define TB_WIDTH 200
# define TB_HEIGHT 600
# define TB_BTNS 1

typedef struct	s_toolbox
{
	t_window	wn;
	t_flags		*flags;
	t_lbutton	buttons[TB_BTNS];
}				t_toolbox;

void		tb_create_toolbox(t_toolbox *tb, int x, int y);
void		tb_destroy_toolbox(t_toolbox *tb);

#endif