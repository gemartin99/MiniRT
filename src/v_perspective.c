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

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

t_perpective	*new_perp(t_cam *cam)
{
	t_perpective	*new;

	new = new_calloc(sizeof(t_perpective), 1, 25);
	new->forward = v_normalized(cam->vector, 0);
	new->rigth = v_cross(*new->forward, vector2(0, 1));
	new->up = v_cross(*new->forward, *new->rigth);
	new->h = tan(cam->fov * M_PI / 180);
	new->w = new->h * ((float) W / (float)H);
	new->origin = new_calloc(sizeof(t_point), 1, 27);
	new->origin = ft_memcpy(new->origin, cam->pov, sizeof(t_point));
	return (new);
}

t_ray	*makeray(t_perpective *pctve, t_vector point)
{
	t_ray	*new;
	t_point	temp;
	t_point	temp2;

	new = new_calloc(sizeof(t_ray), 1, 22);
	temp = v_mult(pctve->rigth, point.x * pctve->w);
	temp = v_sum(pctve->forward, &temp);
	temp2 = v_mult(pctve->up, point.y * pctve->h);
	temp = v_sum(&temp, &temp2);
	new->direction = v_normalized(&temp, 0);
	new->origin = new_calloc(sizeof(t_point), 1, 27);
	new->origin = ft_memcpy(new->origin, pctve->origin, sizeof(t_point));
	new->t_max = RAY_T_MAX;
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
