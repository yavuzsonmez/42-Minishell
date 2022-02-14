/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:37:28 by agunczer          #+#    #+#             */
/*   Updated: 2022/02/14 16:40:25 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	heredoc_free(t_words **words)
{
	t_words	*tmp;

	tmp = NULL;
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

static void	heredoc_output(t_list *lst, t_fd *fd, int fdt[2])
{
	int	stout;

	stout = dup(1);
	close(fd->temp_fd);
	dup2(fdt[0], 0);
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
	command(lst, fd);
	close(fdt[0]);
	close(fd->pipes[1]);
	dup2(stout, 1);
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

static t_words	*heredoc_input(int x, t_list *lst, int fdt[2], char *str)
{
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
		if (str == NULL || (ft_strncmp(str, lst->hd_delimiter, ft_strlen(str))
				== 0 && str[0] != '\0'))
			break ;
	}
	if (env_to_value_lst(words, lst) == 1 && exit_positive(2, MALLOC_FAIL))
		exit(1);
	tmp = words;
	while (tmp && is_same(tmp->word, lst->hd_delimiter) != 1
		&& ft_putendl_fd(tmp->word, fdt[1]))
		tmp = tmp->next;
	close(fdt[1]);
	return (words);
}

/*	Read an input stream literal until delimiter from source FD
*	into dest FD
*	NOTE: Behaves differently from general behavior of the program,
*	since readfile() writes to stdout, redirections don't
*	happen in exec_route.c, but
*	in exec_utils.c -> heredoc_output() called at the end of heredoc()
*/

void	heredoc(t_list *lst, t_fd *fd)
{
	t_words	*words;
	int		x;
	int		fdt[2];
	int		stout;

	signal(SIGINT, &sig_hd);
	signal(SIGQUIT, SIG_IGN);
	stout = dup(1);
	x = 1;
	words = NULL;
	pipe(fdt);
	close(fd->temp_fd);
	words = heredoc_input(x, lst, fdt, NULL);
	dup2(stout, 1);
	if (words == NULL)
		exit(0);
	heredoc_output(lst, fd, fdt);
	heredoc_free(&words);
}
