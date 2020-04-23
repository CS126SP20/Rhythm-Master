// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/app/App.h>
#include <cinder/audio/audio.h>
#include <cinder/gl/gl.h>

#include <random>
#include <string>
#include <vector>

namespace myapp {

enum class PageState {
  kFirstPage, nextPage,
  goBack, playEasy, playMed, playHard
};

const char kNormalFont[] = "Arial";

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void draw_select();
  void draw_main();
  void draw_sheets();
  void keyDown(cinder::app::KeyEvent) override;

 private: 
  PageState state_;
  cinder::audio::VoiceRef star_;
  cinder::audio::VoiceRef birthday_;
  cinder::audio::VoiceRef tetris_;
  
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
