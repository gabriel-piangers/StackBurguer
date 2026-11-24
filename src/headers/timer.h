# ifndef TIMER_H
# define TIMER_H

# include <chrono>

struct Timer { 
    std::chrono::steady_clock::time_point inicio; 
};
void timer_iniciar ( Timer *t) ;
double timer_parar ( Timer * t) ; /* retorna tempo em segundos */

# endif
