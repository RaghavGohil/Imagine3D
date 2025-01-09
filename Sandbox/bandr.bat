pushd build
cmake --build . --clean-first
pushd debug
Game.exe
popd
popd