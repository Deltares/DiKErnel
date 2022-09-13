# Navigate to DiKErnel folder
cd ..\DiKErnel

# CMake configure
start-process C:\msys64\mingw64.exe -ArgumentList "cmake -G 'MinGW Makefiles' -Wno-dev -S . -B ./../Development/MinGW/" -Wait

# Navigate to MinGW folder
cd ..\Development\MinGW

# CMake build
start-process C:\msys64\mingw64.exe -ArgumentList "cmake --build ." -Wait