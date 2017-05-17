/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_symtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:21:29 by ariard            #+#    #+#             */
/*   Updated: 2017/05/17 20:49:35 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void		sym_init(t_sym *sym)
{	
	sym->type = 0;
	sym->name = NULL;
	sym->scope = 0;
	sym->sections = 0;
	sym->value = 0;
}

static int		sym_resolve(int num, t_hashtab *tabsections)
{
	char		*key;
	int			type;
	t_list		*elem;

	key = ft_itoa(num);
	type = 0;
	if ((elem = (hashtab_lookup(tabsections, key, &sections_match))))
	{
		type = (ft_strcmp("__DATA", ((t_section *)elem->content)->segname) == 0) ? 'D' : type;
		type = (ft_strcmp("__bss", ((t_section *)elem->content)->sectname) == 0) ? 'B' : type;
		type = (ft_strcmp("__TEXT", ((t_section *)elem->content)->segname) == 0) ? 'T' : type;
	}
	ft_strdel(&key);
	return (type);
}	

static void		sym_info(t_sym *sym, char *stringtable, struct nlist_64 el,
				t_hashtab *sections)
{
	unsigned char	mask;

	if (el.n_type & N_STAB)
		sym->type = '-';
	else
	{
		if 	(el.n_type & N_PEXT)
			sym->scope = 0;
		else if (el.n_type & N_EXT)
			sym->scope = 1;
		if (el.n_type & N_TYPE)
		{
			mask = el.n_type >> 1;
			sym->type = (mask & N_UNDF) ? 'U' : sym->type;
			sym->type = (mask & N_ABS) ? 'A' : sym->type;
			sym->type = (mask & N_SECT) ?  sym_resolve(el.n_sect, sections) : sym->type;
			sym->type = (mask & N_PBUD) ? 'U' : sym->type;
			sym->type = (mask & N_INDR) ? 'I' : sym->type;
		}
	}
	sym->value = el.n_value;
	sym->name = stringtable + el.n_un.n_strx;
	DG(" ");
	DG("%s", sym->name);
	DG("index %.4x", el.n_un.n_strx);
	DG("type %x or %d or %b", el.n_type, el.n_type, el.n_type);
	DG("sect %x", el.n_sect);
	DG("desc %.2x", el.n_desc);
	DG("value %.4x", sym->value);
}

// don t forget common and no sections symbol

void			parse_symtab(struct symtab_command *tabsym, char *ptr, t_data *data)
{
	int					i;
	int					nsyms;
	char				*stringtable;
	t_sym				sym;

	stringtable = (void *)ptr + tabsym->stroff;
	nsyms = tabsym->nsyms;
	i = -1;
	while (++i < nsyms)
	{
		sym_init(&sym);
		DG("offset %d", tabsym->symoff);
		sym_info(&sym, stringtable, (((struct nlist_64 *)((void *)ptr + tabsym->symoff))[i]),
			&data->tabsections);
		ft_lsteadd(&data->lstsym, ft_lstnew(&sym, sizeof(t_sym)));
	}
}
