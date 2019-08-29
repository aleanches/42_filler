/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alexandr <Alexandr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:39:33 by vsanta            #+#    #+#             */
/*   Updated: 2019/08/29 15:42:17 by Alexandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_filler.h"

static void    ft_fl_init(t_fl **fl)
{
    if (((*fl) = (t_fl*)malloc(sizeof(t_fl))) == NULL)
		ft_lm_put_error(fl, 1);
	(*fl)->line = NULL;
	(*fl)->action = 0;
    (*fl)->player = 0;
    (*fl)->map_w = 0;
    (*fl)->map_h = 0;
    (*fl)->map = NULL;
    (*fl)->token_w = 0;
    (*fl)->token_h = 0;
    (*fl)->token = NULL;
    (*fl)->count_h = 0;
}

static int ft_lm_clean(t_fl **fl, int ret_val)
{
	ft_fl_mtx_free(&((*fl)->map), (*fl)->map_w, (*fl)->map_h, 0);
	ft_fl_mtx_free(&((*fl)->token), (*fl)->token_w, (*fl)->token_h, 0);
	if (fl && *fl)
	{
		free(*fl);
		*fl = NULL;
	}
	return (ret_val);
}

void	ft_lm_put_error(t_fl **fl, int ret_val)
{
	ft_putstr("ERROR\n");
	exit(ft_lm_clean(fl, ret_val));
}

int main(void)
{
    t_fl *fl;

    ft_fl_init(&fl);
	fl->action = 10;
	while (get_next_line(0, &(fl->line)) > 0)
	{
        if (fl->action == 10)
				fl->action = ft_fl_set_player(&fl, &(fl->line));
        else if (fl->action == 20)
			fl->action = ft_fl_set_map_size(&fl, &(fl->line));
		else if (fl->action == 30)
			fl->action = ft_fl_parse_map(&fl, &(fl->line));
		else if (fl->action == 40)
			fl->action = ft_fl_set_token_size(&fl, &(fl->line));
		else if (fl->action == 50)
			fl->action = ft_fl_parse_token(&fl, &(fl->line));
		if (fl->action == 60)
		{
			fl->action = 20;
			ft_fl_token_cut(&fl);
			ft_fl_make_move(fl, fl->player);
		}
		ft_str_free(&(fl->line), 0);
	}
	return (ft_lm_clean(&fl, 0));
}
