#include "rt.h"


void	visual_effects(t_rt *rt, t_raytrace_data *flags)
{
	if (flags->effect_flags == EF_SEPIA)
		sepia_image(rt->pixels, rt->pixels);
	if (flags->effect_flags == EF_WHITE)
		white_rad(rt->pixels, rt->pixels);
	if (flags->effect_flags == EF_GRAY)
		gray_rad(rt->pixels, rt->pixels);
	if (flags->effect_flags == EF_GRAY)
		cartoon(rt->pixels, rt->pixels);
	if (flags->effect_flags == EF_ALIASING)
		anti_aliasing(rt->pixels, 1);
	// if (flags->effect_flags == EF_NONE)
	// {
	// 	app->flags.sepia = false;
	// 	app->flags.white = false;
	// 	app->flags.gray = false;
	// 	app->flags.cartoon = false;
	// 	app->flags.aliasing = false;
	// 	app->flags.clear = false;
	// }
}