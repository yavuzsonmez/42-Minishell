/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:45:22 by home              #+#    #+#             */
/*   Updated: 2022/01/26 13:33:32 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

typedef struct s_replace {
	int		i;
	int		j;
	char	*ret;
	int		len_dst;
	int		len_new;
	int		len_src;
}	t_replace;

/*	Recreates the *str by replacing every instance of
*	*dst by *src
*/

static void	create_str(char *str, t_replace *re, char *src, char *dst)
{
	while (str[re->i] != '\0')
	{
		if (ft_strncmp((str + re->i), dst, ft_strlen(dst)) == 0)
		{
			copy((re->ret + re->j), src);
			re->i += re->len_dst;
			re->j += re->len_src;
		}
		else
			re->ret[re->j++] = str[re->i++];
	}
}

static void	calculate_size(t_replace *re, char *str, char *dst)
{
	while (str[re->i] != '\0')
	{
		if (ft_strncmp((str + re->i), dst, ft_strlen(dst)) == 0)
		{
			re->len_new += re->len_src;
			re->i += re->len_dst;
		}
		else
		{
			re->len_new++;
			re->i++;
		}
	}
}

/*	Function that replaces every instance of *dst
*	to *src in the given *str
*/

char	*replace(char *str, char *src, char *dst)
{
	t_replace	re;

	re.len_new = 0;
	re.len_src = ft_strlen(src);
	re.len_dst = ft_strlen(dst);
	re.i = 0;
	re.j = 0;
	if (str == NULL)
		return (NULL);
	calculate_size(&re, str, dst);
	re.ret = ft_calloc(re.len_new + 1, sizeof(char));
	if (re.ret == NULL)
		return (NULL);
	re.ret[re.len_new] = '\0';
	re.i = 0;
	create_str(str, &re, src, dst);
	return (re.ret);
}
