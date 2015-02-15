// default C includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// dyad
#include "dyad.h"

// lua
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

/* A very lightweight webframework for lua using luadyad */

static int count = 0;
const char* luareturn;
// default port
int port = 8000;


const char* callLua(char string[128]){

  // try to open lua stack
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  // Tell Lua to load main.lua
  luaL_dofile(L, "main.lua");

  // Push function to the Lua stack
  lua_getglobal(L, "main");

  // Checks if top of the Lua stack is a function.
  lua_isfunction(L, -1);

  // push string to lua stack
  lua_pushstring(L, string);

  // Perform the function call (1 arguments, 1 return)
  if (lua_pcall(L, 1, 1, 0) != 0) {
    printf("error when calling lua function");
  }

  // main.lua should always return a string!
  if (lua_isstring(L, -1)) {
    int top = lua_gettop(L);
    luareturn = lua_tostring(L, -1);
    lua_pop(L, 1);
  }

  return luareturn;
}

static void onLine(dyad_Event *e) {
  char path[128];

  if (sscanf(e->data, "GET %127s", path) == 1) {

    /* Print request */
    printf("%s %s\n", dyad_getAddress(e->stream), path);
    /* Send header */
    dyad_writef(e->stream, "HTTP/1.1 200 OK\r\n\r\n");

    luareturn = callLua(path);

    dyad_writef(e->stream, luareturn );

    /* Close stream when all data has been sent */
    dyad_end(e->stream);
  }
}

static void onAccept(dyad_Event *e) {
  dyad_addListener(e->remote, DYAD_EVENT_LINE, onLine, NULL);
}

static void onListen(dyad_Event *e) {
  printf("server listening: http://localhost:%d\n", dyad_getPort(e->stream));
}

static void onError(dyad_Event *e) {
  printf("server error: %s\n", e->msg);
}


int main(int argc, char *argv[] ) {

  // change default port 8000 by using first input argument
  if (argc == 2){
    port = atoi(argv[1]);
  }

  dyad_Stream *s;
  dyad_init();

  s = dyad_newStream();
  dyad_addListener(s, DYAD_EVENT_ERROR,  onError,  NULL);
  dyad_addListener(s, DYAD_EVENT_ACCEPT, onAccept, NULL);
  dyad_addListener(s, DYAD_EVENT_LISTEN, onListen, NULL);
  dyad_listen(s, port);

  while (dyad_getStreamCount() > 0) {
    dyad_update();
  }

  return 0;
}
