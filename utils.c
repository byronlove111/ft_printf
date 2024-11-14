/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:29:56 by abbouras          #+#    #+#             */
/*   Updated: 2024/11/14 17:41:43 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
