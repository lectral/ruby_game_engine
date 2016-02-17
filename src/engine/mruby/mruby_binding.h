#ifndef MRUBY_BINDING_H
#define MRUBY_BINDING_H

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/proc.h>
#include <mruby/variable.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <string>
#include "script.h"
#include "scripted.h"

// for helpers

#define MRUBY_FUNCTION_HEADER(X) mrb_value MRubyBinding::X(mrb_state *mrb,mrb_value self)
#define CURRENT_ENTITY gApp.GetEngine().GetBinding().GetCurrentEntity()

class SoundEngine;

class MRubyBinding
{
public:
  MRubyBinding();
  ~MRubyBinding();
  void InitMRuby();
  void LoadScript(std::string file);
  void AddScript(std::string file);
  Scripted * AddScripted(Scripted scripted);
  std::list<Scripted> & GetScripted();
  void LoadEntryPoint(std::string file);
  void Update();
  void BindCpp();
  void Initialize();
  void CloseMRuby();
  void LoadModule(std::string name);
  void LoadDb(std::string name);
  Entity * GetCurrentEntity();
  void SetCurrentEntity(Entity * entity);
  //Helpers


private:
  mrb_state * mMrb;
  mrb_value mValue;
  bool mRubyInitialized;
  std::list<Script> mScripts;
  std::list<Scripted> mScripted;
  unsigned int mScriptsIndex;
  unsigned int mScriptedIndex;
  
  Entity * mCurrentEntity;

  //Binds
  static mrb_value play_sound(mrb_state *mrb,mrb_value self);
  static mrb_value log(mrb_state *mrb,mrb_value self);
  static mrb_value create_entity(mrb_state *mrb,mrb_value self);
  static mrb_value set_visual(mrb_state *mrb,mrb_value self);
  static mrb_value set_animation(mrb_state *mrb,mrb_value self);
  static mrb_value set_animation_repeat(mrb_state *mrb,mrb_value self);
  static mrb_value move_drawable(mrb_state *mrb,mrb_value self);
  static mrb_value set_position(mrb_state *mrb,mrb_value self);
  static mrb_value rotate_drawable(mrb_state *mrb,mrb_value self);
  static mrb_value set_drawable_rotation(mrb_state *mrb,mrb_value self);
  static mrb_value hide_drawable(mrb_state *mrb,mrb_value self);
  static mrb_value load_script(mrb_state *mrb,mrb_value self);
  static mrb_value add_script(mrb_state *mrb,mrb_value self);
  static mrb_value set_scripted(mrb_state *mrb,mrb_value self);
  static mrb_value load_texture(mrb_state *mrb,mrb_value self);
  static mrb_value load_visuals(mrb_state *mrb,mrb_value self);
  static mrb_value random_number(mrb_state *mrb,mrb_value self);
  static mrb_value add_string(mrb_state *mrb,mrb_value self);
  static mrb_value get_string(mrb_state *mrb,mrb_value self);
  static mrb_value current_localization(mrb_state *mrb,mrb_value self);
  static mrb_value add_texture_file(mrb_state *mrb,mrb_value self);
  static mrb_value add_music_file(mrb_state *mrb,mrb_value self);
  static mrb_value add_sound_file(mrb_state *mrb,mrb_value self);
  static mrb_value hires_textures(mrb_state *mrb,mrb_value self);
  static mrb_value add_new_visual(mrb_state *mrb,mrb_value self);
  static mrb_value add_new_animation(mrb_state *mrb,mrb_value self);
  static mrb_value add_new_frame(mrb_state *mrb,mrb_value self);
  static mrb_value is_key_pressed(mrb_state *mrb,mrb_value self);
  static mrb_value mouse_pos_x(mrb_state *mrb,mrb_value self);
  static mrb_value mouse_pos_y(mrb_state *mrb,mrb_value self);
  static mrb_value drawable_contains_point(mrb_state *mrb,mrb_value self);
  static mrb_value check_collision(mrb_state *mrb,mrb_value self);
  static mrb_value is_mouse_pressed(mrb_state *mrb,mrb_value self);
  static mrb_value get_position_x(mrb_state *mrb,mrb_value self);
  static mrb_value get_position_y(mrb_state *mrb,mrb_value self);
  static mrb_value load_module(mrb_state *mrb,mrb_value self);
  static mrb_value load_db(mrb_state *mrb,mrb_value self);
  static mrb_value stop_engine(mrb_state *mrb,mrb_value self);
  static mrb_value set_layer(mrb_state *mrb,mrb_value self);
  static mrb_value set_text_layer(mrb_state *mrb,mrb_value self);
  static mrb_value move_view(mrb_state *mrb,mrb_value self);
  static mrb_value get_frame_time(mrb_state *mrb,mrb_value self);
  static mrb_value add_bounding_box(mrb_state *mrb,mrb_value self);
  static mrb_value set_text(mrb_state *mrb,mrb_value self);
  static mrb_value change_text(mrb_state *mrb,mrb_value self);
  static mrb_value get_current_fps(mrb_state *mrb,mrb_value self);
  static mrb_value set_text_size(mrb_state *mrb,mrb_value self);
  static mrb_value set_text_color(mrb_state *mrb,mrb_value self);
  static mrb_value get_object(mrb_state *mrb,mrb_value self);
  //Binds




  void InstallFunction(mrb_func_t func,std::string func_name);

};




#endif // MRUBY_BINDING_H
