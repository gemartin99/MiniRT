/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartin <gemartin@student.42barcelona>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:07:37 by gemartin          #+#    #+#             */
/*   Updated: 2023/01/02 13:07:39 by gemartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

static void	check_fo(char *s, t_pd *pd)
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
	pd->rgb = init_rgb(ft_atoi(n[0]), ft_atoi(n[1]), ft_atoi(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
	if ((pd->rgb->r < 0 || pd->rgb->r > 255)
		|| (pd->rgb->g < 0 || pd->rgb->g > 255)
		|| (pd->rgb->b < 0 || pd->rgb->b > 255))
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
}

static void	check_ta(char *s, t_pd *pd)
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
	pd->scalar = ft_atof(s);
}

static void	check_sa(char *s, t_pd *pd)
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
		exit_error("ERROR\nPARAMETROS VECTOR INCORRECTOS", 1);
	pd->vector = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
	if ((pd->vector->x > 1 || pd->vector->x < -1)
		|| (pd->vector->y > 1 || pd->vector->y < -1)
		|| (pd->vector->z > 1 || pd->vector->z < -1))
		exit_error("ERROR\nPARAMETROS VECTOR INCORRECTOS", 1);
	pd->vector = v_normalized(pd->vector, 1);
}

static void	check_fa(char *s, t_pd *pd)
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
	pd->point = init_point(ft_atof(n[0]), ft_atof(n[1]), ft_atof(n[2]));
	i = -1;
	while (n[++i])
		free(n[i]);
	free(n);
}

void	parsing_pd(char **argv, int argc, t_pd *pd)
{
	if (argc != 5)
		exit_error("ERROR\nPD CON MAS ARGUMENTOS DE LOS INDICADOS", 1);
	check_fa(argv[1], pd);
	check_sa(argv[2], pd);
	check_ta(argv[3], pd);
	check_fo(argv[4], pd);
}