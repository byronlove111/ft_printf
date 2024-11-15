/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:20:39 by abbouras          #+#    #+#             */
/*   Updated: 2024/11/15 16:42:37 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr(unsigned long *ptr, int *ct)
{
	unsigned long	addr;

	addr = (unsigned long)ptr;
	if (addr == 0)
		*ct += write(1, "(nil)", 5);
	else
	{
		ft_putstr_fd("0x", 1, ct);
		ft_putnbr_base_ul(addr, "0123456789abcdef", ct);
	}
}

void	ft_putunsigned_fd(unsigned int n, int fd, int *ct)
{
	if (n > 9)
		ft_putunsigned_fd(n / 10, fd, ct);
	ft_putchar_fd((n % 10) + 48, fd, ct);
}

void	ft_putnbr_base(unsigned int nbr, char *base, int *ct)
{
	unsigned int	base_l;

	base_l = ft_strlen(base);
	if (nbr >= base_l)
	{
		ft_putnbr_base(nbr / base_l, base, ct);
	}
	ft_putchar_fd(base[nbr % base_l], 1, ct);
}

static void	if_statement(char c, va_list args, int *ct)
{
	if (c == 'c')
		ft_putchar_fd(va_arg(args, int), 1, ct);
	else if (c == 's')
		ft_putstr_fd(va_arg(args, char *), 1, ct);
	else if (c == 'i' || c == 'd')
		ft_putnbr_fd(va_arg(args, int), 1, ct);
	else if (c == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", ct);
	else if (c == 'X')
		ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", ct);
	else if (c == 'u')
		ft_putunsigned_fd(va_arg(args, unsigned int), 1, ct);
	else if (c == 'p')
		ft_putptr(va_arg(args, unsigned long *), ct);
	else if (c == '%')
		ft_putchar_fd('%', 1, ct);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		*ct;
	int		count;

	count = 0;
	ct = &count;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if_statement(*str++, args, ct);
		}
		else
		{
			write(1, str++, 1);
			(*ct)++;
		}
	}
	return (count);
}
