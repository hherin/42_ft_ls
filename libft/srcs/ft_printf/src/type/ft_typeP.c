/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typeP.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:23:50 by hherin            #+#    #+#             */
/*   Updated: 2019/12/17 17:14:16 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/ft_printf.h"

static int		ft_checkerror(s_option opt)
{
	if (opt.flag.zero || opt.precision >= 0)
		return (1);
	return (0);
}

static char		*ft_optchoose(char *str, s_option opt)
{
	char	*tmp;
	size_t	len;
	size_t	start;
	size_t	i;

	i = 0;
	len = FT_MAX((int)ft_strlen(str), opt.width);
	tmp = malloc(sizeof(char) * len + 1);
	tmp[len] = '\0';
	tmp = ft_memset(tmp, ' ', len);
	start = (opt.flag.minus) ? 0 : len - ft_strlen(str);
	while (i < ft_strlen(str))
		tmp[start++] = str[i++];
	free(str);
	return (tmp);
}

char		*ft_typeP(va_list ap, s_option opt)
{
	long	nb;
	char	*str;

	if (ft_checkerror(opt))
		return (0);
	nb = va_arg(ap, long);
	str = ft_itoahexa(nb);
	str = ft_optchoose(str, opt);
	return (str);
}