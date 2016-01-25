#ifndef REACTOR_SIGNAL_DISPATCHER_H_INCLUDED
#define REACTOR_SIGNAL_DISPATCHER_H_INCLUDED

#define REACTOR_SIGNAL_DISPATCHER_SIGNO  SIGUSR1

enum REACTOR_SIGNAL_DISPATCHER_FLAG
{
  REACTOR_SIGNAL_DISPATCHER_RELEASE = 0x01,
};

enum REACTOR_SIGNAL_DISPATCHER_EVENT
{
  REACTOR_SIGNAL_DISPATCHER_ERROR   = 0x00,
  REACTOR_SIGNAL_DISPATCHER_MESSAGE = 0x01,
  REACTOR_SIGNAL_DISPATCHER_CLOSE   = 0x02
};

typedef struct reactor_signal_dispatcher_singleton reactor_signal_dispatcher_singleton;
struct reactor_signal_dispatcher_singleton
{
  reactor_signal      signal;
  int                 ref;
  int                 flags;
};

typedef struct reactor_signal_dispatcher reactor_signal_dispatcher;
struct reactor_signal_dispatcher
{
  reactor_user        user;
};

void reactor_signal_dispatcher_init(reactor_signal_dispatcher *, reactor_user_call *, void *);
int  reactor_signal_dispatcher_hold(void);
void reactor_signal_dispatcher_release(void);
void reactor_signal_dispatcher_call(void *, int, void *);
void reactor_signal_dispatcher_sigev(reactor_signal_dispatcher *, struct sigevent *);
void reactor_signal_dispatcher_event(void *, int, void *);

#endif /* REACTOR_SIGNAL_DISPATCHER_H_INCLUDED */
