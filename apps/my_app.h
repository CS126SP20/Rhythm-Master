// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_


#include <choreograph/Timeline.h>
#include <cinder/Rect.h>
#include <cinder/app/App.h>
#include <cinder/audio/audio.h>
#include <cinder/gl/gl.h>

//#include "/Users/allanhuang/Desktop/cinder_0.9.2_mac/blocks/Choreograph/samples/src/pockets/cobweb/CobWeb.h"
//#include "/Users/allanhuang/Desktop/cinder_0.9.2_mac/blocks/Choreograph/samples/src/pockets/Scene.h"
//#include "/Users/allanhuang/Desktop/cinder_0.9.2_mac/blocks/Choreograph/samples/src/pockets/cobweb/RootNode.h"

#include <choreograph/Output.hpp>
#include <random>
#include <string>
#include <vector>
#include <string>



namespace myapp {

//using namespace pockets;


enum class PageState {
  kFirstPage, nextPage,
  goBack, playEasy, playMed
};

const char kNormalFont[] = "Arial";

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void set_animation();
  void set_songs();
  void draw() override;
  void draw_select();
  void draw_main();
  void draw_sheets();
  void draw_drop_animation();
  void keyDown(cinder::app::KeyEvent) override;
  
  

  

 private: 
  PageState state_;
  cinder::audio::VoiceRef star_;
  cinder::audio::VoiceRef birthday_;
  cinder::audio::VoiceRef tetris_;

  choreograph::Timeline timeline;
  choreograph::Output<ci::vec2> _position_a;
  choreograph::Output<ci::vec2> _position_b;
  choreograph::Output<ci::vec2> _position_c;
  choreograph::Output<ci::vec2> _position_d;
  
  
  ci::Timer _timer;
  

  
  
 
 
 // choreograph::Output<cinder::vec3> target;
  
  //rectange;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
