@echo off
REM ##################################################################################################################
REM ################################[Instructions for use]############################################################
REM STEP1: Modify TOOL_PATH_RLEASE_SDK to the installation path of RSIC-V IDE, be careful not to have spaces in the path,
REM        or surrounded by double quotes.
REM STEP2: Choose project to generate bins, 0: not excute, 1: excute.
REM STEP3: Modify the version number.
REM STEP4: Double click this file to run.
REM ##################################################################################################################

set TOOL_PATH_RLEASE_SDK=D:\Program Files\ands323
set Project_Path_Rlease_SDK=%~dp0..\..\
set EMI_compile_option=EMI_BQB_Demo

REM Choose project to generate bins, 0: not excute, 1: excute
set release_B91_flag=1

REM Modify the version number
set B91_EMI_Release_Version=_V0001

set chip_name=B91m
set release_version=_vxxxx
set cap_switch=_CapInternal
set power_mode=_PowerDCDC
set calibration_position=_CalibFlash
set program_mode=_ProgramFlashSRAM
set emi_bin_name=%chip_name%_EMI%cap_switch%%power_mode%%calibration_position%%program_mode%%release_version%


set Project_Path_B91=%Project_Path_Rlease_SDK%\project\tlsr_riscv\B91
set Project_Path_B92=%Project_Path_Rlease_SDK%\project\tlsr_riscv\B92


goto :MAIN


:TEST_COMPILE
if not exist %~dp0output mkdir %~dp0output

setlocal EnableDelayedExpansion

REM ###########################################################
REM B91EMI
REM ###########################################################

set Project_Path_Compile=%Project_Path_B91%
set Test_Compile_CompileOption=TL_PLATFORM_SDK_B91

if %release_B91_flag% == 1 (

set chip_name=B91
set release_version=%B91_EMI_Release_Version%
set calibration_position=_CalibFlash
set power_mode=
set program_mode=

if not exist %~dp0output\!chip_name! mkdir %~dp0output\!chip_name!

REM set to EMI_DEMO
call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\demo\vendor\%EMI_compile_option%\app_config.h TEST_DEMO EMI_DEMO

REM SRAM Program
set program_mode=_ProgramSRAM
call %~dp0.\tool st_node %Project_Path_Compile%\.cproject %~dp0config\config.ini B91m_Boot_Macro %EMI_compile_option%:MCU_STARTUP_FLASH:MCU_STARTUP_RAM 
call %~dp0.\tool st_node %Project_Path_Compile%\.cproject %~dp0config\config.ini B91m_Link_File %EMI_compile_option%:flash_boot.link:ram_boot.link 
call :GNERATE_BIN_B91_UNIT2

REM Flash Program
set program_mode=_ProgramFlash
call %~dp0.\tool st_node %Project_Path_Compile%\.cproject %~dp0config\config.ini B91m_Boot_Macro %EMI_compile_option%:MCU_STARTUP_RAM:MCU_STARTUP_FLASH
call %~dp0.\tool st_node %Project_Path_Compile%\.cproject %~dp0config\config.ini B91m_Link_File %EMI_compile_option%:ram_boot.link:flash_boot.link 
call :GNERATE_BIN_B91_UNIT2

)

setlocal DisableDelayedExpansion
goto :END


:GNERATE_BIN_B91_UNIT1
REM Internal Cap
set cap_switch=_CapInternal
call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\demo\vendor\%EMI_compile_option%\app_emi.c CLOSE_INTERNAL_CAP_EN 0

set emi_bin_name=!chip_name!_EMI!cap_switch!!power_mode!!calibration_position!!program_mode!!release_version!
call %~dp0.\show_info "Compile %EMI_compile_option% !chip_name!" 1
call :COMPILE_PROCESS
copy %Project_Path_Compile%\%EMI_compile_option%\output\%EMI_compile_option%.bin %~dp0output\!chip_name!\!emi_bin_name!.bin
call %~dp0.\show_info "Generate !emi_bin_name!.bin successfully!" 4

REM External Cap
set cap_switch=_CapExternal
call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\demo\vendor\%EMI_compile_option%\app_emi.c CLOSE_INTERNAL_CAP_EN 1

set emi_bin_name=!chip_name!_EMI!cap_switch!!power_mode!!calibration_position!!program_mode!!release_version!
call %~dp0.\show_info "Compile %EMI_compile_option% !chip_name!" 1
call :COMPILE_PROCESS
copy %Project_Path_Compile%\%EMI_compile_option%\output\%EMI_compile_option%.bin %~dp0output\!chip_name!\!emi_bin_name!.bin
call %~dp0.\show_info "Generate !emi_bin_name!.bin successfully!" 4

goto :END


:GNERATE_BIN_B91_UNIT2
REM Power DCDC1V8_DCDC1V4
set power_mode=_PowerDCDC1V8DCDC1V4
call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\demo\vendor\%EMI_compile_option%\main.c POWER_MODE_SELECT POWER_MODE_DCDC1V4_DCDC1V8
call :GNERATE_BIN_B91_UNIT1

REM Power DCDC1V4_LDO1V8
set power_mode=_PowerDCDC1V4LDO1V8
call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\demo\vendor\%EMI_compile_option%\main.c POWER_MODE_SELECT POWER_MODE_DCDC1V4_LDO1V8
call :GNERATE_BIN_B91_UNIT1

REM Power LDO1V4_LDO1V8
set power_mode=_PowerLDO1V4LDO1V8
call %~dp0.\tool st_macro %Project_Path_Rlease_SDK%\demo\vendor\%EMI_compile_option%\main.c POWER_MODE_SELECT POWER_MODE_LDO1V4_LDO1V8
call :GNERATE_BIN_B91_UNIT1

goto :END


:COMPILE_PROCESS

if exist %Project_Path_Compile%\%EMI_compile_option% (rmdir /s /q %Project_Path_Compile%\%EMI_compile_option%)
call %~dp0.\compile "%TOOL_PATH_RLEASE_SDK%" %Project_Path_Compile% %Test_Compile_CompileOption% %EMI_compile_option%
if exist %Project_Path_Compile%\%EMI_compile_option%\output\*.bin (
call %~dp0.\show_info "PASS" 2
) else (
call %~dp0.\show_info "FAIL" 2
pause
)
goto :END

:REMOVE_TEMP_FILE
if exist %~dp0.\~workspace (rmdir /s /q %~dp0.\~workspace)
if exist %~dp0.\customize_chip_profile (rmdir /s /q %~dp0.\customize_chip_profile)
if exist %~dp0.\~cfgTmp.txt (del /s /q /f %~dp0.\~cfgTmp.txt)
goto :END

:MAIN
call :REMOVE_TEMP_FILE
echo ------BEGIN(%date%  %time%)--------
call :TEST_COMPILE
echo ------END(%date%  %time%)---------
call :REMOVE_TEMP_FILE
pause

:END