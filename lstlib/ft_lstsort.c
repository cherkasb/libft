/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:52:15 by bcherkas          #+#    #+#             */
/*   Updated: 2017/11/21 16:45:05 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		splitlist(t_list *src, t_list **p1, t_list **p2)
{
	t_list	*fast;
	t_list	*slow;

	if (src == NULL || src->next == NULL)
	{
		*p1 = src;
		return ;
	}
	slow = src;
	fast = src->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*p1 = src;
	*p2 = slow->next;
	slow->next = NULL;
}

t_list		*mergesorted(t_list *p1, t_list *p2, int (*cmp)(t_list *, t_list *))
{
	t_list	*ret;

	if (!p1)
		return (p2);
	else if (!p2)
		return (p1);
	ret = NULL;
	if (cmp(p1, p2))
	{
		ret = p1;
		ret->next = mergesorted(p1->next, p2, cmp);
	}
	else
	{
		ret = p2;
		ret->next = mergesorted(p1, p2->next, cmp);
	}
	return (ret);
}

void		ft_lstsort(t_list **player, int (*cmp)(t_list *, t_list *))
{
	t_list	*head;
	t_list	*p1;
	t_list	*p2;

	head = *player;
	if (head == NULL || head->next == NULL)
		return ;
	p1 = NULL;
	p2 = NULL;
	splitlist(head, &p1, &p2);
	ft_lstsort(&p1, cmp);
	ft_lstsort(&p2, cmp);
	*player = mergesorted(p1, p2, cmp);
}
