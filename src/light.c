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

static t_rgb	*specular(t_intersection *i, t_lp *lp)
{
	float		dp;
	t_vector	ip;
	t_vector	*io;
	t_vector	*normal;
	t_rgb		color;

	color = (t_rgb){200, 200, 200};
	ip = i_position(*i);
	normal = get_normal(i);
	ip = v_minus(lp->lpoint, &ip);
	ip = v_sum(&ip, i->ray->direction);
	io = v_normalized(&ip, 0);
	dp = v_dot(*normal, *io);
	free(io);
	free(normal);
	if (dp < 0)
		dp = 0;
	return (intensity(&color, pow(dp, 100)));
}

static float	light_dp(t_intersection *i, t_lp *lp)
{
	float		dp;
	t_vector	ip;
	t_vector	*io;
	t_vector	*normal;

	ip = i_position(*i);
	normal = get_normal(i);
	ip = v_minus(lp->lpoint, &ip);
	io = v_normalized(&ip, 0);
	dp = v_dot(*normal, *io);
	free(io);
	free(normal);
	if (dp < 0)
		dp = -dp;
	return (dp);
}

t_rgb	*lightray(t_intersection *i, t_mrt *mrt, t_cy *shape)
{
	t_lp	*temp;
	t_rgb	*color[2];
	float	dp;
	t_rgb	*intsy;
	int		l;
	int 	s;

	temp = mrt->lp;
	l = 0;
	s = 0;
	color[0] = color_sum(new_cpy(shape->rgb, sizeof(t_rgb)), new_cpy(mrt->al->rgb, sizeof(t_rgb)));
	color[1] = intensity(shape->rgb, 0);
	while (temp)
	{
		dp = light_dp(i, temp);
		intsy = intensity(temp->rgb, temp->brt * dp);
		if (dp <= 0)
		{
			free(intsy);
			return (color[0]);
		}
		if (is_shadow(i, temp, mrt->obj))
		{
			if (!l && !s)
			{
				color[1] = color_mult(mrt->al->rgb, intsy);
				s = 1;
			}
		}
		else
		{
			l = 1;
			color[1] = color_sum(color_sum(color_mult(intsy, color[0]), specular(i, temp)), color[1]);
		}
		free(intsy);
		temp = temp->next;
	}
	return (color[1]);
}
