@REM Build for Visual Studio compiler. Run your copy of vcvars32.bat or vcvarsall.bat to setup command-line compiler.
@set OUT_EXE=external
@set INCLUDES=/Ivendor/enet/include /Ivendor/imgui /Ivendor/lua /I"%DXSDK_DIR%/Include"
@set SOURCES=src/*.cpp src/misc/*.cpp src/wrapper/*.cpp vendor/enet/*c vendor/imgui/*.cpp vendor/lua/*.c
@set LIBS=/LIBPATH:"%DXSDK_DIR%/Lib/x86" d3d9.lib winmm.lib ws2_32.lib
mkdir Release
mkdir obj

cl /std:c++17 /GS /GL /analyze- /W3 /Gy /Zc:wchar_t /Zi /Gm- /O2 /Zc:inline /fp:precise /D UNICODE /D _UNICODE /WX- /Zc:forScope /Gd /Oy- /Oi /EHsc /nologo /Foobj/ /FeRelease/%OUT_EXE%.exe %SOURCES% %INCLUDES% /link %LIBS%
