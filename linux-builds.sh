echo Starting building section

if [ -d "./GLFW" ]; then
  echo Building GLFW
  
  cd ./GLFW
  cmake -S . -B ./cmake-build-debug -G Ninja
  cmake --build ./cmake-build-debug

  if [ $1 = "--run" ]; then
    cd ../bin/
    ./ekg_glfw_demo
    cd ../
  fi
fi

echo End of building section
echo Bye ;3