// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
//#include <CinderImGui.h>
#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>
#include <iostream>

#include <choreograph/Choreograph.h>

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/GeomIo.h>

namespace myapp {

using namespace choreograph;
using choreograph::Time;

using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;

using std::chrono::seconds;
using std::chrono::system_clock;

using std::string;



MyApp::MyApp() :
  state_{PageState::firstPage} {}
  
void MyApp::setup() {
  start_song = false;

  set_easy_animation();
  set_songs();
  
  tracker_.start();
}

template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 40))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(1, 1, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::update() {
 
  if (state_ == PageState::playEasy) {
    auto dt = (Time)timer_.getSeconds();
    timer_.start();
    timeline.step(dt);
    
    if (!start_song) {
      star_->start();
      start_song = true;
      track_start = tracker_.getSeconds();
    } else {
       if (tracker_.getSeconds() - track_start > 5.0) {
        star_->stop();
        timeline.clear();
        state_ = PageState::endgame;
      } 
    } 
  }
  
  if (state_ == PageState::endgame) {
    timeline.clear();
    star_->stop();
  }
 // Reset Animation (currently working on it)
  if (state_ == PageState::goBack) {
    start_song = false; // Set it to false so the song starts over
    star_->stop();
    timeline.clear();
  }
}

void MyApp::draw() {
  draw_main();
  
  if (state_ == PageState::nextPage) {
    if (state_ == PageState::goBack) {
      draw_main();
    }
    draw_select();
  }

  if (state_ == PageState::playEasy) {
    draw_sheets();
    draw_nodes();
  }
  
  if (state_ == PageState::playMed) {
    draw_sheets();
  }
  
  if (state_ == PageState::endgame) {
    draw_endgame();
  }
}

void MyApp::draw_main() {
  cinder::gl::clear(cinder::Color(1,1,1));

  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {1300, 400};
  const Color pink = {1, 0, 1};
  PrintText("Rhythm Master", pink, size, center);

  const cinder::vec2 center2 = getWindowCenter();
  const cinder::ivec2 size2 = {1300, 220};
  const Color color2 = Color::black();
  PrintText("Press s to select", color2, size2, center2);

  const cinder::vec2 center3 = getWindowCenter();
  const cinder::ivec2 size3 = {1300, 50};
  const Color color3 = Color::black();
  PrintText("Press esc to quit", color3, size3, center3);
}

void MyApp::draw_select() {
  cinder::gl::clear(cinder::Color(1,1,1));
  
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {1300, 400};
  const Color color = {0, 1, 0};
  PrintText("Easy (press 1)", color, size, center);

  const cinder::vec2 center2 = getWindowCenter();
  const cinder::ivec2 size2 = {1300, 220};
  const Color color2 = {0, 0, 1};
  PrintText("Not Easy (press 2)", color2, size2, center2);

  const cinder::vec2 center3 = getWindowCenter();
  const cinder::ivec2 size3 = {1300, 50};
  const Color color3 = {1, 0, 0};
  PrintText("Go Back(left arrow key)", color3, size3, center3);
}

void MyApp::draw_sheets() {
  // Vertical lines
  cinder::gl::clear(cinder::Color(1,1,1));
  
  cinder::gl::drawSolidRect(Rectf(190, 800, 200, 0));
  cinder::gl::drawSolidRect(Rectf(390, 800, 400, 0));
  cinder::gl::drawSolidRect(Rectf(590, 800, 600, 0));
  // Horizontal line
  cinder::gl::drawSolidRect(Rectf(800, 690, 0, 700));
}

void MyApp::draw_endgame() {
  cinder::gl::clear(cinder::Color(0,0,0));
  
  const cinder::vec2 center2 = getWindowCenter();
  const cinder::ivec2 size2 = {1500, 220};
  const Color yellow = {1, 1, 0};
  PrintText("You Win!", yellow, size2, center2);
}

void MyApp::draw_nodes() {
  
  // Draws out the nodes consist of 4 circles
  cinder::gl::ScopedColor color( Color(cinder::CM_HSV, 0.72f, 1.0f, 1.0f));
  cinder::gl::drawSolidCircle(position_a_, 30.0f);

  cinder::gl::ScopedColor color2(Color(cinder::CM_HSV, 0.72f, 1.0f, 1.0f));
  cinder::gl::drawSolidCircle(position_b_, 30.0f);

  cinder::gl::ScopedColor color3( Color(cinder::CM_HSV, 0.72f, 1.0f, 1.0f));
  cinder::gl::drawSolidCircle(position_c_, 30.0f);

  cinder::gl::ScopedColor color4( Color(cinder::CM_HSV, 0.72f, 1.0f, 1.0f));
  cinder::gl::drawSolidCircle(position_d_, 30.0f); 
} 


void MyApp::keyDown(KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_ESCAPE) {
    exit(0);
  }
  
  if (event.getChar() == 's') {
    state_ = PageState::nextPage;
  }
  
  if (event.getCode() == KeyEvent::KEY_LEFT) {
    state_ = PageState::goBack;
    timeline.clear();
  }
  
  if (event.getCode() == KeyEvent::KEY_1) {
    state_ = PageState::playEasy;
    timeline.resetTime();
    set_easy_animation();
  }

  if (event.getCode() == KeyEvent::KEY_2) {
    state_ = PageState::playMed;
  }
  
  // This is for in game interactions

  if (event.getChar() == 'q') {
    state_ = PageState::Qpressed;
  }

  if (event.getChar() == 'w') {
    state_ = PageState::Wpressed;
  }

  if (event.getChar() == 'o') {
    state_ = PageState::Opressed;
  }

  if (event.getChar() == 'p') {
    state_ = PageState::Ppressed;
  }
}

void MyApp::set_songs() {
  cinder::audio::SourceFileRef songOneFile =
      cinder::audio::load(cinder::app::loadAsset("star.mp3"));
  star_ = cinder::audio::Voice::create(songOneFile);
}

void MyApp::set_easy_animation() {
  
  // Make the slide ramp for each circle with different speed
  PhraseRef<cinder::vec2> slide =
      makeRamp(cinder::vec2(85, kBegin), cinder::vec2(85, kEnd), 6.0f, EaseInOutCubic());

  PhraseRef<cinder::vec2> slide_second =
      makeRamp(cinder::vec2(300, kBegin), cinder::vec2(300, kEnd), 10.0f, EaseInOutCubic());

  PhraseRef<cinder::vec2> slide_third =
      makeRamp(cinder::vec2(500, kBegin), cinder::vec2(500, kEnd), 8.0f, EaseInOutCubic());

  PhraseRef<cinder::vec2> slide_fourth =
      makeRamp(cinder::vec2(710, kBegin), cinder::vec2(710, kEnd), 12.0f, EaseInOutCubic());

  // Apply the sliding animation for each circle, and loop them
  timeline.apply(&position_a_, slide).finishFn([&m = *position_a_.inputPtr()] {
    m.resetTime();
  });

  timeline.apply(&position_b_, slide_second).finishFn([&m = *position_b_.inputPtr()] {
    m.resetTime();
  });

  timeline.apply(&position_c_, slide_third).finishFn([&m = *position_c_.inputPtr()] {
    m.resetTime();
  });

  timeline.apply(&position_d_, slide_fourth).finishFn([&m = *position_d_.inputPtr()] {
    m.resetTime();
  });
  
  timeline.jumpTo(0);
  
  
  
  
  
}


}  // namespace myapp
