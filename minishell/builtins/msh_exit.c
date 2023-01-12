/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:43:39 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/10 13:31:59 by amalbrei         ###   ########.fr       */
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
	int	count[2];

	count[0] = 0;
	count[1] = 0;
	while (target[count[0]] && count[1] < 2)
	{
		while (target[count[0]] == ' ')
			count[0]++;
		if (target[count[0]] == '+' || target[count[0]] == '-')
			count[0]++;
		while ((target[count[0]] >= '0' && target[count[0]] <= '9'))
		{
			if (target[count[0] + 1] == ' ' || target[count[0] + 1] == '\0')
				count[1]++;
			count[0]++;
		}
		if (target[count[0]] != ' ' && target[count[0]] != '\0')
		{
			if (count[1] == 0)
				break ;
			else
				count[1]++;
		}
	}
	return (count[1]);
}

/**
 * @brief Uses the exit command to terminate the shell and gives an exit code
 * 
 * @param command The struct containing the command's components
 */
void	msh_exit(t_shell *shell, t_command *command)
{
	int	exit_code;
	int	count;

	pt_printf("exit\n");
	if (!command->target)
	{
		msh_free_list(&shell->env);
		msh_free_list(&shell->dec_env);
		exit(0);
	}
	count = msh_count(command->target);
	if (command->target)
	{
		if (count == 0)
		{
			pt_printf("minishell: %s: %s: numeric argument required\n",
				command->command, command->target);
			msh_free_list(&shell->env);
			msh_free_list(&shell->dec_env);
			exit(255);
		}
		if (count > 1)
		{
			pt_printf("minishell: %s: too many arguments\n",
				command->command);
			shell->exit_code = 1;
			return ;
		}
		msh_free_list(&shell->env);
		msh_free_list(&shell->dec_env);
		exit_code = ft_atoi(command->target);
		exit(exit_code);
	}
}
