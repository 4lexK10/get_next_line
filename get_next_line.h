/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:53:47 by akloster          #+#    #+#             */
/*   Updated: 2023/12/05 12:53:47 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif
typedef struct s_list
{
	char			*content;
	int				cnt;
	char			*nl;
	int				i_nl;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2, int i_nl);
char	*ft_strdup(char const *s1, int special_case);
t_list	*ft_lstnew(char *buf, int fd);
void	ft_lstclear(t_list **lst);
int		ft_lstadd_back(t_list **lst, int fd);
int		ft_strlen(char const *s);
int		find_next_line(char *s);

#endif