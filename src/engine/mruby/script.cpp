
#include "script.h"
#include "easylogging++.h"
#include "app/app.h"



Script::Script(unsigned int id, std::string path):
  mPath(path)
{
  mLoaded = false;
}

Script::~Script(){

}


void Script::LoadTo(mrb_state * mrb){
  LOG(DEBUG) << mPath << ": loading.";
  FILE* f;
  mrb_value obj;
  f = fopen(mPath.c_str(), "r");
  obj = mrb_load_file(mrb, f);
  if (mrb->exc) {
    // Error
    obj = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0);
    LOG(ERROR) << mrb << ": failed.";
    LOG(ERROR) << RSTRING_PTR(obj);
  }
  mMrb = mrb;
  mLoaded = true;
  LOG(DEBUG) << mrb << ": script loaded.";
}



void Script::SetObject(mrb_value obj){
  mObject = obj;
}

void Script::ExecuteUpdate(){
  mrb_value obj;
  LOG(DEBUG) << "updating: "+mPath;
  obj = mrb_funcall(mMrb, mObject, "update", 0);
   if (mMrb->exc) {
    // Error
    obj = mrb_funcall(mMrb, mrb_obj_value(mMrb->exc), "inspect", 0);
    LOG(ERROR) << RSTRING_PTR(obj);
    gApp.Error(mPath+": parsing error");
  }
}

void Script::SetOwner(Entity * owner){
  mOwner = owner;
}

Entity * Script::GetOwner(){
  return mOwner;
}
