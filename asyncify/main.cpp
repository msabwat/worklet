#include <emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

using namespace emscripten;

EM_JS(void, init_worklet, (), {
    return Asyncify.handleSleep( function(wakeUp) {
	var context = new AudioContext();
	context.audioWorklet.addModule("worklet-processor.js").then(() =>{
	    var wp = new AudioWorkletNode(context, "worklet-processor");
	    wp.connect(context.destination);
	    wakeUp();
	  });
      });
  });

static EM_BOOL btn_click_handler(int eventType, const EmscriptenMouseEvent *e, void *userData)
{
  (void) userData;
  if (eventType == EMSCRIPTEN_EVENT_CLICK)
     init_worklet();
  return 0;
}

int main()
{
  emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, 1, btn_click_handler);
  return 0;
}
