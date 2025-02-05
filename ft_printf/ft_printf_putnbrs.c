/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsoulas <vsoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:53:33 by vsoulas           #+#    #+#             */
/*   Updated: 2024/11/22 13:53:02 by vsoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int i, int *count)
{
	(*count)++;
	if (i == INT_MIN)
	{
		write(1, "-2147483648", 12);
		*count += 10;
	}
	else
	{
		if (i < 0)
		{
			write(1, "-", 1);
			i *= -1;
			(*count)++;
		}
		if (i >= 10)
		{
			ft_putnbr(i / 10, count);
		}
		ft_putchar((i % 10) + '0');
	}
	return (*count);
}

int	ft_putunsignednbr(unsigned int i, int *count)
{
	int				result;

	result = 0;
	if (i >= 10)
		result = ft_putnbr(i / 10, count);
	ft_putchar((i % 10) + '0');
	return (result + 1);
}

int	ft_printhexa(unsigned int x, char a, int *count)
{
	char	c;
	char	base_up_hexa [17];
	char	base_low_hexa [17];
	int		i;

	i = 0;
	while (i < 17)
	{
		base_up_hexa[i] = "0123456789ABCDEF"[i];
		base_low_hexa[i] = "0123456789abcdef"[i];
		i++;
	}
	(*count)++;
	if (x >= 16)
		ft_printhexa(x / 16, a, count);
	if (a == 'x')
		c = base_low_hexa[x % 16];
	else if (a == 'X')
		c = base_up_hexa[x % 16];
	write(1, &c, 1);
	return (*count);
}
