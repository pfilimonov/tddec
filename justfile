clean:
  rm -rf build

build:
  cmake -B build -S . 
  cmake --build build
  ln -sf build/compile_commands.json compile_commands.json

run *args:
  ./build/{{args}}
