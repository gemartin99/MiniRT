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

# ifndef MINIRT_H
#define MINIRT_H

#include "defines.h"

void	start(t_mrt *mrt);

int	close_program(t_mrt *mrt);
int	key_hook(int key, t_mrt *mrt);

//PARSING

void parsing(char *file_name, t_mrt *mrt);
void parsing_la(char **argv, int argc, t_mrt *mrt);
void parsing_cam(char **argv, int argc, t_mrt *mrt);
void parsing_lp(char **argv, int argc, t_mrt *mrt);
void parsing_sp(char **argv, int argc, t_sp *sp);

//INIT

void	init_al(t_mrt *mrt, char **line);
void	init_cam(t_mrt *mrt, char **line);
void	init_lp(t_mrt *mrt, char **line);
void	init_newobj(t_obj *obj, char **line, int id);
void	check_less(char *s);
void	check_point(char *s);
t_rgb	*init_rgb(int r, int g, int b);
t_point *init_point(float x, float y, float z);
t_sp	*init_sp(char **line);
t_pl	*init_pl(char **line);
t_cy	*init_cy(char **line);
void 	init_mlx(t_mrt	*mrt);

//VECTORS

void	v_normalize(t_point **v);
t_point	*v_normalized(t_point *v);
t_point *v_cross(t_point **v1, t_point **v2);
float	sqr(float n);
void	v_div(t_point	**v1, t_point **v2);
float	v_len(t_point	*v);
float	v_len2(t_point	*v);
void	v_sum(t_point **v1, t_point **v2);
void	v_minus(t_point	**v1, t_point **v2);

//UTILS

void	exit_error(char *str, int n);
float	ft_atof(char *n);
t_obj	*ft_last(t_obj **obj);

#endif
