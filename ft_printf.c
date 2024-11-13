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
	else if (c == '%')
		ft_putchar_fd('%', 1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		counter;

	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if_statement(*str++, args);
		}
		else
			write(1, str++, 1);
	}
	return (1);
}

#include <stdio.h>
#include <limits.h>

int	main(void)
{
	char c = 'z';
	char *str = " et luna";
	int nb = INT_MIN;
	int nb2 = INT_MAX;
	ft_printf("%d%%%c%s%%",INT_MIN, c, str);
	// printf("%%");
}