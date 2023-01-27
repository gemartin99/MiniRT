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

#ifndef MINIRT_H
# define MINIRT_H

# include "defines.h"
# include "vector.h"

void			start(t_mrt *mrt);

int				close_program(t_mrt *mrt);
int				key_hook(int key, t_mrt *mrt);

//PARSING

void			parsing(char *file_name, t_mrt *mrt);
void			parsing_la(char **argv, int argc, t_mrt *mrt);
void			parsing_cam(char **argv, int argc, t_cam *cam);
void			parsing_lp(char **argv, int argc, t_lp *lp);
void			parsing_sp(char **argv, int argc, t_sp *sp);
void			parsing_pl(char **argv, int argc, t_pl *pl);
void			parsing_cy(char **argv, int argc, t_cy *cy);

//INIT

void			init_al(t_mrt *mrt, char **line);
void			init_cam(t_cam **cam, char **line);
void			init_lp(t_lp **lp, char **line);
t_img			*new_img(t_mlx	*mlx);
void			init_newobj(t_obj **obj, char **line, int id);
void			check_less(char *s);
void			check_point(char *s);
t_rgb			*init_rgb(int r, int g, int b);
t_point			*init_point(float x, float y, float z);
t_sp			*init_sp(char **line);
t_pl			*init_pl(char **line);
t_cy			*init_cy(char **line);
void			init_mlx(t_mrt	*mrt);
void			put_func(t_obj **obj);

//VECTORS

void			v_normalize(t_point **v);
t_point			*v_normalized(t_point *v, int control);
t_point			*v_cross(t_point v1, t_point v2);
float			v_dot(t_point v1, t_point v2);
float			sqr(float n);
float			v_len(t_point	*v);
float			v_len2(t_point	*v);
t_point			v_sum(t_point *v1, t_point *v2);
t_point			v_minus(t_point	*v1, t_point *v2);
t_point			v_mult(t_point	*v1, float n);
t_point			v_div(t_point	*v1, t_point *v2);
t_ray			*makeray(t_perpective *pctve, t_vector point);
int				obj_int(t_intersection *i, t_obj **o);
int				obj_doesint(t_intersection *i, t_obj **o);
int				sp_inter(t_intersection *i, t_obj	*o);
int				sp_doesinter(t_intersection *i, t_obj	*o);
int				pl_inter(t_intersection *i, t_obj	*o);
int				cy_inter(t_intersection *i, t_obj	*o);
int				pl_doesinter(t_intersection *i, t_obj	*o);
t_vector		vector2(float x, float y);
t_perpective	*new_perp(t_cam *cam);
t_point			r_calculate(t_ray ray, float t);
t_point			i_position(t_intersection i);
t_vector		*pl_normal(t_vector *vector);
t_vector		*cy_normal(t_cy *cylinder, t_point inter);
t_vector		*get_normal(t_intersection *i);
int				cuadratic(t_intersection *i, float *n);
int				cy_doesinter(t_intersection *i, t_obj	*o);

//COLOR & LIGHT

t_rgb			*lightray(t_intersection *i, t_mrt *mrt, t_cy *shape);
int				create_trgb(t_rgb	*color);
t_rgb			*intensity(t_rgb *c, float intensity);
t_rgb			*color_mult(t_rgb *c1, t_rgb *c2);
t_rgb			*color_sum(t_rgb *c1, t_rgb *c2);
int				is_shadow(t_intersection *i, t_lp *lp, t_obj *o);

//UTILS

int				check_wrong_char(char *s);
int				ft_isspace(char *s);
void			exit_error(char *str, int n);
float			ft_atof(char *n);
t_obj			*ft_last(t_obj **obj);
t_lp			*ft_last2(t_lp **lp);
t_cam			*ft_last3(t_cam **cam);
void			*new_calloc(size_t n, size_t size, int error);
void			*new_cpy(void *src, size_t size);

#endif
