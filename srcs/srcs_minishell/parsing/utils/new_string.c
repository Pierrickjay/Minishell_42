/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <pjay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:22:31 by pjay              #+#    #+#             */
/*   Updated: 2023/03/04 12:27:28 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"


int	count_lengh(char *str)
{
	int	size;
	int	i;
	int	tmp;

	i = -1;
	tmp = 0;
	size = (int)ft_strlen(str);
	while (str[++i])
	{
		if (str[i] == '>' && ((str[i - 1] && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ') || str[i + 1] == '>'))
		{
			if (str[i + 1] == '>')
			{
				i += 1;
				size += 2;
			}
			else
				size += 2;
		}
		else if (str[i] == '<' && ((str[i - 1] && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ') || str[i + 1] == '<'))
		{
			if (str[i + 1] == '<')
			{
				i += 1;
				size += 2;
			}
			else
				size += 2;
		}
	}
	return (size);
}

char	*new_string(char *str)
{
	char	*new_str;
	int		i;
	int		tmp;
	int		j;

	j = 0;
	i = -1;
	new_str = malloc(sizeof(char) * (count_lengh(str) + 1));
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			tmp = i;
			while (i <= go_next_quote(str, tmp, '\''))
			{
				new_str[i + j] = str[i];
				i++;
			}
			i--;
		}
		else if (str[i] == '\"')
		{
			tmp = i;
			while (i <= go_next_quote(str, tmp, '\"'))
			{
				new_str[i + j] = str[i];
				i++;
			}
			i--;
		}
		else if (str[i] != ' ' && str[i + 1] && str[i + 1] == '>')
		{
			if (str[i + 2] && str[i + 2] == '>')
			{
				new_str[i + j] = str[i];
				new_str[i + j + 1] = ' ';
				new_str[i + j + 2] = '>';
				new_str[i + j + 3] = '>';
				new_str[i + j + 4] = ' ';
				j += 2;
				i += 2;
			}
			else
			{
				new_str[i + j] = str[i];
				new_str[i + j + 1] = ' ';
				new_str[i + j + 2] = '>';
				new_str[i + j + 3] = ' ';
				j += 2;
				i += 1;
			}
		}
		else if (str[i] != ' ' && str[i + 1] && str[i + 1] == '<')
		{
			if (str[i + 2] && str[i + 2] == '<')
			{
				new_str[i + j] = str[i];
				new_str[i + j + 1] = ' ';
				new_str[i + j + 2] = '<';
				new_str[i + j + 3] = '<';
				new_str[i + j + 4] = ' ';
				j += 3;
				i += 2;
			}
			else
			{
				new_str[i + j] = str[i];
				new_str[i + j + 1] = ' ';
				new_str[i + j + 2] = '<';
				new_str[i + j + 3] = ' ';
				j += 2;
				i += 1;
			}
		}
		else
			new_str[i + j] = str[i];
	}
	new_str[i + j] = '\0';
	//str = ft_strdup_modif(new_str, 1);
	//free(str);
	return (new_str);
}

// int main(int ac, char **av)
// {
// 	char	*str = ft_strdup(av[1]);
// 	printf("str befor cut = %s\n", str);
// 	printf("new_str = %s\n", new_string(str));
// 	//free(str);
// }
