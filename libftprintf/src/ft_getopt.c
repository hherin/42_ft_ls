/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:24:58 by hherin            #+#    #+#             */
/*   Updated: 2021/11/16 17:58:24 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/ft_printf.h"

static s_flag	get_flag(char **str)
{
	s_flag	i;

	i.minus = 0;
	i.zero = 0;
	while (**str && (**str == '0' || **str == '-'))
	{
		if (**str == '0')
		{
			i.zero = 1;
			(*str)++;
		}
		else if (**str == '-')
		{
			i.zero = 0;
			i.minus = 1;
			(*str)++;
		}
	}
	return (i);
}

static int		get_width(char **str, va_list ap)
{
	int	ret;

	ret = 0;
	if (FT_ISDIGIT(**str))
	{
		ret = ft_atoi(*str);
		while (FT_ISDIGIT(**str))
			(*str)++;
	}
	else if (**str == '*')
	{
		ret = va_arg(ap, int);
		(*str)++;
	}
	return (ret);
}

static int		get_precision(char **str, va_list ap)
{
	int	ret;

	ret = -1;
	if (**str == '.')
	{
		(*str)++;
		ret = 0;
		if (FT_ISDIGIT(**str))
		{
			ret = ft_atoi(*str);
			while (FT_ISDIGIT(**str))
				(*str)++;
		}
		if (**str == '*')
		{
			ret = va_arg(ap, int);
			(*str)++;
		}
	}
	return (ret);
}

s_option		get_options(va_list ap, char **str)
{
	s_option	opt;

	opt.width = 0;
	opt.precision = 0;
	opt.flag = get_flag(str);
	opt.width = get_width(str, ap);
	opt.precision = get_precision(str, ap);
	return (opt);
}