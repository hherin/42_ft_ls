/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typeS.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:24:11 by hherin            #+#    #+#             */
/*   Updated: 2019/12/18 14:47:27 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/ft_printf.h"

static int	ft_checkerror(s_option opt)
{
	if (opt.flag.zero)
		return (1);
	return (0);
}

static char	*ft_optchoose(char *s, s_option opt)
{
	int len;
	int abso;
	int len_prec;
	int start;
	int i;
	char *str;

	i = 0;
	len_prec = ft_strlen(s);
	abso = (opt.width < 0) ? -opt.width: opt.width;
	if (opt.precision >= 0)
		len_prec = FT_MIN(opt.precision, len_prec);
	len = FT_MAX(len_prec, abso);
	if (opt.flag.minus)
		len = FT_MAX(opt.width, len_prec);
	str = malloc(sizeof(char) * len + 1);
	str = ft_memset(str, ' ', len);
	str[len] = '\0';
	start = (opt.flag.minus || opt.width < 0) ? 0 : len - len_prec;
	while (i < len_prec)
		str[start++] = s[i++];
	return (str);
}

char		*ft_typeS(va_list ap, s_option opt)
{
	char *s;

	if (ft_checkerror(opt))
		return (0);
	s = va_arg(ap, char*);
	s = ft_optchoose(s, opt);
	return (s);
}