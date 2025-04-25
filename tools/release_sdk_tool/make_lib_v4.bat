set tool_path_make_lib="%~1"\RDS\V5.3.x\toolchains\nds32le-elf-mculib-v5f\bin
set lib_obj_name_release=libdriver_d25f%~6.a
set chip_type=%~4
set rm_file_flag=%~5

goto :MAIN_MAKE_LIB

:MAIN_MAKE_LIB
set lib_obj_name_normal=libdriver_d25f.a
set file_path=%~2\project\tlsr_riscv\%~4\%~3\drivers\lib\src
set lib_obj_name=lib%~4%~6.a
set lib_save_path=%~2\chip\%~4\drivers\lib
set lib_release_path=%~dp0..\release_lib\%~4

if not exist %lib_release_path% (
    mkdir %lib_release_path%
)

cd /d %~dp0
call read_cfg .\config\cfg.ini %~4 lib
call :PROCESS_MAKE_LIB

REM REM make lib for B91
REM set file_path=%~2\project\tlsr_riscv\B91\%~3\drivers\lib\src
REM set lib_obj_name=libB91.a
REM set lib_save_path=%~2\chip\B91\drivers\lib
REM cd /d %~dp0
REM call read_cfg .\config\cfg.ini B91 lib
REM call :PROCESS_MAKE_LIB

REM REM make lib for B92
REM set file_path=%~2\project\tlsr_riscv\B92\%~3\drivers\lib\src
REM set lib_obj_name=libB92.a
REM set lib_save_path=%~2\chip\B92\drivers\lib
REM cd /d %~dp0
REM call read_cfg .\config\cfg.ini B92 lib
REM call :PROCESS_MAKE_LIB

goto :END


:PROCESS_MAKE_LIB

REM delete exist lib file
if exist %lib_release_path%\%lib_obj_name_release% (
del /s /q /f %lib_release_path%\%lib_obj_name_release%
)

@REM set mk_lib_temp= 
setlocal EnableDelayedExpansion
for /f %%i in (.\~cfgTmp.txt) do (
@REM set mk_lib_temp=!mk_lib_temp!%file_path%\%%i.o 
call %~dp0.\show_info "lib: %file_path%\%lib_obj_name% %file_path%\%%i.o"
@REM copy "%file_path%\%%i.o" ".\%%i.o"
copy "%file_path%\%%i.o" ".\%%~nxi.o"
%tool_path_make_lib%\riscv32-elf-gcc-ar -crs %file_path%\%lib_obj_name% "%%~nxi.o"
del "%%~nxi.o"
)

@REM echo !mk_lib_temp!
@REM echo %file_path%\%lib_obj_name%
@REM %tool_path_make_lib%\riscv32-elf-gcc-ar -crs %file_path%\%lib_obj_name% !mk_lib_temp!
if exist %file_path%\%lib_obj_name% (
call %~dp0.\show_info "Make %lib_obj_name% successfully." 
copy %file_path%\%lib_obj_name% %lib_save_path%\%lib_obj_name_normal%
copy %file_path%\%lib_obj_name% %lib_release_path%\%lib_obj_name_release%
call %~dp0.\show_info "rm src file:%lib_save_path%\src"
@REM rd /s /q %lib_save_path%\src
) else (
call %~dp0.\show_info "Make %lib_obj_name% Failed." 
pause
)

if %rm_file_flag% == 1 (

if exist %lib_release_path%\%lib_obj_name_release% (
REM for /f %%i in (%~dp0.\~cfgTmp.txt) do (
REM if exist %lib_save_path%\src\%%i.c del /s /q /f %lib_save_path%\src\%%i.c
REM )
@REM if exist %lib_save_path%\src rd /s /q %lib_save_path%\src
)

)
cd /d %~dp0
setlocal DisableDelayedExpansion
goto :END


:END



