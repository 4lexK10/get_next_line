#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LIBE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# define BUFFER_SIZE 42

typedef struct s_list
{
	char			*content;
	int				cnt;
	char			*nl;
	int				i_nl;
	struct s_list	*next;
	int				status;
}					t_list;

char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2, int i_nl);
char	*ft_strdup(char const *s1, int i_nl);
t_list	*ft_lstnew(char *content, int fd);
size_t	find_next_line(char *s);
void	ft_lstclear(t_list **lst);
int		ft_lstadd_back(t_list **lst, int fd);

#endif