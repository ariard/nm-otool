/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:26:53 by ariard            #+#    #+#             */
/*   Updated: 2017/05/21 19:27:29 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_cliopts		g_nm_opts[]=
{
	{'n', NULL, NM_NOPT, 0, NULL, 0},
	{'r', NULL, NM_ROPT, 0, NULL, 0},
};

static void		data_init(t_data *data)
{
	data->flag = 0;
	data->av_data = NULL;
	data->lstsym = NULL;
	data->filetype = 0;
	hashtab_init(&data->tabsections, 100, &ft_hash_string);
}

static void		parse_archi(char *ptr, t_data *data)
{
	unsigned int		magic_number;

	magic_number = *(unsigned int *)ptr;
	if (magic_number == MH_MAGIC_64)
		handle_64(ptr, data);
	if (magic_number == MH_MAGIC)
		handle_32(ptr);
	if (magic_number == FAT_CIGAM) 	
		handle_fat(ptr);
}

int				main(int argc, char **argv)
{
	int			fd;
	t_data		data;
	int			i;
	char		*ptr;
	struct stat buf;

	if (argc < 2)
	{
		ft_dprintf(2, "Argumnent needed");
		return (1);
	}
	data_init(&data);
	cliopts_get(argv, g_nm_opts, &data);
	i = data.av_data - argv;
	while (i < argc && argv[i])
	{
		if ((fd = open(argv[i], O_RDONLY)) < 0)
			return (1);
		if (fstat(fd, &buf) < 0)
			return (1);
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (1);
		parse_archi(ptr, &data);
		if (munmap(ptr, buf.st_size) < 0)
			return (1);
		i++;
	}
	return (0);
}
