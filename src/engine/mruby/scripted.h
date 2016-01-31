#ifndef SCRIPTED_H
#define SCRIPTED_H
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/proc.h>
#include <mruby/variable.h>
#include <mruby/string.h>
#include <mruby/array.h>

class Entity;

class Scripted {
public:
  Scripted();
  ~Scripted();
  void ExecuteUpdate(mrb_state * mrb);
  mrb_value & GetScriptObject();
  void SetScriptObject(mrb_value object);
  void SetOwner(Entity * owner);
  Entity * GetOwner();
private:
  mrb_state * mMrb;
  mrb_value mObject;

  Entity * mOwner;
};


#endif // SCRIPTED_H
