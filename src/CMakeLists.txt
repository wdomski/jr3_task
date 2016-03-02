
#
# Components, types and plugins.
#
# The CMake 'target' names are identical to the first argument of the
# macros below, except for orocos_typegen_headers, where the target is fully
# controlled by generated code of 'typegen'.
#

# Creates a component library libjr3_task-<target>.so
# and installs in the directory lib/orocos/jr3_task/
#
orocos_component(jr3_task jr3_task-component.hpp jr3_task-component.cpp) # ...you may add multiple source files
#
# You may add multiple orocos_component statements.

#
# Additional headers:
#
# Installs in the include/orocos/jr3_task/ directory
#
orocos_install_headers(jr3_task-component.hpp) # ...you may add multiple header files
#
# You may add multiple orocos_install_headers statements.

