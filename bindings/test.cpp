#include "test.hpp"
#include "glue.cpp"

using namespace emscripten;

static EM_BOOL btn_click_handler(int eventType, const EmscriptenMouseEvent *e, void *userData)
{
  (void) userData;
  if (eventType == EMSCRIPTEN_EVENT_CLICK)
  {
    val dummy = val::global("Dummy").new_();
    val context = val::global("AudioContext").new_();
    val audioWorkletNode = context["audioWorklet"].call<val>("addModule", std::string("worklet-processor.js"));
    
    // TODO: bind Audio Context to function, to pass the context 

    val fun = dummy["add_worklet_node"];//.bind();
    audioWorkletNode.call<void>("then", fun);    
  }
  return 0;
}

int main()
{
  emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, btn_click_handler);
  return 0;
}
