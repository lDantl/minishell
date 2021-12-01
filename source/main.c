/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:36:22 by rdanica           #+#    #+#             */
/*   Updated: 2021/11/30 16:14:44 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

int	check_env(char **env, char *str, int k)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[k][j++] == str[i])
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

char	*ft_dollar(char *str, char **env)
{
	int		j;
	int		i;
	int		k;
	int		z;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	j = i;
	z = 0;
	while (str[++i])
		if (!ifkey(str[i]))
			break ;
	if (i == j + 1)
		return (str);
	tmp = ft_substr(str, j + 1, i - j - 1);
	tmp2 = NULL;
	k = -1;
	while (env[++k])
	{
		if (check_env(env, tmp, k))
		{
			z = 0;
			while (env[k][z] && env[k][z] != '=')
				z++;
			tmp2 = ft_substr(env[k], 0, z);
			if (strcmp(tmp, tmp2) == 0)
				break ;
		}
	}	
	if (tmp2 != NULL)
	{
		tmp2 = ft_substr(env[k], z + 1, ft_strlen(env[k]) - z);
		tmp = ft_substr(str, 0, i - (ft_strlen(tmp) + 1));
		tmp3 = ft_substr(str, i, (ft_strlen(str) - i));
		tmp = ft_strjoin(tmp, tmp2);
		tmp = ft_strjoin(tmp, tmp3);
		printf("tmp = %s\n", tmp);
		free (str);
		return (tmp);
	}
	else
	{
		free (tmp);
		tmp = ft_substr(str, 0, j);
		tmp2 = ft_strjoin(tmp, "\"\" ");
		tmp3 = ft_substr(str, i + 1, (ft_strlen(str) - i));
		tmp = ft_strjoin(tmp2, tmp3);
		printf("TMP!!!: %s\n", tmp);
		free (str);
		return (tmp);
	}
}

char	*ft_quote(char *str, char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	if (str[i] == '\'')
		return (ft_strtrim(str, "\'"));
	else if (str[i] == '"')
	{
		if (str[++i] == '$')
		{
			tmp = ft_strtrim(str, "\"");
			tmp = ft_dollar(tmp, env);
		}
		else
			return (ft_strtrim(str, "\""));
	}
	return (tmp);
}

void	parser(char **mass, char **env)
{
	int		i;
	int		j;

	i = -1;
	while (mass[++i])
	{
		j = 0;
		if (mass[i][j] == '\'' || mass[i][j] == '"')
		{
			if (mass[i][j + 1] == '|' && (mass[i][j + 2] == '"'
			|| mass[i][j + 2] == '\''))
				continue ;
			mass[i] = ft_quote(mass[i], env);
		}
		else if (mass[i][j] == '$')
			mass[i] = ft_dollar(mass[i], env);
	}
}

t_lst	*new_cmd(char **massive, int i, int p, char **env)
{
	t_lst	*el;
	int		n;

	n = 0;
	el = (t_lst *)malloc(sizeof(t_lst));
	el->field = (char **)malloc(sizeof(char *) * p + 1);
	if (!el)
		return (NULL);
	el->next = NULL;
	el->back = NULL;
	el->redirs = NULL;
	el->field[n] = ft_find_path(massive[i], env);
	if (el->field[n] != 0)
	{
		n++;
		i++;
	}
	while (i != p)
		el->field[n++] = ft_strdup(massive[i++]);
	el->field[n] = NULL;
	return (el);
}

void	lst_add(t_lst **lst, t_lst *el)
{
	if (!el)
		return ;
	if (!(*lst))
	{
		*lst = el;
		return ;
	}
	el->back = *lst;
	(*lst)->next = el;
	*lst = el;
}

char	*preparser(char *str)
{
	int	i;
	int	q;
	int	q2;

	i = -1;
	q = 0;
	q2 = 0;
	while (str[++i])
	{
		if (str[i] == '"')
			q2++;
		if (str[i] == '\'')
			q++;
	}
	printf("quote: %d\n", q);
	printf("double_quote: %d\n\n", q2);
	if ((q % 2) != 0 || (q2 % 2) != 0)
		return (NULL);
	return (str);
}

void	recording_to_lists(t_lst **cmd, char **massive, char **env)
{
	int	i;
	int	pipe;

	i = -1;
	pipe = 0;
	while (massive[++i])
	{
		if (massive[i][0] == '|')
		{
			lst_add(cmd, new_cmd(massive, pipe, i, env));
			pipe = i + 1;
		}
	}
	lst_add(cmd, new_cmd(massive, pipe, i, env));
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
}



char	**record_redicts(char **argv)
{
	int		str;
	int		i;
	char	**temp;

	str = 0;
	i = 0;
	temp = (char **)malloc((redirect_count(argv) + 1) * sizeof(char *));
	while (argv[str])
	{
		if (!ft_strcmp(argv[str], ">>") || \
		!ft_strcmp(argv[str], ">") || \
		!ft_strcmp(argv[str], "<") || \
		!ft_strcmp(argv[str], "<<"))
		{
			temp[i] = ft_strdup(argv[str]);
			temp[i + 1] = ft_strdup(argv[str + 1]);
			i += 2;
			str += 2;
			continue ;
		}
		str++;
	}
	temp[i] = NULL;
	return (temp);
}


void	free_str(char *string_free)
{
	if (string_free)
		free(string_free);
}

void	free_argv(char **argv)
{
	int	i;

	i = -1;
	if (argv && *argv != '\0')
	{
		if (*argv)
			while (argv[++i])
				free_str(argv[i]);
	}
	if (argv)
		free(argv);
}


int	len_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	redirect_count(char **argv)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (argv[++i])
		if (!ft_strcmp(argv[i], ">>") || \
		!ft_strcmp(argv[i], ">") || \
		!ft_strcmp(argv[i], "<") || \
		!ft_strcmp(argv[i], "<<"))
			count++;
	return (count * 2);
}


char	**rewrite_cmd(char **argv)
{
	int		i;
	int		str;
	char	**temp;

	i = 0;
	str = 0;
	temp = (char **)malloc(((len_tab(argv) - redirect_count(argv)) + 1) * \
	sizeof(char *));
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], ">>") || \
		!ft_strcmp(argv[i], ">") || \
		!ft_strcmp(argv[i], "<") || \
		!ft_strcmp(argv[i], "<<"))
		{
			i += 2;
			continue ;
		}
		temp[str] = ft_strdup(argv[i]);
		str++;
		i++;
	}
	temp[str] = NULL;
	return (temp);
}


void redirects_find(t_lst **cmd)
{
	t_lst		*temp;
	char		**ar;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (*cmd)
	{
		ar = (*cmd)->field;
		if (!ar || !*ar)
		{
			*cmd = (*cmd)->next;
			continue ;
		}
		(*cmd)->redirs = record_redicts(ar);
		if (!(*cmd)->redirs)
			break ;
		(*cmd)->field = rewrite_cmd(ar);
		free_argv(ar);
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
}




int	main(int argc, char **argv, char **env)
{
	t_lst	*cmd;
	int		i;
	char	**massive;
	char	*str;
	char	*tmp;

	i = -1;
	cmd = NULL;
	(void) argc;
	(void) argv;
	while (1)
	{
		str = readline("\033[0;32mIskander $> \033[0;29m");
		if (!str)
			break ;
		if (!*str)
			continue ;
		if (str)
			add_history(str);
		printf("%s\n\n", str);
		str = preparser(str);
		str = ft_strtrim(str, " ");
		str = ft_space_delited(str);
		massive = ft_split_f_shell(str, ' ');
		while (massive[++i])
			printf("massive[%d]: %s\n", i, massive[i]);
		if (str == NULL)
			return (1);
		parser(massive, env);
		i = -1;
		recording_to_lists(&cmd, massive, env);
		redirects_find(&cmd);
		i = -1;
		printf("\n\n\n");
		while (massive[++i])
			printf("MASSIVE[%d]: %s\n", i, massive[i]);
		i = -1;
		t_lst *temp = cmd;
		while (cmd)
		{
			while (cmd->field[++i])
				printf("List[%d] %s\n\n", i, cmd->field[i]);
			i = -1;
			cmd = cmd->next;
		}
		i = -1;
		while (temp)
		{
			if (!temp->redirs || !*temp->redirs)
			{
				temp = temp->next;
				continue ;
			}
			while (temp->redirs[++i])
				printf("Rediret[%d] %s\n\n", i, temp->redirs[i]);
			i = -1;
			temp = temp->next;
		}
	}
	return (0);
}

char	*ft_find_path(char *cmd, char **env)
{
	char	**path_split;
	char	*path;
	int		i;

	i = 0;
	if (!ft_this_built_in(cmd))
		return (0);
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
		ft_error(strerror(errno));
	path_split = ft_split(env[i] + 5, ':');
	i = 0;
	while (path_split[i])
	{
		path = ft_strjoin_slash(path_split[i], cmd);
		if (access(path, F_OK) == 0)
		{
			ft_split_free(path_split);
			return (path);
		}
		free (path);
		i++;
	}
	ft_split_free(path_split);
	return (0);
}

char	*ft_strjoin_slash(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	str[i] = '/';
	i++;
	j = -1;
	while (++j < ft_strlen(s2))
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

void	ft_error(char *str)
{
	write (2, str, ft_strlen(str));
	exit (EXIT_FAILURE);
}

int	ft_this_built_in(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd"))
		return (0);
	else if (!ft_strcmp(cmd, "export"))
		return (0);
	else if (!ft_strcmp(cmd, "unset"))
		return (0);
	else if (!ft_strcmp(cmd, "cd"))
		return (0);
	else if (!ft_strcmp(cmd, "echo"))
		return (0);
	else if (!ft_strcmp(cmd, "env"))
		return (0);
	else if (!ft_strcmp(cmd, "exit"))
		return (0);
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}


char	*ft_space_delited(char *str)
{
	int		i;
	int		space;
	char	*temp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
			i++;
		}
		if (str[i] == '\"')
		{
			while (str[++i] != '\"')
				;
			i++;
		}
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			space = i;
			while (str[space++] == ' ')
				;
			str[i + 1] = '\0';
			temp = str;
			str = ft_strjoin(str, str + space - 1);
			free(temp);
		}
	}
	return (str);
}