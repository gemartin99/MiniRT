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

int	cuadratic(t_intersection *i, float *n)
{
	int	t[2];
	float discriminant;

	discriminant = sqr(n[1]) - 4 * n[0] * n[2];
	if (discriminant < 0)
		return (-1);
	t[0] = (-n[1] - sqrt(discriminant)) / (2 * n[0]);
	t[1] = (-n[1] + sqrt(discriminant)) / (2 * n[0]);
	if (t[0] > RAY_T_MIN && t[0] < i->t && t[0] < t[1])
		i->t = t[0];
	else if (t[1] > RAY_T_MIN && t[1] < i->t)
		i->t = t[1];
	else
		return (-1);
	return (0);
}

///BORRAR

void	printv(t_point *temp)
{
	printf("X=%f, Y=%f, Z=%f\n", temp->x, temp->y, temp->z);
}

t_vector	*pl_normal(t_vector *vector)
{
	t_vector	*normal;
	t_vector	*temp;

	temp = v_cross(vector2(0, 1), *vector);
	normal = v_cross(*vector, *temp);
	free(temp);
	v_normalize(&normal);
	return (normal);
}

t_vector	*cy_normal(t_cy *cylinder, t_point inter)
{
	t_vector	*normal;
	t_vector	temp;
	t_vector	temp2;
	float			dn;

	temp = v_minus(&inter, cylinder->point);
	dn = v_dot(*cylinder->vector, temp);
	temp2 = v_mult(cylinder->vector, dn);
	temp = v_minus(&temp, &temp2);
	normal = v_normalized(&temp, 0);
	return (normal);
}

t_vector	*get_normal(t_intersection *i)
{
	t_cy	*shape;
	t_vector	temp;

	shape = i->shape->elem;
	if (i->shape->id == PL)
		return (pl_normal(shape->vector));
	else if (i->shape->id == CY)
		return (cy_normal(shape, i_position(*i)));
	temp = i_position(*i);
	temp = v_minus(&temp, shape->point);
	return (v_normalized(&temp, 0));
}

int	pl_inter(t_intersection *i, t_obj	*o)
{ 
	float	dn;
	float	xv;
	float	t;
	t_pl	*plane;
	t_vector *normal;
	
	plane = new_cpy(o->elem, sizeof(t_pl));
	normal = pl_normal(plane->vector);
	dn = v_dot(*i->ray->direction, *normal);
	if (!dn)
	{
		free(normal);
		free(plane);
		return (0);
	}
	xv = v_dot(v_minus(plane->point, i->ray->origin), *normal) * -1;
	if ((dn < 0 && xv > 0) || (dn > 0 && xv < 0))
	{
		free(normal);
		free(plane);
		return (0);
	}
	t = xv / dn;
	free(normal);
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
	float	xv;
	float	t;
	t_pl	*plane;
	t_vector *normal;
	
	plane = new_cpy(o->elem, sizeof(t_pl));
	normal = pl_normal(plane->vector);
	dn = v_dot(*i->ray->direction, *normal);
	if (!dn)
	{
		free(normal);
		free(plane);
		return (0);
	}
	xv = v_dot(v_minus(plane->point, i->ray->origin), *normal) * -1;
	if ((dn < 0 && xv > 0) || (dn > 0 && xv < 0))
	{
		free(normal);
		free(plane);
		return (0);
	}
	t = xv / dn;
	free(plane);
	free(normal);
	if (t <= RAY_T_MIN || t >= i->t)
		return (0);
	return (1);
}

int	sp_inter(t_intersection *i, t_obj	*o)
{
	t_vector	*local;
	float	n[3];
	t_sp	*sphere;

	sphere = o->elem;
	local = new_cpy(i->ray->origin, sizeof(t_point));
	*local = v_minus(sphere->point, local);
	n[0] = v_len2(i->ray->direction);
	n[1] = 2 * v_dot(*(i->ray->direction), *(local));
	n[2] = v_len2(local) - sqr(sphere->dia / 2);
	free(local);
	if (cuadratic(i, n) == -1)
		return (0);
	i->shape = o;
	return (1);
}

int	sp_doesinter(t_intersection *i, t_obj	*o)
{
	t_vector	*local;
	float	n[3];
	t_sp	*sphere;

	sphere = o->elem;
	local = new_cpy(i->ray->origin, sizeof(t_point));
	*local = v_minus(sphere->point, local);
	n[0] = v_len2(i->ray->direction);
	n[1] = 2 * v_dot(*(i->ray->direction), *(local));
	n[2] = v_len2(local) - sqr(sphere->dia / 2);
	free(local);
	if (cuadratic(i, n) == -1)
		return (0);
	return (1);
}

int	cy_caps(t_cy	*cylinder, t_intersection	*i)
{
	t_obj	*tempobj;
	t_pl	*pl;
	t_vector	temp;

	tempobj = new_calloc(sizeof(t_obj), 1, 98);
	tempobj->intx = &pl_inter;
	tempobj->doesintx = &pl_doesinter;
	pl = new_calloc(sizeof(t_pl), 1, 76);
	pl->rgb = new_cpy(cylinder->rgb, sizeof(t_rgb));
	pl->point = new_cpy(cylinder->point, sizeof(t_rgb));
	temp = v_mult(cylinder->vector, -1);
	pl->vector = v_normalized(&temp, 0);
	tempobj->elem = pl;
	if (tempobj->intx(i, tempobj))
		return (1);
	return (-1);
}

int	cy_inter(t_intersection *i, t_obj	*o)
{
	float	n[4];
	t_cy	*cylinder;
	float	dotp[2];
	t_vector	origin;
	float	t;

	t = i->t;
	cylinder = o->elem;
	cylinder->vector = v_normalized(cylinder->vector, 1);
	origin = v_minus(cylinder->point, i->ray->origin);
	dotp[0] = v_dot(*i->ray->direction, *cylinder->vector);
	dotp[1] = v_dot(*cylinder->vector, origin);
	n[0] = v_len2(i->ray->direction) - sqr(dotp[0]);
	n[1] = 2 * (v_dot(*i->ray->direction, origin) - dotp[0] * dotp[1]);
	n[2] = v_len2(&origin) - sqr(v_dot(origin, *cylinder->vector)) - sqr(cylinder->dia / 2);
	if (cuadratic(i, n) == -1)
		return (0);
	n[3] = v_dot(*i->ray->direction, *cylinder->vector) * i->t + v_dot(origin, *cylinder->vector);
	if ((n[3] < 0 || n[3] > cylinder->hgt) && n[3] != 0)
	{
		// if (cy_caps(cylinder, i) == -1)
		// {
			i->t = t;
			return (0);
		// }
	}
	i->shape = o;
	return (1);
}
