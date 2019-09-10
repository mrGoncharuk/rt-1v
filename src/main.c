/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:36:52 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/10 17:43:01 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "guimp.h"
#include "rt.h"

int		main(void)
{
	t_sdls		app;

	ft_sdl_init(&app);
	ft_mainloop(&app);
	// SDL_Delay(4000);
	ft_sdl_clean(&app);


    return (0);
}