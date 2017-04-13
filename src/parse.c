#include "rt.h"

int		check_entry(char *line, char *content)
{
	 int		j;
	j = 0;
	while (line[j])
	{
		if ((line[j] >= 48 && line[j] <= 57) || (line[j] >=65 && line[j] <= 90) || (line[j] >= 97 && line[j] <= 122) || (line[j] == 123) || (line[j] == 125) || (line[j] == 44))
				j++;
		else
		{
			ft_putstr("invalid entry file");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
	}

int     loop_main(int fd)
{
	char    *line;
	char **content;
	int		buffer;
	int     ret;
	int		i;

	buffer = 1000;
	content = malloc(sizeof(char*) * buffer);
	i = 0;
	line = NULL;
	while ((ret = (get_next_line(fd, &line)) > 0))
	{
		if (!(check_entry(line)))
			content[i] = ft_strdup(line);
		free(line);
		i++;
	}
	content[i] = NULL;
	
	free(line);
	return (ret);
}

int     ft_parsing(int argc, char **argv)
{
	int     fd;
	int     ret;

	if (argc != 2)
		exit(EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (!(ret = loop_main(fd)))
		return (-1);
	return (0);
}
