#include "../inc/ft_printf.h"

static s_print	ft_filetab(char c, fct funct)
{
	s_print tab;

	tab.c = c;
	tab.function = funct;
	return (tab);
}

s_print		*ft_struct_printf(void)
{
	s_print *dispatch;

	dispatch = (s_print*)malloc(sizeof(s_print) * NB_STRUCT);
	dispatch[0] = ft_filetab('d', &ft_typeD);
	dispatch[1] = ft_filetab('i', &ft_typeD);
	dispatch[2] = ft_filetab('s', &ft_typeS);
	dispatch[3] = ft_filetab('c', &ft_typeC);
	dispatch[4] = ft_filetab('x', &ft_typeX);
	dispatch[5] = ft_filetab('X', &ft_typeXmaj);
	dispatch[6] = ft_filetab('p', &ft_typeP);
	dispatch[7] = ft_filetab('u', &ft_typeU);
	dispatch[8] = ft_filetab('%', &ft_type_pourcent);
	return (dispatch);
}