/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:25:41 by abbouras          #+#    #+#             */
/*   Updated: 2024/10/05 23:03:40 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_iswhitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

long	ft_check_base(char *base)
{
	long	i;
	long	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || ft_iswhitespace(base[i]))
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

long	calculate(char *str, long i, char *base, long base_size)
{
	long	res;
	long	j;

	res = 0;
	while (str[i])
	{
		j = 0;
		while (base[j])
		{
			if (str[i] == base[j])
				break ;
			j++;
		}
		if (base[j] == '\0')
			break ;
		res = res * base_size + j;
		i++;
	}
	return (res);
}

long	ft_atoi_base(char *str, char *base)
{
	long	i;
	long	symbol;
	long	base_size;

	i = 0;
	symbol = 1;
	base_size = ft_check_base(base);
	if (base_size < 2)
		return (0);
	while (ft_iswhitespace(str[i]))
		i++;
	while ((str[i] == '+' || str[i] == '-') && str[i])
	{
		if (str[i] == '-')
			symbol = -symbol;
		i++;
	}
	return (calculate(str, i, base, base_size) * symbol);
}
