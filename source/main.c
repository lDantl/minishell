/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 23:28:34 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/23 19:56:12 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_msh	*ft_msh(t_env	*ev)
{
	t_msh	*msh;

	msh = (t_msh *)malloc(sizeof(t_msh));
	if (!msh)
	{
		ft_print_error("main", "malloc error", 0);
		ft_free_env(ev);
		exit (1);
	}
	msh->env = ev;
	msh->envp = ft_my_envp(msh);
	msh->cmd = NULL;
	return (msh);
}

void	ft_start(t_msh *msh, t_lst *cmd)
{
	msh->cmd = cmd;
	msh->in = dup(0);
	msh->out = dup(1);
	msh->fdin = -1;
	msh->fdout = -1;
	msh->ret = 0;
	msh->pipefd = NULL;
	msh->herdocfd = NULL;
	msh->pid = -1;
	msh->herdocnum = -1;
	if (msh->in == -1 || msh->out == -1)
		ft_print_error("main", 0, errno);
	else
		ft_minishell(msh);
}

int	parsing(char *str, t_lst **cmd, char **env)
{
	char	**massive;

	if (!preparser(str))
	{
		printf("Error! Quotes are not closed\n");
		return (1);
	}
	str = ft_trim(str, " ");
	str = ft_space_delited(str);
	massive = ft_split_f_shell(str, ' ');
	free (str);
	if (!validator_for_pipe_and_redir(massive))
		return (1);
	parser(massive, env);
	recording_to_lists(cmd, massive, env);
	if (!validator(*cmd))
	{
		ft_free_lst(cmd);
		return (1);
	}
	redirects_find(cmd, env);
	final_find(*cmd, env);
	free_argv(massive);
	return (0);
}

void	circle(t_lst *cmd, char **env, t_msh *msh)
{
	char	*str;

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
		if (parsing(str, &cmd, env))
			continue ;
		ft_print_result(cmd);
		ft_start(msh, cmd);
		ft_free_lst(&cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_lst	*cmd;
	t_env	*ev;
	t_msh	*msh;

	cmd = NULL;
	(void)argc;
	(void)argv;
	if (*env)
		ev = ft_env_to_list(argvdup(env));
	else
		ev = NULL;
	msh = ft_msh(ev);
	ft_inc_shlvl(msh);
	circle(cmd, env, msh);
	return (0);
}
