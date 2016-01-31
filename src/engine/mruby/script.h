#ifndef SCRIPT_H
#define SCRIPT_H
#include <string>
#include <list>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/proc.h>
#include <mruby/variable.h>
#include <mruby/string.h>
#include <mruby/array.h>


class Entity;

class Script
{
public:
  Script(unsigned int id,std::string path);
  ~Script();
  void LoadTo(mrb_state * mrb);
  void SetObject(mrb_value obj);
  void ExecuteUpdate();

  void SetOwner(Entity * owner);
  Entity * GetOwner();
private:
  unsigned int mId;
  std::string mPath;
  bool mLoaded;
  mrb_value mObject;
  Entity * mOwner;
  mrb_state * mMrb;
};



#endif // SCRIPT_H
