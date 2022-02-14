/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:23:11 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/14 17:15:47 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	minishell(char *cmd, int stin, int stout, t_env *env)
{
	t_list	*data;

	while (1)
	{
		dup2(stin, 0);
		dup2(stout, 1);
		signal(SIGINT, &main_sighandler);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline("➔\t");
		if (ft_strcmp(cmd, "\0") == 0 && ft_memfree((void **)cmd))
			continue ;
		if (cmd == NULL && ft_putendl_fd("exit", 1))
			exit(1);
		signal(SIGINT, SIG_IGN);
		data = parser(cmd, env, 0, NULL);
		if (data == NULL)
		{
			data = ft_lstnew();
			init_data(data, cmd, env);
		}
		pipex(data);
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
	minishell(NULL, stin, stout, env);
	return (0);
}
