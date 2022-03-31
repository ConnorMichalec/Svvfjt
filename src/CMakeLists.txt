add_executable (main main.cc renderer.cc displayElements.cc process.cc audioSynthesis.cc userin.cc)

find_library(SDL2 NAMES sdl2 libSDL2)
find_library(SDL2_image NAMES libSDL2_image)
find_library(stk NAMES libstk)


target_link_libraries(main SDL2 stk)
