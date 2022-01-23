/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:53:00 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/23 13:44:09 by rdanica          ###   ########.fr       */
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
# include "../libft1/libft.h"

typedef struct s_lst
{
	char			**field;
	char			**redirs;
	struct s_lst	*next;
	struct s_lst	*back;
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

typedef struct s_msh
{
	t_env            *env;
	t_lst            *cmd;
	char            **envp;
	int                in;
	int                out;
	int                fdin;
	int                fdout;
	int                ret;
	int                **pipefd;
	int                pid;
	int				**herdocfd;
	int				herdocnum;
}    t_msh;

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
int		validator_for_pipe_and_redir2(char **mass, int *i);
int		ft_get_nbr_symbols2(char const *s, char c, size_t *i, size_t *nb_strs);
int		ft_get_nbr_symbols(char const *s, char c, size_t *i, size_t *nb_strs);
size_t	ft_get_get_nbstr(char const *s, char c, size_t i, size_t nb_strs);
int		if_equals(char **next_str, size_t **next_str_len, char c, int i);
int		if_redirect(char **next_str, size_t **next_str_len, char c, int i);
int		if_quotes(char **next_str, size_t **next_str_len, char c, int i);
void	cmd_c_sl(int signum);
void	cmd_c_fork(int signum);
void	cmd_c(int signum);
void	free_argv(char **argv);
char	**argvdup(char **ar);
int		validator_for_pipe_and_redir(char **mass);
int		validator(t_lst *cmd);
void	redirects_find(t_lst **cmd, char **env);
void	qwerty(t_lst *cmd, char **env);


int    built_in(char *cmd);

//j_start.c
void	ft_free_env(t_env *env);
void	ft_free_msh(t_msh *msh);
void	ft_print_error(char *name, char *error, int num);
void	ft_error_exit(char *name, char *error, int num, t_msh *msh);
void	ft_inc_shlvl(t_msh *msh);

//j_minishell.c
void	ft_close(int fd);
int		ft_is_red(char *s);
void	ft_minishell(t_msh *msh);

//j_redirs.c
void	ft_redirs(t_lst *temp, t_msh *msh, int num_pipe);

//j_pipex.c
void	ft_free_fds(t_msh *msh);
int	**ft_create_pipe(int count, t_msh *msh);
void	ft_pipex(int count, t_msh *msh);

//j_built_in.c
void	ft_echo(t_lst *cmd, t_msh *msh);
void	ft_env(t_lst *cmd, t_msh *msh);
void	ft_pwd(t_msh *msh);
int		ft_exit(t_lst *cmd, t_msh *msh);

//j_export.c
int		ft_envp_count(t_env **env);
void	ft_print_error_export(char *arg);
int		ft_export(t_lst *cmd, t_msh *msh);

//j_unset.c
void	ft_rewrite_envp(t_msh *msh);
void	ft_unset(t_lst *cmd, t_msh *msh);

//j_envp.c
char	**ft_my_envp(t_msh *msh);
int		ft_change_env(char *key, char *value, t_msh *msh);
int		ft_add_env(char *key, char *value, t_msh *msh);

//j_sort_env.c
int		ft_env_count(t_env **env);
int		ft_print_sorted_env(t_msh *msh);

//j_cd.c
void	ft_cd(t_lst *cmd, t_msh *msh);

// j_herdoc.c
int		ft_herdoc_count(t_msh *msh);
void	ft_herdocs_input(t_msh *msh);
void	ft_inc_herdocnum(t_lst *temp, t_msh *msh);
void	ft_herdoc(char **redirs, t_msh *msh, t_lst *temp, int num_pipe);

// j_utils.c
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(const char *s1, int n);
int		ft_strisnum(const char *str);
void	ft_free_strs(char **strs, int len);
int		ft_strs_count(char **strs);

#endif
 