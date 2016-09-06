//-------------------------------------------------------------------------
//
//  Quick and Easy Review of Data Types for Appendix A in "Learning C with Pebble"
//
//  Mike Jipping, September 2016

#include <pebble.h>
#include <limits.h>
#include <stdint.h>
#include <float.h>

static Window *window;
static TextLayer *text_layer;

static void display_chars() {    
    APP_LOG(APP_LOG_LEVEL_INFO, "\nCHARACTER SIZES\n   char = %d, max char = %d\n   unsigned char = %d", 
            sizeof(char), CHAR_MAX, sizeof(unsigned char));
}

static void display_integers() {
    APP_LOG(APP_LOG_LEVEL_INFO, "\nINTEGER SIZES\n   short = %d, max short = %d\n   int = %d, max int = %d", 
            sizeof(short int), SHRT_MAX, sizeof(int), INT_MAX);
    APP_LOG(APP_LOG_LEVEL_INFO, "\n   unsigned short = %d, max unsigned short = %d", 
            sizeof(unsigned short int), USHRT_MAX);
    APP_LOG(APP_LOG_LEVEL_INFO, "\n   unsigned int = %d, unsigned max int = %u", 
            sizeof(unsigned int), UINT_MAX);
    APP_LOG(APP_LOG_LEVEL_INFO, "\n   long = %d, max long = %li\n   long long = %d, max long long = %lli", 
            sizeof(long), LONG_MAX, sizeof(long long), LLONG_MAX);
    APP_LOG(APP_LOG_LEVEL_INFO, "\n   unsigned long = %d, unsigned max long = %lu", 
            sizeof(unsigned long), ULONG_MAX);
    APP_LOG(APP_LOG_LEVEL_INFO, "\n   unsigned long long = %d, max unsigned long long = %llu", 
            sizeof(long long), ULLONG_MAX);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
    display_integers();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
    display_chars();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create(GRect(0, 72, bounds.size.w, 20));
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
    
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}