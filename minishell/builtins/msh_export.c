/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:54 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/10 13:32:07 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Updates or adds a node within the env and dec_env, depending on
 * whether it already exists or not
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the variables of a command block
 */
void	msh_export_node(t_shell *shell, t_command *command)
{
	char	*value;
	char	*dec_value;
	t_env	*last;
	t_env	*last_dec;

	value = msh_separate(command->target, '=');
	last = msh_find_node(shell->env, command->target);
	if (last)
		msh_update_env(last, command->target, value);
	else
		msh_update_env(msh_find_last_node(shell->env), command->target,
			value);
	dec_value = ft_strjoin("\"", value);
	dec_value = ft_free_strjoin(dec_value, "\"", 1);
	last_dec = msh_find_node(shell->dec_env, command->target);
	if (last_dec)
		msh_update_env(last_dec, command->target, dec_value);
	else
		msh_update_env(msh_find_last_node(shell->dec_env), command->target,
			dec_value);
	msh_free(&value);
	msh_free(&dec_value);
}

/**
 * @brief Separates the target of export to gain the value portion of the 
 * environment variable struct
 * 
 * @param target The target containing the value
 * @return char* The value of the environment variable
 */
char	*msh_separate(char *target, char sep)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	value = ft_strchr(target, sep) + 1;
	len = ft_strlen(value);
	while (1)
	{
		if (target[i] == sep)
		{
			i++;
			break ;
		}
		i++;
	}
	value = ft_substr(target, i, len);
	ft_bzero(&target[i], len);
	return (value);
}

/**
 * @brief Prints out the declared environment variables
 * 
 * @param env Struct containing the declared environment variables
 */
void	msh_print_dec(t_env *env)
{
	pt_printf("declare -x ");
	pt_printf("%s%s\n", env->variable, env->value);
}

/**
 * @brief Lists the declared environment variables if export command is
 * executed without arguments
 * 
 * @param dec_env The struct containing the declared environment variable
 */
void	msh_list_dec(t_env *dec_env)
{
	t_env	*start;

	start = dec_env;
	while (dec_env->next != NULL)
	{
		msh_print_dec(dec_env);
		dec_env = dec_env->next;
	}
	dec_env = start;
}

/**
 * @brief Uses export command to update the environmental variable struct
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the variables of a command block
 */
void	msh_export(t_shell *shell, t_command *command)
{
	if (command->target == NULL)
		msh_list_dec(shell->dec_env);
	else if (!ft_strchr(command->target, '='))
	{
		if (msh_find_env(shell->dec_env, command->target))
			return ;
		msh_update_env(msh_find_last_node(shell->dec_env), command->target,
			NULL);
	}
	else
		msh_export_node(shell, command);
	shell->exit_code = 0;
}
