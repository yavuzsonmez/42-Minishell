/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 16:43:33 by home              #+#    #+#             */
/*   Updated: 2022/02/14 15:45:13 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	creates a new t_store_env list */

static t_store_env	*var_new(char *str, t_list *lst)
{
	t_store_env	*new_struct;
	char		*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	new_struct = NULL;
	while (ft_isalnum(*(str + i)) == 1)
		i++;
	tmp = ft_substr(str, 0, i);
	if (tmp == NULL)
		return (NULL);
	new_struct = malloc(sizeof(t_store_env));
	if (new_struct == NULL && cst_free(tmp, NULL, 0))
		return (NULL);
	new_struct->string = ft_strdup(ft_getenv(tmp, lst->env));
	if (new_struct->string == NULL && cst_free(tmp, NULL, 0))
	{
		free(new_struct);
		return (NULL);
	}
	new_struct->var_len = ft_strlen(new_struct->string);
	new_struct->next = NULL;
	free(tmp);
	return (new_struct);
}

/*	Recreates the *str by replacing env names with their values
*	based on the contents of the *var list.
*/

static void	create_str(char *str, t_dollar *re, t_store_env *var)
{
	while (str[re->i] != '\0')
	{
		if (*(str + re->i) == '$' && ft_isalnum(*(str + re->i + 1)) == 1)
		{
			copy((re->ret + re->j), var->string);
			re->i++;
			while (ft_isalnum(*(str + re->i)) != 0)
				re->i++;
			re->j += var->var_len;
			var = var->next;
		}
		else
			re->ret[re->j++] = str[re->i++];
	}
}

static int	new_translation(t_dollar *re, char *str, t_list *lst)
{
	if (0 == re->x++)
	{
		re->tmp = var_new(str + re->i++ + 1, lst);
		if (re->tmp == NULL && cst_free(NULL, re, 1))
			return (1);
		re->var = re->tmp;
	}
	else
	{
		re->tmp->next = var_new(str + re->i++ + 1, lst);
		if (re->tmp->next == NULL && cst_free(NULL, re, 1))
			return (1);
		re->tmp = re->tmp->next;
	}
	re->len_new += re->tmp->var_len;
	while (ft_isalnum(*(str + re->i)) != 0
		&& *(str + re->i) != '\0' && *(str + re->i) != '$')
		re->i++;
	return (0);
}

/*	Different pairs in env have different amount of characters
*	thus we create a list to store the env value and the length
*	of the env value.
*/

static int	create_lst(char *str, t_dollar *re, t_list *lst)
{
	while (str[re->i] != '\0')
	{
		if (*(str + re->i) == '$' && *(str + re->i + 1) != '\0'
			&& ft_isalnum(*(str + re->i + 1)) == 1)
		{
			if (new_translation(re, str, lst) == 1)
				return (1);
		}
		else if (*(str + re->i) != '\0')
		{
			re->len_new++;
			re->i++;
		}
	}
	return (0);
}

/*	Detects environment variable name in *str
*	and replaces that name with the environment value.
*/

char	*path_replace(char *str, t_list *lst)
{
	t_dollar	re;

	re.x = 0;
	re.len_new = 0;
	re.i = 0;
	re.j = 0;
	re.var = NULL;
	re.tmp = NULL;
	if (str == NULL)
		return (NULL);
	if (create_lst(str, &re, lst) == 1)
		return (NULL);
	re.ret = ft_calloc(re.len_new + 1, sizeof(char));
	if (re.ret == NULL)
		return (NULL);
	re.ret[re.len_new] = '\0';
	re.i = 0;
	create_str(str, &re, re.var);
	cst_free(str, &re, 1);
	return (re.ret);
}
