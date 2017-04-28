int object_type (char *line, int obj_mode, int nbr_obj_param)
{
	if (strcmp(line, "sphere"))
	{
		obj_mode = 1;
		nbr_obj_param = 4;
	}
	if (strcmp(line, "plane"))
		obj_mode = 2;
	if (strcmp(line, "cylinder"))
		obj_mode = 3;
	return (0);
}

int use_values(char **content)
{
	int i;
	int obj_mode;
	char **params_obj;
	int	nbr_obj_param;

	i = 0;
	obj_mode = 0;
	nbr_obj_param = 0;
	while (content[i])
	{
		object_type(content[i], obj_mode, nbr_obj_param);
		if (obj_mode != 0)
		{
			params_obj = malloc (sizeof(char *) * nbr_obj_param);
			while (i < [i + nbr_obj_params])
			{
				params_obj[cpt] = ft_strdup(content[i]);
				i++;
				cpt++;
			}
		}
		fill_struct(params_obj, obj_mode);
		i++;
	}
	
}
