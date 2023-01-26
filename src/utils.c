/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:07:37 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 13:07:39 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

int	check_wrong_char(char *s)
{
	int	i;

	i = -1;
	if (!s)
		exit_error("ERROR\nCARACTER INCORRECTO", 1);
	while (s[++i])
	{
		if (s[i] != '-' && s[i] != '.' && s[i] != ','
			&& s[i] != ' ' && ft_isdigit(s[i]) == 0 && s[i] != '\n')
			exit_error("CARACTER INCORRECTO", 1);
	}
	return (0);
}

float	ft_atof(char *n)
{
	int		i;
	int		j;
	float	nb;
	int		m;

	i = 0;
	nb = 0;
	m = 1;
	j = 1;
	if (n[i] == '-')
	{
		m = -m;
		i++;
	}
	while (n[i])
	{
		if (j > 1 && n[i - 1] != '.')
			j *= 10;
		if (n[i] == '.')
			j *= 10;
		else
			nb = nb * 10 + (n[i] - 48);
		i++;
	}
	return (m * nb / j);
}

int	ft_isspace(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'
			&& s[i] != '\v' && s[i] != '\f' && s[i] != '\r')
			return (1);
	}
	return (0);
}

void	*new_cpy(void *src, size_t size)
{
	void	*dest;

	dest = new_calloc(size, 1, 90);
	ft_memcpy(dest, src, size);
	return (dest);
}
