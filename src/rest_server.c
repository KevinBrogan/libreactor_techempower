#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/queue.h>
#include <linux/sched.h>
#include <netdb.h>
#include <err.h>

#include <dynamic.h>
#include <reactor.h>
#include <clo.h>

#include "setup.h"

static void plaintext(void *state, int type, void *data)
{
  reactor_http_server_context *context = data;

  (void) state;
  (void) type;
  reactor_http_server_respond_text(context->session, "Hello, World!");
}

static void json(void *state, int type, void *data)
{
  reactor_http_server_context *context = data;
  char buffer[4096];

  (void) state;
  (void) type;
  (void) clo_encode((clo[]) {clo_object({"message", clo_string("Hello, World!")})}, buffer, sizeof(buffer));
  reactor_http_server_respond_mime(context->session, "application/json", buffer, strlen(buffer));;
}

int main()
{
  reactor_http_server server;

  setup(1, 0);
  reactor_core_construct();
  reactor_http_server_open(&server, NULL, &server, "0.0.0.0", "8080");
  reactor_http_server_route(&server, plaintext, NULL, "GET", "/plaintext");
  reactor_http_server_route(&server, json, NULL, "GET", "/json");
  reactor_core_run();
  reactor_core_destruct();
}
