#include "store.h"

#include "tile.h"
#include "tools.h"
#include "keyListener.h"

store::store(){
  open = false;
  storeItems = inventory( 8);
}

store::~store(){}

void store::load_data(){
  if (!( image = load_bitmap("images/GUI_STORE.png", NULL)))
    abort_on_error("Cannot find image images/GUI_STORE.png\nPlease check your files and try again");

  if (!( image_background = load_bitmap("images/GUI_STORE_BACKGROUND.png", NULL)))
    abort_on_error("Cannot find image images/GUI_STORE_BACKGROUND.png\nPlease check your files and try again");

  if (!( indicator = load_bitmap("images/indicator_store.png", NULL)))
    abort_on_error("Cannot find image images/indicator_store.png\nPlease check your files and try again");

  if( !(buy= load_sample("sfx/buy.wav")))
    abort_on_error( "Cannot find file sfx/buy.wav \n Please check your files and try again");

  if( !(sell= load_sample("sfx/sell.wav")))
    abort_on_error( "Cannot find file sfx/sell.wav \n Please check your files and try again");

  if( !(error= load_sample("sfx/error.wav")))
    abort_on_error( "Cannot find file sfx/error.wav \n Please check your files and try again");
}

void store::draw_background( BITMAP *tempBitmap){
  if( open)
    draw_sprite( tempBitmap, image_background, 0, 0);
}

void store::draw( BITMAP *tempBitmap){
  if( open){
    draw_sprite( tempBitmap, image, 0, 0);

    for( int i = 0; i < (signed)storeItems.getSize(); i++){
      storeItems.getItem(i) -> draw_at( 25 + i * 19, 90, tempBitmap);

      if( selector_index == i)
        draw_sprite( tempBitmap, indicator, 25 + i * 19, 90);
    }
    if( selector_index < (signed)storeItems.getSize())
      textprintf_ex( tempBitmap, font, 25, 106, makecol(0,0,0), -1, "%s : %i coins",
                    storeItems.getItem(selector_index) -> getName().c_str(),
                    storeItems.getItem(selector_index) -> getValue());
    else{
      if( customer_inventory -> getItem(1) -> getID() == 0){
        textprintf_ex( tempBitmap, font, 25, 106, makecol(0,0,0), -1, "%s : %s",
                       customer_inventory -> getItem(1) -> getName().c_str(),
                       "NOT FOR SALE");
      }
      else{
        textprintf_ex( tempBitmap, font, 25, 106, makecol(0,0,0), -1, "%s : %i coins",
                       customer_inventory -> getItem(1) -> getName().c_str(),
                       customer_inventory -> getItem(1) -> getValue());
      }
    }

    if( customer_inventory != NULL)
      customer_inventory -> getItem(1) -> draw_at( 185, 90, tempBitmap);

    if( selector_index == (signed)storeItems.getSize())
      draw_sprite( tempBitmap, indicator, 185, 90);
  }
}

void store::update(){
  tick++;
  /*if( open){
    if(( key[KEY_LEFT] || key[KEY_A] || joy[0].stick[0].axis[0].d1)  && tick>10){
      tick = 0;
      selector_index--;
      if( selector_index < 0)
        selector_index = storeItems.getSize();
    }
    else if(( key[KEY_RIGHT] || key[KEY_D] || joy[0].stick[0].axis[0].d2) && tick>10){
      tick = 0;
      selector_index++;
      if(selector_index > (signed)storeItems.getSize())
        selector_index = 0;
    }

    if( keyListener::keyPressed[KEY_LCONTROL] || keyListener::keyPressed[KEY_RCONTROL] || mouse_b & 1 || joy[0].button[2].b){
      if( selector_index < (signed)storeItems.getSize()){
        if( customer_inventory -> getItem(1) -> getID() == 0){
          if(customer_inventory -> getItem(1) >= storeItems.at(selector_index) -> getValue()){
            customer_inventory -> money -= storeItems.at(selector_index) -> getValue();
            customer_inventory -> give_item( storeItems.at(selector_index) -> getID());
            storeItems.erase(storeItems.begin() + selector_index);
            play_sample(buy,255,125,1000,0);
            customer_inventory -> push_message("Purchased item");
          }
          else {
            play_sample(error,255,125,1000,0);
            customer_inventory -> push_message("Can't afford item!");
          }
        }
        else {
          play_sample(error,255,125,1000,0);
          customer_inventory -> push_message("Hands full");
        }
      }
      else if( selector_index == (signed)storeItems.getSize() && customer_inventory -> inventory_item -> getID() != 0){
        customer_inventory -> money += customer_inventory -> inventory_item -> getValue();
        customer_inventory -> remove_item();
        play_sample(sell,255,125,1000,0);
      }
    }
  }*/
}

void store::close_store() {
  open = false;
  storeItems.emptyInv();
}

void store::open_store( inventory *new_inventory){
  open = true;
  customer_inventory = new_inventory;

  // Give items to store
  if( storeItems.getSize() == 0){
    selector_index = 8;

    for( int i = 0; i < 8; i ++){
      int newType = random(1, 15);

      item *storeItem = new item( 0, 0, newType);
      add_item(storeItem);
    }
  }
}
