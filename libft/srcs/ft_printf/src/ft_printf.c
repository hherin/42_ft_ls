/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:25:03 by hherin            #+#    #+#             */
/*   Updated: 2019/12/18 13:03:27 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/ft_printf.h"

static char	*ft_joins(char *str, char *index, char *s)
{
	char *tmp;

	tmp = ft_substr(index, 0, str - index);
	s = ft_strjoin(s, tmp);
	return (s);
}

static char	*ft_whilenorm(char str, s_print *tab, s_option opt, va_list ap)
{
	size_t j;
	char *tmp;

	j = 0;
	tmp = NULL;
	while (j < NB_STRUCT)
	{
		if (tab[j].c == str)
		{
			if (!(tmp = tab[j].function(ap, opt)))
				return (0);
		}
		j++;
	}
	return (tmp);
}

static char *ft_finalprint(va_list ap, char *str, s_print *tab)
{
	s_option	opt;
	char		*index;
	char		*tmp;
	char		*s;

	s = NULL;
	index = str;
	while (*str)
	{
		if (*str == '%')
		{
			s = ft_joins(str, index, s);
			str++;
			opt = ft_getopt(ap, &str);
			tmp = ft_whilenorm(*str, tab, opt, ap);
			s = ft_strjoin(s, tmp);
			free(tmp);
			str++;
			index = str;
		}
		(*str != '\0') ? str++ : 0;
		s = (*str == '\0') ? ft_joins(str, index, s) : s;
	}
	return (s);
}

int		ft_printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	s_print *tab;
	int ret;
	char *str;

	ret = 0;
	str = (char*)format;
	tab = ft_struct_printf();
	if (!(str = ft_finalprint(ap, str, tab)))
		return (0);
	ret = ft_strlen(str);
	ft_putstr(str);
	free(str);
	free(tab);
	va_end(ap);
	return (ret);
}