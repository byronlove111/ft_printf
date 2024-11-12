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

int	if_statement(char c)
{
	if (c == 'd' || c == 'i' || c == 
}

int	ft_printf(const char *str, ...)
{
	va_list	args;

	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			if_statement(str + 1, args);	
		}
		write(1, str, 1);
		str++;
	}
	return (1);
}

#include <stdio.h>
int	main(void)
{
	ft_printf("malik %s");
	printf("malik %si", "lol");

}
