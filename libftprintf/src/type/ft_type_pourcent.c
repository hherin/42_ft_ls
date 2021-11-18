/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_pourcent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:26:44 by hherin            #+#    #+#             */
/*   Updated: 2019/12/17 17:13:47 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/ft_printf.h"

static char	*ft_optchoose(s_option opt, char *s)
{
	char	*tmp;
	size_t	size;
	size_t	start;
	size_t	i;

	i = 0;
	size = opt.width;
	if (size < ft_strlen(s))
		return (s);
	tmp = malloc(sizeof(char) * size + 1);
	tmp[size] = '\0';
	tmp = ft_memset(tmp, (opt.flag.zero) ? '0' : ' ', size);
	start = (opt.flag.minus) ? 0 : size - ft_strlen(s);
	while (i < ft_strlen(s))
		tmp[start++] = s[i++];
	free(s);
	return (tmp);
}

char		*ft_type_pourcent(va_list ap, s_option opt)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = '%';
	str[1] = '\0';
	str = ft_optchoose(opt, str);
	(void)ap;
	(void)opt;
	return (str);
}