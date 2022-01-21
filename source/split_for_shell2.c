/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_shell2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdanica <rdanica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:14:18 by rdanica           #+#    #+#             */
/*   Updated: 2022/01/21 22:11:06 by rdanica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_get_nbr_symbols2(char const *s, char c, size_t *i, size_t *nb_strs)
{
	if (s[(*i)] == c)
	{
		if ((s[(*i) + 1] != '|' && s[(*i) + 1] != '\'' && s[(*i) + 1] != '"'
				&& s[(*i) + 1] != '<' && s[(*i) + 1] != '>')
			&& (s[(*i) - 1] != '|' && s[(*i) - 1] != '\''
				&& s[(*i) - 1] != '"' && s[(*i) - 1] != '<'
				&& s[(*i) - 1] != '>'))
		{
			(*nb_strs)++;
			while (s[(*i)] && s[(*i)] == c)
				(*i)++;
			return (2);
		}
		else
			(*i)++;
	}
	if (s[(*i)] == '|' && s[(*i) + 1] != '|')
		(*nb_strs)++;
	return (0);
}

int	ft_get_nbr_symbols(char const *s, char c, size_t *i, size_t *nb_strs)
{
	if (s[(*i)] != c && s[(*i)] != '\"' && s[(*i)] != '\''
		&& s[(*i)] != '|' && s[(*i)] != '<' && s[(*i)] != '>')
	{
		if (((*i) != 0) && s[(*i) - 1] != c)
			(*nb_strs)++;
		if ((*i) != 0 && (s[(*i) - 1] == c && (s[(*i) - 2] == '|'
					|| s[(*i) - 2] == '"' || s[(*i) - 2] == '\''
					|| s[(*i) - 2] == '<' || s[(*i) - 2] == '>')))
			(*nb_strs)++;
		while (s[(*i)] && s[(*i)] != c && s[(*i)] != '\"' && s[(*i)] != '\''
			&& s[(*i)] != '|' && s[(*i)] != '<' && s[(*i)] != '>')
		{
			(*i)++;
			if (s[(*i)] == '=' && s[(*i) + 1] != c)
			{
				(*i)++;
				while (s[(*i)] && !(s[(*i)] != '|'
						|| s[(*i)] != '<' || s[(*i)] != '>'
						|| s[(*i)] != c))
					(*i)++;
			}
		}
		return (2);
	}
	return (0);
}

size_t	ft_get_get_nbstr(char const *s, char c, size_t i, size_t nb_strs)
{
	while (s[i])
	{
		if (ft_get_nbr_symbols2(s, c, &i, &nb_strs) == 2
			|| ft_get_nbr_symbols(s, c, &i, &nb_strs) == 2)
			continue ;
		if (s[i] == 34 || s[i] == 39)
		{
			nb_strs++;
			if (s[i++] == 34)
				while (s[i++] != 34)
					;
			else
				while (s[i++] != 39)
					;
			continue ;
		}
		if (s[i] == '<' || s[i] == '>')
		{
			nb_strs++;
			if (s[i + 1] == '<' || s[i + 1] == '>')
				i++;
		}
		i++;
	}
	return (nb_strs);
}

int	if_equals(char **next_str, size_t **next_str_len, char c, int i)
{
	if ((*next_str)[i] == '=' && (*next_str)[i + 1] != c)
	{
		(*(*next_str_len))++;
		i++;
		while ((*next_str)[i] && !((*next_str)[i] == '|'
			|| (*next_str)[i] == '<' || (*next_str)[i] == '<'
			|| (*next_str)[i] == ' '))
		{
			(*(*next_str_len))++;
			i++;
		}
		return (2);
	}
	return (0);
}

int	if_redirect(char **next_str, size_t **next_str_len, char c, int i)
{
	if ((*next_str)[i] == '<' || (*next_str)[i] == '>')
	{
		i++;
		(*(*next_str_len))++;
		if ((*next_str)[i] == '<' || (*next_str)[i] == '>')
		{
			i++;
			(*(*next_str_len))++;
		}
		return (2);
	}
	if ((*next_str)[i] == '|' && (*next_str)[i + 1] != '|')
	{
		i++;
		(*(*next_str_len))++;
		return (2);
	}
	if ((*next_str)[i] == '|' && (*next_str)[i + 1] == '|')
	{
		i += 2;
		*(*next_str_len) += 2;
		return (2);
	}
	return (0);
}
