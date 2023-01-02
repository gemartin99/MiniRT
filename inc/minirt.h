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

void parsing(char *file_name, t_mrt *mrt);
void parsing_la(char **argv, int argc, t_mrt *mrt);

//INIT

void	init_al(t_mrt *mrt, char **line);
void	init_cam(t_mrt *mrt, char **line);
void	init_lp(t_mrt *mrt, char **line);
void	init_newobj(t_obj *obj, char **line, int id);
t_rgb	*init_rgb(int r, int g, int b);
t_sp	*init_sp(char *line);
t_pl	*init_pl(char *line);
t_cy	*init_cy(char *line);

//UTILS

void	exit_error(char *str, int n);
float	ft_atof(char *n);
t_obj	*ft_last(t_obj **obj);

#endif
