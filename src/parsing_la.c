#include "minirt.h"
#include "../inc/libft/libft.h"

static int check_sa(char *s, t_mrt *mrt)
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
	mrt->al->rgb = init_rgb(ft_atoi(nums[0]), ft_atoi(nums[1]), ft_atoi(nums[2]));
	i = -1;
	while (nums[++i])
		free(nums[i]);
	free(nums);
	if ((mrt->al->rgb->r < 0 || mrt->al->rgb->r > 255)
		|| (mrt->al->rgb->g < 0 || mrt->al->rgb->g > 255)
		|| (mrt->al->rgb->b < 0 || mrt->al->rgb->b > 255))
		exit_error("ERROR\nPARAMETROS INCORRECTOS", 1);
	return (0);
}

static int check_fa(char *s)
{
	int i;

	i = -1;
	if (ft_strlen(s) == 1 && ft_isdigit(s[0]) != 0)
		return (0);
	check_point(s);
	while(s[++i])
	{
		if (ft_isdigit(s[i]) == 0 && s[i] != '.')
			exit_error("ERROR\nCARACTER INCORRECTO", 1);
	}
	return (0);
}

void parsing_la(char **argv, int argc, t_mrt *mrt)
{
	int i;

	i = -1;
	if (argc != 3)
		exit_error("ERROR\nA CON MAS ARGUMENTOS DE LOS INDICADOS", 1);
	if (ft_strlen(argv[1]) > 5 || check_fa(argv[1]) == -1)
		exit_error("ERROR\nARGUMENTO CON DEMASIADOS CARACTERES", 1);
	mrt->al->ratio = ft_atof(argv[1]);
	if (mrt->al->ratio > 1 || mrt->al->ratio < 0)
		exit_error("ERROR\nPARAMETRO INCORRECTO AL", 1);
	if (ft_strlen(argv[2]) > 12 || check_sa(argv[2], mrt) == -1)
		exit_error("ERROR\nARGUMENTO CON DEMASIADOS CARACTERES", 1);
	while (argv[++i])
		free(argv[i]);
	free(argv);
}