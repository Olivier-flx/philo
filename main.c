/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:16:33 by ofilloux          #+#    #+#             */
/*   Updated: 2024/09/16 16:39:30 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Tu(s) programa(s) debe(n) aceptar los siguientes argumentos:
	- number_of_philosophers : es el número de filósofos, pero también el número
								de tenedores.
	- time_to_die : si un filósofo no empieza a comer en
					time_to_die desde el comienzo de su ultima
					comida o desde el principio de la simulación, este morirá.
	- time_to_eat : es el tiempo que tiene un filósofo para comer.
					Durante ese tiempo, tendrá los tenedores ocupados.
	- time_to_sleep : es el tiempo que tiene un filósofo para dormir.
	- [number_of_times_each_philosopher_must_eat] (argumento opcional) : si todos
			los filós comen al menos number_of_times_each_philosopher_must_eat
			veces, la simulación se detendrá. Si no se especifica, la simulación
			se detendrá con la muerte de un filósofo.

• Le temps est exprimé en milisegundos

• Cada filósofo tendrá asignado un número del 1 al number_of_philosophers.

• El filósofo número 1 se sentará al lado del filósofo
	número number_of_philosophers. Cualquier otro filósofo número N se sentarán
	entre el filósofo número N - 1 y el filósofo número N + 1.

Los logs de tu programa:
• Cualquier cambio de estado de un filósofo debe tener el siguiente formato:
	◦ timestamp_in_ms X has taken a fork
	◦ timestamp_in_ms X is eating
	◦ timestamp_in_ms X is sleeping
	◦ timestamp_in_ms X is thinking
	◦ timestamp_in_ms X died
Reemplaza timestamp_in_ms con la marca de tiempo actual en milisegundos y X con
el numero del filósofo.
• El estado impreso no debe estar roto o alterado por el estado de
	otros filósofos
• No puedes tener más de 10ms entre la muerte de un filósofo y el momento
	en el que imprimes su muerte.
• Los filósofos deben evitar morir.

• Tu programa no debe tener ningún data races.

Las reglas específicas para la parte obligatoria son:
• Cada filósofo debe ser un hilo.
• Hay un tenedor entre cada filósofo. por lo tanto, si hay varios filósofos,
	cada filósofo debe tener un tenedor a su izquierda y otro a su derecha.
	si solo hay un filósofo, solo habrá un tenedor en la mesa.
• Para prevenir que los filósofos dupliquen los tenedores, deberás proteger
	los estados de los tenedores con un mutex por cada uno de ellos.
*/

/*
 arg :
 number_of_philosophers : phil_n,
 time_to_die : ttd,
 time_to_eat : tte;
 time_to_sleep : tts
 option - number_of_times_each_philosopher_must_eat : lunchs
*/

#include "./inc/philo.h"

int	main(int ac, char **av)
{
	t_params	params;

	if (ac != 5 && ac != 6)
		simple_exit("Wrong number of arguments", EXIT_FAILURE);
	init_params(av, &params);
	lets_eat(&params);

	////////////////////
	t_filo *tmp;
	int		i = 0;
	tmp = params.filos_lst;
	while (params.filos_lst && i < params.phil_n)
	{
		printf("ID = %i\n", params.filos_lst->id);
		params.filos_lst = params.filos_lst->next;
		i++;
	}
	printf("ttd_max = %li\n", params.ttd_max);
	printf("tts_max = %li\n", params.tts_max);
	printf("tot_lunchs = %i\n", params.tot_lunchs);
	free_lst_exit(tmp, EXIT_SUCCESS);
	return (0);
}
