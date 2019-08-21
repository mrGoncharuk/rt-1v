/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <mhonchar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 16:46:14 by mhonchar          #+#    #+#             */
/*   Updated: 2019/08/19 20:22:39 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "button.h"

SDL_Texture	*load_texture(const char *path, SDL_Renderer *renderer)
{
	SDL_Texture		*tex;
	SDL_Surface		*surf;

	surf = IMG_Load(path);
	tex = NULL;
	if (surf == NULL)
	{
		err_sdl(ERR_IMG_LOAD);
		return (NULL);
	}
	else
	{
		tex = SDL_CreateTextureFromSurface(renderer, surf);
		if (tex == NULL)
		{
			err_sdl_load(ERR_CREATE_TEX_FROM_SURF, path);
			SDL_FreeSurface(surf);
			return (NULL);
		}
		SDL_FreeSurface(surf);
	}
	return (tex);
}

void	bt_create(t_lbutton *bt, SDL_Rect r, const char *label, void (*handle_event)(SDL_Event *, t_lbutton *, t_flags *))
{
	char		*nb;
	static int	id = -1;

	if (!bt)
		return ;
	id++;
	bt->id = id;
	bt->clip_rect = r;
	bt->handle_event = NULL;
	if (label)
		bt->label = ft_strdup(label);
	else
	{
		bt->label = ft_strnew(STD_BT_LABLE_SIZE);
		ft_strcpy(bt->label, "Button ");
		nb = ft_itoa(id);
		ft_strcat(bt->label, nb);
		free(nb);
	}
	if (handle_event)
		bt->handle_event = handle_event;
	bt->is_active = false;
	bt->curr_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void	bt_load_sprites(t_lbutton *bt, const char *bt_out, const char *bt_down, SDL_Renderer *renderer)
{
	bt->sprite[BUTTON_SPRITE_MOUSE_OUT] = load_texture(bt_out, renderer);
	if (bt->sprite[BUTTON_SPRITE_MOUSE_OUT] == NULL)
		bt->sprite[BUTTON_SPRITE_MOUSE_OUT] = load_texture("res/bad_img.png", renderer);
	bt->sprite[BUTTON_SPRITE_MOUSE_DOWN] = load_texture(bt_down, renderer);
	if (bt->sprite[BUTTON_SPRITE_MOUSE_DOWN] == NULL)
		bt->sprite[BUTTON_SPRITE_MOUSE_DOWN] = load_texture("res/bad_img.png", renderer);
}

void	bt_render(t_lbutton *bt, SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, bt->sprite[bt->curr_sprite], NULL, &(bt->clip_rect));
}

void	bt_destroy(t_lbutton *bt)
{
	int		i;

	if (bt->label)
		free(bt->label);
	i = -1;
	while (++i < BUTTON_SPRITE_TOTAL)
	{
		if (bt->sprite[i])
			SDL_DestroyTexture(bt->sprite[i]);
	}
}
