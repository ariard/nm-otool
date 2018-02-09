/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:30:07 by ariard            #+#    #+#             */
/*   Updated: 2017/05/15 18:32:42 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

t_tool_cpu	g_cpu[] =
{
	{CPU_TYPE_I386, 1, 32},
	{CPU_TYPE_X86_64, 1, 64},
	{0, 0, 0},
};


void		handle_fat(char *ptr, t_data *data)
{
	int			ncmds;
	int			offset;
	void			*tmp;
	int			i;

	ncmds = ntohl(((struct fat_header *)ptr)->nfat_arch);
	tmp = ptr + sizeof(struct fat_header);
	DG("sizeof %lu", sizeof(struct fat_header));
	DG("sizeof %lu", sizeof(struct fat_arch));
	i = 0;
	while (i++ < ncmds)
	{	
		offset = ntohl(((struct fat_arch *)tmp)->offset);
		// machine.h for guessing 32-bit or 64-bit
		DG("offset %d\n", offset);
		if (i == 2)
			handle_64(ptr + offset, data);
//		ft_printf("architecture %d\n", i);
//		j = -1;
//		cputype = (((struct fat_arch *)tmp)->cputype);
//		ft_printf("	cputype %d\n", ntohl(cputype));
//		while (g_cpu[++j].cputype)
//			if (!(g_cpu[j].endianf(cputype) ^ g_cpu[j].cputype))
//				break;	
//		ft_printf("cputype %d\n", g_cpu[j].endianf(cputype));
//		ft_printf("	offset %d\n", ntohl(((struct fat_arch *)tmp)->offset));
		tmp = (void *)tmp + sizeof(struct fat_arch);
	}
}
