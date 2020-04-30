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


using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;

using std::chrono::seconds;
using std::chrono::system_clock;

using std::string;
using choreograph::Time;

MyApp::MyApp() :
  state_{PageState::kFirstPage} {}


void MyApp::setup() {

  // Setup drop animation
  set_animation();
  set_songs();
  
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
    auto dt = (Time)_timer.getSeconds();
    _timer.start();
    timeline.step(dt);
    //star_->start();
  } 
  
  if (state_ == PageState::playMed) {
  //  birthday_->start();
  }
 
 
  if (state_ == PageState::goBack) {
    star_->stop();
    _timer.stop();
  //  birthday_->stop();
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
    draw_drop_animation();
  }
  
  if (state_ == PageState::playMed) {
    draw_sheets();
  }
}

void MyApp::draw_main() {
  cinder::gl::clear(cinder::Color(1,1,1));

  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {1300, 400};
  const Color color = {1, 0, 0};
  //size_t row = 0;
  PrintText("Rhythm Master", color, size, center);

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
  //size_t row = 0;
  PrintText("Easy (press 1)", color, size, center);

  const cinder::vec2 center2 = getWindowCenter();
  const cinder::ivec2 size2 = {1300, 220};
  const Color color2 = {0, 0, 1};
  PrintText("Not Easy (press 2)", color2, size2, center2);
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


void MyApp::draw_drop_animation() {
  cinder::gl::ScopedColor color( Color(cinder::CM_HSV, 0.72f, 1.0f, 1.0f));
  cinder::gl::drawSolidCircle( _position_a, 30.0f);

  cinder::gl::ScopedColor color2(Color(cinder::CM_HSV, 0.72f, 1.0f, 1.0f));
  cinder::gl::drawSolidCircle(_position_b, 30.0f);

  cinder::gl::ScopedColor color3( Color(cinder::CM_HSV, 0.72f, 1.0f, 1.0f));
  cinder::gl::drawSolidCircle(_position_c, 30.0f);

  cinder::gl::ScopedColor color4( Color(cinder::CM_HSV, 0.72f, 1.0f, 1.0f));
  cinder::gl::drawSolidCircle(_position_d, 30.0f); 
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
  }
  
  if (event.getCode() == KeyEvent::KEY_1) {
    state_ = PageState::playEasy;
  }

  if (event.getCode() == KeyEvent::KEY_2) {
    state_ = PageState::playMed;
  }
  
}

void MyApp::set_songs() {
  cinder::audio::SourceFileRef songOneFile =
      cinder::audio::load(cinder::app::loadAsset("star.mp3"));
  star_ = cinder::audio::Voice::create(songOneFile);

  cinder::audio::SourceFileRef songTwoFile =
      cinder::audio::load(cinder::app::loadAsset("birthday.mp3"));
  birthday_ = cinder::audio::Voice::create(songTwoFile);
}

void MyApp::set_animation(){
  float h = (float)cinder::app::getWindowHeight();
  float y1 = h * 0.02f;
  float y2 = h - y1;
  PhraseRef<cinder::vec2> slide =
      makeRamp(cinder::vec2(85, 0), cinder::vec2(85, 1000), 6.0f, EaseInOutCubic());

  PhraseRef<cinder::vec2> slide_second =
      makeRamp(cinder::vec2(300, 0), cinder::vec2(300, 1000), 10.0f, EaseInOutCubic());

  PhraseRef<cinder::vec2> slide_third =
      makeRamp(cinder::vec2(500, 0), cinder::vec2(500, 1000), 8.0f, EaseInOutCubic());

  PhraseRef<cinder::vec2> slide_fourth =
      makeRamp(cinder::vec2(710, 0), cinder::vec2(710, 1000), 12.0f, EaseInOutCubic());

  timeline.apply(&_position_a, slide);
  timeline.apply(&_position_b, slide_second);
  timeline.apply(&_position_c, slide_third);
  timeline.apply(&_position_d, slide_fourth);
  timeline.jumpTo(0);
}

}  // namespace myapp
