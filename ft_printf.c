/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:20:39 by abbouras          #+#    #+#             */
/*   Updated: 2024/11/14 17:19:59 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd, int *ct)
{
	write(fd, &c, 1);
	(*ct)++;
}

void	ft_putstr_fd(char *s, int fd, int *ct)
{
	if (!s)
	{
		*ct += write(1, "(null)", 6);
		return ;
	}
	while (*s)
	{
		ft_putchar_fd(*s, fd, ct);
		s++;
	}
}

void	ft_putnbr_fd(int n, int fd, int *ct)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd, ct);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd, ct);
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd, ct);
	ft_putchar_fd((n % 10) + 48, fd, ct);
}

void	ft_putnbr_base_ul(unsigned long nbr, char *base, int *ct)
{
	unsigned long	base_l;

	base_l = ft_strlen(base);
	if (nbr >= base_l)
		ft_putnbr_base_ul(nbr / base_l, base, ct);
	ft_putchar_fd(base[nbr % base_l], 1, ct);
}

void	ft_putptr(unsigned long *ptr, int *ct)
{
	unsigned long	addr;

	addr = (unsigned long)ptr;
	ft_putstr_fd("0x", 1, ct);
	if (addr == 0)
		ft_putchar_fd('0', 1, ct);
	else
		ft_putnbr_base_ul(addr, "0123456789abcdef", ct);
}

void	ft_putunsigned_fd(unsigned int n, int fd, int *ct)
{
	if (n > 9)
		ft_putunsigned_fd(n / 10, fd, ct);
	ft_putchar_fd((n % 10) + 48, fd, ct);
}

void	ft_putnbr_base(int nbr, char *base, int *ct)
{
	long	nb;
	long	base_l;

	nb = nbr;
	base_l = ft_strlen(base);
	if (nb >= base_l)
	{
		ft_putnbr_base(nb / base_l, base, ct);
	}
	ft_putchar_fd(base[nb % base_l], 1, ct);
}

void	if_statement(char c, va_list args, int *ct)
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
		ft_putptr(va_arg(args, unsigned long*), ct);
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

int	main(void)
{
	ft_printf("%s", NULL);
	printf("%s", NULL);
}
