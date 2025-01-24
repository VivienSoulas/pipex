/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:53:33 by vsoulas           #+#    #+#             */
/*   Updated: 2024/11/28 17:15:58 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// int	main(void)
// {
// 	char			c;
// 	char			*s;
//	char			*s1;
// 	void			*p;
//	void			*p1;
// 	int				d;
// 	int				i;
// 	unsigned int	u;
// 	int				x;
// 	int				X;
// 	int				result;
// 	int				results;
//	int				results1;
//	int				results2;
//	int				results3;
//	int				results4;
//	int				results5;
//	int				results6;

// 	c = 'a';
// 	s = NULL;
//	s1 = "This is working ?";
// 	p = NULL;
//	p1 = &i;
// 	d = 666;
// 	i = INT_MIN;
// 	u = -1;
// 	x = 568913;
// 	X = 568913;
// 	result = 0;
// 	results = 0;
//	results1 = 0;
//	results2 = 0;
//	results3 = 0;
//	results4 = 0;
//	results5 = 0;
//	results6 = 0;

// 	printf("\n");
// 	printf("original printf:\n");
// 	printf("char c = %c\n", c);
//results1 = printf("string s = %s\n", s);
//printf("%i\n", results1);
//result = printf("string1 s = %s\n", s1);
//printf("%i\n", result);
//	printf("pointer p = %p\n", p);
//	printf("pointer p1 = %p\n", p1);
// 	printf("int d = %d\n", d);
// 	printf("int i = %i\n", i);
// 	printf("unsigned decimal u = %u\n", u);
// 	printf("hex lower x = %x\n", x);
// 	printf("hexa upper X = %X\n", X);
//results3 = printf("this is a trial %");
//printf("\n");
//printf("%i\n", results3);
//results5 = printf("this is %, a trial");
//printf("\n");
//printf("%i\n", results5);
// 	printf("%%\n");
// 	printf("\n\n");

// 	ft_printf("my ft_printf:\n");
// 	ft_printf("char c = %c\n", c);
//results2 = printf("string s = %s\n", s);
//printf("%i\n", results2);
//results = ft_printf("string1 s = %s\n", s1);
//printf("%i\n", results);
//	ft_printf("pointer p = %p\n", p);
//	ft_printf("pointer p1 = %p\n", p1);
// 	ft_printf("int d = %d\n", d);
// 	ft_printf("int i = %i\n", i);
// 	ft_printf("unsigned decimal u = %u\n", u);
// 	ft_printf("hex lower x = %x\n", x);
// 	ft_printf("hexa upper X = %X\n", X);
//results4 = printf("this is a trial %");
//printf("\n");
//printf("%i\n", results4);
//results6 = printf("this is %, a trial");
//printf("\n");
//printf("%i\n", results6);
// 	ft_printf("%%\n");
// 	printf("\n");
// 	return (0);
// }

int	ft_printf(const char *format, ...)
{
	va_list	ptr;
	int		i;
	int		count;

	if (format == NULL)
		return (-1);
	i = 0;
	count = 0;
	va_start(ptr, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			count += ft_check_format(format, i + 1, ptr);
			i++;
		}
		else if (format[i] == '%' && format[i + 1] == '\0')
			return (-1);
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(ptr);
	return (count);
}

int	ft_check_format(const char *format, int i, va_list ptr)
{
	int	count;

	count = 0;
	if (format[i] == '\0')
		return (-1);
	if (format[i] == 'c')
		return (ft_putchar(va_arg(ptr, int)));
	if (format[i] == 's')
		return (ft_putstr(va_arg(ptr, char *)));
	if (format[i] == 'p')
		return (ft_printptr(va_arg(ptr, void *), &count));
	if (format[i] == 'd' || format[i] == 'i')
		return (ft_putnbr(va_arg(ptr, int), &count));
	if (format[i] == 'u')
		return (ft_putunsignednbr(va_arg(ptr, unsigned int), &count));
	if (format[i] == 'x')
		return (ft_printhexa(va_arg(ptr, unsigned int), format[i], &count));
	if (format[i] == 'X')
		return (ft_printhexa(va_arg(ptr, unsigned int), format[i], &count));
	if (format[i] == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (0);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	ft_printptr(void *ptr, int *count)
{
	int	result;

	result = 0;
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	result = ft_printhexa((uintptr_t)ptr, 'x', count);
	return (result + 2);
}
