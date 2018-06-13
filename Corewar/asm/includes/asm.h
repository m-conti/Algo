/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanley <mmanley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 11:36:54 by mmanley           #+#    #+#             */
/*   Updated: 2018/06/13 14:42:03 by mmanley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "ft_printf.h"
# include "op.h"

enum {D = 1, H = 2, I = 4};

typedef struct		s_pars
{
	char			*line;
	char			*label;
	char			*op_name;
	char			*value[3];
	char			*line_code;
	int				line_nb;
	int				dir_size;
	int				type[3];
	int				op_code;
	int				size_code;
	int				label_size;
	int				position;
	struct s_pars	*next;
}					t_pars;
typedef struct		s_labels
{
	int				max_size;
	struct s_pars	*lst;
	struct s_labels	*next;
}					t_labels;
typedef struct		s_op
{
	char			*op_name;
	int				nb_params;
	int				type[3];
	int				op_code;
	int				cycles;
	char			*message;
	int				oct_code;
	int				mod_dir;
}					t_op;
/*
**ERRORS
*/
void				ft_error_head_name(char *line, char *name);
void				ft_exit(char *message, int i);
void				ft_exit_str(char *name, char *mes, char c[6], char c2[6]);
void				ft_print_lst(t_pars *lst);
void				ft_error_values(char *value, int code, int counter);
void				ft_print_labeled(t_labels *lst);
void				ft_check_label(t_pars *l, int i, int counter);
void				ft_print_lst_current(t_pars *lst);
/*
**PARSING
*/
t_op				all_info(int i);
char				*check_line(char *line);
void				ft_add_lst(t_pars **lst, t_pars *new);
t_pars				*ft_check_line(char *line, t_pars *lst, header_t **head,\
	int counter);
t_pars				*ft_check_opname_type(t_pars *l, int i, int counter);
char				*ft_comment_delete(char *line);
int					ft_create_tab(char *line, int counter);
t_pars				*ft_get_code(t_pars *lst, t_labels *label, int fd, int opt);
t_pars				*ft_get_hexadecimal(t_pars *lst, int fd);
t_pars				*ft_get_info(int fd, t_labels **save, header_t **head);
t_pars				*ft_get_label(char *line, t_pars *lst, t_labels **save);
t_pars				*ft_get_label_values(t_pars *lst, t_labels *label, int k,\
	t_op *op_tab);
t_pars				*ft_get_op_name(char *line, t_pars *lst);
t_pars				*ft_get_size_code(t_pars *lst, int i, int tot_size);
t_pars				*ft_get_type(char *line, t_pars *lst);
int					ft_hd_com(char *line, header_t **head, int cnt, int len);
int					ft_hd_name(char *line, header_t **head, int cnt);
t_pars				*ft_init_lst(t_pars *lst, char *line);
t_pars				*ft_parsing(t_pars *lst, t_pars *tmp, t_labels **save);
int					ft_total_size_code(t_pars *lst, int tot_size);
/*
**FILE CREATION
*/
t_pars				*create_file(char *file, t_labels *lab, header_t *head,\
	t_pars *ops);
char				*ft_get_filename(char *name);
void				ft_write_bits(unsigned char octet, int size, int fd);
void				write_commands(int fd, t_pars *lst);
void				write_header(int fd, header_t *head);
int					byte_size(unsigned int w);
void				ft_print_params(t_pars *lst, int fd, int k, int bytes);
char				*ft_get_filename(char *name);
/*
**OPTION
*/
int					count_op_size(t_pars *lst);
t_pars				*ft_print_hexa(t_pars *lst);
char				**option_check(char **av, int ac, int *opt);
void				print_hexa(t_labels *lab, header_t *head, t_pars *ops,\
	int opt);
void				print_header(header_t *head);
char				**find_non_flag(char **av, int ac);

#endif
