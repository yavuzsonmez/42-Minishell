/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:44:02 by home              #+#    #+#             */
/*   Updated: 2022/02/14 17:10:28 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Replaces ENV name with it's value */

int	env_to_value_lst(t_words *words, t_list *lst)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = ft_itoa(g_exit_status);
	if (tmp2 == NULL && exit_positive(2, MALLOC_FAIL))
		return (1);
	while (words)
	{
		tmp = words->word;
		words->word = replace(words->word, tmp2, "$?");
		free(tmp);
		if (words->word == NULL && exit_positive(2, MALLOC_FAIL))
			return (1);
		tmp = words->word;
		words->word = path_replace(words->word, lst);
		free(tmp);
		if (words->word == NULL && exit_positive(2, MALLOC_FAIL))
			return (1);
		words = words->next;
	}
	free(tmp2);
	return (0);
}

static int	norminator(char **words, int i, t_list *lst)
{
	char	*tmp;
	char	*tmp2;

	tmp = words[i];
	tmp2 = ft_itoa(g_exit_status);
	if (tmp2 == NULL && exit_positive(2, MALLOC_FAIL))
		return (1);
	if (lst->quote_cmd != '\'')
	{
		words[i] = replace(words[i], tmp2, "$?");
		free(tmp);
	}
	free(tmp2);
	if (words[i] == NULL && exit_positive(2, MALLOC_FAIL))
		return (1);
	tmp = words[i];
	if (lst->quote_cmd != '\'')
	{
		words[i] = path_replace(words[i], lst);
		free(tmp);
	}
	if (words[i] == NULL && exit_positive(2, MALLOC_FAIL))
		return (1);
	return (0);
}

int	env_to_value(char **words, t_list *lst)
{
	int		i;

	i = 0;
	if (words == NULL)
		return (0);
	while (words[i] != NULL)
	{
		if (norminator(words, i, lst) == 1)
			return (1);
		i++;
	}
	return (0);
}

/*	Checks if *str and *src match */

int	is_same(char *str, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == src[j] && str[i] != '\0' && str[j] != '\0')
	{
		j++;
		i++;
	}
	if (src[j] == str[i] || (src[j] == '\0' && str[i] == '\0'))
		return (TRUE);
	else
		return (FALSE);
}

/*	Takes *str, and tries it against the names of the env
*	if *str == env[i] -> TRUE, returns the value of the env[i]
*	if FALSE, returns an empty string
*/

char	*ft_getenv(char *str, t_env *lst)
{
	while (str && lst)
	{
		if (is_same(str, lst->var) == 1)
			return (lst->value);
		lst = lst->next;
	}
	return (ft_strdup(""));
}
