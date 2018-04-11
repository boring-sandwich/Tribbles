#include <pebble.h>
#define KEY_TEMPERATURE 0
#define KEY_CONDITIONS 1
#define KEY_TEMPERATUREF 2
  
//declaring pointers
static Window *s_main_window;
static TextLayer *s_time_layer;
static GFont s_time_font;
static TextLayer *s_weather_layer;
static GFont s_weather_font;
static BitmapLayer *s_tribble01_layer;
static GBitmap *s_tribble01_bitmap;
static BitmapLayer *s_tribble02_layer;
static GBitmap *s_tribble02_bitmap;
static BitmapLayer *s_tribble03_layer;
static GBitmap *s_tribble03_bitmap;
static BitmapLayer *s_tribble04_layer;
static GBitmap *s_tribble04_bitmap;
static BitmapLayer *s_tribble05_layer;
static GBitmap *s_tribble05_bitmap;
static BitmapLayer *s_tribble06_layer;
static GBitmap *s_tribble06_bitmap;
static BitmapLayer *s_tribble07_layer;
static GBitmap *s_tribble07_bitmap;
static BitmapLayer *s_tribble08_layer;
static GBitmap *s_tribble08_bitmap;
static BitmapLayer *s_tribble09_layer;
static GBitmap *s_tribble09_bitmap;
static BitmapLayer *s_tribble10_layer;
static GBitmap *s_tribble10_bitmap;
static BitmapLayer *s_tribble11_layer;
static GBitmap *s_tribble11_bitmap;
static int tribbles_visible = 0;
static int tribble_temp = 0;

static char temperature_buffer[8] = "";
static char temperatureF_buffer[8] = "";
static char conditions_buffer[32] = "";

static void update_time()
  {
  //get a tm structure
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  //create a long lived buffer
  static char buffer[] = "00:00";
  
  //write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true){
    //use 24 hour clock
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    //use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }
    //display this time of textlayer
  text_layer_set_text(s_time_layer, buffer);
}

static void main_window_load(Window *window){
  //create gBitmap, then set to created Bitmap layer
  s_tribble01_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble01);
  s_tribble01_layer = bitmap_layer_create(GRect(0,133,144,35));
  bitmap_layer_set_bitmap(s_tribble01_layer, s_tribble01_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble01_layer));
  
  s_tribble02_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble02);
  s_tribble02_layer = bitmap_layer_create(GRect(40,95,38,52));
  bitmap_layer_set_bitmap(s_tribble02_layer, s_tribble02_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble02_layer));
  
  s_tribble03_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble03);
  s_tribble03_layer = bitmap_layer_create(GRect(60,82,84,48));
  bitmap_layer_set_bitmap(s_tribble03_layer, s_tribble03_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble03_layer));
  
  s_tribble04_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble04);
  s_tribble04_layer = bitmap_layer_create(GRect(129,27,15,118));
  bitmap_layer_set_bitmap(s_tribble04_layer, s_tribble04_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble04_layer));
  
  s_tribble05_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble05);
  s_tribble05_layer = bitmap_layer_create(GRect(28,9,55,59));
  bitmap_layer_set_bitmap(s_tribble05_layer, s_tribble05_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble05_layer));
  
  s_tribble06_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble06);
  s_tribble06_layer = bitmap_layer_create(GRect(0,0,39,120));
  bitmap_layer_set_bitmap(s_tribble06_layer, s_tribble06_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble06_layer));
  
  s_tribble07_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble07);
  s_tribble07_layer = bitmap_layer_create(GRect(109,0,35,38));
  bitmap_layer_set_bitmap(s_tribble07_layer, s_tribble07_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble07_layer));
  
  s_tribble08_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble08);
  s_tribble08_layer = bitmap_layer_create(GRect(98,44,46,64));
  bitmap_layer_set_bitmap(s_tribble08_layer, s_tribble08_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble08_layer));
  
  s_tribble09_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble09);
  s_tribble09_layer = bitmap_layer_create(GRect(71,27,50,41));
  bitmap_layer_set_bitmap(s_tribble09_layer, s_tribble09_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble09_layer));
  
  s_tribble10_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble10);
  s_tribble10_layer = bitmap_layer_create(GRect(0,0,121,153));
  bitmap_layer_set_bitmap(s_tribble10_layer, s_tribble10_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble10_layer));
  
  s_tribble11_bitmap = gbitmap_create_with_resource(RESOURCE_ID_tribble11);
  s_tribble11_layer = bitmap_layer_create(GRect(5,0,130,80));
  bitmap_layer_set_bitmap(s_tribble11_layer, s_tribble11_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_tribble11_layer));  
  
   // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 60, 139, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  
  // Improve the layout to be more like a watchface
  //Create GFont
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_font_arial_24));
  //Apply to TextLayer
  text_layer_set_font(s_time_layer, s_time_font);
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);  

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  
  //make the bitmap for the blink invisible
  layer_set_hidden(bitmap_layer_get_layer(s_tribble01_layer), true);
  layer_set_hidden(bitmap_layer_get_layer(s_tribble02_layer), true);
  layer_set_hidden(bitmap_layer_get_layer(s_tribble03_layer), true);
  layer_set_hidden(bitmap_layer_get_layer(s_tribble04_layer), true);
  layer_set_hidden(bitmap_layer_get_layer(s_tribble05_layer), true);
  layer_set_hidden(bitmap_layer_get_layer(s_tribble06_layer), true);
  layer_set_hidden(bitmap_layer_get_layer(s_tribble07_layer), true);
  layer_set_hidden(bitmap_layer_get_layer(s_tribble08_layer), true);
  layer_set_hidden(bitmap_layer_get_layer(s_tribble09_layer), true);
  layer_set_hidden(bitmap_layer_get_layer(s_tribble10_layer), true);
  layer_set_hidden(bitmap_layer_get_layer(s_tribble11_layer), true);
  
  //create temperature layer
  s_weather_layer = text_layer_create(GRect(0,140,144,25));
  text_layer_set_background_color(s_weather_layer, GColorClear);
  text_layer_set_text_color(s_weather_layer, GColorBlack);
  text_layer_set_text_alignment(s_weather_layer, GTextAlignmentCenter);
  text_layer_set_text(s_weather_layer, "loading...");
  
  //create second custom font, apply it and add to Window
  s_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_font_arial_18));
  text_layer_set_font(s_weather_layer, s_weather_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_weather_layer));
}

static void main_window_unload(Window *window){
  //destroy GBitmap
  gbitmap_destroy(s_tribble01_bitmap);
  gbitmap_destroy(s_tribble02_bitmap);
  gbitmap_destroy(s_tribble03_bitmap);
  gbitmap_destroy(s_tribble04_bitmap);
  gbitmap_destroy(s_tribble05_bitmap);
  gbitmap_destroy(s_tribble06_bitmap);
  gbitmap_destroy(s_tribble07_bitmap);
  gbitmap_destroy(s_tribble08_bitmap);
  gbitmap_destroy(s_tribble09_bitmap);
  gbitmap_destroy(s_tribble10_bitmap);
  gbitmap_destroy(s_tribble11_bitmap);
  
  //destroy BitmapLayer
  bitmap_layer_destroy(s_tribble01_layer);
  bitmap_layer_destroy(s_tribble02_layer);
  bitmap_layer_destroy(s_tribble03_layer);
  bitmap_layer_destroy(s_tribble04_layer);
  bitmap_layer_destroy(s_tribble05_layer);
  bitmap_layer_destroy(s_tribble06_layer);
  bitmap_layer_destroy(s_tribble07_layer);
  bitmap_layer_destroy(s_tribble08_layer);
  bitmap_layer_destroy(s_tribble09_layer);
  bitmap_layer_destroy(s_tribble10_layer);
  bitmap_layer_destroy(s_tribble11_layer);
  //Destroy GFont
  fonts_unload_custom_font(s_time_font);
  fonts_unload_custom_font(s_weather_font);
  //destroy textlayer
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_weather_layer);
}

static int random_numbers(int first_number, int second_number){
  int c = second_number - first_number;
  return first_number + rand() % c;
}

static void weather_visibility_handler(void *tribble_weather){ 
  // Use setlocale() to obtain the system locale for translation
  static char weather_layer_buffer[32];
  if (conditions_buffer[0]){
  // Set the TextLayer's contents depending on locale
  if (tribble_temp == 0) {
  snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", temperatureF_buffer, conditions_buffer);
  } else {
  // Fall back to English UK
  snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", temperature_buffer, conditions_buffer);
  }  
  text_layer_set_text(s_weather_layer, weather_layer_buffer); 
  tribble_temp = !tribble_temp;
}
  app_timer_register(5000, weather_visibility_handler, NULL);
  
}

static void visibility_handler(void *tribbles){
  switch (tribbles_visible){
    case 0:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble01_layer), false);
    tribbles_visible++;
    break;
    case 1:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble02_layer), false);
    tribbles_visible++;
    break;
    case 2:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble03_layer), false);
    tribbles_visible++;
    break;
    case 3:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble04_layer), false);
    tribbles_visible++;
    break;
    case 4:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble05_layer), false);
    tribbles_visible++;
    break;
    case 5:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble06_layer), false);
    tribbles_visible++;
    break;
    case 6:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble07_layer), false);
    tribbles_visible++;
    break;
    case 7:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble08_layer), false);
    tribbles_visible++;
    break;
    case 8:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble09_layer), false);
    tribbles_visible++;
    break;
    case 9:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble10_layer), false);
    tribbles_visible++;
    break;
    case 10:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble11_layer), false);
    tribbles_visible++;
    break;
    case 11:
    layer_set_hidden(bitmap_layer_get_layer(s_tribble01_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_tribble02_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_tribble03_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_tribble04_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_tribble05_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_tribble06_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_tribble07_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_tribble08_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_tribble09_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_tribble10_layer), true);
    layer_set_hidden(bitmap_layer_get_layer(s_tribble11_layer), true);  
    tribbles_visible = 0;
    break;
  }
  
 app_timer_register(random_numbers(1000, 8000), visibility_handler, NULL);
 
}      

static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  update_time();
  //get the weather every 30 minutes
  if(tick_time->tm_min % 30==0){
    //begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    //add key value pair
    dict_write_uint8(iter, 0, 0);
    
    //send the message
    app_message_outbox_send();
  }
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context){
 //Store incoming information
  //Read first item
  Tuple *t = dict_read_first(iterator);
  //For all items
  while(t != NULL) {
    //Which key was received?
    switch(t->key) {
      case KEY_TEMPERATURE:
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%dC", (int)t->value->int32);
      break;
      case KEY_TEMPERATUREF:
      snprintf(temperatureF_buffer, sizeof(temperatureF_buffer), "%dF", (int)t->value->int32);
      break;
      case KEY_CONDITIONS:
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
      break;
      default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognised!", (int)t->key);
      break;
    }
    //Look for next item
    t = dict_read_next(iterator);
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context){
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context){
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context){
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void init() 
{
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) 
  {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Make sure the time is displayed from the start
  update_time();
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  //Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  //register the visibility with the TickTimerService
  app_timer_register(5000, visibility_handler, NULL);
  app_timer_register(5000, weather_visibility_handler, NULL);
}

static void deinit() 
{
// Destroy Window
    window_destroy(s_main_window);
}

int main(void) 
{
  init();
  app_event_loop();
  deinit();
}