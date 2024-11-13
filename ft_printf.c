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

static long	find_size(long nb)
{
	long	size;

	size = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		size++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nb;
	long	i;
	char	*str;

	nb = n;
	i = find_size(nb) - 1;
	str = malloc(sizeof(char) * find_size(nb) + 1);
	if (!str)
		return (NULL);
	str[i + 1] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	return (str);
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

void	ft_putunsigned_fd(unsigned int n, int fd)
{
	if (n > 9)
		ft_putunsigned_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + 48, fd);
}

int	print_hex(char c, va_list args)
{
	char	*ascii;
	char	*str;
	int	count;

	count = 0;
	ascii = ft_itoa(va_arg(args, int));
	if (c == 'X')
		str = ft_convert_base(ascii, "0123456789", "0123456789abcdef");
	else
		str = ft_convert_base(ascii, "0123456789", "0123456789ABDCDEF");
	count = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(ascii);
	free(str);
	return (count);	
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
	else if (c == 'x' || c == 'X')
		count = print_hex(c, args);
	// else if (c == 'u')
	// 	ft_putunsigned_fd(va_arg(args, unsigned int), 1);
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
	char *str = " et luna";
	int nb = INT_MIN;
	int nb2 = INT_MAX;
	int n = -3243212;
	// ft_printf("%d     %cccccc%%%s    ",INT_MIN, c, str);
	printf("%x\n", n);
	ft_printf("%x\n", n);
}