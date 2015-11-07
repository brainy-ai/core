require 'mkmf'
extension_name = 'neural'

swig_cmd = find_executable 'swig'
current_path = File.expand_path('../', __FILE__)

puts 'Creating C wrap'

%x{#{swig_cmd} -c++ -ruby #{current_path}/brainy_neural.i }
%x{#{swig_cmd} -c++ -ruby #{current_path}/brainy_util.i }

# have_header('brainy.h')
find_library('brainy', nil)

dir_config(extension_name)
create_makefile('neural/neural')
