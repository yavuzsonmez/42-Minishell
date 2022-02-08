/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:37:28 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/03 16:06:51 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	heredoc_free(t_words **words)
{
	t_words	*tmp;

	if (words == NULL)
		return (1);
	tmp = *words;
	if (tmp == NULL)
		return (1);
	while (tmp != NULL)
	{
		if (tmp->word)
			free(tmp->word);
		tmp = tmp->next;
	}
	if (*words != NULL)
		free(*words);
	return (1);
}

/*	Determine and set route, then write the heredoc input FD
*	stored in a list into the output FD
*/

static void	heredoc_output(t_words *words, t_list *lst,
			t_fd *fd, char *delimiter)
{
	if (lst->suffix == FILE_OUT)
	{
		fd->outfile = open(lst->fileout_path, O_RDWR | O_CREAT | O_TRUNC, 0666);
		dup2(fd->outfile, 1);
		close(fd->outfile);
	}
	else if (lst->suffix == FILE_APPEND)
	{
		fd->outfile = open(lst->fileout_path, O_RDWR | O_CREAT
				| O_APPEND, 0666);
		dup2(fd->outfile, 1);
		close(fd->outfile);
	}
	else if (lst->suffix == PIPE_OUT)
		dup2((fd->pipes)[1], 1);
	if (env_to_value_lst(words, lst) == 1 && exit_positive(2, MALLOC_FAIL))
		exit(g_exit_status);
	while (ft_strncmp(words->word, delimiter, ft_strlen(words->word)) != 0
		|| (words->word[0] == '\0'))
	{
		write(1, words->word, ft_strlen(words->word));
		ft_putchar_fd('\n', 1);
		words = words->next;
	}
}

/*	*/

static int	heredoc_create_lst(t_words **tmp,
				t_words **words, char *str, int *x)
{
	if ((*x)-- == 1)
	{
		*tmp = ft_wordsnew(str);
		if (*tmp == NULL)
			return (1);
		*words = *tmp;
	}
	else
	{
		(*tmp)->next = ft_wordsnew(str);
		if ((*tmp)->next == NULL && heredoc_free(words))
			return (1);
		*tmp = (*tmp)->next;
	}
	return (0);
}

static t_words	*heredoc_input(char *delimiter, int x)
{
	char	*str;
	t_words	*tmp;
	t_words	*words;

	words = NULL;
	tmp = NULL;
	while (1)
	{
		str = readline("heredoc>");
		if (str == NULL)
			return (NULL);
		if (heredoc_create_lst(&tmp, &words, str, &x) == 1)
			return (NULL);
		if (str == NULL || (ft_strncmp(str, delimiter, ft_strlen(str))
				== 0 && str[0] != '\0'))
			break ;
	}
	return (words);
}

/*	Read an input stream literal until delimiter from source FD
*	into dest FD
*	NOTE: Behaves differently from general behavior of the program,
*	since readfile() writes to stdout, redirections don't
*	happen in exec_route.c, but
*	in exec_utils.c -> heredoc_output() called at the end of heredoc()
*/

void	heredoc(char *delimiter, t_list *lst, t_fd *fd)
{
	int		x;
	t_words	*words;

	signal(SIGINT, &sig_hd);
	signal(SIGQUIT, SIG_IGN);
	x = 1;
	words = NULL;
	words = heredoc_input(delimiter, x);
	if (words == NULL)
		exit(0);
	heredoc_output(words, lst, fd, delimiter);
	heredoc_free(&words);
}
