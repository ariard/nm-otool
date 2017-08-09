/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_elf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:37:10 by ariard            #+#    #+#             */
/*   Updated: 2017/06/09 22:29:04 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		resolve_elf_name(void *content, char *strtab)
{
	t_sym	*sym;

	sym = content;
	sym->name = &strtab[sym->index];
	return (0);
}

void		parse_sections_elf(char *sectname,
	       	t_hashtab *tabsections, int index)
{
	t_section	section;	

	sections_init(&section);
	section.sectname = sectname;
	section.key = ft_itoa(index + 1);
	hashtab_insert(tabsections, ft_lstnew(&section, sizeof(t_section)),
		section.key, sections_match);
	DG("sectname [%s] ind %d", section.sectname, index);	
}

void		handle_64_elf(char *ptr, t_data *data)
{
	struct elf64_hdr	*header;
	struct elf64_shdr	*section_header;
	char			*strtab;
	char			*shstrtab;
	int			i;

	header = (struct elf64_hdr *)ptr;
	section_header = (struct elf64_shdr *)(ptr + header->e_shoff);
	i = -1;
	shstrtab = ptr + (section_header + header->e_shstrndx)->sh_offset;
	while (++i < header->e_shnum)
	{
		section_header = section_header + 1;
		if (section_header->sh_type == SHT_SYMTAB)
			parse_symtab_elf(ptr, section_header, data);
		else if (section_header->sh_type == SHT_STRTAB && i 
			!= header->e_shstrndx)
			strtab = ptr + section_header->sh_offset;
		else
			parse_sections_elf(&shstrtab[section_header->sh_name],
				&data->tabsections, i);
	}
	ft_lstiter(data->lstsym, &resolve_elf_name, strtab);
	lst_insert_sort(&data->lstsym, sort_elf);
	ft_lstiter(data->lstsym, &print_sym_elf, data);
}

/*
 *
	printf("section header %llx\n", header->e_shoff);
	printf("index shstr %hu\n", header->e_shstrndx);
	printf("num %u\n", header->e_shnum);
	section_header = section_header + 1;
	i = *(ptr + 0x1a10);
	j = *(ptr + header->e_shoff + sizeof(struct elf64_shdr));
	printf("%x\n", i);
	printf("%x\n", section_h l leader->sh_name);
	i = *(ptr + 0x1a14);
	printf("%x\n", i);


	strtab = ptr + (section_header + header->e_shstrndx)->sh_offset;
	printf("sect name %s\n", &strtab[section_header->sh_name]);
*/
