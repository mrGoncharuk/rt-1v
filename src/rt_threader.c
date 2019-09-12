/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_threader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 19:59:27 by mhonchar          #+#    #+#             */
/*   Updated: 2019/09/12 20:59:56 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rt_thread_tracer(t_rt *rt)
{
	pthread_t	pt[THREADS_AMOUNT];
	t_rt		rts[THREADS_AMOUNT];
	int			i;

	i = 0;
	while (i < THREADS_AMOUNT)
	{
		ft_memcpy((void *)(rts + i), (void *)rt, sizeof(t_rt));
		rts[i].x_start = (CN_HEIGHT / THREADS_AMOUNT) * i - CN_HEIGHT / 2;
		rts[i].x_end = (CN_HEIGHT / THREADS_AMOUNT) * (i + 1) - CN_HEIGHT / 2;
		i++;
	}
	i = -1;
	while (++i < THREADS_AMOUNT)
		pthread_create((pt + i), NULL, rt_threaded_loop, (void *)(rts + i));
	i = -1;
	while (++i < THREADS_AMOUNT)
		pthread_join(pt[i], NULL);
}
