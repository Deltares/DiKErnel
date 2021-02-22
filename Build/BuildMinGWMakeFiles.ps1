# Move to DiKErnel folder
cd ..\DiKErnel

# CMake configure
start-process C:\msys64\mingw64.exe -ArgumentList "cmake -G 'MinGW Makefiles' --config Release . -Wno-dv -B ..\Development\MinGW\" -NoNewWindow -Wait

# Move to MinGW folder
cd ..\Development\MinGW

#CMake build
start-process C:\msys64\mingw64.exe -ArgumentList "cmake --build . --config Release" -NoNewWindow -Wait