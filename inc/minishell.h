/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agunczer <agunczer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:29:48 by ysonmez           #+#    #+#             */
/*   Updated: 2022/02/14 16:20:17 by agunczer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

/*
*		INT MIN : -2147483648
*		INT MAX : 2147483647
*/

/*	Our lovely prompt 四ボールオメガシェル ➔ */

# include "../libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

/*	Prefix and Suffix, from where we read to where we write */

typedef enum e_fix
{
	FILE_IN		=	1,
	STDIN		=	2,
	PIPE_IN		=	3,
	HEREDOC		=	4,
	FILE_OUT	=	6,
	STDOUT		=	7,
	PIPE_OUT	=	8,
	FILE_APPEND	=	9
}	t_fix;

/*	Errors handling, global exit status variable and maccros */

int	g_exit_status;

# define PARSE_ERROR 100
# define PARSE_ERR_MSG "Parse error\n"

# define CMD_MISSING 101
# define CMD_MISSING_MSG "Command cannot be found\n"

# define FILE_MISSING 102
# define FILE_MISSING_MSG "No such file or directory\n"

# define FILE_ACCESS 103
# define FILE_ACCESS_MSG "File cannot be accessed\n"

# define STR_NOT_IN_PWD 104
# define PWD "String not in pwd\n"

# define MALLOC_FAIL "malloc() failed: insufficient memory!\n"

# define FILE_MISSING_127 105

# define TRUE 1
# define FALSE 0

/*	list to scalably store a series of *strings */

typedef struct s_words{
	char			*word;
	struct s_words	*next;
}	t_words;

/*	struct to store file descriptors */

typedef struct s_fd {
	int	infile;
	int	outfile;
	int	pipes[2];
	int	temp_fd;
}	t_fd;

/*	List to store the shell's own env
*	each node is a different env var
*	with var and value (ex: var=USER, value=ysonmez)
*/

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

/*	List to store the parsed user input data
*	Prepared for execution
*/

typedef struct s_list
{
	t_env			*env;
	int				*read_index;
	char			*readline;
	char			**cmd;
	char			*bin_path;
	char			*filein_path;
	char			*fileout_path;
	char			*hd_delimiter;
	int				suffix;
	int				prefix;
	bool			builtin;
	bool			filein_access;
	bool			fileout_access;
	int				quote_cmd;
	int				quote_in;
	int				quote_out;
	struct s_list	*next;
}	t_list;

/*	Inclusion of dollar_sign.c exclusive structs to comply
*	norm
*/

typedef struct s_store_env {
	char				*string;
	int					var_len;
	struct s_store_env	*next;
}	t_store_env;

typedef struct s_dollar {
	int			i;
	int			j;
	char		*ret;
	int			len_dst;
	int			len_new;
	int			len_src;
	int			x;
	t_store_env	*var;
	t_store_env	*tmp;
}	t_dollar;

/*	Readline has some pb on macOS, the prototype is not already implemented */
void			rl_replace_line(const char *text, int clear_undo);

/*	signals.c */
void			main_sighandler(int signal);
void			blocking_sighandler(void);
void			sig_hd(int sig);

/*	parser.c */
void			init_data(t_list *node, char *readline, t_env *env);
t_list			*parser(char *cmd, t_env *env, int i, t_list *list);

/*	syntax.c */
void			get_fix(t_list *node, char **arr, int i);
void			get_file_path(t_list *node, char **arr, int i);
void			is_file_accessible(t_list *node);
void			heredoc_delimiter(t_list *node, char **arr);

/*	cmd.c */
void			get_cmd(t_list *node, char **arr, int i);
void			is_builtin(t_list *node);

/*	cmd_path.c */
void			get_path(t_list *node);

/*	file_hd_spaces */
char			**space_fix(char **arr, int i, int j, int count);

/*	HANDLE QUOTES */
void			trim_quotes_prefix(t_list *node, unsigned char q, int k);
void			trim_quotes_suffix(t_list *node, unsigned char q, int k);
void			trim_quotes_cmd(t_list *node);
unsigned char	which_quote(char *cmd);
int				count_quotes(char *cmd, unsigned char q);
int				on_opt(char a, char b);
char			*copy_trimmed_str(t_list *node, unsigned char q);
int				contain_quote(const char *s, int c);

/*	utils.c */
int				is_opt(char *str);
int				ft_strcmp(const char *s1, const char *s2);

int				count_str(char **arr);

/*	env_lst.c */
void			get_var_value(char *env, t_env *node);
t_env			*env_create(char **envp);

/*	lst_utils.c */
t_env			*new_node(void);
t_list			*ft_lstnew(void);
void			addto_lst(t_env **lst, t_env *new);
void			ft_lstadd_back(t_list **lst, t_list *new);

/*	Built-in commands */
void			ft_cd(t_list	*lst, int err, char *home, t_env *tmp);
void			ft_echo(t_list	*lst, int i, int nl);
void			ft_env(t_list	*lst);
void			ft_exit(t_list	*lst);
void			ft_export(t_list *lst, t_env *new, t_env *tmp, t_env *to_free);
void			ft_pwd(t_list	*lst);
void			ft_unset(t_list	*lst);

/*	exec_main.c */
void			pipex(t_list *lst);

/*	exec_main_utils.c */
int				cmd_count(t_list *lst);
void			ft_wait(int cmd_cnt);
int				exit_zero(void);
int				check_fails(t_list *lst);

/*	exec_task.c */
void			execute_task(t_list *lst, t_fd *fd);

/*	exec_route.c */
void			sourceof_in_out(t_list *lst, t_fd *fd);

/*	exec_route2.c */
void			stdin_pipe_out(t_fd *fd);
void			check_if_pipe(t_list *lst, t_fd *fd);

/*	exec_utils.c */
void			copy(char *str, char *dst);
void			close_pipes(t_fd *fd);
int				exit_positive(int exit_status, char *exit_text);
int				cst_free(char *str, t_dollar *lst, int mode);
int				expansion(t_list *tmp);

/*	exec_lst_utils.c */
t_words			*ft_wordsnew(void *content);
int				ft_lstsize(t_env *env);

/*	exec_command.c */
void			command(t_list *lst, t_fd *fd);

/*	exec_heredoc.c */
void			heredoc(t_list *lst, t_fd *fd);

/*	env_get.c */
int				env_to_value_lst(t_words *words, t_list *lst);
int				env_to_value(char **words, t_list *lst);
char			*ft_getenv(char *str, t_env *lst);
int				is_same(char *str, char *src);

/*	dollar_sign.c */
char			*path_replace(char *str, t_list *env);
char			*replace(char *str, char *src, char *dst);

/*	free.c	*/
void			lst_clear_words(t_words **lst);
int				lst_clear_env(t_env **env);
int				lst_clear_data(t_list **lst, t_list *tmp, t_list *to_free);

#endif
