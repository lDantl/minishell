/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:19:16 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/19 12:42:11 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	**rewrite_cmd(char **argv, char **env, t_lst **cmd)
{
	int		i;
	int		str;
	char	**temp;

	i = 0;
	str = 0;
	if (*argv[0] == '>' || *argv[0] == '<')
		(*cmd)->redirs_first = 1;
	temp = (char **)malloc(((len_tab(argv) - redirect_count(argv)) + 1) * \
	sizeof(char *));
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], ">>") || !ft_strcmp(argv[i], ">")
			|| !ft_strcmp(argv[i], "<") || !ft_strcmp(argv[i], "<<"))
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

void	redirects_find(t_lst **cmd, char **env)
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
		(*cmd)->field = rewrite_cmd(ar, env, cmd);
		free_argv(ar);
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
}
