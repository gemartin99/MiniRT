/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:58:56 by smiro             #+#    #+#             */
/*   Updated: 2023/01/03 12:58:58 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

#include "minirt.h"

# define RAY_T_MAX 1.0e30
# define RAY_T_MIN 0.0001

typedef struct s_ray
{
	//t_point		origin;
	//t_vector	direction;
	float			t_max;
} 					t_ray;

typedef struct s_intersection
{
	//t_ray	ray;
	float	t;
	//t_obj	shape;
}						t_intersection;

typedef struct s_perspective
{
	//t_point		origin;
	//t_vector	forward;
	//t_vector	up;
	//t_vector	rigth;
	float			h;
	float			w;
}						t_perpective;

#endif
