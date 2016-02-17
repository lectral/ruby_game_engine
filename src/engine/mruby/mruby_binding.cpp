#include "mruby_binding.h"
#include "easylogging++.h"
#include <string>
#include "engine/sounds/sound_engine.h"
#include "app/app.h"
#include <chrono>

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
  LOG(DEBUG) << "Trying to load mrb file: "+file+" .";
  FILE* f;
  mrb_value obj;

  f = fopen(file.c_str(), "r");
  obj = mrb_load_file(mMrb, f);
  if (mMrb->exc) {
    // Error
    obj = mrb_funcall(mMrb, mrb_obj_value(mMrb->exc), "inspect", 0);
    LOG(ERROR) << "Failed on loading file: "<<file;
    LOG(ERROR) << RSTRING_PTR(obj);
    gApp.Error("");
  }
  LOG(DEBUG) << "Loading mrb file: "+file+" completed.";
}

void MRubyBinding::AddScript(std::string file){
  mScripts.push_back(Script(mScriptsIndex,file));
  mScripts.back().LoadTo(mMrb);
}

Scripted * MRubyBinding::AddScripted(Scripted scripted){
  mScripted.push_back(scripted);
  return &mScripted.back();
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


Entity * MRubyBinding::GetCurrentEntity(){
  return mCurrentEntity;
}

void MRubyBinding::SetCurrentEntity(Entity * entity){
  mCurrentEntity = entity;
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
  InstallFunction(set_position,"cpp_set_position");
  InstallFunction(rotate_drawable,"cpp_rotate_drawable");
  InstallFunction(set_drawable_rotation,"cpp_set_drawable_rotation");
  InstallFunction(hide_drawable,"cpp_hide_drawable");
  InstallFunction(load_script,"cpp_load_script");
  InstallFunction(add_script,"cpp_add_script");
  InstallFunction(set_scripted,"cpp_set_scripted");
  InstallFunction(load_texture,"cpp_load_texture");
  InstallFunction(load_visuals,"cpp_load_visuals");
  InstallFunction(random_number,"cpp_random_number");
  InstallFunction(add_string,"cpp_add_string");
  InstallFunction(get_string,"cpp_get_string");
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
  InstallFunction(check_collision,"cpp_check_collision");
  InstallFunction(is_mouse_pressed,"cpp_is_mouse_pressed");
  InstallFunction(get_position_x,"cpp_get_position_x");
  InstallFunction(get_position_y,"cpp_get_position_y");
  InstallFunction(load_module,"cpp_load_module");
  InstallFunction(load_db,"cpp_load_db");
  InstallFunction(stop_engine,"cpp_stop_engine");
  InstallFunction(set_layer,"cpp_set_layer");
  InstallFunction(set_text_layer,"cpp_set_text_layer");
  InstallFunction(move_view,"cpp_move_view");
  InstallFunction(get_frame_time,"cpp_get_frame_time");
  InstallFunction(add_bounding_box,"cpp_add_bounding_box");
  InstallFunction(set_text,"cpp_set_text");
  InstallFunction(change_text,"cpp_change_text");
  InstallFunction(get_current_fps,"cpp_get_current_fps");
  InstallFunction(set_text_size,"cpp_set_text_size");
  InstallFunction(set_text_color,"cpp_set_text_color");
  InstallFunction(get_object,"cpp_get_object");
  //Binds
}





void MRubyBinding::Initialize(){
  mrb_value obj;
  obj = mrb_funcall(mMrb, mrb_top_self(mMrb), "initialize", 0);
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
  for(auto it = mScripted.begin();it != mScripted.end();++it){
    mCurrentEntity = it->GetOwner();
    it->ExecuteUpdate(mMrb);
  }
}


void MRubyBinding::LoadModule(std::string name){
  LoadScript("data/"+name+"/init.rb");
  mrb_value obj;
  obj = mrb_funcall(mMrb, mrb_top_self(mMrb), "on_load", 0);
   if (mMrb->exc) {
    // Error
    obj = mrb_funcall(mMrb, mrb_obj_value(mMrb->exc), "inspect", 0);
    LOG(ERROR) << "Module: "+name+" failed on load";
    LOG(ERROR) << RSTRING_PTR(obj);
  } 
}

void MRubyBinding::LoadDb(std::string name){
  LoadScript("data/"+name+"/db/db.rb");
  LoadScript("data/"+name+"/db/string.db.rb");
  LoadScript("data/"+name+"/db/texture.db.rb");
  LoadScript("data/"+name+"/db/sound.db.rb");
  LoadScript("data/"+name+"/db/music.db.rb");
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
  gApp.GetEngine().GetBinding().SetCurrentEntity(&gApp.GetEngine().GetEntities().GetEntity(ret_id));
  gApp.GetEngine().GetEntities().GetEntity(ret_id).SetPhysical(gApp.GetEngine().GetPhysics().GetPhysical(physical_id));
  return mrb_fixnum_value(ret_id);
}

mrb_value MRubyBinding::set_visual(mrb_state *mrb,mrb_value self){
  mrb_int rb_id;
  mrb_value arg2;
  mrb_get_args(mrb, "iS", &rb_id,&arg2);
  std::string visual(mrb_string_value_cstr(mrb, &arg2));
  //[TO-DO] Add method to graphics manager to shorten this.
  unsigned int drawable_id = gApp.GetEngine().GetGraphics().AddDrawable(visual);
  gApp.GetEngine().GetEntities().GetEntity(rb_id).SetVisual(gApp.GetEngine().GetGraphics().GetDrawable(drawable_id));
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
  CURRENT_ENTITY->GetVisual()->SetRepeatAnimation(rb_state);
  return mrb_nil_value();
}

mrb_value MRubyBinding::move_drawable(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_float rb_x;
  mrb_float rb_y;
  mrb_get_args(mrb, "iff", &rb_id,&rb_x,&rb_y);
  CURRENT_ENTITY->GetPhysical()->Move(rb_x,rb_y);
  return mrb_nil_value();
}

mrb_value MRubyBinding::set_position(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_float rb_x;
  mrb_float rb_y;
  mrb_get_args(mrb, "iff", &rb_id,&rb_x,&rb_y);
  CURRENT_ENTITY->GetPhysical()->SetPosition(rb_x,rb_y);

  return mrb_nil_value();
}




mrb_value MRubyBinding::rotate_drawable(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_float rb_rotation;
  mrb_get_args(mrb, "if", &rb_id,&rb_rotation);
  CURRENT_ENTITY->GetPhysical()->Rotate(rb_rotation);
  return mrb_nil_value();
}



mrb_value MRubyBinding::set_drawable_rotation(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_float rb_rotation;
  mrb_get_args(mrb, "if", &rb_id,&rb_rotation);
  CURRENT_ENTITY->GetPhysical()->SetRotation(rb_rotation);
  return mrb_nil_value();
}


mrb_value MRubyBinding::hide_drawable(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_bool rb_state;
  mrb_get_args(mrb, "ib", &rb_id,&rb_state);
   CURRENT_ENTITY->GetVisual()->SetHidden(rb_state);
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

mrb_value MRubyBinding::add_script(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_value arg2;
  mrb_get_args(mrb, "SS", &arg1,&arg2);
  std::string module(mrb_string_value_cstr(mrb, &arg1));
  std::string script(mrb_string_value_cstr(mrb, &arg2));
  gApp.GetEngine().GetBinding().AddScript("data/"+module+"/scripts/"+script+".rb");
  return mrb_nil_value();
}


mrb_value MRubyBinding::set_scripted(mrb_state *mrb,mrb_value self){
  mrb_int rb_id;
  mrb_value arg2;
  mrb_get_args(mrb, "io", &rb_id,&arg2);
  std::string script(mrb_string_value_cstr(mrb, &arg2));
  Scripted new_scripted;
  new_scripted.SetScriptObject(arg2);
  Scripted * script_ptr = gApp.GetEngine().GetBinding().AddScripted(new_scripted);
  gApp.GetEngine().GetEntities().GetEntity(rb_id).SetScripted(script_ptr);
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


mrb_value MRubyBinding::get_string(mrb_state *mrb,mrb_value self){
  mrb_value arg1;
  mrb_value arg2;
  mrb_get_args(mrb, "S", &arg1);
  std::string name(mrb_string_value_cstr(mrb, &arg1));
  std::string a = gApp.GetEngine().GetStrings().GetString(name);
  int len = a.length();
  const char * b = a.c_str();
  return mrb_str_new(mrb, b, len);
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
  gApp.GetEngine().GetGraphics().GetVisual(visual).AddAnimation(name,arg3);
  return mrb_nil_value();
}

mrb_value MRubyBinding::add_new_frame(mrb_state *mrb,mrb_value self){
  mrb_value arg1,arg2;
  mrb_int arg3,arg4,arg5,arg6;
  mrb_get_args(mrb, "SSiiii", &arg1,&arg2,&arg3,&arg4,&arg5,&arg6);
  std::string visual(mrb_string_value_cstr(mrb, &arg1));
  std::string animation(mrb_string_value_cstr(mrb, &arg2));
  gApp.GetEngine().GetGraphics().GetVisual(visual).AddAnimationFrame(animation,arg3,arg4,arg5,arg6);
  return mrb_nil_value();
}


mrb_value MRubyBinding::is_key_pressed(mrb_state *mrb,mrb_value self){
  mrb_int arg1;
  mrb_get_args(mrb, "i", &arg1);
  bool ret = gApp.GetEngine().GetInput().IsKeyPressed(static_cast<sf::Keyboard::Key>(arg1));
  //bool ret = true;
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

mrb_value MRubyBinding::check_collision(mrb_state *mrb,mrb_value self){
  mrb_int rb_id;
  mrb_value rb_entity;
  mrb_get_args(mrb, "iS", &rb_id,&rb_entity);
  std::string entity(mrb_string_value_cstr(mrb, &rb_entity));
  bool ret = CURRENT_ENTITY->GetPhysical()->CollidedWith(entity);

  return mrb_bool_value(ret);
}

mrb_value MRubyBinding::is_mouse_pressed(mrb_state *mrb,mrb_value self){
  mrb_int arg1;
  mrb_get_args(mrb, "i", &arg1);
  bool ret = gApp.GetEngine().GetInput().IsMousePressed(sf::Mouse::Left);
  //bool ret = true;
  if(ret){
    return mrb_true_value();
  }else{
    return mrb_false_value();
  }
}


mrb_value MRubyBinding::get_position_x(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_get_args(mrb, "i", &rb_id);

  float pos = CURRENT_ENTITY->GetPhysical()->GetPosition().x;


  return mrb_float_value(mrb,pos);
}

mrb_value MRubyBinding::get_position_y(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_get_args(mrb, "i", &rb_id);
  //std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  float pos = CURRENT_ENTITY->GetPhysical()->GetPosition().y;
  //std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  //LOG(DEBUG) << "GetEntity time: " <<std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  return mrb_float_value(mrb,pos);
}


mrb_value MRubyBinding::load_module(mrb_state *mrb,mrb_value self){
  mrb_value rb_name;
  mrb_get_args(mrb, "S", &rb_name);
  std::string name(mrb_string_value_cstr(mrb, &rb_name));
  gApp.GetEngine().GetBinding().LoadModule(name);
  return mrb_nil_value();
}

mrb_value MRubyBinding::load_db(mrb_state *mrb,mrb_value self){
  mrb_value rb_name;
  mrb_get_args(mrb, "S", &rb_name);
  std::string name(mrb_string_value_cstr(mrb, &rb_name));
  gApp.GetEngine().GetBinding().LoadDb(name);
  return mrb_nil_value();
}

mrb_value MRubyBinding::stop_engine(mrb_state *mrb,mrb_value self){
  gApp.GetEngine().Stop();
  return mrb_nil_value();
}

mrb_value MRubyBinding::set_layer(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_int rb_layer=0;
  mrb_get_args(mrb, "ii", &rb_id, &rb_layer);
  CURRENT_ENTITY->GetVisual()->SetLayer(rb_layer); 
  return mrb_nil_value();
}


mrb_value MRubyBinding::set_text_layer(mrb_state *mrb,mrb_value self){
  mrb_int rb_id=0;
  mrb_int rb_layer=0;
  mrb_get_args(mrb, "ii", &rb_id, &rb_layer);
  CURRENT_ENTITY->GetTexted()->SetLayer(rb_layer);
  return mrb_nil_value();
}

mrb_value MRubyBinding::move_view(mrb_state *mrb,mrb_value self){
  mrb_float rb_x;
  mrb_float rb_y;
  mrb_get_args(mrb, "ff", &rb_x,&rb_y);
  gApp.GetEngine().GetGraphics().GetMainView().move(rb_x,rb_y);
  return mrb_nil_value();
}

MRUBY_FUNCTION_HEADER(get_frame_time){
  return mrb_float_value(mrb,gApp.GetEngine().GetFrameTime().asSeconds());
}

MRUBY_FUNCTION_HEADER(add_bounding_box){
  mrb_int rb_id;
  mrb_int rb_type;
  mrb_value rb_array;
  sf::Vector2f a;
  sf::Vector3f b;
  sf::FloatRect c;
  mrb_get_args(mrb, "iio", &rb_id,&rb_type,&rb_array);
  if ( mrb_array_p( rb_array ) ){
    int len = RARRAY_LEN( rb_array );
    if(len==2){
      // point
      float x = mrb_fixnum( mrb_ary_ref( mrb, rb_array, 0 ));
      float y = mrb_fixnum( mrb_ary_ref( mrb, rb_array, 1 ));
      a = sf::Vector2f(x,y);
    }else if(len==3){
      float x = mrb_fixnum( mrb_ary_ref( mrb, rb_array, 0 ));
      float y = mrb_fixnum( mrb_ary_ref( mrb, rb_array, 1 ));
      float z = mrb_fixnum( mrb_ary_ref( mrb, rb_array, 2 ));
      b = sf::Vector3f(x,y,z);
    }else if(len==4){
        float x = mrb_fixnum( mrb_ary_ref( mrb, rb_array, 0 ));
        float y = mrb_fixnum( mrb_ary_ref( mrb, rb_array, 1 ));
        float h = mrb_fixnum( mrb_ary_ref( mrb, rb_array, 2 ));
        float w = mrb_fixnum( mrb_ary_ref( mrb, rb_array, 3 ));
        c = sf::FloatRect(x,y,h,w);
      }
    }
  BoundingBoxType type = static_cast<BoundingBoxType>(rb_type); switch(type){ case CIRCLE:
      CURRENT_ENTITY->GetPhysical()->AddBoundingBox((static_cast<BoundingBoxType>(rb_type)),b);
    break;
    case POINT:
      CURRENT_ENTITY->GetPhysical()->AddBoundingBox((static_cast<BoundingBoxType>(rb_type)),a);
    break;
    case RECT:  
      CURRENT_ENTITY->GetPhysical()->AddBoundingBox((static_cast<BoundingBoxType>(rb_type)),c);
    break;
    }

  }

MRUBY_FUNCTION_HEADER(set_text){
  mrb_int rb_id;
  mrb_value rb_string;
  mrb_get_args(mrb, "iS", &rb_id, &rb_string);
  std::string content (mrb_string_value_cstr(mrb, &rb_string));
  Text * text = gApp.GetEngine().GetGraphics().AddText();
  gApp.GetEngine().GetEntities().GetEntity(rb_id).SetTexted(text);
  gApp.GetEngine().GetEntities().GetEntity(rb_id).GetTexted()->SetText(content);

}

MRUBY_FUNCTION_HEADER(change_text){
  mrb_int rb_id;
  mrb_value rb_string;
  mrb_get_args(mrb, "iS", &rb_id, &rb_string);
  std::string content(mrb_string_value_cstr(mrb, &rb_string));
  CURRENT_ENTITY->GetTexted()->SetText(content);
}

MRUBY_FUNCTION_HEADER(get_current_fps){
  return mrb_fixnum_value(gApp.GetEngine().GetCurrentFPS());
}

MRUBY_FUNCTION_HEADER(set_text_size){
  mrb_int rb_id;
  mrb_int rb_size;
  mrb_get_args(mrb, "ii", &rb_id, &rb_size);
  CURRENT_ENTITY->GetTexted()->SetSize(rb_size);
}

MRUBY_FUNCTION_HEADER(set_text_color){
  mrb_int rb_id;
  mrb_int r;
  mrb_int g;
  mrb_int b;
  mrb_get_args(mrb, "iiii", &rb_id,&r,&g,&b);
  CURRENT_ENTITY->GetTexted()->SetColor(r,g,b);    
}

MRUBY_FUNCTION_HEADER(get_object){
  mrb_int rb_id;
  mrb_get_args(mrb,"i", &rb_id); 
  return gApp.GetEngine().GetEntities().GetEntity(rb_id).GetScripted()->GetScriptObject();  


}
