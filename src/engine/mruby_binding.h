#ifndef MRUBY_BINDING_H
#define MRUBY_BINDING_H

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/proc.h>
#include <mruby/variable.h>
#include <mruby/string.h>
#include <string>

// for helpers



class SoundEngine;

class MRubyBinding
{
public:
  MRubyBinding();
  ~MRubyBinding();
  void InitMRuby();
  void LoadScript(std::string file);
  void LoadEntryPoint(std::string file);
  void Update();
  void BindCpp();
  void Initialize();
  void CloseMRuby();

  //Helpers


private:
  mrb_state * mMrb;
  mrb_value mValue;
  bool mRubyInitialized;

  //Binds
  static mrb_value play_sound(mrb_state *mrb,mrb_value self);
  static mrb_value log(mrb_state *mrb,mrb_value self);
  static mrb_value create_entity(mrb_state *mrb,mrb_value self);
  static mrb_value set_visual(mrb_state *mrb,mrb_value self);
  static mrb_value set_animation(mrb_state *mrb,mrb_value self);
  static mrb_value set_animation_repeat(mrb_state *mrb,mrb_value self);
  static mrb_value move_drawable(mrb_state *mrb,mrb_value self);
  static mrb_value rotate_drawable(mrb_state *mrb,mrb_value self);
  static mrb_value set_drawable_rotation(mrb_state *mrb,mrb_value self);
  static mrb_value hide_drawable(mrb_state *mrb,mrb_value self);
  static mrb_value load_script(mrb_state *mrb,mrb_value self);
  static mrb_value load_texture(mrb_state *mrb,mrb_value self);
  static mrb_value load_visuals(mrb_state *mrb,mrb_value self);
  static mrb_value random_number(mrb_state *mrb,mrb_value self);
  static mrb_value add_string(mrb_state *mrb,mrb_value self);
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
  //Binds




  void InstallFunction(mrb_func_t func,std::string func_name);

};




#endif // MRUBY_BINDING_H
