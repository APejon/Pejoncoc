/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:47:19 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/08 19:41:57 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Return New Allocated String, Old Substring Length with \ 
   new Substring at Index */
char	*str_replace_str_at(char *str, int idx, int length, char *replacement)
{
	char	*new_str;
	char	*tmp;

	if (!str || idx < 0 || length < 0 || !replacement)
		return (NULL);
	if (idx >= (int)ft_strlen(str))
		return (ft_strjoin(str, replacement));
	if (length > (int)ft_strlen(&str[idx]))
		length = (int)ft_strlen(&str[idx]);
	str[idx] = '\0';
	tmp = ft_strjoin(str, replacement);
	if (!tmp)
		return (NULL);
	new_str = ft_strjoin(tmp, &str[idx + length]);
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	if (!new_str)
		return (NULL);
	return (new_str);
}

/* Returns New Allocated ENV Variable Value String from Name  */
char	*get_env_value(t_env **env, char *variable)
{
	int		variable_length;
	char	*env_var;
	t_env	*temp;

	temp = *env;
	env_var = ft_strjoin(variable, "=");
	variable_length = ft_strlen(env_var);
	while (temp)
	{
		if (!ft_strncmp(temp->variable, env_var, variable_length))
			return (temp->value);
		temp = temp->next;
	}
	return (ft_strdup(""));
}
