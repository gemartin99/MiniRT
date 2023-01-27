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

void	check_ray_color(t_rgb **color, t_point *temp2, t_mrt *mrt, t_rgb *intsy)
{
	t_rgb	*temp;

	if (!temp2->z && !temp2->y)
	{
		temp = color_mult(mrt->al->rgb, intsy);
		free(color[1]);
		color[1] = temp;
		temp2->y = 1;
	}
}

t_rgb	*ray_color(t_rgb *c[2], t_intersection *i, t_mrt *mrt, t_point *temp2)
{
	t_lp	*temp;
	t_rgb	*intsy;

	temp = mrt->lp;
	while (temp)
	{
		temp2->x = light_dp(i, temp);
		intsy = intensity(temp->rgb, temp->brt * temp2->x);
		if (temp2->x <= 0)
		{
			free(intsy);
			return (new_cpy(c[0], sizeof(t_rgb)));
		}
		if (is_shadow(i, temp, mrt->obj))
			check_ray_color(c, temp2, mrt, intsy);
		else
		{
			temp2->z = 1;
			c[1] = color_sum(color_sum(color_mult(intsy,
							c[0]), specular(i, temp)), c[1]);
		}
		free(intsy);
		temp = temp->next;
	}
	return (new_cpy(c[1], sizeof(t_rgb)));
}

t_rgb	*lightray(t_intersection *i, t_mrt *mrt, t_cy *shape)
{
	t_rgb	*color[2];
	t_rgb	*res;
	t_point	*temp2;

	temp2 = init_point(0, 0, 0);
	color[0] = color_sum(new_cpy(shape->rgb, sizeof(t_rgb)),
			new_cpy(mrt->al->rgb, sizeof(t_rgb)));
	color[1] = intensity(shape->rgb, 0);
	res = ray_color(color, i, mrt, temp2);
	free(color[0]);
	free(color[1]);
	free(temp2);
	return (res);
}
