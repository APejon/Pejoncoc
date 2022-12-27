/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:43:39 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/27 14:03:28 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Counts the number of numbers within the exit command's target
 * 
 * @param target The array to be read
 * @return int The number of numbers found
 */
static	int	msh_count(char *target)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (target[i] && count < 2)
	{
		while (target[i] == ' ')
			i++;
		while (target[i] >= '0' && target[i] <= '9')
		{
			if (target[i + 1] == ' ' || target[i + 1] == '\0')
				count++;
			i++;
		}
		if (!(target[i] == ' ') && !(target[i] == '\0'))
			break ;
		else
		{
			count++;
			break ;
		}
	}
	printf("%d\n", count);
	return (count);
}

/**
 * @brief Uses the exit command to terminate the shell and gives an exit code
 * 
 * @param command The struct containing the command's components
 */
void	msh_exit(t_command *command)
{
	int	exit_code;
	int	count;

	pt_printf("exit\n");
	if (command->target == NULL)
		exit(0);
	count = msh_count(command->target);
	if (command->target)
	{
		if (count == 0)
		{
			pt_printf("minishell: %s: %s: numeric argument required\n",
				command->command, command->target);
			exit(255);
		}
		if (count > 1)
		{
			pt_printf("minishell: %s: too many arguments\n",
				command->command);
			return ;
		}
		exit_code = ft_atoi(command->target);
		exit(exit_code);
	}
}
