#include "scripted.h"
#include "engine/entities/entity.h"
#include "easylogging++.h"

Scripted::Scripted(){

}

Scripted::~Scripted(){

}

void Scripted::SetScriptObject(mrb_value object){
  mObject = object;
}

void Scripted::ExecuteUpdate(mrb_state * mrb){
  mrb_value obj;
  obj = mrb_funcall(mrb, mObject, "update", 0);
   if (mrb->exc) {
    // Error
    obj = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0);
    LOG(ERROR) << RSTRING_PTR(obj);
    LOG(ERROR) << GetOwner()->GetName() << ": script failed";
  }
}

void Scripted::SetOwner(Entity * owner){
  mOwner = owner;
}

Entity * Scripted::GetOwner(){
  return mOwner;
}

mrb_value & Scripted::GetScriptObject(){
  return mObject;
}


