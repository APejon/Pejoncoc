/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:43:12 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/17 22:00:51 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Checks if the identifier for unset or export is invalid
 * 
 * @param identi The string containing the identifier
 * @param flag Checks whether its from "export" or "unset"
 * @return int Whether its invalid or not to reflect in an if condition
 */
int	msh_invalid(char *identi, char flag)
{
	int		i;
	char	*dup;
	char	*value;

	i = -1;
	dup = ft_strdup(identi);
	value = msh_separate(dup, '=');
	while (dup[++i])
	{
		if (dup[i] == '_' || dup[i] == '=')
			continue ;
		else if (!ft_isalnum(dup[i]))
		{
			msh_free(&dup);
			msh_free(&value);
			return (1);
		}
	}
	msh_free(&dup);
	msh_free(&value);
	if (flag == 'u')
		return (ft_strchr(identi, '=') || ft_isdigit(identi[0]));
	else if (flag == 'e')
		return (identi[0] == '=' || ft_isdigit(identi[0]));
	return (0);
}

/**
 * @brief Removes a node from the environment list using "unset"
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the command's components
 * @param i The index of the command arguments
 */
void	msh_pluck(t_shell *shell, t_command *command, int i)
{
	t_env	*check;
	t_env	*dec_check;

	if (shell->env)
	{
		check = msh_find_node(shell->env, command->cmd_args[i]);
		if (check)
			msh_remove_node(&shell->env,
				msh_find_node(shell->env, command->cmd_args[i]));
	}
	if (shell->dec_env)
	{
		dec_check = msh_find_node(shell->dec_env, command->cmd_args[i]);
		if (dec_check)
			msh_remove_node(&shell->dec_env,
				msh_find_node(shell->dec_env, command->cmd_args[i]));
	}
}

/**
 * @brief Uses the unset command to remove the variables from the environment
 * and the export list
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the command's components
 */
void	msh_unset(t_shell *shell, t_command *command)
{
	int		i;

	if (command->cmd_args[1])
	{
		i = 0;
		while (command->cmd_args[++i])
		{
			if (msh_invalid(command->cmd_args[i], 'u'))
			{
				write(2, "minishell: ", 11);
				write(2, command->cmd_args[0], ft_strlen(command->cmd_args[0]));
				write(2, ": ", 2);
				write(2, command->cmd_args[i], ft_strlen(command->cmd_args[i]));
				write(2, ": ", 2);
				write(2, "not a valid identifier\n", 23);
				shell->exit_code = 1;
				continue ;
			}
			else if (shell->dec_env)
				msh_pluck(shell, command, i);
		}
	}
	if (shell->exit_code != 1)
		shell->exit_code = 0;
}
