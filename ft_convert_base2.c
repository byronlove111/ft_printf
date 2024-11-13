/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 13:57:28 by abbouras          #+#    #+#             */
/*   Updated: 2024/11/13 12:43:13 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

long	ft_atoi_base(char *str, char *base);
long	ft_check_base(char *base);
long	calculate(char *str, long i, char *base, long base_size);
long	ft_iswhitespace(char c);

long	ft_nbrlen_base(long nb, long base_size)
{
	if (nb < base_size)
		return (1);
	return (1 + ft_nbrlen_base(nb / base_size, base_size));
}

void	ft_convert_to_base(char *dest, char *base_to, long i, long n)
{
	long	size;
	long	neg;

	size = ft_check_base(base_to);
	neg = 0;
	if (n < 0)
	{
		n = n * (-1);
		neg = 1;
	}
	dest[i] = '\0';
	while (i-- > 0)
	{
		dest[i] = base_to[n % size];
		n = n / size;
	}
	if (neg)
		dest[0] = '-';
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*dest;
	long	neg;
	long	n;
	long	i;

	if (ft_check_base(base_from) < 2 || ft_check_base(base_to) < 2)
		return (NULL);
	n = ft_atoi_base(nbr, base_from);
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = n * (-1);
	}
	i = ft_nbrlen_base(n, ft_check_base(base_to)) + neg;
	dest = (char *)malloc((i + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	if (neg)
		n = n * (-1);
	ft_convert_to_base(dest, base_to, i, n);
	return (dest);
}

// int	main(int ac, char **av)
// {
// 	if (ac > 1)
// 		printf("%s\n", ft_convert_base(av[1], av[2], av[3]));	
// }
