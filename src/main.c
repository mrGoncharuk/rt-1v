/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:36:52 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/20 18:03:49 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	ft_check_input(int argc)
{
	if (argc != 2)
	{
		ft_putendl("Usage: ./RTv1 scenes/[scene_name]");
		return (false);
	}
	return (true);
}

int		main(int argc, char **argv)
{
	t_sdls		app;

	if (ft_check_input(argc))
	{
		app.fname = argv[1];
		ft_sdl_init(&app);
		ft_mainloop(&app);
		ft_sdl_clean(&app);
	}
	return (0);
}
