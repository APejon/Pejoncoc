/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:14:39 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/27 21:51:56 by amalbrei         ###   ########.fr       */
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
	value = ft_free_strjoin("\"", value, '3');
	value = ft_free_strjoin(value, "\"", '1');
	return (value);
}

/**
 * @brief Creates the first node of the linked list
 * 
 * @param head The pointer that traverses the linked list
 * @param env Environment variables gained from the int main
 * @param i The array containing the indexes
 * @return t_env* The pointer to the first node
 */
t_env	*msh_create_first(char **env, int *i)
{
	t_env		*enviro;

	enviro = malloc(sizeof(t_env));
	while (env[i[0]][i[1]] != '=')
		i[1]++;
	i[1]++;
	enviro->variable = ft_substr(env[i[0]], 0, i[1]);
	while (env[i[0]][i[1]])
	{
		i[1]++;
		i[2]++;
	}
	enviro->value = ft_substr(env[i[0]], i[1] - i[2], i[2]);
	enviro->next = NULL;
	i[1] = 0;
	i[2] = 0;
	return (enviro);
}

/**
 * @brief Creates the rest of the nodes of the linked lists
 * 
 * @param head The pointer that traverses the linked list
 * @param env Environment variables gained from the int main
 * @param i The array containing the indexes
 */
void	msh_create_rest(t_env **head, char **env, int *i)
{
	t_env	*section;

	section = malloc(sizeof(t_env));
	while (env[i[0]][i[1]] != '=')
		i[1]++;
	i[1]++;
	section->variable = ft_substr(env[i[0]], 0, i[1]);
	while (env[i[0]][i[1]])
	{
		i[2]++;
		i[1]++;
	}
	section->value = ft_substr(env[i[0]], i[1] - i[2], i[2]);
	i[2] = 0;
	i[1] = 0;
	section->next = NULL;
	(*head)->next = section;
}

/**
 * @brief Creates the entire linked list fo the shell->dec_env struct
 * 
 * @param shell The struct containing all variables for minishell
 * @param env Environment variables gained from the int main
 * @note i[0] is for counting the index of the 2D array of the 
 * environment variable
 * @note i[1] is for counting the indexes before and at the "=" sign
 * as well as counting the indexes within an single array
 * @note i[2] is for counting the indexes after the "=" sign
 */
void	msh_create_denv(t_shell **shell, char **env)
{
	int		i[3];
	t_env	*head;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	head = NULL;
	(*shell)->dec_env = msh_create_first(env, i);
	(*shell)->dec_env->value = msh_quotes((*shell)->dec_env->value);
	i[0]++;
	head = (*shell)->dec_env;
	while (env[i[0]])
	{
		msh_create_rest(&head, env, i);
		head = head->next;
		head->value = msh_quotes(head->value);
		i[0]++;
	}
}

/**
 * @brief Creates the entire linked list fo the shell->env struct
 * 
 * @param shell The struct containing all variables for minishell
 * @param env Environment variables gained from the int main
 * @note i[0] is for counting the index of the 2D array of the 
 * environment variable
 * @note i[1] is for counting the indexes before and at the "=" sign
 * as well as counting the indexes within an single array
 * @note i[2] is for counting the indexes after the "=" sign
 */
void	msh_create_env(t_shell **shell, char **env)
{
	int		i[3];
	t_env	*head;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	head = NULL;
	(*shell)->env = msh_create_first(env, i);
	i[0]++;
	head = (*shell)->env;
	while (env[i[0]])
	{
		msh_create_rest(&head, env, i);
		head = head->next;
		i[0]++;
	}
}
