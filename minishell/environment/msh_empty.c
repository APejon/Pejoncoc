/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_empty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:41:37 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/14 20:09:11 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msh_create_new_env(t_shell **shell, char *mixed)
{
	char	*value;
	t_env	*envn;

	value = ft_strchr(mixed, '=');
	envn = ft_calloc(1, sizeof(t_env));
	envn->variable = ft_strdup(mixed);
	envn->value = ft_strdup(value);
	envn->next = NULL;
	(*shell)->env = envn;
}

void	msh_create_new_d_env(t_shell **shell, char *mixed)
{
	char	*mixed_dup;
	char	*value;
	char	*value_q;
	t_env	*d_envn;

	mixed_dup = ft_strdup(mixed);
	value = NULL;
	value_q = NULL;
	if (ft_strchr(mixed_dup, '='))
	{
		value = msh_separate(mixed_dup, '=');
		value_q = msh_quotes(value);
	}
	d_envn = ft_calloc(1, sizeof(t_env));
	d_envn->variable = ft_strdup(mixed_dup);
	if (value_q)
	{
		d_envn->value = ft_strdup(value_q);
		msh_free(&value_q);
	}
	d_envn->next = NULL;
	(*shell)->dec_env = d_envn;
	msh_free(&mixed_dup);
}

void	msh_empty(t_shell **shell, char *mixed)
{
	printf("CREATION\n");
	if (ft_strchr(mixed, '=') && !(*shell)->env)
		msh_create_new_env(shell, mixed);
	if (!(*shell)->dec_env)
		msh_create_new_d_env(shell, mixed);
	else if (!ft_strchr(mixed, '=') && (*shell)->dec_env)
	{
		if (msh_find_env_ex((*shell)->dec_env, mixed))
			return ;
		msh_update_env(msh_find_last_node((*shell)->dec_env),
			mixed, NULL);
	}
}
