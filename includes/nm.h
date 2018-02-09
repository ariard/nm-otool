/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:29:11 by ariard            #+#    #+#             */
/*   Updated: 2018/02/09 21:28:30 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H


# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/sysctl.h>

# include <inttypes.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach/machine.h>
# include <mach-o/arch.h>

# include "../libft/includes/libft.h"
# include "elf.h"


/*
 * Nm
*/

# define NM_NOPT		(1 << 1)
# define NM_ROPT		(1 << 2)
# define NM_POPT		(1 << 3)
# define NM_GOPT		(1 << 4)
# define NM_AOPT		(1 << 5)
# define NM_OOPT		(1 << 6)
# define NM_uOPT		(1 << 7)
# define NM_UOPT		(1 << 8)
# define NM_JOPT		(1 << 9)

# define MH_FAITHFUL	(MH_OBJECT | MH_EXECUTE | MH_DYLIB)

struct s_data
{	
	t_flag					flag;	
	char					**av_data;
	t_list					*lstsym;
	int						filetype;
	char					*filename;
	unsigned int			cpu;
	char					bits;				
	t_hashtab				tabsections;
};

typedef struct s_data		t_data;

struct s_section
{
	char		*sectname;
	char		*segname;
	char		*key;
};

typedef struct s_section	t_section;


struct s_sym
{
	char			type;
	char			*name;
	char			*desc;
	uint64_t		value;
	int				index;
};

typedef struct s_sym		t_sym;


struct s_stabs
{
	char	value;
	char	*entry;
};

typedef struct s_stabs		t_stabs;

struct s_tool_cpu
{
	integer_t	cputype;
//	uint32_t	(*endianf)(uint32_t);
	char		endianf;
	char		size;	
};

typedef struct s_tool_cpu	t_tool_cpu;

extern t_tool_cpu		g_cpu[];

struct s_elfsect
{
	char 	*value;
	char	type;
};

typedef struct s_elfsect	t_elfsect;

/* MachO binary */

void		handle_64(char *ptr, t_data *data);
void		handle_32(char *ptr, t_data *data);
void		handle_fat(char *ptr, t_data *data);

void		parse_archi(char *ptr, t_data *data);
void		parse_segment64(struct segment_command_64 *segm,
			t_hashtab *tabsections, int *nsects);
void		parse_segment32(struct segment_command *segm,
			t_hashtab *tabsections, int *nsects);
void		parse_symtab(struct symtab_command *sym, char *ptr, t_data *data);
void		parse_symtab32(struct symtab_command *sym, char *ptr, t_data *data);


void		sym_init(t_sym *sym);
void		symtab_sort(t_list **lstsym, t_data *data);
void		symtab_del(t_list **lstsym, t_data *data);
int			sym_resolve(int num, t_hashtab *tabsections);
int			print_sym(void *content, t_data *data);
void		sym_stab(t_sym *sym, uint8_t type);
void		sym_del(void *data_ref, size_t size);


int			sections_match(const void *data_ref, const void *key);
int			sections_print(const void *data_ref);
void		sections_init(t_section *section);
int			sections_del(void *data_ref);

/*
 * Otool
*/

void		ft_hexdump(struct section_64 *sect, char *ptr, char *filename);

#endif
