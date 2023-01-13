/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:10:06 by smiro             #+#    #+#             */
/*   Updated: 2023/01/03 14:10:09 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

///BORRAR

void	printv(t_point *temp)
{
	printf("X=%f, Y=%f, Z=%f\n", temp->x, temp->y, temp->z);
}

int	pl_inter(t_intersection *i, t_obj	*o)
{
	float	dn;
	float	t;
	t_pl	*plane;
	t_vector	origin;
	
	plane = new_cpy(o->elem, sizeof(t_pl));
	dn = v_dot(*i->ray->direction, *plane->vector);
	if (!dn)
		return (0);
	origin = v_minus(i->ray->origin, plane->point);
	t = v_dot(v_mult(&origin, -1), *plane->vector) / dn;
	free(plane);
	if (t <= RAY_T_MIN || t >= i->t)
		return (0);
	i->t = t;
	i->shape = o;
	return (1);
}

int	pl_doesinter(t_intersection *i, t_obj	*o)
{
	float	dn;
	float	t;
	t_pl	*plane;

	plane = o->elem;
	dn = v_dot(*i->ray->origin, *plane->vector);
	if (!dn)
		return (0);
	t = v_dot(v_minus(plane->point, i->ray->origin), *plane->vector);
	if (t <= RAY_T_MIN || t >= i->t)
		return (0);
	return (1);
}

int	sp_inter(t_intersection *i, t_obj	*o)
{
	t_vector	*local;
	float	n[3];
	float	discriminant;
	float	t[2];
	t_sp	*sphere;

	sphere = o->elem;
	local = new_cpy(i->ray->origin, sizeof(t_point));
	*local = v_minus(local, sphere->point);		
	n[0] = v_len2(i->ray->direction);
	n[1] = 2 * v_dot(*(i->ray->direction), *(local));
	n[2] = v_len2(local) - sqr(sphere->dia / 2);
	discriminant = sqr(n[1]) - 4 * n[0] * n[2];
	free(local);
	if (discriminant < 0)
		return (0);
	t[0] = (-n[1] - sqrt(discriminant)) / (2 * n[0]);
	t[1] = (-n[1] + sqrt(discriminant)) / (2 * n[0]);
	if (t[0] > RAY_T_MIN && t[0] < i->t)
		i->t = t[0];
	else if (t[1] > RAY_T_MIN && t[1] < i->t)
		i->t = t[1];	
	else
		return (0);
	i->shape = o;
	return (1);
}

int	sp_doesinter(t_intersection *i, t_obj	*o)
{
	t_vector	*local;
	float	n[3];
	float	discriminant;
	float	t[2];
	t_sp	*sphere;

	sphere = o->elem;
	local = new_cpy(i->ray->origin, sizeof(t_point));
	*local = v_minus(local, sphere->point);		
	n[0] = v_len2(i->ray->direction);
	n[1] = 2 * v_dot(*(i->ray->direction), *(local));
	n[2] = v_len2(local) - sqr(sphere->dia / 2);
	discriminant = sqr(n[1]) - 4 * n[0] * n[2];
	free(local);
	if (discriminant < 0)
		return (0);
	t[0] = (-n[1] - sqrt(discriminant)) / (2 * n[0]);
	t[1] = (-n[1] + sqrt(discriminant)) / (2 * n[0]);
	if (t[0] > RAY_T_MIN && t[0] < i->t)
		i->t = t[0];
	else if (t[1] > RAY_T_MIN && t[1] < i->t)
		i->t = t[1];	
	else
		return (0);
	i->shape = o;
	return (1);
}

int	cy_inter(t_intersection *i, t_obj	*o)
{
	t_ray	*localray;
	float	n[3];
	float	discriminant;
	float	t[3];
	t_cy	*cylinder;

	cylinder = o->elem;
	t_obj	*tempobj;
	
	tempobj = new_calloc(sizeof(t_obj), 1, 90);
	cylinder->vector = v_normalized(cylinder->vector);
	localray = new_cpy(i->ray, sizeof(t_ray));
	*localray->origin = v_minus(i->ray->origin, cylinder->point);
	n[0] = v_len2(i->ray->direction) - sqr(v_dot(*i->ray->direction, *cylinder->vector));
	n[1] = 2 * (v_dot(*i->ray->direction, *localray->origin) - v_dot(*i->ray->direction, *cylinder->vector) * v_dot(*localray->origin, *cylinder->vector));
	n[2] = v_len2(localray->origin) - sqr(v_dot(*localray->origin, *cylinder->vector)) - sqr(cylinder->dia / 2);
	discriminant = sqr(n[1]) - 4 * n[0] * n[2];
	if (discriminant < 0)
		return (0);
	t[0] = (-n[1] - sqrt(discriminant)) / (2 * n[0]);
	t[1] = (-n[1] + sqrt(discriminant)) / (2 * n[0]);
	if (t[1] < 0)
		return (0);
	if (t[0] > RAY_T_MIN && t[0] < i->t)
		i->t = t[0];
	else
		i->t = t[1];
	t[2] = v_dot(*i->ray->direction, *cylinder->vector) * i->t + v_dot(*localray->origin, *cylinder->vector);
	if (t[2] < 0 || t[2] > cylinder->hgt)
	{
		t[2] = v_dot(v_mult(localray->origin, -1), v_mult(cylinder->vector, -1)) / t[2];
		if (t[2] <= RAY_T_MIN || t[2] >= i->t)
			return (0);
	}
	t_point	temp2 = v_mult(cylinder->vector, cylinder->hgt);
	temp2 = v_sum(cylinder->point, &temp2);
	i->shape = o;
	return (1);
}


// int	cy_inter(t_intersection *i, t_obj	*o)
// {
// 	t_ray	*localray;
// 	float	n[3];
// 	float	discriminant;
// 	float	t[3];
// 	t_cy	*cylinder;

// 	cylinder = o->elem;
// 	cylinder->vector = v_normalized(cylinder->vector);
// 	localray = new_cpy(i->ray, sizeof(t_ray));
// 	localray->origin = v_cross(v_minus(i->ray->origin, cylinder->point), *cylinder->vector);
// 	localray->direction = v_cross(*(i->ray->direction), *cylinder->vector);
// 	n[0] = v_len2(localray->direction);
// 	n[1] = 2 * v_dot(*localray->direction, *localray->origin);
// 	n[2] = v_len2(localray->origin) - sqr(cylinder->dia / 2);
// 	discriminant = sqr(n[1]) - 4 * n[0] * n[2];
// 	if (discriminant < 0)
// 		return (0);
// 	t[0] = (-n[1] - sqrt(discriminant)) / (2 * n[0]);
// 	t[1] = (-n[1] + sqrt(discriminant)) / (2 * n[0]);
// 	if (t[1] < 0)
// 		return (0);
// 	if (t[0] > RAY_T_MIN && t[0] < i->t)
// 		i->t = t[0];
// 	else
// 		i->t = t[1];
// 	t_point temp = v_mult(i->ray->direction, i->t);
// 	temp = v_sum(i->ray->origin, &temp);
// 	temp = v_minus(&temp, cylinder->point);
// 	if (v_dot(*cylinder->vector, temp) < 0)
// 		return (0);
// 	temp = v_mult(i->ray->direction, i->t);
// 	temp = v_sum(i->ray->origin, &temp);
// 	t_point	temp2 = v_mult(cylinder->point, cylinder->hgt);
// 	temp2 = v_minus(v_cross(*cylinder->vector, temp2), cylinder->point);
// 	temp = v_minus(&temp, &temp2);
// 	if (v_dot(*cylinder->vector, temp) > 0)
// 		return (0);
// 	i->shape = o;
// 	return (1);
// }
