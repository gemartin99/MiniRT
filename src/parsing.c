#include "minirt.h"
#include "../inc/libft/libft.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	c;

	if (!s1)
	{
		s1 = malloc(sizeof(char) + 1);
		if (!s1)
			exit_error("Error malloc", 2);
		s1[0] = 0;
	}
	str = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		exit_error("Error malloc", 3);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	c = -1;
	while (s2[++c])
		str[i + c] = s2[c];
	str[i + c] = '\0';
	free(s1);
	return (str);
}

void check_id(char *s)
{
	if (ft_strncmp(s, "A", 2) == 0)
		printf("ENTRO A\n");
	if (ft_strncmp(s, "C", 2) == 0)
		printf("ENTRO C\n");
	if (ft_strncmp(s, "L", 2) == 0)
		printf("ENTRO L\n");
	if (ft_strncmp(s, "sp", 3) == 0)
		printf("ENTRO sp\n");
	if (ft_strncmp(s, "pl", 3) == 0)
		printf("ENTRO pl\n");
	if (ft_strncmp(s, "cy", 3) == 0)
		printf("ENTRO cy\n");
}

void check_valid_arg(char *s)
{
	char **res;
	int i = -1;

	res = ft_split(s, ' ');
	while (res[++i])
		printf("res: %s\n", res[i]);
	check_id(res[0]);
	free(res);
}

void ft_read_file(char *s)
{
	char *big_line = NULL;
	char *temp;
	int fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
		exit(0);
	temp = get_next_line(fd);
	while (temp)
	{
		check_valid_arg(temp);
		big_line = ft_strjoin2(big_line, temp);
		free(temp);
		temp = get_next_line(fd);
	}
	printf("%s\n", big_line);
}

int ft_check_file_type(char *s)
{
	int i;

	i = ft_strlen(s);
	if (s[i - 1] == 't' && s[i - 2] == 'r' && s[i - 3] == '.')
		return (0);
	return (-1);
}

void parsing(char *file_name)
{
	if (ft_check_file_type(file_name) == -1)
	{
		printf("ERROR\n");
		exit (0);
	}
	printf("salgo\n");
	if (access(file_name, F_OK) == -1)
	{
		printf("ERROR2\n");
		exit (0);
	}
	printf("salgo2\n");
	ft_read_file(file_name);
}