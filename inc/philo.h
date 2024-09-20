/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:17:57 by ofilloux          #+#    #+#             */
/*   Updated: 2024/09/18 18:55:01 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> // printf
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

typedef struct lst_filo
{
	unsigned int	id;
	unsigned int	ttd;
	unsigned int	tte;
	unsigned int	sleep_time;
	int				lunchs;
	bool			is_eating;
	bool			is_sleeping;
	bool			is_dead;
	pthread_t		thread;
	struct s_params	*params;
	struct lst_filo	*next;
	struct lst_filo	*prev;
}	t_filo;

typedef struct s_params
{
	int				phil_n;
	long			ttd_max;
	long			tte_max;
	long			tts_max;
	int				tot_lunchs;
	double			start_time;
	bool			dinner_started; //unused
	bool			dinner_finished; //unused
	t_filo			*filos_lst;
}	t_params;


//////// SRC ////////////
void	init_params(char **av, t_params *params);

//////// UTILS ////////
///string.c
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
long	ft_atol(char *s);

///time.c
int		msleep(unsigned int msec);
void	set_simulation_start_time(t_params *params);
int		timestamp_msg(int phil_id, char *action);

/////// CLEAN EXIT ///////
void	simple_exit(char *msg, int exit_num);
void	free_lst_exit(t_filo *filos_lst, int exit_num);

#endif

/*
Funciones autorizadas :
memset, printf, malloc, free, write,

int usleep(useconds_t usec);
gettimeofday (struct timeval *tv, struct timezone *tz); :
			return 0 for success, or -1 for failure (in which case
			errno is set appropriately).

		   struct timeval {
			   time_t	  tv_sec;	 // seconds
			   suseconds_t tv_usec;	//microseconds
		   };


pthread_create :
pthread_detach :
pthread_join :
pthread_mutex_init :
pthread_mutex_destroy :
pthread_mutex_lock :
pthread_mutex_unlock :

pthread_create :
	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, \
	void *(*start_routine) (void *), void *arg)
	Fonctionnement : Crée un nouveau thread qui exécute la fonction spécifiée
					(start_routine) avec l'argument passé (arg).
	Usage typique : Démarrer des tâches concurrentes ou parallèles pour optimiser
					l'utilisation des ressources du système.
	Exemple :
		void *print_message(void *message) {
			printf("%s\n", (char *)message);
			return NULL;
		}
		int main() {
			pthread_t thread;
			const char *msg = "Hello from the thread!";
			pthread_create(&thread, NULL, print_message, (void *)msg);
			pthread_join(thread, NULL);  // Attendre que le thread se termine
			return 0;
		}
/

pthread_detach : int pthread_detach(pthread_t thread)
	Fonctionnement : Détache un thread pour qu'il se nettoie automatiquement
					une fois terminé, sans besoin d'appeler pthread_join.
	Usage typique : Libérer les ressources d'un thread qui n'a pas besoin d'être
					 synchronisé avec le programme principal.
	Exemple :
		void *print_message(void *message) {
			printf("%s\n", (char *)message);
			return NULL;
		}
		int main() {
			pthread_t thread;
			const char *msg = "Hello from a detached thread!";
			pthread_create(&thread, NULL, print_message, (void *)msg);
			pthread_detach(thread);  // Détache le thread pour
				//qu'il se nettoie automatiquement
			// Pas de pthread_join ici
			return 0;
		}
/

pthread_join : int pthread_join(pthread_t thread, void **retval)
	Fonctionnement : Attend la terminaison d'un thread spécifique et
					récupère sa valeur de retour.
	Usage typique : Synchroniser le programme principal avec un thread pour
					s'assurer que certaines tâches sont terminées
					avant de poursuivre.
	Exemple :
		void *calculate(void *arg) {
			int *num = (int *)arg;
			*num *= 2;
			return NULL;
		}
		int main() {
			pthread_t thread;
			int value = 5;
			pthread_create(&thread, NULL, calculate, (void *)&value);
			pthread_join(thread, NULL);  // Attend que le thread termine
			printf("Result: %d\n", value);  // Affiche 10
			return 0;
		}
/

pthread_mutex_init :
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
	Fonctionnement : Initialise un mutex avec les attributs spécifiés, ou
					par défaut si attr est NULL.
	Usage typique : Préparer un mutex pour être utilisé pour protéger des
					sections critiques de code dans un programme multithread.
	Exemple :
		pthread_mutex_t lock;
		int main() {
			pthread_mutex_init(&lock, NULL);  // Initialiser le mutex
			// Code utilisant le mutex...
			pthread_mutex_destroy(&lock);	 // Détruire le mutex à la fin
			return 0;
		}
/

pthread_mutex_destroy : int pthread_mutex_destroy(pthread_mutex_t *mutex)
	Fonctionnement : Détruit un mutex, libérant les ressources associées.
	Usage typique : Nettoyer un mutex qui n'est plus nécessaire,
					après que tous les threads l'ont terminé.
	Exemple :
		pthread_mutex_t lock;
		pthread_mutex_init(&lock, NULL);
		// Utilisation du mutex...
		pthread_mutex_destroy(&lock);  // Libère les ressources du mutex
		return 0;
/

pthread_mutex_lock : int pthread_mutex_lock(pthread_mutex_t *mutex)
	Fonctionnement : Verrouille un mutex, bloquant le thread appelant
					jusqu'à ce que le mutex soit disponible.
	Usage typique : Protéger une section critique pour empêcher l'accès
					concurrent d'autres threads.
	Exemple :
		pthread_mutex_t lock;
		pthread_mutex_init(&lock, NULL);
		void *increment_counter(void *counter) {
			pthread_mutex_lock(&lock); // Verrouille avant d'accéder à \
				//la section critique
			(*(int *)counter)++;
			pthread_mutex_unlock(&lock); // Déverrouille après l'accès
			return NULL;
		}
/

pthread_mutex_unlock : int pthread_mutex_unlock(pthread_mutex_t *mutex)
	Fonctionnement : Déverrouille un mutex précédemment verrouillé,
					permettant à d'autres threads d'y accéder.
	Usage typique : Libérer un mutex après avoir terminé l'accès à
					une section critique.
	Exemple :
		pthread_mutex_t lock;
		pthread_mutex_init(&lock, NULL);
		void *increment_counter(void *counter) {
			pthread_mutex_lock(&lock);	// Verrouille avant la section critique
			(*(int *)counter)++;
			pthread_mutex_unlock(&lock);  // Déverrouille après
			return NULL;
		}


/////////////////// MUTEX CONCEPT ///////////////////////

Un mutex (abréviation de "mutual exclusion" en anglais) est un mécanisme
de synchronisation utilisé en programmation multithread pour protéger
les ressources partagées (comme des variables, des fichiers ou des structures
de données) contre les accès concurrents.

Il garantit que, à un moment donné, une seule tâche ou un seul thread peut
accéder à la section critique du code qui manipule cette ressource partagée.
/

---------- Fonctionnement du Mutex -----------
Verrouillage (lock) :
		Avant d'entrer dans une section critique, un thread doit verrouiller
		le mutex associé. Si le mutex est déjà verrouillé par un autre thread,
		le thread actuel attendra (sera bloqué) jusqu'à ce que le mutex soit
		déverrouillé.
Déverrouillage (unlock) :
		Après avoir terminé l'opération sur la ressource
		partagée, le thread doit déverrouiller le mutex, ce qui permet à
		d'autres threads d'entrer dans la section critique.

Exemple d'Usage Typique :
		plusieurs threads essayant de modifier une variable.
		Sans synchronisation, deux threads pourraient essayer de lire,
		modifier et écrire cette variable en même temps, ce qui entraînerait
		des résultats incorrects ou incohérents. L'utilisation d'un mutex
		empêche cela :

------------ EXEMPLE DE CODE ------------
#include <stdio.h>
#include <pthread.h>

int counter = 0;               // Variable partagée
pthread_mutex_t lock;          // Déclaration du mutex

void *increment_counter(void *arg) {
	pthread_mutex_lock(&lock);  // Verrouille le mutex avant la section critique
	counter++;		  // Section critique : modification de la variable partagée
	printf("Counter: %d\n", counter);
	pthread_mutex_unlock(&lock); // Déverrouille le mutex après
	return NULL;
}

int main() {
	pthread_t threads[10];
	pthread_mutex_init(&lock, NULL); // Initialise le mutex

	// Crée 10 threads
	for (int i = 0; i < 10; i++) {
		pthread_create(&threads[i], NULL, increment_counter, NULL);
	}

	// Attend que tous les threads se terminent
	for (int i = 0; i < 10; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&lock); // Détruit le mutex après utilisation
	return 0;
}


*/
