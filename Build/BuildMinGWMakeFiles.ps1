# Navigate to DiKErnel folder
cd ..\DiKErnel

# CMake configure
start-process C:\msys64\mingw64.exe -ArgumentList "cmake -G 'MinGW Makefiles' -DBUILD_WITH_TESTS:BOOL=ON --config Release . -Wno-dv -B ..\Development\MinGW\" -NoNewWindow -Wait

# Navigate to MinGW folder
cd ..\Development\MinGW

# CMake build
start-process C:\msys64\mingw64.exe -ArgumentList "cmake --build . --config Release" -NoNewWindow -Wait