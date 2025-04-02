project('test_ui', 'cpp')

# ftxui-screen, ftxui-dom, ftxui-component

ftxui = subproject('ftxui')
ftxui_screen = ftxui.get_variable('screen_dep')
ftxui_dom = ftxui.get_variable('dom_dep')
ftxui_component = ftxui.get_variable('component_dep')

gtest = subproject('gtest')
gtest_dep = gtest.get_variable('gtest_main_dep')


sources = files(
  'src/TestFinder.cpp'
)

include_dirs = include_directories([
  'include'
])

deps = [ftxui_screen, ftxui_dom, ftxui_component ]

main_lib = shared_library(
  'main_lib',
  sources: sources,
  dependencies: [deps],
  include_directories: include_dirs,
  install: true
)

executable('testu',
  sources: ['main.cpp', sources],
  dependencies: deps,
  include_directories: include_dirs
)


############### TESTING ########################


##### TEST FILES
test_src = files(
  'test/test.cpp'
)

##### TEST EXECUTABLE
executable('test_ex',
  sources: test_src,
  dependencies: [gtest_dep, deps],
  include_directories: include_dirs,
  link_with: main_lib
)
