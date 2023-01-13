/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:18:57 by cafriem           #+#    #+#             */
/*   Updated: 2023/01/12 17:45:45 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_opr_counter(const char *c)
{
	int	op_counter;
	int	sp_mark;
	int	s_mark;
	int	i;

	op_counter = 0;
	sp_mark = 0;
	s_mark = 0;
	i = 0;
	while (c[i])
	{
		if (c[i] == '\'')
			s_mark++;
		if (c[i] == '"')
			sp_mark++;
		while ((s_mark % 2 != 0 || sp_mark % 2 != 0) && c[i])
		{
			i++;
			if (c[i] == '\'')
				s_mark++;
			if (c[i] == '"')
				sp_mark++;
			// if (!c[i])
			// 	return (0);
		}
		if ((c[i] == '>' && c[i + 1] == '>') || (c[i] == '<' && c[i + 1] == '<'))
		{
			op_counter++;
			i += 2;
		}
		else if (c[i] == '>' || c[i] == '<' || c[i] == '|' )
		{
			op_counter++;
			i++;
		}
		else
			i++;
	}
	return (op_counter);
}

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*t;
	size_t			i;
	size_t			j;
	size_t			size;

	i = start;
	j = 0;
	size = ft_strlen(s);
	if (!s)
		return (0);
	if (len > size)
		len = size;
	if (start + len > size)
		len = size - start;
	if (start >= size)
		len = 0;
	t = (char *)malloc(sizeof(char) * (len + 1));
	if (!t)
		return (0);
	while (i < size && j < len)
		t[j++] = s[i++];
	t[j] = '\0';
	return (t);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*t;
	size_t			i;
	size_t			j;
	size_t			size;

	i = start;
	j = 0;
	size = ft_strlen(s);
	if (!s)
		return (0);
	if (len > size)
		len = size;
	if (start + len > size)
		len = size - start;
	if (start >= size)
		len = 0;
	t = (char *)malloc(sizeof(char) * (len + 1));
	if (!t)
		return (0);
	while (i < size && j < len)
		t[j++] = s[i++];
	t[j] = '\0';
	return (t);
}

static void	assigns(const char *s, char **str, int count)
{
	int	start_index;
	int	sp_mark;
	int	s_mark;
	int	i;
	int	j;

	sp_mark = 0;
	s_mark = 0;
	i = 0;
	j = 0;
	while (i < count && s[j])
	{
		start_index = j;
		while (c[i] != '\0' && ((s[j] == '|' || s[j] == '>' || s[j] == '<')))
		{
			while (sp_mark % 2 != 0 || s_mark % 2 != 0)
			{
				if (s[j] == '\'')
					s_mark++;
				if (s[j] == '"')
					sp_mark++;
				j++;
			}
			while (s[j] != c)
			{
				if (s[j] == '\'')
				{
					s_mark++;
					j++;
					break ;
				}
				if (s[j] == '"')
				{
					sp_mark++;
					j++;
					break ;
				}
				j++;
			}
			while ((s[j] == '|' || s[j] == '>' || s[j] == '<')
				&& (sp_mark % 2 != 0 || s_mark % 2 != 0))
			{
				if (s[j] == '\'')
				{
					s_mark++;
					j++;
					break ;
				}
				if (s[j] == '"')
				{
					sp_mark++;
					j++;
					break ;
				}
				j++;
			}
			j++;
		}
		str[i] = ft_substr(s, start_index, j - start_index);
		i++;
	}
	str[i] = 0;
}

char	**ft_splitps(const char *s)
{
	size_t		count;
	char		**str;

	if (!s)
		return (NULL);
	count = ft_opr_counter(s);
	if (count == 0)
		return (NULL);
	str = (char **)malloc((count + 1) * sizeof(char *));
	if (str == NULL)
		return (str);
	assigns(s, str, count);
	return (str);
}

// void	command_input(t_parse *parse, t_shell shell, int counter)
// {
// 	if (ft_strncmp(parse->pipe[counter], "cd ", 3) == 1
// 		|| ft_strncmp(parse->pipe[counter], "cd\0", 3) == 1)
// 	{
// 		parse->command[counter] = ft_strdup("cd");
// 		parse->target[counter] = ft_substr(parse->pipe[counter], 3, ft_operfinder(parse->pipe[counter]));
// 		free(parse->pipe[counter]);
// 	}
	
// 	else if (ft_strncmp(parse->pipe[counter], "export ", 7) == 1
// 		|| ft_strncmp(parse->pipe[counter], "export\0", 7) == 1)
// 	{
// 		parse->command[counter] = ft_strdup("export");
// 		parse->target[counter] = ft_substr(parse->pipe[counter], 7, ft_operfinder(parse->pipe[counter]));
// 		free(parse->pipe[counter]);
// 	}
	
// 	else if (ft_strncmp(parse->pipe[counter], "pwd ", 4) == 1
// 		|| ft_strncmp(parse->pipe[counter], "pwd\0", 4) == 1)
// 	{
// 		parse->command[counter] = ft_strdup("pwd");
// 		parse->target[counter] = ft_strdup("\0");
// 		free(parse->pipe[counter]);
// 	}
	
// 	else if (ft_strncmp(parse->pipe[counter], "env ", 4) == 1
// 		|| ft_strncmp(parse->pipe[counter], "env\0", 4) == 1)
// 	{
// 		parse->command[counter] = ft_strdup("env");
// 		parse->target[counter] = ft_substr(parse->pipe[counter], 3, ft_operfinder(parse->pipe[counter]));
// 		free(parse->pipe[counter]);
// 	}
	
// 	else if (ft_strncmp(parse->pipe[counter], "echo", 4) == 1)
// 	{
// 		parse->command[counter] = ft_strdup("echo");
// 		parse->pipe[counter] = ft_substr(parse->pipe[counter], 4, ft_operfinder(parse->pipe[counter]));
// 		echo_n(parse, shell, parse->pipe[counter], counter);
// 		// parse->target[counter];
// 		free(parse->pipe[counter]);
// 	}
	
// 	else if (ft_strncmp(parse->pipe[counter], "exit ", 5) == 1
// 		|| ft_strncmp(parse->pipe[counter], "exit\0", 5) == 1)
// 	{
// 		parse->command[counter] = ft_strdup("exit");
// 		if (ft_strncmp(parse->pipe[counter], "exit\0", 5) == 1)
// 			parse->target = ft_strdup("\0");
// 		else
// 		{
// 			parse->pipe[counter] = ft_strtrim(ft_substr(parse->pipe[counter], 5, ft_operfinder(parse->pipe[counter])), ' ');
// 			parse->target[counter] = ft_substr(parse->pipe[counter], 5, ft_operfinder(parse->pipe[counter]));
// 		}
// 		free(parse->pipe[counter]);
// 	}
// }

int	main(void)
{
	t_parse	parse;
	t_shell	shell;
	char	*string;
	int		pcounter;
	int		pc;

	string = ft_strtrim("ls", ' ');
	parse.pipe = ft_splitps(parse.pipe[pcounter], '|');
	pc = ft_double_pointer_counter2(parse.pipe);
	parse.command = ft_calloc(pc + 1, sizeof(char *));
	parse.target = ft_calloc(pc + 1, sizeof(char *));
	pcounter = 0;
	while (pcounter < pc)
	{
		command_input(&parse, &shell, pcounter);
		pcounter++;
	}
}
