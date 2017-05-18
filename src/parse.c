
#include "../includes/rt.h"

int loop_main(int fd, t_env *e)
{
	char    *line;
	char	**content;
	int		buffer;
	int     ret;
	int		i;

	buffer = 1000;
	content = malloc(sizeof(char*) * buffer);
	i = 0;
	line = NULL;
	while ((ret = (get_next_line(fd, &line)) > 0))
	{
		content[i] = ft_strdup(line);
		ft_putstr (content[i]);
		free(line);
		printf ("i : %i\n", i);
		i++;
	}
	content[i] = NULL;
	free(line);
	use_values(content, e);
	return (0);
}

int ft_parsing(int argc, char **argv, t_env *e)
{
    int     fd;
    int     ret;

    if (argc != 2)
        exit(EXIT_FAILURE);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exit(EXIT_FAILURE);
    if ((ret = loop_main(fd, e)))
        return (0);
	//*e = init();
    return (0);
}
