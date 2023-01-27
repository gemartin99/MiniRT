/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:00:58 by smiro             #+#    #+#             */
/*   Updated: 2023/01/20 15:01:00 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

t_vector	*cy_normal(t_cy *cylinder, t_point inter)
{
	t_vector	*normal;
	t_vector	temp;
	t_vector	temp2;
	float		dn;

	temp = v_minus(&inter, cylinder->point);
	dn = v_dot(*cylinder->vector, temp);
	temp2 = v_mult(cylinder->vector, dn);
	temp = v_minus(&temp, &temp2);
	normal = v_normalized(&temp, 0);
	return (normal);
}

int	cy_caps(t_cy	*cylinder, t_intersection	*i, float *n)
{
	t_intersection	*tempi;
	int				res;

	res = 0;
	tempi = new_cpy(i, sizeof(t_intersection));
	tempi->t = i->t;
	tempi->ray = new_cpy(i->ray, sizeof(t_ray)
			+ sizeof(t_vector) + sizeof(t_point));
	res += cylinder->bottomcap->intx(tempi, cylinder->bottomcap);
	res += cylinder->topcap->intx(tempi, cylinder->topcap);
	if (tempi->t > n[0] && tempi->t > n[1])
	{
		free(tempi->ray);
		free(tempi);
		return (0);
	}
	i->t = tempi->t;
	i->shape = tempi->shape;
	free(tempi->ray);
	free(tempi);
	return (res);
}

int	cy_inter(t_intersection *i, t_obj	*o)
{
	float		n[4];
	t_cy		*cylinder;
	float		dotp[2];
	t_vector	origin;
	float		t;

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
	n[3] = v_dot(*i->ray->direction, *cylinder->vector) * n[0] + v_dot(origin, *cylinder->vector);
	if (n[3] <= 0 || n[3] >= cylinder->hgt)
	{
		n[2] = v_dot(*i->ray->direction, *cylinder->vector) * n[1] + v_dot(origin, *cylinder->vector);
		i->t = t;
		if ((n[2] < 0 && n[3] < 0) || (n[2] > cylinder->hgt && n[3] > cylinder->hgt))
				return (0);
		return (cy_caps(cylinder, i, n));
	}
	i->shape = o;
	return (1);
}

int	cy_doesinter(t_intersection *i, t_obj	*o)
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
	if (n[3] <= 0 || n[3] >= cylinder->hgt)
	{
		n[2] = v_dot(*i->ray->direction, *cylinder->vector) * n[0] + v_dot(origin, *cylinder->vector);
		n[3] = v_dot(*i->ray->direction, *cylinder->vector) * n[1] + v_dot(origin, *cylinder->vector);
		i->t = t;
		if ((n[2] < 0 && n[3] < 0) || (n[2] > cylinder->hgt && n[3] > cylinder->hgt))
			return (0);
		return (cy_caps(cylinder, i, n));
	}
	return (1);
}
