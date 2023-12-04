#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*temp;
	char			*buf;
	char			*str;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(BUFFER_SIZE));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	head = ft_lstnew(buf, fd);
	if (head->status)
		return(ft_lstclear(&head), free(buf), NULL);
	temp = head;
	if (temp->nl)
	{
		str = ft_strdup(temp->content, 0);
		if(!str)
			return (ft_lstclear(&head), free(buf), NULL);
		return (str);
	}
	while (temp->i_nl != -1)
	{
		if (ft_lstadd_back(head, fd) == 1)
			return (ft_lstclear(&head), free(buf), NULL);
		str = ft_strjoin(temp->content, temp->next->content, temp->next->i_nl);
		if (!str)
			return(ft_lstclear(&head), free(buf), NULL);
	}
	if (clean(&head))
		return(ft_lstclear(&head), free(buf), NULL);
	return (str);
}

static int	find_next_line(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0' && s[i] != EOF)
		++i;
	if (s[i] == '\0')
		return (-1);
	return ((int) i);
}

static	int	clean(t_list **head)
{
	t_list	*current;
	t_list	*prev;
	t_list	*temp;
	char	*s;

	temp = *head;
	current = *head;
	while (current->next != NULL && find_next_line(current->content) != -1)
	{
		prev = current;
		current = current->next;
	}
	*head = current;
	prev->next = NULL;
	ft_lstclear(&temp);
	s = ft_strdup(current->content, current->i_nl + 1);
	if (!s)
		return (1);
	free(current->content);
	current->content = s;
	return (0);
}
