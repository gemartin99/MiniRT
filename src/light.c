/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ligth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:21:05 by smiro             #+#    #+#             */
/*   Updated: 2023/01/14 17:21:07 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	printrgb(t_rgb *c, char *str)
{
	printf("%s:", str);
	printf(" R:%d, G:%d, B:%d\n", c->r, c->g, c->b);
}

static float	light_dp(t_intersection *i, t_lp *lp, t_obj *o, t_cy *shape)
{
	float		dp;
	t_vector	ip;
	t_vector	*io;
	t_vector	*vector;

	ip = i_position(*i);
	if (o->id == SP)
	{
		ip = v_minus(shape->point, &ip);
		vector = v_normalized(&ip, 0);
		ip = i_position(*i);
	}
	else
		vector = shape->vector;
	ip = v_minus(&ip, lp->lpoint);
	io = v_normalized(&ip, 0);
	dp = v_dot(*vector, *io) * -1;
	free(io);
	if (o->id == SP)
		free(vector);
	return (dp);
}

t_rgb	*lightray(t_intersection *i, t_mrt *mrt, t_cy *shape)
{
	t_lp	*temp;
	t_rgb	*color;
	float	dp;
	t_rgb	*intsy;

	(void)i;
	temp = mrt->lp;
	color = color_mult(shape->rgb, mrt->al->rgb);
	while (temp)
	{
		dp = light_dp(i, mrt->lp, i->shape, shape);
		intsy = intensity(temp->rgb, temp->brt * dp);
		if (dp <= 0)
		{
			free(intsy);
			return (color);
		}
		if (is_shadow(i, temp))
			dp = 0.01;
		color = color_sum(color, color_mult(intsy, mrt->al->rgb));
		free(intsy);
		temp = temp->next;
	}
	return (color);
}
