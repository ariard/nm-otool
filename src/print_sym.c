/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sym.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:22:18 by ariard            #+#    #+#             */
/*   Updated: 2017/05/17 16:35:46 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			print_sym(void *content)
{
	t_sym	*sym;

	sym = content;
	ft_printf("0000000100%x %c %s\n", sym->value, sym->type, sym->name);
	return (0);
}