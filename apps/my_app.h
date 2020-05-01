// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_


#include <choreograph/Timeline.h>
#include <cinder/Rect.h>
#include <cinder/app/App.h>
#include <cinder/audio/audio.h>
#include <cinder/gl/gl.h>

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
  void set_easy_animation(); // Use choreograph to make the slide animation
  void set_songs();
  void draw() override;
  void draw_select();
  void draw_main();
  void draw_sheets();
  void draw_nodes();
  void keyDown(cinder::app::KeyEvent) override;
  
 private: 
  PageState state_;
  
  int kBegin = 0;
  int kEnd = 1000;
  
  cinder::audio::VoiceRef star_;
  cinder::audio::VoiceRef birthday_;

  choreograph::Timeline timeline;
  
  // Circle positions represented by 2d vectors
  choreograph::Output<ci::vec2> _position_a;
  choreograph::Output<ci::vec2> _position_b;
  choreograph::Output<ci::vec2> _position_c;
  choreograph::Output<ci::vec2> _position_d;
  
  ci::Timer timer_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
