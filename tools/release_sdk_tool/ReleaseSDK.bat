@echo off

REM ##################################################################################################################
REM ################################[Instructions for use]############################################################
REM STEP1: Modify ide_tool_path_release_sdk to the installation path of RSIC-V IDE, be careful not to have spaces in the path.
REM STEP2: Modify release_B8x_flag, if you want to release the corresponding SDK, set it to 1, otherwise set it to 0.
REM STEP3: Modify exc_xxxxx_flag as required, where "mklib" is the compilation library, "rmopt" is the deletion of the 
REM        compilation option, "rmlnk" is the deletion of the file link in the project, "rmfile" is the deletion of the
REM        file, and "tstcmp" is the test compilation. Set to 1 to execute the item, otherwise not execute.
REM STEP4: Modify config/cfg.ini, rm_options is the compile option to be deleted, rm_links is the link of the file to 
REM        be deleted, rm_files is the file to be deleted, lib is the name of the file to be compiled into the library.
REM STEP5: Double click this file to run.
REM ##################################################################################################################

set ide_tool_path_v2="C:\TelinkIoTStudio"
REM set ide_tool_path_v1="D:\Andestech\AndeSight_RDS_v323"
set Project_Path_Rlease_SDK=%~dp0..\..\
set make_lib_compile_option=UART_Demo
set make_lib_compile_option_n22=N22_STIMER_Demo


set release_B91_flag=1
set release_B92_flag=1
set release_TL7518_flag=0
set release_TL751X_flag=1
set release_TL721X_flag=1
set release_TL321X_flag=1
set release_W92_flag=0

set exc_mklib_flag=1
set exc_rmopt_flag=1
REM set exc_rmlnk_flag=0
REM set exc_rmfile_flag=0
REM set exc_rmcode_flag=1
set exc_clr_prj=1
set exc_tstcmp_flag=1


set exc_tstcmp_single_flag=0
set single_compile_option=UART_Demo

set Project_Path_B91=%Project_Path_Rlease_SDK%\project\tlsr_riscv\B91
set Project_Path_B92=%Project_Path_Rlease_SDK%\project\tlsr_riscv\B92
set Project_Path_TL7518=%Project_Path_Rlease_SDK%\project\tlsr_riscv\TL7518
set Project_Path_TL751X=%Project_Path_Rlease_SDK%\project\tlsr_riscv\tl751x
set Project_Path_TL721X=%Project_Path_Rlease_SDK%\project\tlsr_riscv\TL721X
set Project_Path_TL321X=%Project_Path_Rlease_SDK%\project\tlsr_riscv\TL321X
set Project_Path_W92=%Project_Path_Rlease_SDK%\project\tlsr_riscv\W92

REM If you need to customize the B80 chip, please set the following parameters, 0: S0, 1: S1, 2: S2, 3: S3, 4:s4
set B91_SDK_VERSION=0

goto :MAIN


:TEST_COMPILE
if %release_B91_flag% == 1 (
call :REMOVE_TEMP_FILE
call %~dp0.\show_info "Compile Test B91" 1
set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_B91%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_B91
call :COMPILE_PROCESS_V2
call %~dp0.\show_info "Compile Test B91 Completed!" 4
)

if %release_B92_flag% == 1 (
call :REMOVE_TEMP_FILE
call %~dp0.\show_info "Compile Test B92" 1
set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_B92%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_B92
call :COMPILE_PROCESS_V2
call %~dp0.\show_info "Compile Test B92 Completed!" 4
)

if %release_TL7518_flag% == 1 (
call :REMOVE_TEMP_FILE
call %~dp0.\show_info "Compile Test TL7518" 1
set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_TL7518%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_7518
call :COMPILE_PROCESS_V2
call %~dp0.\show_info "Compile Test TL7518 Completed!" 4
)

if %release_TL751X_flag% == 1 (
call :REMOVE_TEMP_FILE
call %~dp0.\show_info "Compile Test tl751x" 1
set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_TL751X%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_751X
call :COMPILE_PROCESS_V2
call %~dp0.\show_info "Compile Test tl751x Completed!" 4
)

if %release_TL721X_flag% == 1 (
call :REMOVE_TEMP_FILE
call %~dp0.\show_info "Compile Test TL721X" 1
set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_TL721X%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_721X
call :COMPILE_PROCESS_V2
call %~dp0.\show_info "Compile Test TL721X Completed!" 4
)

if %release_TL321X_flag% == 1 (
call :REMOVE_TEMP_FILE
call %~dp0.\show_info "Compile Test TL321X" 1
set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_TL321X%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_321X
call :COMPILE_PROCESS_V2
call %~dp0.\show_info "Compile Test TL321X Completed!" 4
)

if %release_W92_flag% == 1 (
call :REMOVE_TEMP_FILE
call %~dp0.\show_info "Compile Test W92" 1
set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_W92%
set Test_Compile_CompileOption=W92_Driver_Demo
call :COMPILE_PROCESS_V2
call %~dp0.\show_info "Compile Test W92 Completed!" 4
)

goto :END

:TEST_COMPILE_SINGLE
set compile_option=%single_compile_option%
set Project_Path_Compile=%Project_Path_B91%
set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_B91

if %release_B91_flag% == 1 (
call %~dp0.\show_info "Single Compile Test B91" 1
call %~dp0.\show_info "Compile %compile_option%." 3
call compile_v2 %ide_tool_path_release_sdk% %Project_Path_Compile% %Test_Compile_CompileOption% %compile_option%
if exist %Project_Path_Compile%\%compile_option%\*.bin (
call %~dp0.\show_info "PASS" 2
) else (
call %~dp0.\show_info "FAIL" 2
pause
)
if exist %Project_Path_Compile%\%compile_option% (rmdir /s /q %Project_Path_Compile%\%compile_option%)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_B92%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_B92

if %release_B92_flag% == 1 (
call %~dp0.\show_info "Single Compile Test B92" 1
call %~dp0.\show_info "Compile %compile_option%." 3
call compile_v2 %ide_tool_path_release_sdk% %Project_Path_Compile% %Test_Compile_CompileOption% %compile_option%
if exist %Project_Path_Compile%\%compile_option%\*.bin (
call %~dp0.\show_info "PASS" 2
) else (
call %~dp0.\show_info "FAIL" 2
pause
)
if exist %Project_Path_Compile%\%compile_option% (rmdir /s /q %Project_Path_Compile%\%compile_option%)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_TL7518%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_7518

if %release_TL7518_flag% == 1 (
call %~dp0.\show_info "Single Compile Test TL7518" 1
call %~dp0.\show_info "Compile %compile_option%." 3
call compile_v2 %ide_tool_path_release_sdk% %Project_Path_Compile% %Test_Compile_CompileOption% %compile_option%
if exist %Project_Path_Compile%\%compile_option%\*.bin (
call %~dp0.\show_info "PASS" 2
) else (
call %~dp0.\show_info "FAIL" 2
pause
)
if exist %Project_Path_Compile%\%compile_option% (rmdir /s /q %Project_Path_Compile%\%compile_option%)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_TL751X%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_751X

if %release_TL751X_flag% == 1 (
call %~dp0.\show_info "Single Compile Test tl751x" 1
call %~dp0.\show_info "Compile %compile_option%." 3
call compile_v2 %ide_tool_path_release_sdk% %Project_Path_Compile% %Test_Compile_CompileOption% %compile_option%
if exist %Project_Path_Compile%\%compile_option%\*.bin (
call %~dp0.\show_info "PASS" 2
) else (
call %~dp0.\show_info "FAIL" 2
pause
)
if exist %Project_Path_Compile%\%compile_option% (rmdir /s /q %Project_Path_Compile%\%compile_option%)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_TL721X%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_721X

if %release_TL721X_flag% == 1 (
call %~dp0.\show_info "Single Compile Test TL721X" 1
call %~dp0.\show_info "Compile %compile_option%." 3
call compile_v2 %ide_tool_path_release_sdk% %Project_Path_Compile% %Test_Compile_CompileOption% %compile_option%
if exist %Project_Path_Compile%\%compile_option%\*.bin (
call %~dp0.\show_info "PASS" 2
) else (
call %~dp0.\show_info "FAIL" 2
pause
)
if exist %Project_Path_Compile%\%compile_option% (rmdir /s /q %Project_Path_Compile%\%compile_option%)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_TL321X%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_321X

if %release_TL321X_flag% == 1 (
call %~dp0.\show_info "Single Compile Test TL321X" 1
call %~dp0.\show_info "Compile %compile_option%." 3
call compile_v2 %ide_tool_path_release_sdk% %Project_Path_Compile% %Test_Compile_CompileOption% %compile_option%
if exist %Project_Path_Compile%\%compile_option%\*.bin (
call %~dp0.\show_info "PASS" 2
) else (
call %~dp0.\show_info "FAIL" 2
pause
)
if exist %Project_Path_Compile%\%compile_option% (rmdir /s /q %Project_Path_Compile%\%compile_option%)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_Compile=%Project_Path_W92%
set Test_Compile_CompileOption=W92_Driver_Demo

if %release_W92_flag% == 1 (
call %~dp0.\show_info "Single Compile Test W92" 1
call %~dp0.\show_info "Compile %compile_option%." 3
call compile_v2 %ide_tool_path_release_sdk% %Project_Path_Compile% %Test_Compile_CompileOption% %compile_option%
if exist %Project_Path_Compile%\%compile_option%\*.bin (
call %~dp0.\show_info "PASS" 2
) else (
call %~dp0.\show_info "FAIL" 2
pause
)
if exist %Project_Path_Compile%\%compile_option% (rmdir /s /q %Project_Path_Compile%\%compile_option%)
)

goto :END

REM :COMPILE_PROCESS_V1
REM call :REMOVE_TEMP_FILE
REM call %~dp0.\tool rd_options %Project_Path_Compile% .cproject %~dp0.\~cfgTmp.txt
REM for /f %%i in (%~dp0.\~cfgTmp.txt) do (
REM call %~dp0.\show_info "Compile %%i." 3
REM if exist %Project_Path_Compile%\%%i (rmdir /s /q %Project_Path_Compile%\%%i)
REM call compile_v1 %ide_tool_path_release_sdk% %Project_Path_Compile% %Test_Compile_CompileOption% %%i
REM if exist %Project_Path_Compile%\%%i\output\*.bin (
REM call %~dp0.\show_info "PASS" 2
REM ) else (
REM call %~dp0.\show_info "FAIL" 2
REM pause
REM )
REM if exist %Project_Path_Compile%\%%i (rmdir /s /q %Project_Path_Compile%\%%i)
REM )
REM goto :END

:COMPILE_PROCESS_V2
call :REMOVE_TEMP_FILE
call %~dp0.\tool rd_options %Project_Path_Compile% .cproject %~dp0.\~cfgTmp.txt
for /f %%i in (%~dp0.\~cfgTmp.txt) do (
call %~dp0.\show_info "Compile %%i." 3
if exist %Project_Path_Compile%\%%i (rmdir /s /q %Project_Path_Compile%\%%i)
call compile_v2 %ide_tool_path_release_sdk% %Project_Path_Compile% %Test_Compile_CompileOption% %%i
if exist %Project_Path_Compile%\%%i\*.bin (
call %~dp0.\show_info "PASS" 2
) else (
call %~dp0.\show_info "FAIL" 2
pause
)
if exist %Project_Path_Compile%\%%i (rmdir /s /q %Project_Path_Compile%\%%i)
)
goto :END

:MAKE_LIB
call %~dp0.\show_info "Make library" 1
if %release_B91_flag% == 1 (
REM copy %~dp0.\config\libB91.a %Project_Path_Rlease_SDK%\chip\B91\drivers\lib\libdriver.a
)
if %release_B92_flag% == 1 (
REM copy %~dp0.\config\libB92.a %Project_Path_Rlease_SDK%\chip\B92\drivers\lib\libdriver.a
)
if %release_TL7518_flag% == 1 (
REM copy %~dp0.\config\libTL7518.a %Project_Path_Rlease_SDK%\chip\TL7518\drivers\lib\libdriver.a
)
if %release_TL751X_flag% == 1 (
REM copy %~dp0.\config\libTL751X.a %Project_Path_Rlease_SDK%\chip\tl751x\drivers\lib\libdriver.a
)
if %release_TL721X_flag% == 1 (
REM copy %~dp0.\config\libTL721X.a %Project_Path_Rlease_SDK%\chip\TL721X\drivers\lib\libdriver.a
)
if %release_TL321X_flag% == 1 (
REM copy %~dp0.\config\libTL321X.a %Project_Path_Rlease_SDK%\chip\TL321X\drivers\lib\libdriver.a
)
if %release_W92_flag% == 1 (
REM copy %~dp0.\config\libW92.a %Project_Path_Rlease_SDK%\chip\W92\drivers\lib\libdriver.a
)
set build_prj_Rlease_SDK=%make_lib_compile_option%
set build_prj_Rlease_SDK_N22=%make_lib_compile_option_n22%

set Project_Path_MakeLib_Complie=%Project_Path_B91%
set ide_tool_path_release_sdk=%ide_tool_path_v2%
set MakeLib_CompileOption=TL_PLATFORM_SDK_B91
if %release_B91_flag% == 1 (
REM B91 S2
@REM call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\chip\B91\drivers\lib\src\sys.c SDK_VERSION_SELECT SDK_VERSION_S2
call %~dp0.\show_info "Compile B91 %build_prj_Rlease_SDK%." 3

call %~dp0.\tool st_node %Project_Path_B91%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:max:none
call %~dp0.\compile_v2 %ide_tool_path_release_sdk% %Project_Path_MakeLib_Complie% %MakeLib_CompileOption% %build_prj_Rlease_SDK%
call %~dp0.\tool st_node %Project_Path_B91%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:none:max

if exist %Project_Path_MakeLib_Complie%\%build_prj_Rlease_SDK%\*.bin (
call %~dp0.\show_info "PASS" 2
call %~dp0.\show_info "Generate libdriver_s2.a" 3
call %~dp0.\make_lib_v1 %ide_tool_path_release_sdk% %Project_Path_Rlease_SDK% %build_prj_Rlease_SDK% B91 1 _s2
) else (
goto :MAKE_LIB_ERROR
)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_MakeLib_Complie=%Project_Path_B92%
set MakeLib_CompileOption=TL_PLATFORM_SDK_B92
if %release_B92_flag% == 1 (
@REM call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\chip\B92\drivers\lib\src\sys.c SDK_VERSION_SELECT SDK_VERSION_DRIVER
call %~dp0.\show_info "Compile B92 %build_prj_Rlease_SDK%." 3

call %~dp0.\tool st_node %Project_Path_B92%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:max:none
call %~dp0.\compile_v2 %ide_tool_path_release_sdk% %Project_Path_MakeLib_Complie% %MakeLib_CompileOption% %build_prj_Rlease_SDK%
call %~dp0.\tool st_node %Project_Path_B92%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:none:max

if exist %Project_Path_MakeLib_Complie%\%build_prj_Rlease_SDK%\*.bin (
call %~dp0.\show_info "PASS" 2
call %~dp0.\make_lib_v2 %ide_tool_path_release_sdk% %Project_Path_Rlease_SDK% %build_prj_Rlease_SDK% B92 1
) else (
goto :MAKE_LIB_ERROR
)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_MakeLib_Complie=%Project_Path_TL7518%
set MakeLib_CompileOption=TL7518_Driver_Demo
if %release_TL7518_flag% == 1 (
@REM call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\chip\TL7518\drivers\lib\src\sys.c SDK_VERSION_SELECT SDK_VERSION_DRIVER
call %~dp0.\show_info "Compile TL7518 %build_prj_Rlease_SDK%." 3

call %~dp0.\tool st_node %Project_Path_TL7518%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:max:none
call %~dp0.\compile_v2 %ide_tool_path_release_sdk% %Project_Path_MakeLib_Complie% %MakeLib_CompileOption% %build_prj_Rlease_SDK%
call %~dp0.\tool st_node %Project_Path_TL7518%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:none:max

if exist %Project_Path_MakeLib_Complie%\%build_prj_Rlease_SDK%\*.bin (
call %~dp0.\show_info "PASS" 2
call %~dp0.\make_lib_v2 %ide_tool_path_release_sdk% %Project_Path_Rlease_SDK% %build_prj_Rlease_SDK% TL7518 1
) else (
goto :MAKE_LIB_ERROR
)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_MakeLib_Complie=%Project_Path_TL751X%
set MakeLib_CompileOption=TL_PLATFORM_SDK_751X
if %release_TL751X_flag% == 1 (
@REM call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\chip\tl751x\drivers\lib\src\sys.c SDK_VERSION_SELECT SDK_VERSION_DRIVER
REM set to EMI_DEMO
call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\chip\tl751x\drivers\lib\include\pm\pm.h PM_FUNCTION_SUPPORT 0  
call %~dp0.\show_info "Compile tl751x %build_prj_Rlease_SDK%." 3

call %~dp0.\tool st_node %Project_Path_TL751X%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:max:none
call %~dp0.\compile_v2 %ide_tool_path_release_sdk% %Project_Path_MakeLib_Complie% %MakeLib_CompileOption% %build_prj_Rlease_SDK%
call %~dp0.\tool st_node %Project_Path_TL751X%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:none:max

if exist %Project_Path_MakeLib_Complie%\%build_prj_Rlease_SDK%\*.bin (
call %~dp0.\show_info "PASS" 2
call %~dp0.\make_lib_v4 %ide_tool_path_release_sdk% %Project_Path_Rlease_SDK% %build_prj_Rlease_SDK% tl751x 1
) else (
goto :MAKE_LIB_ERROR
)

call %~dp0.\show_info "Compile tl751x %build_prj_Rlease_SDK_N22%." 3
call :REMOVE_TEMP_FILE
call %~dp0.\tool st_node %Project_Path_TL751X%\.cproject %~dp0config\cfg.ini Debug_Level %build_prj_Rlease_SDK_N22%:max:none
call %~dp0.\compile_v2 %ide_tool_path_release_sdk% %Project_Path_MakeLib_Complie% %MakeLib_CompileOption% %build_prj_Rlease_SDK_N22%
call %~dp0.\tool st_node %Project_Path_TL751X%\.cproject %~dp0config\cfg.ini Debug_Level %build_prj_Rlease_SDK_N22%:none:max

if exist %Project_Path_MakeLib_Complie%\%build_prj_Rlease_SDK_N22%\*.bin (
call %~dp0.\show_info "PASS" 2
call %~dp0.\make_lib_v5 %ide_tool_path_release_sdk% %Project_Path_Rlease_SDK% %build_prj_Rlease_SDK_N22% tl751x 1
) else (
goto :MAKE_LIB_ERROR
)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_MakeLib_Complie=%Project_Path_TL721X%
set MakeLib_CompileOption=TL_PLATFORM_SDK_721X
if %release_TL721X_flag% == 1 (
@REM call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\chip\TL721X\drivers\lib\src\sys.c SDK_VERSION_SELECT SDK_VERSION_DRIVER
call %~dp0.\show_info "Compile TL721X %build_prj_Rlease_SDK%." 3

call %~dp0.\tool st_node %Project_Path_TL721X%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:max:none
call %~dp0.\compile_v2 %ide_tool_path_release_sdk% %Project_Path_MakeLib_Complie% %MakeLib_CompileOption% %build_prj_Rlease_SDK%
call %~dp0.\tool st_node %Project_Path_TL721X%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:none:max

if exist %Project_Path_MakeLib_Complie%\%build_prj_Rlease_SDK%\*.bin (
call %~dp0.\show_info "PASS" 2
call %~dp0.\make_lib_v2 %ide_tool_path_release_sdk% %Project_Path_Rlease_SDK% %build_prj_Rlease_SDK% TL721X 1
) else (
goto :MAKE_LIB_ERROR
)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_MakeLib_Complie=%Project_Path_TL321X%
set MakeLib_CompileOption=TL_PLATFORM_SDK_321X
if %release_TL321X_flag% == 1 (
@REM call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\chip\TL321X\drivers\lib\src\sys.c SDK_VERSION_SELECT SDK_VERSION_DRIVER
call %~dp0.\show_info "Compile TL321X %build_prj_Rlease_SDK%." 3

call %~dp0.\tool st_node %Project_Path_TL321X%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:max:none
call %~dp0.\compile_v2 %ide_tool_path_release_sdk% %Project_Path_MakeLib_Complie% %MakeLib_CompileOption% %build_prj_Rlease_SDK%
call %~dp0.\tool st_node %Project_Path_TL321X%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:none:max

if exist %Project_Path_MakeLib_Complie%\%build_prj_Rlease_SDK%\*.bin (
call %~dp0.\show_info "PASS" 2
call %~dp0.\make_lib_v3 %ide_tool_path_release_sdk% %Project_Path_Rlease_SDK% %build_prj_Rlease_SDK% TL321X 1
) else (
goto :MAKE_LIB_ERROR
)
)

set ide_tool_path_release_sdk=%ide_tool_path_v2%
set Project_Path_MakeLib_Complie=%Project_Path_W92%
set MakeLib_CompileOption=W92_Driver_Demo
if %release_W92_flag% == 1 (
@REM call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\chip\W92\drivers\lib\src\sys.c SDK_VERSION_SELECT SDK_VERSION_DRIVER
call %~dp0.\show_info "Compile W92 %build_prj_Rlease_SDK%." 3

call %~dp0.\tool st_node %Project_Path_W92%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:max:none
call %~dp0.\compile_v2 %ide_tool_path_release_sdk% %Project_Path_MakeLib_Complie% %MakeLib_CompileOption% %build_prj_Rlease_SDK%
call %~dp0.\tool st_node %Project_Path_W92%\.cproject %~dp0config\cfg.ini Debug_Level %make_lib_compile_option%:none:max

if exist %Project_Path_MakeLib_Complie%\%build_prj_Rlease_SDK%\*.bin (
call %~dp0.\show_info "PASS" 2
call %~dp0.\make_lib_v2 %ide_tool_path_release_sdk% %Project_Path_Rlease_SDK% %build_prj_Rlease_SDK% W92 1
) else (
goto :MAKE_LIB_ERROR
)
)

call %~dp0.\show_info "Make library Completed!" 4
goto :END

:MAKE_LIB_ERROR
call %~dp0.\show_info "FAIL" 2
call %~dp0.\show_info "Make library Failed!" 4
pause
exit
goto :END


:REMOVE_COMPILE_OPTIONS

call %~dp0.\show_info "Remove Compile Options" 1

if %release_B91_flag% == 1 (
call %~dp0.\show_info "Remove B91 Compile Options" 3
call %~dp0.\tool rm_options %Project_Path_B91% %~dp0.\config\cfg.ini B91 .\.cproject
call %~dp0.\show_info "Remove B91 Compile Options Completed!" 4
)

if %release_B92_flag% == 1 (
call %~dp0.\show_info "Remove B92 Compile Options" 3
call %~dp0.\tool rm_options %Project_Path_B92% %~dp0.\config\cfg.ini B92 .\.cproject
call %~dp0.\show_info "Remove B92 Compile Options Completed!" 4
)

if %release_TL7518_flag% == 1 (
call %~dp0.\show_info "Remove TL7518 Compile Options" 3
call %~dp0.\tool rm_options %Project_Path_TL7518% %~dp0.\config\cfg.ini TL7518 .\.cproject
call %~dp0.\show_info "Remove TL7518 Compile Options Completed!" 4
)

if %release_TL751X_flag% == 1 (
call %~dp0.\show_info "Remove tl751x Compile Options" 3
call %~dp0.\tool rm_options %Project_Path_TL751X% %~dp0.\config\cfg.ini tl751x .\.cproject
call %~dp0.\show_info "Remove tl751x Compile Options Completed!" 4
)

if %release_TL721X_flag% == 1 (
call %~dp0.\show_info "Remove TL721X Compile Options" 3
call %~dp0.\tool rm_options %Project_Path_TL721X% %~dp0.\config\cfg.ini TL721X .\.cproject
call %~dp0.\show_info "Remove TL721X Compile Options Completed!" 4
)

if %release_TL321X_flag% == 1 (
call %~dp0.\show_info "Remove TL321X Compile Options" 3
call %~dp0.\tool rm_options %Project_Path_TL321X% %~dp0.\config\cfg.ini TL321X .\.cproject
call %~dp0.\show_info "Remove TL321X Compile Options Completed!" 4
)

if %release_W92_flag% == 1 (
call %~dp0.\show_info "Remove W92 Compile Options" 3
call %~dp0.\tool rm_options %Project_Path_W92% %~dp0.\config\cfg.ini W92 .\.cproject
call %~dp0.\show_info "Remove W92 Compile Options Completed!" 4
)

goto :END


REM :REMOVE_FILE_LINKS

REM call %~dp0.\show_info "Remove File Links" 1

REM if %release_B91_flag% == 1 (
REM call %~dp0.\show_info "Remove B91 File Links" 3
REM call %~dp0.\tool rm_links %Project_Path_B91% %~dp0.\config\cfg.ini B91 .\.project
REM call %~dp0.\show_info "Remove B91 File Links Completed!" 4
REM )
REM if %release_B92_flag% == 1 (
REM call %~dp0.\show_info "Remove B92 File Links" 3
REM call %~dp0.\tool rm_links %Project_Path_B92% %~dp0.\config\cfg.ini B92 .\.project
REM call %~dp0.\show_info "Remove B92 File Links Completed!" 4
REM )
REM goto :END

REM :REMOVE_FILES
REM call %~dp0.\show_info "Remove Files" 1
REM if %release_B91_flag% == 1 (
REM call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B91
REM call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B91 chip\B91\drivers\driver.h
REM call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B91 chip\B91\drivers\reg_include\register.h
REM )
REM if %release_B92_flag% == 1 (
REM call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B92
REM call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B92 chip\B92\drivers\driver.h
REM call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B92 chip\B92\drivers\reg_include\register.h
REM )
REM call %~dp0.\show_info "Remove Files Completed!" 4
REM goto :END

REM :REMOVE_CODE
REM call %~dp0.\show_info "Remove Code" 1
REM call %~dp0.\tool rm_code %Project_Path_Rlease_SDK%
REM goto :END

:REMOVE_TEMP_FILE
if exist %~dp0.\~workspace_v1 (rmdir /s /q %~dp0.\~workspace_v1)
if exist %~dp0.\~workspace_v2 (rmdir /s /q %~dp0.\~workspace_v2)
if exist %~dp0.\customize_chip_profile (rmdir /s /q %~dp0.\customize_chip_profile)
if exist %~dp0.\~cfgTmp.txt (del /s /q /f %~dp0.\~cfgTmp.txt)
if exist %~dp0.\~log.txt (del /s /q /f %~dp0.\~log.txt)
goto :END

:MAIN
call :REMOVE_TEMP_FILE

echo ------Release SDK BEGIN(%date%  %time%)--------
if %exc_mklib_flag% == 1 call :MAKE_LIB
REM if %exc_rmcode_flag% == 1 call :REMOVE_CODE
if %exc_rmopt_flag% == 1 call :REMOVE_COMPILE_OPTIONS
REM if %exc_rmlnk_flag% == 1 call :REMOVE_FILE_LINKS
REM if %exc_rmfile_flag% == 1 call :REMOVE_FILES
if %exc_clr_prj% == 1 call %~dp0.\ClearProject.bat
if %exc_tstcmp_flag% == 1 call :TEST_COMPILE
if %exc_tstcmp_single_flag% == 1 call :TEST_COMPILE_SINGLE

echo ------Release SDK END(%date%  %time%)---------
call :REMOVE_TEMP_FILE
pause

:END