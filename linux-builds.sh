echo Starting building section

if [ -d "./GLFW" ]; then
  echo Building GLFW
  
  cd ./GLFW
  rm -r ./cmake-build-debug

  cmake -S . -B ./cmake-build-debug -G Ninja
  cmake --build ./cmake-build-debug

  if [ $1 = "--run" ]; then
    cd ../bin/
    ./ekg_glfw_demo
    cd ../
  fi
fi

if [ -d "./SDL" ]; then
  echo Building SDL

  cd ./SDL
  rm -r ./cmake-build-debug

  cmake -S . -B ./cmake-build-debug -G Ninja
  cmake --build ./cmake-build-debug

  if [ $1 = "--run" ]; then
    cd ../bin/
    ./ekg_sdl_demo
    cd ../
  fi
fi

echo End of building section
echo Bye ;3