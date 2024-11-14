/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:20:39 by abbouras          #+#    #+#             */
/*   Updated: 2024/11/12 21:28:17 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

char	*ft_convert_base(char *nbr, char *base_from, char *base_to);

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + 48, fd);
}

void	ft_putnbr_base_ul(unsigned long nbr, char *base)
{
	unsigned long	base_l;

	base_l = ft_strlen(base);
	if (nbr >= base_l)
      	ft_putnbr_base_ul(nbr / base_l, base);
	ft_putchar_fd(base[nbr % base_l], 1);
}

void	ft_putptr(void *ptr)
{
	unsigned long	addr;

	addr = (unsigned long)ptr;
	ft_putstr_fd("0x", 1);
	if (addr == 0)
      	ft_putchar_fd('0', 1);
	else
      	ft_putnbr_base_ul(addr, "0123456789abcdef");
}

void	ft_putunsigned_fd(unsigned int n, int fd)
{
	if (n > 9)
		ft_putunsigned_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + 48, fd);
}

int	ft_putnbr_base(int nbr, char *base)
{
	long	nb;
	long	base_l;
	int	counter;

	counter = 0;
	nb = nbr;
	base_l = ft_strlen(base);
	if (nb >= base_l)
	{
		ft_putnbr_base(nb / base_l, base);
	}
	ft_putchar_fd(base[nb % base_l], 1);
	return (counter);
}

int	if_statement(char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	else if (c == 's')
		ft_putstr_fd(va_arg(args, char *), 1);
	else if (c == 'i' || c == 'd')
		ft_putnbr_fd(va_arg(args, int), 1);
	else if (c == 'x')
		count = ft_putnbr_base(va_arg(args, int), "0123456789abcdef");
	else if (c == 'X')
		count = ft_putnbr_base(va_arg(args, int), "0123456789ABCDEF");
	else if (c == 'u')
		ft_putunsigned_fd(va_arg(args, unsigned int), 1);
	else if (c == 'p')
		ft_putptr(va_arg(args, void *));
	else if (c == '%')
		ft_putchar_fd('%', 1);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count = if_statement(*str++, args);
		}
		else
			write(1, str++, 1);
	}
	return (count);
}

#include <stdio.h>
#include <limits.h>

int	main(void)
{
	char c = 'z';
	char *str = " et Kylian";
	int nb = INT_MIN;
	int nb2 = INT_MAX;
	unsigned int n = INT_MAX;
	ft_printf("%p\n", &n);
	printf("%p\n", &n);
	// ft_printf("%u\n", n);
}