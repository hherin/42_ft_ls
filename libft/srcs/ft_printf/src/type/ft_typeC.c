/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typeC.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:23:56 by hherin            #+#    #+#             */
/*   Updated: 2019/12/17 17:13:36 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/ft_printf.h"

static int			ft_checkerror(s_option opt)
{
	if (opt.flag.zero || opt.precision >= 0)
		return (1);
	return (0);
}

char		*ft_typeC(va_list ap, s_option opt)
{
	char c;
	char *str;
	size_t start;
	size_t len;

	if (ft_checkerror(opt))
		return (0);
	c = va_arg(ap, int);
	len = FT_MAX(1, opt.width);
	str = malloc(sizeof(char) * len + 1);
	str[len] = '\0';
	str = ft_memset(str, ' ', len);
	start = (opt.flag.minus) ? 0 : ft_strlen(str) - 1;
	str[start] = c;
	return (str);
}