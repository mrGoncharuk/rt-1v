/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 16:18:49 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/22 20:49:36 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

Uint32	rt_channel_color_to_uint(t_channel color)
{
	Uint32	color_hex;

	color_hex = 0;
	color_hex += (Uint32)color.r << 16;
	color_hex += (Uint32)color.g << 8;
	color_hex += (Uint32)color.b;
	return (color_hex);
}
