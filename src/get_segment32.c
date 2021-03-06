/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_archi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:19:15 by ariard            #+#    #+#             */
/*   Updated: 2018/02/20 19:49:42 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		get_section_text32(struct segment_command *segm,
				char *ptr, t_data *data)
{
	struct section		*sect;
	int					segsects;

	EV(check_32(segm, data));
	segsects = segm->nsects;
	MC(sect = (void *)segm + sizeof(struct segment_command));
	while (segsects--)
	{
		if (!ft_strcmp("__text", sect->sectname) && !(data->flag
			& OT_DOPT))
			ft_hexdump32(sect, ptr, data, "Contents of (__TEXT,__text) "
				"section");
		if (!ft_strcmp("__data", sect->sectname) && (data->flag &
			OT_DOPT))
			ft_hexdump32(sect, ptr, data, "Contents of (__DATA,__data) "
				"section");
		MC(sect = (void *)sect + sizeof(struct section));
	}
}

void			get_segment32(char *ptr, t_data *data)
{
	int						ncmds;
	int						i;
	struct load_command		*lc;

	if (!(OT_HOPT & data->flag) && !(OT_FOPT & data->flag)
		&& !(OT_AOPT & data->flag))
		ft_printf("%s:\n", data->filename);
	data->bits = 32;
	ncmds = ((struct mach_header *)ptr)->ncmds;
	MC(lc = (void *)ptr + sizeof(struct mach_header));
	i = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
			get_section_text32((struct segment_command *)lc, ptr,
				data);
		MC(lc = (void *)lc + lc->cmdsize);
	}
}
