/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:53:00 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/15 18:52:52 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <locale.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <editline/readline.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct s_lst
{
	char			**field;
	char			**redirs;
	struct s_lst	*next;
	struct s_lst	*back;
	int				redirs_first;
}	t_lst;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*back;
	struct s_env	*next_order;
	struct s_env	*back_order;
}	t_env;

char	*preparser(char *str);
char	**ft_split_f_shell(char const *s, char c);
char	*ft_dollar(char *str, char **env);
char	*ft_quote(char *str, char **env);
void	parser(char **mass, char **env);
int		main(int argc, char **argv, char **env);
int		ifkey(char c);
void	lst_add(t_lst **lst, t_lst *el);
t_lst	*new_cmd(char **massive, int i, int p, char **env);
void	recording_to_lists(t_lst **cmd, char **massive, char **env);
char	**ft_split_free(char **tab);
char	*ft_find_path(char *cmd, char **env);
char	*ft_strjoin_slash(char const *s1, char const *s2);
void	ft_error(char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_this_built_in(char *cmd);
int		redirect_count(char **argv);
int		len_tab(char **str);
char	*ft_space_delited(char *str);
int		ft_quote_redir_or_pipe(char *str);
void	ft_print_result(t_lst *cmd, char **massive);
void	rl_replace_line(const char *text, int clear_undo);
t_env	*ft_env_to_list(char **enviroment);
t_env	*new_env_elem(char *str);
void	lst_add_env(t_env **lst, t_env *el);
char	*ft_get_key(char *str, int *n);
char	*ft_get_value(char *str);
void	ft_free_lst(t_lst **cmd);

#endif