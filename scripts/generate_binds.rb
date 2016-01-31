require 'pathname'



binds_cpp_path = Pathname.new("src/engine/mruby/mruby_binding.cpp")
binds_h_path = Pathname.new("src/engine/mruby/mruby_binding.h")
binds_cpp = File.read(binds_cpp_path)
bind_header =  File.read(binds_cpp_path.to_s.gsub(".cpp",".h"))
headers = []
installs = []
binds_cpp.lines.each do |line|
  if((line.include? "mrb_value MRubyBinding::") || (line.include? "MRUBY_FUNCTION_HEADER"))
    bind = line.gsub("mrb_value MRubyBinding::","").gsub("(mrb_state *mrb,mrb_value self)","").gsub("}","").gsub("{","").gsub("MRUBY_FUNCTION_HEADER(","").gsub(")","")
    headers.push("  static mrb_value "+bind.strip+"(mrb_state *mrb,mrb_value self);\n")
    installs.push("  InstallFunction("+bind.strip+",\"cpp_"+bind.strip+"\");\n")
  end
end

 bind_header_new = bind_header.gsub(/\/\/Binds.*\/\/Binds/m,"//Binds\n"+headers.join+"  //Binds")
 bind_cpp_new = binds_cpp.gsub(/\/\/Binds.*\/\/Binds/m,"//Binds\n"+installs.join+"  //Binds")


 if(binds_cpp != bind_cpp_new) 
  File.write(binds_cpp_path,bind_cpp_new)
  File.write(binds_h_path,bind_header_new)
 end
