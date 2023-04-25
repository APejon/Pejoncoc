/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:47:19 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/25 13:29:13 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Find PWD from the ENV, if not there it Get's it from Memory, /
   Return NULL if Error */
static char	*get_pwd(t_env **env)
{
	char	*pwd;

	pwd = get_env_value(env, "PWD");
	if (!pwd)
		return (NULL);
	return (pwd);
}

/* Find PWD and Returns it's Value in ENV List, PWD is Taken out of Memory */
static char	*resolving_env(t_env **env, char *env_name)
{
	if (!ft_strncmp(env_name, "PWD", 4))
		return (get_pwd(env));
	else
		return (get_env_value(env, env_name));
}

/* Allocating a New String from a Value that will Replace
   the ENV Variable, Returns NULL if Error */
char	*replace_str_env(t_shell *data, char *input, int idx, int flag)
{
	char	*new_str;
	char	*env_value;
	int		length;

	length = 0;
	while (input[idx] && (ft_isalpha(input[idx])
			|| ft_isdigit(input[idx]) || input[idx] == '_'))
	{
		idx++;
		length++;
		if (!(length - 1) && ft_isdigit(input[idx - 1]))
			break ;
	}
	new_str = ft_substr(input, idx - length, length);
	if (!new_str)
		return (NULL);
	env_value = resolving_env(&data->env, new_str);
	msh_free(&new_str);
	if (!env_value)
		return (NULL);
	new_str = str_replace_str_at(input, idx - length - 1, length + 1,
			env_value);
	if (flag == 2)
		msh_free(&input);
	return (new_str);
}

/* Check if ENV Variable is a $? and Returns \
   it if it Finds it */
static char	*check_and_get_env(t_shell *data, char *input, int idx)
{
	char	*exit_status;
	char	*ret;

	idx++;
	if (g_stdin == 1)
	{
		data->exit_code = 1;
		g_stdin = -1;
	}
	if (input[idx] && input[idx] == '?')
	{
		exit_status = ft_itoa(data->exit_code);
		ret = str_replace_str_at(input, idx - 1, 2, exit_status);
		return (ret);
	}
	else if (input[idx] == '"')
		return (ft_strdup(input));
	else
		return (replace_str_env(data, input, idx, 1));
}

/* Checks All ENV Variables in the String \
   and Resolves them */
int	env_resolver(t_shell *data, char **input)
{
	int		i;
	char	quote;
	char	*tmp;

	quote = 0;
	i = -1;
	while ((*input)[++i])
	{
		if ((!quote || quote == '"') && (*input)[i] == '$')
		{
			if (!(*input)[i + 1] || (*input)[i + 1] == '<'
				|| (*input)[i + 1] == '>' || (*input)[i + 1] == '|')
				continue ;
			tmp = check_and_get_env(data, *input, i);
			if (!tmp)
				return (0);
			free(*input);
			*input = tmp;
		}
		else
			i = assign_meta(input, &quote, i);
		if (*input[0] == '\0')
			return (0);
	}
	return (1);
}
