/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:25:03 by hherin            #+#    #+#             */
/*   Updated: 2021/11/17 15:32:35 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

 char *ft_joins(char *begin, char *end, char *s2)
{
	char *tmp;
	char *tmp2;

	tmp = ft_substr(begin, 0, end - begin);
	tmp2 = ft_strjoin(s2, tmp);
	free(tmp);
	return tmp2;
}

static char *get_variable(char str, s_print *tab, s_option opt, va_list ap)
{
	size_t j;
	char *tmp;

	j = 0;
	tmp = NULL;
	while (j < NB_STRUCT)
	{
		if (tab[j].c == str)
			if (!(tmp = tab[j].function(ap, opt)))
				return (0);
		j++;
	}
	return (tmp);
}

#include <stdio.h>

static int ft_finalprint(va_list ap, char *str, s_print *tab)
{
	s_option opt;
	static int ret = 0;
	int idx = 0;
	char *tmp = NULL;

	ft_bzero(buffer, BUFFER_SIZE);
	while (*str && idx < BUFFER_SIZE)
	{
		if (*str == '%')
		{
			str++;
			opt = get_options(ap, &str);
			tmp = get_variable(*str++, tab, opt, ap);
			ft_strlcpy(buffer + idx, tmp, ft_strlen(tmp) + 1);
			idx += ft_strlen(tmp);
			free(tmp);
		}
		else
			buffer[idx++] = *str++;
	}
	ft_putstr(buffer);
	ret += idx;
	return (*str) ? ft_finalprint(ap, str, tab) : ret;

}

int ft_printf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	s_print *tab;
	int ret;

	tab = ft_struct_printf();
	ret = ft_finalprint(ap, (char*)format, tab);
	printf("ret %d\n", ret);
	free(tab);
	va_end(ap);
	return (ret);
}