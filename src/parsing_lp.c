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

static void check_ta(char *s, t_mrt *mrt)
{
	char **nums;
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == '.')
			exit_error("ERROR\nCARACTER INCORRECTO", 1);
	i = 0;
	nums = ft_split(s, ',');
	if (!nums)
		exit_error("Error malloc", 5);
	while (nums[i])
		i++;
	if (i != 3)
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	mrt->lp->rgb = init_rgb(ft_atoi(nums[0]), ft_atoi(nums[1]), ft_atoi(nums[2]));
	i = -1;
	while (nums[++i])
		free(nums[i]);
	free(nums);
	if ((mrt->lp->rgb->r < 0 || mrt->lp->rgb->r > 255)
		|| (mrt->lp->rgb->g < 0 || mrt->lp->rgb->g > 255)
		|| (mrt->lp->rgb->b < 0 || mrt->lp->rgb->b > 255))
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
}

static void check_sa(char *s)
{
	int i;

	i = -1;
	if (ft_strlen(s) == 1 && ft_isdigit(s[0]) != 0)
		return ;
	check_point(s);
	while(s[++i])
	{
		if (ft_isdigit(s[i]) == 0 && s[i] != '.')
			exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	}
}

static void check_fa(char *s, t_mrt *mrt)
{
	char **nums;
	int i;

	nums = ft_split(s, ',');
	if (!nums)
		exit_error("Error malloc", 6);
	i = -1;
	while (nums[++i])
	{
		check_less(nums[i]);
		check_point(nums[i]);
	}
	if (i != 3)
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	mrt->lp->lpoint = init_point(ft_atof(nums[0]), ft_atof(nums[1]), ft_atof(nums[2]));
	i = -1;
	while (nums[++i])
		free(nums[i]);
	free(nums);
	//printf("x%f y%f z%f\n", mrt->lp->lpoint->x, mrt->lp->lpoint->y, mrt->lp->lpoint->z);
}

void parsing_lp(char **argv, int argc, t_mrt *mrt)
{
	if (argc != 4)
		exit_error("ERROR\nC CON MAS ARGUMENTOS DE LOS INDICADOS", 1);
	check_fa(argv[1], mrt);
	check_sa(argv[2]);
	mrt->lp->brt = ft_atof(argv[2]);
	if (mrt->lp->brt > 1 || mrt->lp->brt < 0)
		exit_error("ERROR\nPARAMETRO INCORRECTO AL\n", 1);
	if (ft_strlen(argv[3]) > 12)
		exit_error("ERROR\nARGUMENTO CON DEMASIADOS CARACTERES\n", 1);
	check_ta(argv[3], mrt);
}