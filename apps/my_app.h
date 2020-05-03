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

enum class PageState {
  firstPage, nextPage,
  goBack, playEasy, playMed, endgame,
  Qpressed, Wpressed, Opressed, Ppressed, losegame
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
  void draw_endgame();
  void draw_nodes();
  void keyDown(cinder::app::KeyEvent) override;

  PageState state_;
  
 private:
  
  int kBegin = 0;
  int kEnd = 900;
  bool start_song;
  double track_start;
  
  choreograph::Timeline timeline;
  
  // Circle positions represented by 2d vectors
  choreograph::Output<ci::vec2> position_a_;
  choreograph::Output<ci::vec2> position_b_;
  choreograph::Output<ci::vec2> position_c_;
  choreograph::Output<ci::vec2> position_d_;
  
  cinder::Timer tracker_;
  cinder::Timer timer_;
  cinder::audio::VoiceRef star_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
