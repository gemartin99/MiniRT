/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:01:21 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 15:01:35 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

int check_wrong_char(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != '-' && s[i] != '.' && s[i] != ',' && s[i] != ' ' && ft_isdigit(s[i]) == 0 && s[i] != '\n')
			exit_error("CARACTER INCORRECTO", 1);
	}
	return (0);
}

void check_id(char *s, char **res, t_mrt *mrt)
{
	if (ft_strncmp(s, "A", 2) == 0)
		init_al(mrt, res);
	/*if (ft_strncmp(s, "C", 2) == 0)
		parsing_c(res, i);
	if (ft_strncmp(s, "L", 2) == 0)
		parsing_l(res, i);*/
	if (ft_strncmp(s, "sp", 3) == 0)
		printf("ENTRO sp\n");
	if (ft_strncmp(s, "pl", 3) == 0)
		printf("ENTRO pl\n");
	if (ft_strncmp(s, "cy", 3) == 0)
		printf("ENTRO cy\n");
}

int ft_isspace(char *s)
{
	int i;

	i = -1;
	while(s[++i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\v' && s[i] != '\f' && s[i] != '\r')
			return (1);
	}
	return (0);
}

void check_valid_arg(char *s, t_mrt *mrt)
{
	char **res;
	char *temp;

	if (!s || ft_isspace(s) == 0)
		return ;
	temp = ft_strtrim(s, " ");
	check_wrong_char(ft_strchr(temp, ' '));
	res = ft_split(temp, ' ');
	check_id(res[0], res, mrt);
	free(temp);
	free(res);
}

void ft_read_file(char *s, t_mrt *mrt)
{
	char *temp;
	int fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
		exit(0);
	temp = get_next_line(fd);
	while (temp)
	{
		check_valid_arg(temp, mrt);
		free(temp);
		temp = get_next_line(fd);
	}
}

int ft_check_file_type(char *s)
{
	int i;

	i = ft_strlen(s);
	if (s[i - 1] == 't' && s[i - 2] == 'r' && s[i - 3] == '.')
		return (0);
	return (-1);
}

void parsing(char *file_name, t_mrt *mrt)
{
	if (ft_check_file_type(file_name) == -1)
		exit_error("ERROR\nEL FICHERO NO ES .RT\n", 1);
	if (access(file_name, F_OK) == -1)
		exit_error("ERROR\nNO SE PUEDE ACCEDER AL FICHERO\n", 1);
	ft_read_file(file_name, mrt);
}
