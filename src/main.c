#include "minirt.h"
#include "../inc/libft/libft.h"

void exit_error(char *s, int i)
{
	printf("%s\n", s);
	exit (i);
}

t_mrt *init_data()
{
	t_mrt	*mrt;

	mrt = ft_calloc(sizeof(t_mrt), 1);
	if (!mrt)
		exit_error("Error malloc", 1);
	return (mrt);
}

int main(int argc, char **argv)
{
	t_mrt *mrt;

	if (argc != 2)
		exit (0);
	mrt = init_data();
	parsing(argv[1]);
	return (0);
}