/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:43:42 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 12:43:45 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

static void	check_ta(char *s, t_sp *sp)
{
	char	**n;
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == '.')
			exit_error("ERROR\nCARACTER INCORRECTO", 1);
	i = 0;
	n = ft_split(s, ',');
	if (!n)
		exit_error("Error malloc", 5);
	while (n[i])
		i++;
	if (i != 3)
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	sp->rgb = init_rgb(ft_atoi(n[0]), ft_atoi(n[1]), ft_atoi(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
	if ((sp->rgb->r < 0 || sp->rgb->r > 255)
		|| (sp->rgb->g < 0 || sp->rgb->g > 255)
		|| (sp->rgb->b < 0 || sp->rgb->b > 255))
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
}

static void	check_sa(char *s, t_sp *sp)
{
	int	i;

	i = -1;
	if (ft_strlen(s) == 1 && ft_isdigit(s[0]) != 0)
		return ;
	check_point(s);
	while (s[++i])
	{
		if (ft_isdigit(s[i]) == 0 && s[i] != '.')
			exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	}
	sp->dia = ft_atof(s);
}

static void	check_fa(char *s, t_sp *sp)
{
	char	**n;
	int		i;

	n = ft_split(s, ',');
	if (!n)
		exit_error("Error malloc", 6);
	i = -1;
	while (n[++i])
	{
		check_less(n[i]);
		check_point(n[i]);
	}
	if (i != 3)
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	sp->point = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
}

void	parsing_sp(char **argv, int argc, t_sp *sp)
{
	if (argc != 4)
		exit_error("ERROR\nSP CON NUMERO DE ARGUMENTOS INCORRECTO", 1);
	check_fa(argv[1], sp);
	check_sa(argv[2], sp);
	check_ta(argv[3], sp);
}
