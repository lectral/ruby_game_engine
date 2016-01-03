#include "mruby_binding.h"
#include "easylogging++.h"
#include <string>
#include "engine/sound_engine.h"
#include "app/app.h"

#include <cstdlib>
#include <ctime>

MRubyBinding::MRubyBinding(){
  srand(time(NULL));
}

MRubyBinding::~MRubyBinding(){

}

void MRubyBinding::InitMRuby(){
  mMrb = mrb_open();
  mRubyInitialized = true;
  LOG(DEBUG) << ("mruby initialized.");
}

void MRubyBinding::LoadScript(std::string file){
  FILE* f;
  f = fopen(file.c_str(), "r");
  mValue = mrb_load_file(mMrb, f);
}

void MRubyBinding::LoadEntryPoint(std::string file){
  FILE* f;
  f = fopen(file.c_str(), "r");
  mValue = mrb_load_file(mMrb, f);
  mrb_value obj;
  obj = mrb_funcall(mMrb, mrb_top_self(mMrb), "entry_point", 0);
   if (mMrb->exc) {
    // Error
    obj = mrb_funcall(mMrb, mrb_obj_value(mMrb->exc), "inspect", 0);
    LOG(ERROR) << RSTRING_PTR(obj);
  } 
}



void MRubyBinding::BindCpp(){
  //Binds
  InstallFunction(play_sound,"cpp_play_sound");
  InstallFunction(log,"cpp_log");
  InstallFunction(create_entity,"cpp_create_entity");
  InstallFunction(set_visual,"cpp_set_visual");
  InstallFunction(set_animation,"cpp_set_animation");
  InstallFunction(set_animation_repeat,"cpp_set_animation_repeat");
  InstallFunction(move_drawable,"cpp_move_drawable");
  InstallFunction(rotate_drawable,"cpp_rotate_drawable");
  InstallFunction(set_drawable_rotation,"cpp_set_drawable_rotation");
  InstallFunction(hide_drawable,"cpp_hide_drawable");
  InstallFunction(load_script,"cpp_load_script");
  InstallFunction(load_texture,"cpp_load_texture");
  InstallFunction(load_visuals,"cpp_load_visuals");
  InstallFunction(random_number,"cpp_random_number");
  InstallFunction(add_string,"cpp_add_string");
  InstallFunction(current_localization,"cpp_current_localization");
  InstallFunction(add_texture_file,"cpp_add_texture_file");
  InstallFunction(add_music_file,"cpp_add_music_file");
  InstallFunction(add_sound_file,"cpp_add_sound_file");
  InstallFunction(hires_textures,"cpp_hires_textures");
  InstallFunction(add_new_visual,"cpp_add_new_visual");
  InstallFunction(add_new_animation,"cpp_add_new_animation");
  InstallFunction(add_new_frame,"cpp_add_new_frame");
  InstallFunction(is_key_pressed,"cpp_is_key_pressed");
  InstallFunction(mouse_pos_x,"cpp_mouse_pos_x");
  InstallFunction(mouse_pos_y,"cpp_mouse_pos_y");
  InstallFunction(drawable_contains_point,"cpp_drawable_contains_point");
  //Binds
}





void MRubyBinding::Initialize(){
  mrb_value obj;
  obj = mrb_funcall(mMrb, mrb_top_self(mMrb), "prepare", 0);
   if (mMrb->exc) {
    // Error
    obj = mrb_funcall(mMrb, mrb_obj_value(mMrb->exc), "inspect", 0);
    LOG(ERROR) << RSTRING_PTR(obj);
  } 
}


void MRubyBinding::InstallFunction(mrb_func_t func,std::string func_name){
  mrb_define_method(mMrb, mMrb->object_class, func_name.c_str(), func, MRB_ARGS_ANY());
}

void MRubyBinding::Update(){
  mrb_value obj;
  obj = mrb_funcall(mMrb, mrb_top_self(mMrb), "run", 0);
   if (mMrb->exc) {
    // Error
    obj = mrb_funcall(mMrb, mrb_obj_value(mMrb->exc), "backtrace", 0);
    LOG(ERROR) << RSTRING_PTR(obj);
    gApp.Error("mRuby error! Aborting...");
  }
}



// All bind should be after this line
// Do not touch the next line
// [BINDS_HEADER]

mrb_value MRubyBinding::play_sound(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_int arg2;
  mrb_get_args(mrb, "S", &arg1);
  std::string par1(mrb_string_value_cstr(mrb, &arg1));
  gApp.GetEngine().GetSound().PlaySound(par1);
  return mrb_nil_value();
}

mrb_value MRubyBinding::log(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_int arg2;
  mrb_get_args(mrb, "S", &arg1);
  std::string par1(mrb_string_value_cstr(mrb, &arg1));
  LOG(INFO) << "[mruby] " << par1;
  return mrb_nil_value();
}



mrb_value MRubyBinding::create_entity(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_get_args(mrb,"S",&arg1);
  std::string name(mrb_string_value_cstr(mrb,&arg1));
  unsigned int physical_id = gApp.GetEngine().GetPhysics().AddPhysical();
  int ret_id = gApp.GetEngine().GetEntities().AddEntity(name);
  gApp.GetEngine().GetEntities().GetEntity(ret_id).SetPhysical( gApp.GetEngine().GetPhysics().GetPhysical(physical_id));
  return mrb_fixnum_value(ret_id);
}

mrb_value MRubyBinding::set_visual(mrb_state *mrb,mrb_value self){
  mrb_int rb_id;
  mrb_value arg2;
  mrb_get_args(mrb, "iS", &rb_id,&arg2);
  std::string visual(mrb_string_value_cstr(mrb, &arg2));
  //[TO-DO] Add method to graphics manager to shorten this.
  gApp.GetEngine().GetGraphics().GetVisual(visual)->CreateThis();
  gApp.GetEngine().GetEntities().GetEntity(rb_id).SetVisual(gApp.GetEngine().GetGraphics().GetVisual(visual));
  return mrb_nil_value();
}

mrb_value MRubyBinding::set_animation(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_value arg2;
  mrb_get_args(mrb, "iS", &rb_id,&arg2);
  std::string animation(mrb_string_value_cstr(mrb, &arg2));
  gApp.GetEngine().GetEntities().GetEntity(rb_id).GetVisual()->PlayAnimation(animation);
  return mrb_nil_value();
}

mrb_value MRubyBinding::set_animation_repeat(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_bool rb_state;
  mrb_get_args(mrb, "ib", &rb_id,&rb_state);
  gApp.GetEngine().GetEntities().GetEntity(rb_id).GetVisual()->SetRepeatAnimation(rb_state);
  return mrb_nil_value();
}

mrb_value MRubyBinding::move_drawable(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_float rb_x;
  mrb_float rb_y;
  mrb_get_args(mrb, "iff", &rb_id,&rb_x,&rb_y);
  gApp.GetEngine().GetEntities().GetEntity(rb_id).GetPhysical()->Move(rb_x,rb_y);

  return mrb_nil_value();
}



mrb_value MRubyBinding::rotate_drawable(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_float rb_rotation;
  mrb_get_args(mrb, "if", &rb_id,&rb_rotation);
  gApp.GetEngine().GetEntities().GetEntity(rb_id).GetPhysical()->Rotate(rb_rotation);
  return mrb_nil_value();
}



mrb_value MRubyBinding::set_drawable_rotation(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_float rb_rotation;
  mrb_get_args(mrb, "if", &rb_id,&rb_rotation);
  gApp.GetEngine().GetEntities().GetEntity(rb_id).GetPhysical()->SetRotation(rb_rotation);
  return mrb_nil_value();
}


mrb_value MRubyBinding::hide_drawable(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_bool rb_state;
  mrb_get_args(mrb, "ib", &rb_id,&rb_state);
   gApp.GetEngine().GetEntities().GetEntity(rb_id).GetVisual()->SetHidden(rb_state);
  return mrb_nil_value();
}



mrb_value MRubyBinding::load_script(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_value arg2;
  mrb_get_args(mrb, "SS", &arg1,&arg2);
  std::string module(mrb_string_value_cstr(mrb, &arg1));
  std::string script(mrb_string_value_cstr(mrb, &arg2));
  gApp.GetEngine().GetBinding().LoadScript("data/"+module+"/scripts/"+script+".rb");
  return mrb_nil_value();
}

mrb_value MRubyBinding::load_texture(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_value arg2;
  mrb_get_args(mrb, "S", &arg1);
  std::string texture(mrb_string_value_cstr(mrb, &arg1));
  gApp.GetEngine().GetGraphics().LoadTexture(texture);
  return mrb_nil_value();
}

mrb_value MRubyBinding::load_visuals(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_get_args(mrb, "S", &arg1);
  std::string module(mrb_string_value_cstr(mrb, &arg1));
  gApp.GetEngine().GetBinding().LoadScript("data/"+module+"/db/visuals.db.rb");
  return mrb_nil_value();
}

mrb_value MRubyBinding::random_number(mrb_state *mrb,mrb_value self){
  mrb_int arg1;
  mrb_int arg2;
  mrb_get_args(mrb, "ii", &arg1,&arg2);

  return mrb_fixnum_value(rand() % (arg2+1) + arg1);
}

mrb_value MRubyBinding::add_string(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_value arg2;
  mrb_get_args(mrb, "SS", &arg1,&arg2);
  std::string name(mrb_string_value_cstr(mrb, &arg1));
  std::string value(mrb_string_value_cstr(mrb, &arg2));
  gApp.GetEngine().GetStrings().AddString(name,value);
  return mrb_nil_value();
}

mrb_value MRubyBinding::current_localization(mrb_state *mrb,mrb_value self){
  const char * a = gApp.GetEngine().GetStrings().GetLanguage().c_str();
  int len = gApp.GetEngine().GetStrings().GetLanguage().length();
  return mrb_str_new(mrb, a, len);
}


mrb_value MRubyBinding::add_texture_file(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_value arg2;
  mrb_value arg3;
  mrb_get_args(mrb, "SSS", &arg1,&arg2,&arg3);
  std::string module(mrb_string_value_cstr(mrb, &arg1));
  std::string name(mrb_string_value_cstr(mrb, &arg2));
  std::string path(mrb_string_value_cstr(mrb, &arg3));
  gApp.GetEngine().GetGraphics().AddTextureFile(module,name,path);
  return mrb_nil_value();
}


mrb_value MRubyBinding::add_music_file(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_value arg2;
  mrb_value arg3;
  mrb_get_args(mrb, "SSS", &arg1,&arg2,&arg3);
  std::string module(mrb_string_value_cstr(mrb, &arg1));
  std::string name(mrb_string_value_cstr(mrb, &arg2));
  std::string path(mrb_string_value_cstr(mrb, &arg3));
  gApp.GetEngine().GetSound().AddMusicFile(module,name,path);
  return mrb_nil_value();
}


mrb_value MRubyBinding::add_sound_file(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_value arg2;
  mrb_value arg3;
  mrb_get_args(mrb, "SSS", &arg1,&arg2,&arg3);
  std::string module(mrb_string_value_cstr(mrb, &arg1));
  std::string name(mrb_string_value_cstr(mrb, &arg2));
  std::string path(mrb_string_value_cstr(mrb, &arg3));
  gApp.GetEngine().GetSound().AddSoundFile(module,name,path);
  return mrb_nil_value();
}

mrb_value MRubyBinding::hires_textures(mrb_state *mrb,mrb_value self){
  if(gApp.GetEngine().GetGraphics().HiResTextures())
    return mrb_true_value();
  else{
    return mrb_false_value();
  }

}

mrb_value MRubyBinding::add_new_visual(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_value arg2;
  mrb_get_args(mrb, "SS", &arg1,&arg2);
  std::string name(mrb_string_value_cstr(mrb, &arg1));
  std::string texture(mrb_string_value_cstr(mrb, &arg2));
  gApp.GetEngine().GetGraphics().AddVisual(name,texture);
  return mrb_nil_value();
}

mrb_value MRubyBinding::add_new_animation(mrb_state *mrb,mrb_value self){
  mrb_value arg1,arg2;
  mrb_float arg3;
  mrb_get_args(mrb, "SSf", &arg1,&arg2,&arg3);
  std::string visual(mrb_string_value_cstr(mrb, &arg1));
  std::string name(mrb_string_value_cstr(mrb, &arg2));
  gApp.GetEngine().GetGraphics().GetVisual(visual)->AddAnimation(name,arg3);
  return mrb_nil_value();
}

mrb_value MRubyBinding::add_new_frame(mrb_state *mrb,mrb_value self){
  mrb_value arg1,arg2;
  mrb_int arg3,arg4,arg5,arg6;
  mrb_get_args(mrb, "SSiiii", &arg1,&arg2,&arg3,&arg4,&arg5,&arg6);
  std::string visual(mrb_string_value_cstr(mrb, &arg1));
  std::string animation(mrb_string_value_cstr(mrb, &arg2));
  gApp.GetEngine().GetGraphics().GetVisual(visual)->AddAnimationFrame(animation,arg3,arg4,arg5,arg6);
  return mrb_nil_value();
}


mrb_value MRubyBinding::is_key_pressed(mrb_state *mrb,mrb_value self){
  mrb_int arg1;
  mrb_get_args(mrb, "i", &arg1);
  //bool ret = gApp.GetEngine().GetInput().IsKeyPressed(sf::Keyboard::A);
  bool ret = true;
  if(ret){
    return mrb_true_value();
  }else{
    return mrb_false_value();
  }
}


mrb_value MRubyBinding::mouse_pos_x(mrb_state *mrb,mrb_value self){
  mrb_int arg1;
  int ret = gApp.GetEngine().GetInput().GetMouseX();
  return mrb_fixnum_value(ret);
}



mrb_value MRubyBinding::mouse_pos_y(mrb_state *mrb,mrb_value self){
  mrb_int arg1;
  int ret = gApp.GetEngine().GetInput().GetMouseY();
  return mrb_fixnum_value(ret);
}

mrb_value MRubyBinding::drawable_contains_point(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_float rb_x,rb_y;
  mrb_get_args(mrb, "iff", &rb_id,&rb_x,&rb_y);
  bool ret = true;
  return mrb_bool_value(ret);
}













































