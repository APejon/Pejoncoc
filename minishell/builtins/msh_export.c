/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:54 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/19 19:22:58 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Updates the environment and declared environment variables
 * 
 * @param shell The struct containing variables of used within the shell
 * @param target Whatever is inputted BEFORE the '='
 * @param value Whatever is inputted AFTER the '='
 * 
 * @note value might contain a null terminator ONLY
 */
void	msh_export_node(t_shell *shell, char *target, char *value)
{
	char	*dec_value;
	t_env	*node;
	t_env	*dec_node;

	node = msh_find_node(shell->env, target);
	if (node)
		msh_update_env(node, target, value);
	else
		msh_update_env(msh_find_last_node(shell->env), target,
			value);
	if (*value == '\0')
		dec_value = ft_strdup("\"\"");
	else
		dec_value = msh_quotes(value);
	dec_node = msh_find_node(shell->dec_env, target);
	if (dec_node)
		msh_update_env(dec_node, target, dec_value);
	else
		msh_update_env(msh_find_last_node(shell->dec_env), target,
			dec_value);
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
	if (*value == '\0')
		value = ft_strdup("\0");
	else
		value = ft_substr(target, i, len);
	ft_bzero(&target[i], len);
	return (value);
}

/**
 * @brief Prepares the arguments to be placed in the environment variables
 * 
 * @param shell The struct containing variables of used within the shell
 * @param cmd The struct containing the command's arguments
 * @param target The argument selected
 */
void	msh_prep_export(t_shell *shell, t_command *cmd, char *target)
{
	char	*value;
	t_env	*check;

	if (target[0] == '=')
	{
		msh_print_error(shell, shell->command, "not a valid identifier", 1);
		return ;
	}
	value = msh_separate(target, '=');
	check = msh_find_node(shell->env, target);
	if (check)
	{
		if (!ft_strncmp(check->value, value, ft_strlen(value)))
		{
			msh_free(&value);
			return ;
		}
	}
	msh_export_node(shell, target, value);
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
		pt_printf("declare -x ");
		pt_printf("%s%s\n", dec_env->variable, dec_env->value);
		dec_env = dec_env->next;
	}
	dec_env = start;
}

/**
 * @brief Uses export command to update the environmental variable struct
 * 
 * @param shell The struct containing variables of used within the shell
 * @param command The struct containing the command's arguments
 */
void	msh_export(t_shell *shell, t_command *cmd)
{
	int	i;

	if (cmd->cmd_args[1] == NULL)
		msh_list_dec(shell->dec_env);
	else
	{
		i = 0;
		while (cmd->cmd_args[++i])
		{
			if (!ft_strchr(cmd->cmd_args[i], '='))
			{
				if (msh_find_env(shell->dec_env, cmd->cmd_args[i]))
					continue ;
				msh_update_env(msh_find_last_node(shell->dec_env),
					cmd->cmd_args[i], NULL);
			}
			else
				msh_prep_export(shell, cmd, cmd->cmd_args[i]);
		}
	}
	shell->exit_code = 0;
}
