# luadyad

Version 0.1

KISS webframework for lua

## about

`luadyad` is using [dyad](https://github.com/rxi/dyad) for asynchronous networking connections while the content is generated with lua by calling `main.lua` file with function `main()` _(must have **one input argument and one return (both strings!)**)_.

## requirements

* lua 5.2.x or lua 5.3.x _(liblua is sufficient)_
* C compiler _(tcc is sufficient)_


## How to

* get the source


    $ git clone --recursive https://github.com/markuman/luadyad


* compile


    $ tcc -Idyad/src/ dyad/src/dyad.c -llua luadyad.c -o luadyad


* run


    $ ./luadyad
    server listening: http://localhost:8000


* use

![luadyad](https://raw.githubusercontent.com/markuman/luadyad/master/doc/helloworld.jpg "luadyad hello world")


