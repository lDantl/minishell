/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_built_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtawanda <jtawanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:54:34 by jtawanda          #+#    #+#             */
/*   Updated: 2022/01/21 15:08:31 by jtawanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' && str[1] != 'n')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_lst *cmd, t_msh *msh)
{
	int		i;
	int		n;
	char	*temp;

	i = 1;
	n = 0;
	while (cmd->field[i] && ft_is_n(cmd->field[i]))
	{
		n = 1;
		i++;
	}
	while (cmd->field[i])
	{
		temp = ft_strtrim(cmd->field[i], "\"");
		if (!temp)
			ft_error_exit("ft_echo", "malloc error", 0, msh);
		ft_putstr_fd(temp, 1);
		free(temp);
		if (cmd->field[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 1);
}

void	ft_env(t_lst *cmd, t_msh *msh)
{
	t_env	*temp;

	if (cmd->field[1])
	{
		ft_print_error("env", "too many arguments", 0);
		msh->ret = 1;
		return ;
	}
	temp = msh->env;
	while (temp)
	{
		if (temp->value)
		{
			ft_putstr_fd(temp->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(temp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		temp = temp->next;
	}
}

void	ft_pwd(t_msh *msh)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
	{
		ft_putendl_fd(buf, 1);
		free(buf);
	}
	else
		ft_error_exit("pwd", "getcwd error", 0, msh);
}

int	ft_exit(t_lst *cmd, t_msh *msh)
{
	ft_putendl_fd("exit", 2);
	if (cmd->field[1] && ft_strisnum(cmd->field[1]) == 0)
	{
		msh->ret = 255;
		ft_putstr_fd("Minishell: exit: ", 2);
		ft_putstr_fd(cmd->field[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (cmd->field[1] && cmd->field[2])
	{
		msh->ret = 1;
		ft_print_error("exit", "too many arguments", 0);
	}
	else if (cmd->field[1])
		msh->ret = ft_atoi(cmd->field[1]);
	else
		msh->ret = 0;
	ft_free_msh(msh);
	exit(msh->ret);
}
