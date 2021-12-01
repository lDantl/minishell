#include "minishell.h"

char	**ft_split_free(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static	size_t	ft_get_nb_strs(char const *s, char c)
{
	size_t	i;
	size_t	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i] != c && s[i] != '\"' && s[i] != '\''
		&& s[i] != '|' && s[i] != '<' && s[i] != '>')
		nb_strs++;
	while (s[i])
	{
		if (s[i] == c)                                                             // пробелы
		{
			if ((s[i + 1] != '|' && s[i + 1] != '\'' && s[i + 1] != '"'
					&& s[i + 1] != '<' && s[i + 1] != '>')
				&& (s[i - 1] != '|' && s[i - 1] != '\''
					&& s[i - 1] != '"' && s[i - 1] != '<' && s[i - 1] != '>'))
			{
				nb_strs++;
				while (s[i] && s[i] == c)
					i++;
				continue ;
			}
			else
				i++;
		}
		if (s[i] == '|')                                                           // пайпы
			nb_strs++;
		if (s[i] == 34 || s[i] == 39)                                              // ковычки двойные и одинарные
		{
			nb_strs++;
			if (s[i++] == 34)
				while (s[i++] != 34)
					;
			else
				while (s[i++] != 39)
					;
			continue ;
			i++;
		}
		if (s[i] == '<' || s[i] == '>')                                             // редиректы
		{
			nb_strs++;
			if (s[i + 1] == '<' || s[i + 1] == '>')
				i++;
		}
		if (s[i] != c && s[i] != '\"' && s[i] != '\''
			&& s[i] != '|' && s[i] != '<' && s[i] != '>')               // остальные символы
		{
			if (s[i - 1] != c && (i != 0))
				nb_strs++;
			if (s[i - 1] == c && (s[i - 2] == '|' || s[i - 2] == '"'
					|| s[i - 2] == '\'' || s[i - 2] == '<' || s[i - 2] == '>'))
				nb_strs++;
			while (s[i] && s[i] != c && s[i] != '\"' && s[i] != '\''
				&& s[i] != '|' && s[i] != '<' && s[i] != '>')
				i++;
			continue ;
		}
		i++;
	}
	return (nb_strs);
}

static void	ft_get_next_str(char **next_str, size_t *next_str_len, char c)
{
	size_t	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		if ((*next_str)[i] == '\"')
		{
			i++;
			while ((*next_str)[i] != '\"')
			{
				i++;
				(*next_str_len)++;
			}
			i++;
			(*next_str_len) += 2;
			return ;
		}
		if ((*next_str)[i] == '\'')
		{
			i++;
			while ((*next_str)[i] != '\'')
			{
				i++;
				(*next_str_len)++;
			}
			(*next_str_len) += 2;
			i++;
			return ;
		}
		if ((*next_str)[i] == '<' || (*next_str)[i] == '>')
		{
			i++;
			(*next_str_len)++;
			if ((*next_str)[i] == '<' || (*next_str)[i] == '>')
			{
				i++;
				(*next_str_len)++;
			}
			return ;
		}
		if ((*next_str)[i] == '|')
		{
			i++;
			(*next_str_len)++;
			return ;
		}
		(*next_str_len)++;
		i++;
		if ((*next_str)[i] == '|' || (*next_str)[i] == '\"' || (*next_str)[i] == '\'' || (*next_str)[i] == '<' || (*next_str)[i] == '>')
			return ;
	}
}

char	**ft_split_f_shell(char const *s, char c)
{
	char	**buf;
	char	*next_str;
	size_t	next_str_len;
	size_t	nb_strs;
	int		i;

	if (!s)
		return (NULL);
	nb_strs = ft_get_nb_strs(s, c);
	buf = (char **)malloc(sizeof(char *) * ((nb_strs) + 1));
	if (!buf)
		return (NULL);
	i = -1;
	next_str = (char *)s;
	next_str_len = 0;
	while (++i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		buf[i] = (char *)malloc(sizeof(char) * (next_str_len + 1));
		//printf("%ld\n", next_str_len);
		if (!buf[i])
			return (ft_split_free(buf));
		ft_strlcpy(buf[i], next_str, (next_str_len + 1));
		//printf("%s\n", buf[i]);
	}
	buf[i] = NULL;
	return (buf);
}


// 'ls -la\'|\"cat\"|>1|echo| < |$fesfesfe|\"|\"|'\"$USER\"'\"\"|\"$USER\"| >> |4| << |5|echo|$PWD