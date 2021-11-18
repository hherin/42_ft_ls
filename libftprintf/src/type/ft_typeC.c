/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typeC.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:23:56 by hherin            #+#    #+#             */
/*   Updated: 2021/11/17 15:34:08 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/ft_printf.h"


char		*ft_typeC(va_list ap, s_option opt)
{
	char c;
	char *str;
	size_t start;
	size_t len;

	if (opt.flag.zero || opt.precision >= 0)
		return (0);
	c = va_arg(ap, int);
	len = FT_MAX(1, opt.width);
	str = ft_calloc(sizeof(char) * len + 1, sizeof(char));
	str = ft_memset(str, ' ', len);
	start = (opt.flag.minus) ? 0 : ft_strlen(str) - 1;
	str[start] = c;
	return (str);
}