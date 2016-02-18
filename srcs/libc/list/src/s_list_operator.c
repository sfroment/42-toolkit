/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_list_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qperez <qperez42@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/08/30 22:50:59 by qperez            #+#    #+#             */
/*   Updated: 2014/01/08 17:55:59 by qperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** <This file contains s_list_operator method>
** < foreach, reverse, delete_if, delete >
** Copyright (C) <2013>  Quentin Perez <qperez42@gmail.com>
** This file is part of 42-toolkit.
** 42-toolkit is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <list/s_list.h>
#include <stddef.h>
#include <stdlib.h>

bool		f_list_foreach(t_list *v_this, bool (*funct)(void *data))
{
	t_list_cell	*cur;

	cur = v_this->v_begin;
	while (cur != NULL)
	{
		if (funct(cur->v_data) == false)
			return (false);
		cur = cur->v_next;
	}
	return (true);
}

void		f_list_reverse(t_list *v_this)
{
	t_list_cell	*begin;
	t_list_cell	*end;
	void		*tmp;

	end = v_this->v_end;
	begin = v_this->v_begin;
	while (begin != end)
	{
		tmp = begin->v_data;
		begin->v_data = end->v_data;
		end->v_data = tmp;
		if (end->v_prev == begin)
			break ;
		begin = begin->v_next;
		end = end->v_prev;
	}
}

t_list_cell	*f_list_delete(t_list *v_this, t_list_cell *mb_del)
{
	void		*del;
	t_list_cell	*ret;

	ret = D_LIST(erase)(v_this, mb_del, &del);
	v_this->f_destroy(del);
	return (ret);
}

void		f_list_delete_if(t_list *v_this,
							bool (*cmp)(void *data, void *value), void *value)
{
	t_list_cell	*cur;

	cur = v_this->v_begin;
	while (cur != NULL)
	{
		if (cmp(cur->v_data, value) == true)
			cur = D_LIST(delete)(v_this, cur);
		else
			cur = cur->v_next;
	}
}

bool		f_list_copy(t_list *v_this, t_list *from_list)
{
	t_list_cell	*cur;

	D_LIST(clear)(v_this);
	cur = from_list->v_begin;
	while (cur != NULL)
	{
		if (D_LIST(push_back)(v_this, cur->v_data) == false)
			return (false);
		cur = cur->v_next;
	}
	return (true);
}
