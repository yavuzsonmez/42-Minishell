/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysonmez <ysonmez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:18:26 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/11 15:17:53 by ysonmez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Heredoc signals are handled like this in child process
*		signal(SIGINT, &sig_hd)
*		signal(SIGQUIT, SIG_IGN)
*		(Overwrite signal handling of blocking commands because called later)
*/

void	sig_hd(int sig)
{
	struct termios	flags;

	tcgetattr(1, &flags);
	if ((flags.c_lflag & (0x1 << 6)) == ECHOCTL)
	{
		flags.c_lflag -= ECHOCTL;
		tcsetattr(1, TCSANOW, &flags);
	}
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		exit(1);
	}
	else if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		exit(1);
	}
}

/*	Blocking commands signals are handled like this	in child process
*			signal(SIGINT, SIG_DFL)
*			signal(SIGQUIT, SIG_DFL)
*		If the child process was terminated due to receipt of a signal
*		The parent process will trigger this fct to imitate the default
*		behavior of bash
*/

void	blocking_sighandler(void)
{
	if (WTERMSIG(g_exit_status) == SIGINT)
	{
		ft_putstr_fd("^C\n", 2);
		exit_positive(130, NULL);
	}
	else if (WTERMSIG(g_exit_status) == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit: 3\n", 2);
		exit_positive(131, NULL);
	}
}

/*	Main
*/

void	main_sighandler(int signal)
{
	struct termios	flags;

	if (signal == SIGINT)
	{
		tcgetattr(1, &flags);
		if ((flags.c_lflag & (0x1 << 6)) == ECHOCTL)
		{
			flags.c_lflag -= ECHOCTL;
			tcsetattr(1, TCSANOW, &flags);
		}
		exit_positive(1, NULL);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
