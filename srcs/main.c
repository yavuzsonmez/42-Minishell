/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:23:11 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/11 15:59:17 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_arr(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return ;
	while(arr[i] != NULL)
	{
		printf("%s\t", arr[i]);
		i++;
	}
	printf("\n");
}

void print_data(t_list	*lst)
{
	t_list *tmp;
	int i;

	tmp = lst;
	while(tmp != NULL)
	{
		i = 0;
		printf("______________________________________\n");
		print_arr(tmp->cmd);
		printf("is builtin?\t%d\n", tmp->builtin);
		printf("binpath\t%s\n", tmp->bin_path);
		printf("prefix\t%d\n", tmp->prefix);
		printf("suffix\t%d\n", tmp->suffix);
		printf("file_in_path\t%s\n", tmp->filein_path);
		printf("file_out_path\t%s\n", tmp->fileout_path);
		printf("file_in_acces\t%d\n", tmp->filein_access);
		printf("file_out_acces\t%d\n", tmp->fileout_access);
		printf("heredoc delim\t%s\n", tmp->hd_delimiter);
		tmp = tmp->next;
	}
	printf("______________________________________\n");
}

static void	minishell(int stin, int stout, t_env *env)
{
	t_list	*data;
	char	*cmd;

	while (1)
	{
		dup2(stin, 0);
		dup2(stout, 1);
		signal(SIGINT, &main_sighandler);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline("➔\t");
		if (cmd == NULL && ft_putendl_fd("exit", 1))
			exit(1);
		signal(SIGINT, SIG_IGN);
		data = parser(cmd, env, 0, NULL);
		if (data == NULL)
		{
			data = ft_lstnew();
			init_data(data, cmd, env);
		}
		print_data(data);
		//pipex(data);
		if (ft_strcmp(cmd, "") != 0)
			add_history(cmd);
		lst_clear_data(&data, NULL, NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		stin;
	int		stout;

	(void)argv;
	stin = dup(0);
	stout = dup(1);
	if (argc != 1 && ft_putendl_fd("Launch minishell without arguments", 1))
		return (1);
	env = env_create(envp);
	minishell(stin, stout, env);
	return (0);
}
