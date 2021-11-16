/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typeD.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:24:48 by hherin            #+#    #+#             */
/*   Updated: 2019/12/18 15:37:42 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/ft_printf.h"

// static int	ft_checkerror(s_option opt)
// {
// 	if (opt.flag.zero && opt.flag.minus)
// 		return (1);
// 	return (0);
// }

static char	*ft_nbnegative(char *s, char *tmp, s_option opt, size_t size)
{
	size_t	start;
	size_t	zero;
	size_t	i;
	int		abso;

	i = 0;
	if (opt.precision >= 0)
	{
		zero = (opt.precision > (int)ft_strlen(s)) ? opt.precision - ft_strlen(s) + 1: 0;
		start = (opt.flag.minus || opt.width < 0) ? 0 : size - FT_MAX(opt.precision + 1, (int)ft_strlen(s));
		tmp[start++] = '-';
		while (i++ < zero)
			tmp[start++] = '0';
		i = 1;
		while (i < ft_strlen(s))
			tmp[start++] = s[i++];
	}
	else
	{
		abso = (opt.width < 0) ? (int)ft_strlen(s) : opt.width;
		zero = (opt.flag.zero) ? abso - ft_strlen(s): 0;
		start = (opt.flag.minus || opt.width < 0) ? 0 : size - FT_MAX(ft_strlen(s), zero);
		tmp[start++] = '-';
		while (i++ < zero)
			tmp[start++] = '0';
		i = 1;
		while (i < ft_strlen(s))
			tmp[start++] = s[i++];
	}
	return (tmp);
}

static char	*ft_zeropad(char *s, char *tmp, s_option opt, size_t size)
{
	size_t	start;
	size_t	zero;
	size_t	i;
	int		abso;

	i = 0;
	if (opt.precision >= 0)
	{
		zero = (opt.precision > (int)ft_strlen(s)) ? opt.precision - ft_strlen(s) : 0;
		start = (opt.flag.minus || opt.width < 0) ? 0 : size - FT_MAX(opt.precision, (int)ft_strlen(s));
		while (i++ < zero)
			tmp[start++] = '0';
		i = 0;
		while (i < ft_strlen(s))
			tmp[start++] = s[i++];
	}
	else
	{
		abso = (opt.width < 0) ? (int)ft_strlen(s) : opt.width;
		zero = (opt.flag.zero) ? abso - ft_strlen(s): 0;
		start = (opt.flag.minus || opt.width < 0) ? 0 : size - FT_MAX(ft_strlen(s), zero);
		while (i++ < zero)
			tmp[start++] = '0';
		i = 0;
		while (i < ft_strlen(s))
			tmp[start++] = s[i++];
	}
	return (tmp);
}

static char	*ft_optschoose(s_option opt, char *s, int nb)
{
	char	*tmp;
	size_t	size;
	int		abso;

	abso = (opt.width < 0) ? -opt.width : opt.width;
	size = (nb < 0) ? FT_MAX(opt.precision + 1, abso) : FT_MAX(opt.precision , abso);
	if ((ft_strlen(s) == 1) && *s == '0' && !opt.precision)
	{
		free(s);
		s = ft_calloc(1,1);
	}
	if (size < ft_strlen(s))
		return (s);

	tmp = malloc(sizeof(char) * size + 1);
	tmp[size] = '\0';
	tmp = ft_memset(tmp, ' ', size);
	if (nb < 0)
		tmp = ft_nbnegative(s, tmp, opt, size);
	else
		tmp = ft_zeropad(s, tmp, opt, size);
	free(s);
	return (tmp);
}

char		*ft_typeD(va_list ap, s_option opt)
{
	char	*s;
	char	*tmp;
	int		nb;

	// if (ft_checkerror(opt))
	// 	return (0);
	nb = va_arg(ap, int);
	if (!(s = ft_itoa(nb)))
		return (NULL);
	tmp = ft_optschoose(opt, s, nb);
	return (tmp);
}