/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:53:36 by vsoulas           #+#    #+#             */
/*   Updated: 2024/11/22 13:53:16 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <limits.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);
int	ft_check_format(const char *format, int i, va_list ptr);
int	ft_putchar(char c);
int	ft_putstr(const char *s);
int	ft_printptr(void *ptr, int *count);
int	ft_putnbr(int i, int *count);
int	ft_putunsignednbr(unsigned int i, int *count);
int	ft_printhexa(unsigned int x, char a, int *count);

#endif