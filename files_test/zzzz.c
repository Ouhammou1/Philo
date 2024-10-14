/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zzzz.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:13:06 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/11 20:13:07 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

int main()
{
	pthread_mutex_t	ok;
	pthread_t	p;


    printf("Size of pthread_mutex_t: %zu bytes | adress = %p \n", sizeof(ok) , &ok);
    printf("Size of pthread_mutex_t: %zu bytes | adress = %p \n", sizeof(p) , &p);


    return 0;
}
