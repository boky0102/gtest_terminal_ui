project('test_ui', 'cpp', default_options: ['cpp_std=c++23'])

# ftxui-screen, ftxui-dom, ftxui-component

ftxui = subproject('ftxui')
ftxui_screen = ftxui.get_variable('screen_dep')
ftxui_dom = ftxui.get_variable('dom_dep')
ftxui_component = ftxui.get_variable('component_dep')

gtest = subproject('gtest')
gtest_dep = gtest.get_variable('gtest_main_dep')
gmock_dep = gtest.get_variable('gmock_main_dep')


sources = files(
  'src/TestFinder.cpp',
  'src/Logger.cpp',
  'src/Renderer.cpp',
  'components/TestItem.cpp'
)

include_dirs = include_directories([
  'include',
  'components/include'
])

deps = [ftxui_screen, ftxui_dom, ftxui_component ]

main_lib = shared_library(
  'main_lib',
  sources: sources,
  dependencies: [deps],
  include_directories: include_dirs,
  override_options: ['cpp_std=c++23'],
  install: true
)

executable('testu',
  sources: ['main.cpp', sources],
  dependencies: deps,
  include_directories: include_dirs,
  override_options: ['cpp_std=c++23'],
)


############### TESTING ########################


##### TEST FILES
test_src = files(
  'test/test.cpp',
  'test/TestDom.cpp',
  'test/TestTestFinder.cpp'
)

##### TEST EXECUTABLE
executable('test_ex',
  sources: test_src,
  dependencies: [gtest_dep, gmock_dep, deps],
  include_directories: [include_dirs, 'test/Mocks'],
  link_with: main_lib,
  override_options: ['cpp_std=c++23']
)

##### FAKE TEST EXES
executable('TestFake1', 'test/FakeTestDir/TestFake1.cpp', dependencies: [gtest_dep])
executable('TestFake2', 'test/FakeTestDir/TestFake2.cpp', dependencies: [gtest_dep])
executable('TestFake3', 'test/FakeTestDir/TestFake3.cpp', dependencies: [gtest_dep])
