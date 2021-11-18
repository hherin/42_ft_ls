/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:26:19 by hherin            #+#    #+#             */
/*   Updated: 2019/12/17 21:18:45 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MACRO_H
#define MACRO_H

#define FT_ISDIGIT(x) (((x) >= '0' && (x) <= '9') ? 1 : 0)
#define FT_ISSPACE(x) (((x) > 0 && (x) < 33) ? 1 : 0)
#define FT_
#define FT_ISTYPE(x) (((x) == '%' || (x) == 'c' || (x) == 'd' || (x) == 'p' || (x) == 's' || (x) == 'u' || (x) == 'x' || (x) == 'X') ? 1 : 0)
#define FT_MIN(x, y) (((x) >= (y)) ? y : x)
#define FT_MAX(x, y) (((x) >= (y)) ? x : y)
#define NB_STRUCT 9
#endif