/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abbouras <abbouras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:36:48 by abbouras          #+#    #+#             */
/*   Updated: 2024/11/14 17:48:42 by abbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd, int *ct);
void	ft_putstr_fd(char *s, int fd, int *ct);
void	ft_putnbr_fd(int n, int fd, int *ct);
void	ft_putnbr_base_ul(unsigned long nbr, char *base, int *ct);

#endif