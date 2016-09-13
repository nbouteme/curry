#ifndef CURRY_H
# define CURRY_H

typedef union
{
	void *p;
	long v;
} t_value __attribute__((transparent_union));


typedef t_value(*t_4)(t_value, t_value, t_value, t_value);
typedef t_value(*t_3)(t_value, t_value, t_value);
typedef t_value(*t_2)(t_value, t_value);
typedef t_value(*t_1)(t_value);
typedef t_value(*t_0)(void);
typedef t_value(*t_curryg)(t_value);

t_value curry(void *f, t_value arg);
void eat(void *curry);

#endif
