/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:30:19 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/26 19:25:23 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Turns a given string into a number with type int
 * 
 * @param str String to be transformed
 * @return int Number after conversion
 */
int	ft_atoi(const char *str)
{
	int					sign;
	size_t				i;
	long long unsigned	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
	}
	if (res > 1844674407370955169 && sign == 1)
		return (-1);
	if (res > 1844674407370955169 && sign == -1)
		return (0);
	return (res * sign);
}

static long	ft_atol_helper(const char *str, int i, bool *check)
{
	long	temp;
	long	num;

	num = 0;
	temp = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = num;
		num *= 10;
		num += str[i++] - '0';
		if (temp > num)
		{
			*check = false;
			return (-1);
		}
	}
	return (num);
}

long	ft_atol(const char *str, bool *check)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	*check = true;
	while (ft_isspace(str[i]))
		i++;
	if (!ft_strncmp(&str[i], "-9223372036854775808", 20))
		return (LONG_MIN);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_atol_helper(str, i, check) * sign);
}
