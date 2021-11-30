/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:53:00 by rdanica           #+#    #+#             */
/*   Updated: 2021/11/30 13:02:34 by rdanica          ###   ########.fr       */
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
# include "libft/libft.h"

typedef struct s_lst
{
	char			**field;
	struct s_lst	*next;
	struct s_lst	*back;
}	t_lst;

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

#endif