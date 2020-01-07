#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <emscripten.h>
#include <emscripten/html5.h>

class Dummy{
public:
  void add_worklet_node(){
    //    (void)context;
    // emscripten::val AudioContext = emscripten::val(context); 
    emscripten_log(EM_LOG_CONSOLE, "Hello World!");
  }
};
