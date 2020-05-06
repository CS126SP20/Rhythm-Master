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
    kFirstPage,
    kNextPage,
    kGoBack,
    kPlayEasy,
    kEndgame,
    kLosegame
  };
  
  enum class QKeyState {
    QNotPressed,
    Qpressed
  };

  enum class WKeyState {
    WNotPressed,
    Wpressed, 
  };

  enum class OKeyState {
    ONotPressed,
    Opressed
  };

  enum class PKeyState {
    PNotPressed,
    Ppressed
  };
  
 public:
  MyApp();
  void update() override;
  
  void setup() override;
  void set_easy_animation(); // Use choreograph to make the slide animation
  void set_songs();
  void draw() override;
  
  // Draws each sub pages
  void draw_select();
  void draw_main();
  void draw_sheets();
  void draw_wingame();
  void draw_losegame();
  // Draws the circle nodes
  void draw_nodes();
  
  void keyDown(cinder::app::KeyEvent) override;
  
  // Function that return the losing condition by checking if 
  // whether the key is being pressed before the tile goes out
  // of bounds
  void check_pos();
  void reset_key_state();

  // Set starting game state
  PageState state_ = PageState::kFirstPage;
  
  // Assume that non of the keys are being pressed at the start
  QKeyState key_Q = QKeyState::QNotPressed;
  WKeyState key_W = WKeyState::WNotPressed;
  OKeyState key_O = OKeyState::ONotPressed;
  PKeyState key_P = PKeyState::PNotPressed;
  
 private:

  const cinder::vec2 kCenter = getWindowCenter();
  
  int kBegin = 0; // Starting position of the animation
  int kEnd = 900; // Ending position of the animation
  int kBottom = 850; // Final bound for the tile
  bool start_song;
  
  // track when the user starts the game page
  double track_start;
  
  choreograph::Timeline timeline;
  
  // Circle positions represented by 2d vectors
  choreograph::Output<ci::vec2> position_a_;
  choreograph::Output<ci::vec2> position_b_;
  choreograph::Output<ci::vec2> position_c_;
  choreograph::Output<ci::vec2> position_d_;
  
  // Timer used for reseting the key states back
  // to unpressed after certain time
  cinder::Timer q_after_press_;
  cinder::Timer w_after_press_;
  cinder::Timer o_after_press_;
  cinder::Timer p_after_press_;
  
  // Tracks the time when the game begins
  cinder::Timer tracker_;
  
  // Tracks the time 
  cinder::Timer timer_;
  
  cinder::audio::VoiceRef star_;
  cinder::audio::VoiceRef click_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
