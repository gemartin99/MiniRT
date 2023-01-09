/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:25:03 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 11:25:04 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <mlx.h>
# include	<stdio.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<fcntl.h>
# include	<limits.h> 
# include <math.h>
# include "vector.h"

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}						t_point;

typedef t_point	t_vector;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}						t_rgb;

//Luz de ambiente:
//Ratio de luz de ambiente rango[0.0,1.0],
//colores RGB
typedef struct s_al
{
	float	ratio;
	t_rgb	*rgb;
}						t_al;

//Camara:
//Cordenadas del punto de vista,
//Vecror de orientación normalizado para cada eje rango[-1,1],
//Campo de vision rango [0,180]
typedef struct s_cam
{
	t_point	*pov;
	t_point	*vector;
	int		fov;
}						t_cam;

//Luz:
//Punto de luz,
//Brillo rango[0.0,1.0],
//colores RGB
typedef struct s_lp
{
	t_point	*lpoint;
	float	brt;
	t_rgb	*rgb;
}							t_lp;

//Esfera:
//Coordenadas,
//Diametro de la esfera,
//colores RGB
typedef struct sp
{
	t_point	*point;
	float	dia;
	t_rgb	*rgb;
}							t_sp;

//Plano:
//Coordenadas,
//Vector de dirección 3D normalizado rango [-1,1],
//colores RGB
typedef struct s_pl
{
	t_point	*point;
	t_point	*vector;
	t_rgb	*rgb;
}							t_pl;

//Cilindro:
//Coordenadas,
//Vector de dirección 3D normalizado rango [-1,1],
//Diametro del cilindro,
//Altura del cilindro,
//colores RGB
typedef struct s_cy
{
	t_point	*point;
	t_point	*vector;
	float	dia;
	float	hgt;
	t_rgb	*rgb;
}							t_cy;

//Objetos:
//Identificador,
//puntero al elemento,
//puntero al siguiente objetos si hay mas
typedef struct s_obj
{
	char			id;
	void			*elem;
	struct s_obj	*next;
	int				(*intx)(t_intersection *i, struct s_obj *elem);
	int				(*doesintx)(t_intersection *i, struct s_obj *elem);
}							t_obj;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}						t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}						t_img;

typedef struct s_mrt
{
	t_mlx	*mlx;
	t_img	*img;
	t_al	*al;
	t_cam	*cam;
	t_lp	*lp;
	t_obj	*obj;
}						t_mrt;

# define H 1080
# define W 1920

# define SP 0
# define PL 1
# define CY 2

#endif
