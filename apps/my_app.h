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



const char kNormalFont[] = "Arial";

class MyApp : public cinder::app::App {

  enum class PageState {
    firstPage, nextPage,
    goBack, playEasy, playMed, endgame,
     losegame
  };
  
  enum class QKeyState {
    QNotPressed, Qpressed
  };

  enum class WKeyState {
    WNotPressed,  Wpressed, 
  };

  enum class OKeyState {
    ONotPressed, Opressed
  };

  enum class PKeyState {
    PNotPressed, Ppressed
  };
  
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
  void draw_wingame();
  void draw_losegame();
  void draw_nodes();
  
  void keyDown(cinder::app::KeyEvent) override;
  
  void check_pos();
  void reset_press();

  PageState state_ = PageState::firstPage;
  
  QKeyState key_Q = QKeyState::QNotPressed;
  WKeyState key_W = WKeyState::WNotPressed;
  OKeyState key_O = OKeyState::ONotPressed;
  PKeyState key_P = PKeyState::PNotPressed;
  
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
  
  cinder::Timer q_after_press;
  cinder::Timer w_after_press;
  cinder::Timer o_after_press;
  cinder::Timer p_after_press;
  
  cinder::Timer tracker_;
  cinder::Timer timer_;
  cinder::audio::VoiceRef star_;
  cinder::audio::VoiceRef click_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
