/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:26:49 by smiro             #+#    #+#             */
/*   Updated: 2023/01/03 16:26:52 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_perpective	new_perp(t_cam *cam)
{
	t_perpective new;
	t_vector	v;

	v = *cam->vector;
	v = v_minus(&v, &cam->pov);
	new.forward = v_normalized(&v);
	new.rigth = v_cross(&new.forward, vector2(0, 0));
	new.up = v_cross(&new.rigth, new.forward);
	new.h = tan(cam->fov);
	new.w = new.h * ((float)W/(float)H);
	return (new);
}

t_ray	makeray(t_perpective pctve, t_vector point)
{
	t_ray	new;
	t_vector	direction;

	direction = v_sum(v_sum(pctve.forward, 
				v_mult(pctve.rigth, pctve.w * point.x)), 
				v_mult(pctve.up, pctve.h * point.y));
	new.direction = direction;
	new.origin = pctve.origin;
	new.t_max = RAY_T_MAX;
	return (new);
}

t_vector	vector2(float x, float y)
{
	t_vector	new;

	new.x = x;
	new.y = y;
	new.z = 0;
	return (new);
}