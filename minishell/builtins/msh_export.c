/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:42:54 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/27 18:39:03 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds double quotation marks to the value of the declared environment
 * variable
 * 
 * @param value The value to be double quoted
 * @return char* The value with double quotes
 */
char	*msh_quotes(char *value)
{
	value = ft_free_strjoin("\"", value, 3);
	value = ft_free_strjoin(value, "\"", 1);
	return (value);
}

/**
 * @brief Separates the target of export to gain the value portion of the 
 * environment variable struct
 * 
 * @param target The target containing the value
 * @return char* The value of the environment variable
 */
char	*msh_separate(char *target)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	value = ft_strchr(target, '=') + 1;
	len = ft_strlen(value);
	while (1)
	{
		if (target[i] == '=')
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
 */
void	msh_export(t_shell *shell, t_command *command)
{
	char	*dec_value;

	if (command->target == NULL)
		msh_list_dec(shell->dec_env);
	else if (!ft_strchr(command->target, '='))
	{
		msh_create_node(msh_find_last_node(shell->dec_env),
			command->target, NULL);
	}
	else
	{
		dec_value = msh_separate(command->target);
		msh_create_node(msh_find_last_node(shell->env),
			command->target, dec_value);
		dec_value = msh_quotes(dec_value);
		msh_create_node(msh_find_last_node(shell->dec_env),
			command->target, dec_value);
		msh_free(&dec_value);
	}
}
