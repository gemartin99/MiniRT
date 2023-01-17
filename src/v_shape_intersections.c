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

int	pl_inter(t_intersection *i, t_obj	*o)
{
	float	dn;
	float	xv;
	float	t;
	t_pl	*plane;
	
	plane = new_cpy(o->elem, sizeof(t_pl));
	dn = v_dot(*i->ray->direction, *plane->vector);
	if (!dn)
	{
		free(plane);
		return (0);
	}
	xv = v_dot(v_minus(i->ray->origin, plane->point), *plane->vector) * -1;
	if ((dn < 0 && xv > 0) || (dn > 0 && xv < 0))
	{
		free(plane);
		return (0);
	}
	t = xv / dn;
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
	
	plane = new_cpy(o->elem, sizeof(t_pl));
	dn = v_dot(*i->ray->direction, *plane->vector);
	if (!dn)
	{
		free(plane);
		return (0);
	}
	xv = v_dot(v_minus(i->ray->origin, plane->point), *plane->vector) * -1;
	if ((dn < 0 && xv > 0) || (dn > 0 && xv < 0))
	{
		free(plane);
		return (0);
	}
	t = xv / dn;
	free(plane);
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
	*local = v_minus(local, sphere->point);		
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
	*local = v_minus(local, sphere->point);		
	n[0] = v_len2(i->ray->direction);
	n[1] = 2 * v_dot(*(i->ray->direction), *(local));
	n[2] = v_len2(local) - sqr(sphere->dia / 2);
	free(local);
	if (cuadratic(i, n) == -1)
		return (0);
	return (1);
}

int	cy_caps(t_cy	*cylinder, t_intersection	*i, float dn)
{
	t_point	p1;
	// t_point	p2;
	float		t;

	p1 = v_minus(i->ray->origin, cylinder->point);
	t = v_dot(p1, *cylinder->vector) / dn;
	if (t <= RAY_T_MIN || t >= i->t)
		return (-1);
	i->t = t;
	// p2 = v_mult(cylinder->vector, cylinder->hgt);
	// p2 = v_sum(&p2, &p1);
	// t = v_dot(p2, v2)
	return (1);
}

// int	cy_inter(t_intersection *i, t_obj	*o)
// {
// 	float	n[4];
// 	t_cy	*cylinder;
// 	t_vector	origin[2];
// 	t_ray	localray;
// 	float	t;

// 	t = i->t;
// 	cylinder = o->elem;
// 	cylinder->vector = v_normalized(cylinder->vector, 1);
// 	origin[0] = v_minus(i->ray->origin, cylinder->point);
// 	localray.origin = v_cross(*cylinder->vector, origin[0]);
// 	localray.origin = v_cross(*localray.origin, *cylinder->vector);
// 	localray.direction = v_cross(*cylinder->vector, *i->ray->direction);
// 	localray.direction = v_cross(*localray.direction, *cylinder->vector);
// 	n[0] = v_len2(localray.direction);
// 	n[1] = 2 * v_dot(*localray.origin, *localray.direction);
// 	n[2] = v_len2(localray.origin) - sqr(cylinder->dia / 2);
// 	if (cuadratic(i, n) == -1)
// 		return (0);
// 	origin[0] = v_mult(i->ray->direction, i->t);
// 	origin[0] = v_sum(&origin[0], i->ray->origin);
// 	origin[1] = v_minus(&origin[0], cylinder->point);
// 	if (v_dot(origin[1], *cylinder->vector) < 0)
// 	{
// 		// if (cy_caps(cylinder, i, n[3]) == -1)
// 		// {
// 			i->t = t;
// 			return (0);
// 		// }
// 	}
// 	origin[1] = v_mult(cylinder->vector, cylinder->hgt);
// 	origin[1] = v_sum(&origin[1], cylinder->point);
// 	origin[1] = v_minus(&origin[0], &origin[1]);
// 	if (v_dot(origin[1], *cylinder->vector) > 0)
// 	{
// 		i->t = t;
// 		return (0);
// 	}
// 	i->shape = o;
// 	return (1);
// }

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
	origin = v_minus(i->ray->origin, cylinder->point);
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
		// if (cy_caps(cylinder, i, n[3]) == -1)
		// {
			i->t = t;
			return (0);
		// }
	}
	i->shape = o;
	return (1);
}
