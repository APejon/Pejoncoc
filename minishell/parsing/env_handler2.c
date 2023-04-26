/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 23:47:19 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/26 14:08:49 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	remove_from_line(char *input, int i)
{
	int	start;

	start = i;
	if ((input[i] == '"' && input[i + 1] == '"')
		|| (input[i] == '"' && input[i - 1] == '"')
		|| (input[i] == '\'' && input[i + 1] == '\'')
		|| (input[i] == '\'' && input[i - 1] == '\''))
		return (start + 1);
	while (input[i])
	{
		input[i] = input[i + 1];
		i++;
	}
	if (input[start] == '"' || input[start] == '\'')
		remove_from_line(input, start);
	return (start);
}

int	assign_meta(char **input, char *quote, int i)
{
	if (!(*quote) && ((*input)[i] == '\'' || (*input)[i] == '"'))
		*quote = (*input)[i];
	else if ((*quote) && (*input)[i] == (*quote))
		*quote = 0;
	if ((*input)[i] == '<' && (*input)[i + 1] == '<')
	{
		i = i + 2;
		while (((*input)[i] != '<' && (*input)[i] != '>'
			&& (*input)[i] != '|') && (*input)[i])
		{
			if ((*input)[i] == '"' || (*input)[i] == '\'')
				i = remove_from_line(*input, i);
			else
				i++;
		}
		if (!(*input)[i])
			i--;
		return (--i);
	}
	return (i);
}

char	*env_replace_hd(t_shell *shell, char *limiter)
{
	int		i;

	i = -1;
	while (limiter[++i])
	{
		if (limiter[i] == '$')
		{
			i++;
			if (is_meta_char(limiter[i]) || limiter[i] == '\n')
				continue ;
			else
			{
				limiter = replace_str_env(shell, limiter, i, 2);
				i = 0;
			}
		}
	}
	return (limiter);
}

/* Return New Allocated String, Old Substring Length with \ 
   new Substring at Index */
char	*str_replace_str_at(char *str, int idx, int length, char *replacement)
{
	char	*new_str;
	char	*tmp;

	if (ambigious_redir(str, idx, length, replacement))
		return (NULL);
	if (!str || idx < 0 || length < 0 || !replacement)
		return (NULL);
	if (idx >= (int)ft_strlen(str))
		return (ft_strjoin(str, replacement));
	if (length > (int)ft_strlen(&str[idx]))
		length = (int)ft_strlen(&str[idx]);
	str[idx] = '\0';
	tmp = ft_strjoin("\\", replacement);
	tmp = ft_free_strjoin(str, tmp, 3);
	if (!tmp)
		return (NULL);
	new_str = ft_strjoin(tmp, &str[idx + length]);
	free(tmp);
	tmp = NULL;
	if (!new_str)
		return (NULL);
	msh_free(&replacement);
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
		{
			msh_free(&env_var);
			return (ft_strdup(temp->value));
			return (env_var);
		}
		temp = temp->next;
	}
	msh_free(&env_var);
	return (ft_strdup(""));
}
