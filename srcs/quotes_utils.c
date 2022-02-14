/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:26:09 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/14 14:43:18 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	contain_quote(const char *s, int c)
{
	size_t	i;
	int		k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			k++;
		i++;
	}
	return (k);
}

/*	Find and return the first instance of any type of quote
*	single or double in the command
*/

unsigned char	which_quote(char *cmd)
{
	int				i;
	unsigned char	q;

	i = 0;
	q = 0;
	while (cmd[i] != '\0')
	{
		if (q == 0 && cmd[i] == '\"')
			q = cmd[i];
		else if (q == 0 && cmd[i] == '\'')
			q = cmd[i];
		i++;
	}
	return (q);
}

/*	Count the umber of instance of a specific quote in
*	the command
*/

int	count_quotes(char *cmd, unsigned char q)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == q)
			k++;
		i++;
	}
	if (k != 0 && k % 2 == 0)
		return (k);
	return (k);
}

static void	remove_after_quotes(t_list *node, char **ptr)
{
	int		i;
	char	*str;

	i = 0;
	str = *ptr;
	while (str[i] == node->readline[*node->read_index + i + 1])
	{
		i++;
	}
	*node->read_index += (i + 2);
	*ptr = ft_substr(str, 0, i);
	free(str);
}

char	*copy_trimmed_str(t_list *node, unsigned char q)
{
	char	**new;
	int		i;
	char	*tmp;
	char	*buf;

	i = 0;
	if (ft_strcmp(node->cmd[0], "echo") == 0
		&& ft_strcmp(node->cmd[1], "-n") == 0)
		new = ft_split(&node->readline[*node->read_index + 3], q);
	else
		new = ft_split(&node->readline[*node->read_index], q);
	if (new[i] == NULL && ft_memfreeall((void **)new))
		return (ft_strdup("\0"));
	buf = ft_strdup(new[i]);
	i++;
	while (new[i] != NULL)
	{
		tmp = ft_strjoin(buf, new[i]);
		free(buf);
		buf = tmp;
		i++;
	}
	ft_memfreeall((void **)new);
	remove_after_quotes(node, &buf);
	return (buf);
}
