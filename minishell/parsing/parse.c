/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:18:57 by cafriem           #+#    #+#             */
/*   Updated: 2022/12/27 19:41:51 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parsing.h"

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

static void	assigns(const char *s, char **str, char c, int count)
{
	int	start_index;
	int	sp_counter;
	int	s_counter;
	int	j;
	int	i;

	i = 0;
	j = 0;
	sp_counter = 0;
	s_counter = 0;
	while (i < count && s[j])
	{
		if (s[j] == c && (sp_counter % 2 == 0 && s_counter % 2 == 0))
			j++;
		else
		{
			start_index = j;
			while (s[j] != '\0' && (s[j] != c && (sp_counter % 2 == 0 || s_counter % 2 == 0)))
			{
				while (sp_counter % 2 != 0 || s_counter % 2 != 0)
				{
					if (s[j] == '\'')
						s_counter++;
					if (s[j] == '"')
						sp_counter++;
					j++;
				}
				while (s[j] != c)
				{
					if (s[j] == '\'')
					{
						s_counter++;
						j++;
						break ;
					}
					if (s[j] == '"')
					{
						sp_counter++;
						j++;
						break ;
					}
					j++;
				}
			}
			while (s[j] == c && (sp_counter % 2 != 0 || s_counter % 2 != 0))
			{
				if (s[j] == '\'')
				{
					s_counter++;
					j++;
					break ;
				}
				if (s[j] == '"')
				{
					sp_counter++;
					j++;
					break ;
				}
				j++;
			}
			str[i] = ft_substr(s, start_index, j - start_index);
			i++;
		}
	}
	str[i] = 0;
}

static int	getwordcount(const char *s, char c)
{
	int	sp_counter;
	int	s_counter;
	int	i;
	int	j;

	i = 0;
	j = 0;
	sp_counter = 0;
	s_counter = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			s_counter++;
		if (s[i] == '\"')
			sp_counter++;
		if (s[i] == c)
		{
			i++;
			if (s[i] == c && (sp_counter % 2 == 0 && s_counter % 2 == 0))
			{
				printf("fail\n");
				// shell->command->command->"||";
				// shell->command->direct->6;
			}
		}
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			if (sp_counter % 2 == 0 && s_counter % 2 == 0)
				j++;
			i++;
		}
		else if (s[i] != c && s[i + 1] != c)
			i++;
	}
	printf("word = %d\n", j);
	return (j);
}

char	**ft_splitps(const char *s, char c)
{
	size_t		count;
	char		**str;

	if (!s)
		return (NULL);
	count = getwordcount(s, c);
	if (count == 0)
		return (NULL);
	str = (char **)malloc((count + 1) * sizeof(char *));
	if (str == NULL)
		return (str);
	assigns(s, str, c, count);
	return (str);
}

void	command_input(t_parse *parse)
{
	char	string;
	int		ncounter;
	int		counter;

	counter = 0;
	if (ft_strncmp(string, "cd ", 3) == 1
		|| ft_strncmp(string, "cd\0", 3) == 1 )
	{
		shell->command->command = "cd";
		string = ft_substr(string, 3, ft_strlen);
		ncounter = n_finder(string, shell);
		shell->command->target = ft_substr(string, 0, ncounter);
	}
	
	if (ft_strncmp(string, "export ", 7) == 1
		|| ft_strncmp(string, "export\0", 7) == 1)
		shell->command->command = "export";
	
	if (ft_strncmp(string, "pwd ", 4) == 1
		|| ft_strncmp(string, "pwd\0", 4) == 1)
		shell->command->command = "pwd";
	
	if (ft_strncmp(string, "env ", 4) == 1
		|| ft_strncmp(string, "env\0", 4) == 1)
	{
		shell->command->command = "env";
		shell->command->target = ft_substr(string, 3, ft_strlen);
	}
	
	if (ft_strncmp(string, "echo", 4) == 1)
	{
		shell->command->command = "echo";
		shell->command->target = ft_substr(string, 4, ft_strlen);
	}
	
	if (ft_strncmp(string, "exit ", 5) == 1
		|| ft_strncmp(string, "exit\0", 5) == 1)
	{
		shell->command->command = "exit";
		if (ft_strncmp(string, "exit\0", 5) == 1)
			shell->command->target = NULL;
		else
		{
			string = ft_strtrim(ft_substr(string, 5, ft_strlen), ' ');
			shell->command->target = string;
		}
	}
}

int	main(void)
{
	t_parse	parse;
	char	*string;
	int		pcounter;
	int		pc;

	string = ft_strtrim("ls | grep par");
	parse.pipe[pcounter] = ft_strtrim(parse.pipe[pcounter], ' ');
	parse.pipe = ft_splitps(parse.pipe[pcounter], '|');
	pc = ft_double_pointer_counter2(parse.pipe);
	pcounter = 0;
	while (pcounter < pc)
	{
		command_input(&parse);
		pcounter++;
	}
}
