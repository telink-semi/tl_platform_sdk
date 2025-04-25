set tool_path_make_lib="%~1"\RDS\V3.2.3\toolchains\nds32le-elf-mculib-v5f\bin
set lib_obj_name_release=libdriver%~6.a
set chip_type=%~4
set rm_file_flag=%~5

goto :MAIN_MAKE_LIB

:MAIN_MAKE_LIB
set lib_obj_name_normal=libdriver.a
set file_path=%~2\project\tlsr_riscv\%~4\%~3\drivers\lib\src
set lib_obj_name=lib%~4%~6.a
set lib_save_path=%~2\chip\%~4\drivers\lib
set lib_release_path=%~dp0..\release_lib\%~4
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
set mk_lib_temp= 
setlocal EnableDelayedExpansion
for /f %%i in (.\~cfgTmp.txt) do (
set mk_lib_temp=!mk_lib_temp!%file_path%\%%i.o 
)
REM delete exist lib file
if exist %lib_release_path%\%lib_obj_name_release% (
del /s /q /f %lib_release_path%\%lib_obj_name_release%
)

REM echo !mk_lib_temp!
%tool_path_make_lib%\riscv32-elf-ar -crs %file_path%\%lib_obj_name% !mk_lib_temp!
if exist %file_path%\%lib_obj_name% (
call %~dp0.\show_info "Make %lib_obj_name% successfully." 
copy %file_path%\%lib_obj_name% %lib_save_path%\%lib_obj_name_normal%
copy %file_path%\%lib_obj_name% %lib_release_path%\%lib_obj_name_release%
) else (
call %~dp0.\show_info "Make %lib_obj_name% Failed." 
)

if %rm_file_flag% == 1 (

if exist %lib_release_path%\%lib_obj_name_release% (
REM for /f %%i in (%~dp0.\~cfgTmp.txt) do (
REM if exist %lib_save_path%\src\%%i.c del /s /q /f %lib_save_path%\src\%%i.c
REM )
)
if exist %lib_save_path%\src rd /s /q %lib_save_path%\src
)
cd /d %~dp0
setlocal DisableDelayedExpansion
goto :END


:END



