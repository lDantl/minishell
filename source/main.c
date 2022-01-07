/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:36:22 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/07 17:19:33 by rdanica          ###   ########.fr       */
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
			if (mass[i][j + 1] == '|' || mass[i][j + 1] == '<'
			|| mass[i][j + 1] == '>')
			{
				j = ft_quote_redir_or_pipe(mass[i]);
				if (j)
					continue ;
			}
			else
				mass[i] = ft_quote(mass[i], env);
		}
		else if (mass[i][j] == '$')
			mass[i] = ft_dollar(mass[i], env);
	}
}

int	ft_quote_redir_or_pipe(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
	{
		if (str[i + 1] == '|'
			&& (str[i + 2] == '"' || str[i + 2] == '\''))
			return (1);
		if ((str[i + 1] == '>' || str[i + 1] == '<')
			&& (str[i + 2] == '"' || str[i + 2] == '\''))
			return (1);
		if ((str[i + 1] == '>' || str[i + 1] == '<')
			&& (str[i + 2] == '>' || str[i + 2] == '<')
			&& (str[i + 3] == '"' || str[i + 3] == '\''))
			return (1);
	}
	return (0);
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

char **argvdup(char **ar)
{
	int		i;
	char 	**new_argv;

	new_argv = (char **)malloc(sizeof(char *) * (len_tab(ar) + 1));
	i = -1;
	while (ar[++i])
		new_argv[i] = ft_strdup(ar[i]);
	new_argv[i] = NULL;
	return (new_argv);
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


int	validator(t_lst *cmd)
{
	int i;

	while (cmd)
	{
		i = -1;
		while (cmd->field[++i])
		{
			if((!ft_strcmp(cmd->field[i], ">>") || \
			!ft_strcmp(cmd->field[i], ">") || \
			!ft_strcmp(cmd->field[i], "<") || \
			!ft_strcmp(cmd->field[i], "<<")) && !cmd->field[i + 1])
			{
				printf("syntax error near unexpected token\n");
				return (0);
			}
		}
		cmd = cmd->next;
	}
	return (1);
}

char	*ft_find_path(char *cmd, char **env)
{
	char	**path_split;
	char	*path;
	int		i;

	i = 0;
	if (!cmd || !*cmd || !ft_this_built_in(cmd) || cmd[i] == '.')
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
			while (str[++i] && str[i] != '\'')
				;
			if (!str[i++])
				return (str);
		}
		if (str[i] == '\"')
		{
			while (str[++i] && str[i] != '\"')
				;
			if (!str[i++])
				return (str);
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

int	validator_ne_pidr(char **massive)
{
	int	i;

	i = -1;
	while (massive[++i])
	{
		if ((*massive[i] == '|' && !massive[i + 1]) || **massive == '|')
		{
			printf("syntax error near unexpected token '|\'\n");
			return (0);
		}
	}
	return (1);
}

void	cmd_c_sl(int signum)
{
	(void)signum;
	printf("Quit :3\n");
}

void	cmd_c_fork(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	cmd_c(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **env)
{
	t_lst	*cmd;
	t_env	*ev;
	int		i;
	char	**massive;
	char	*str;
	char	*tmp;

	i = -1;
	cmd = NULL;
	(void) argc;
	(void) argv;
	ev = ft_env_to_list(argvdup(env));
	while (1)
	{
		signal(SIGINT, cmd_c);
		signal(SIGQUIT, SIG_IGN);
		str = readline("\033[0;32mMinishell $> \033[0;29m");
		signal(SIGINT, cmd_c_fork);
		signal(SIGQUIT, cmd_c_sl);
		if (!str)
			break ;
		if (!*str)
			continue ;
		if (str)
			add_history(str);
		str = preparser(str);
		if (str == NULL)
		{
			printf("Error! Quotes are not closed\n");
			continue ;
		}
		str = ft_strtrim(str, " ");
		str = ft_space_delited(str);
		massive = ft_split_f_shell(str, ' ');
		if (!validator_ne_pidr(massive))
			continue ;
		if (str == NULL)
			return (1);
		parser(massive, env);
		recording_to_lists(&cmd, massive, env);
		if (!validator(cmd))
			continue ;
		redirects_find(&cmd);
		ft_print_result(cmd, massive);
		cmd = NULL;
	}
	return (0);
}

void	ft_print_result(t_lst *cmd, char **massive)
{
	t_lst	*temp;
	int		i;

	i = -1;
	temp = cmd;
	while (massive[++i])
		printf("MASSIVE[%d]: %s\n", i, massive[i]);
	printf("\n\n\n");
	i = -1;
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

t_env	*ft_env_to_list(char **enviroment)
{
	t_env	*env;
	int		i;

	i = -1;
	env = NULL;
	while (enviroment[++i])
	{
		lst_add_env(&env, new_env_elem(enviroment[i]));
	}
	while (env->back)
		env = env->back;
	free_argv(enviroment);
	return (env);
}

t_env	*new_env_elem(char *str)
{
	t_env	*el;
	int		n;
	int		i;

	n = 0;
	i = 0;
	el = (t_env *)malloc(sizeof(t_env));
	el->back_order = NULL;
	el->next_order = NULL;
	el->next = NULL;
	el->back = NULL;
	el->key = ft_get_key(str, &n);
	el->value = ft_get_value(str + (n + 1));
	return (el);
}

void	lst_add_env(t_env **lst, t_env *el)
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

char	*ft_get_key(char *str, int *n)
{
	if (!str || !*str)
		return (NULL);
	while (str[*n] && str[*n] != '=')
		(*n)++;
	str[*n] = '\0';
	return (ft_strdup(str));
}

char	*ft_get_value(char *str)
{
	if (!str || !*str)
		return (NULL);
	return (ft_strdup(str));
}
