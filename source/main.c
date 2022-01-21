/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:36:22 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/21 21:40:57 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		while (str[++i])
		{
			if (str[i] == ' ')
				;
			else
				break ;
		}
		if (str[i] == '\0' && str[i - 1] == ' ')
		{
			free (str);
			continue ;
		}
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
		if (!validator_for_pipe_and_redir(massive))
			continue ;
		if (str == NULL)
			return (1);
		parser(massive, env);
		recording_to_lists(&cmd, massive, env);
		if (!validator(cmd))
		{
			ft_free_lst(&cmd);
			continue ;
		}
		redirects_find(&cmd, env);
		if (cmd->redirs_first == 1)
		{
			tmp = cmd->field[0];
			cmd->field[0] = ft_find_path(cmd->field[0], env);
			if (cmd->field[0] == NULL)
				cmd->field[0] = tmp;
		}
		ft_print_result(cmd, massive);
		ft_free_lst(&cmd);
		free(str);
		free_argv(massive);
	}
	return (0);
}

void	ft_print_result(t_lst *cmd, char **massive)     //_____________эта функция не нужна____________________________//
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
