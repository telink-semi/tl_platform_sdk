@echo off

set Project_Path_Rlease_SDK=%~dp0..\..\
set Project_Path_B91=%Project_Path_Rlease_SDK%\project\tlsr_riscv\B91
set Project_Path_B92=%Project_Path_Rlease_SDK%\project\tlsr_riscv\B92
set Project_Path_TL7518=%Project_Path_Rlease_SDK%\project\tlsr_riscv\TL7518
set Project_Path_TL751X=%Project_Path_Rlease_SDK%\project\tlsr_riscv\tl751x
set Project_Path_TL721X=%Project_Path_Rlease_SDK%\project\tlsr_riscv\TL721X
set Project_Path_TL321X=%Project_Path_Rlease_SDK%\project\tlsr_riscv\TL321X
set Project_Path_W92=%Project_Path_Rlease_SDK%\project\tlsr_riscv\W92

goto :MAIN

:REMOVE_FILE_LINKS

call %~dp0.\show_info "Remove File Links" 1

if exist %Project_Path_B91% (
call %~dp0.\show_info "Remove B91 File Links" 3
call %~dp0.\tool rm_links %Project_Path_B91% %~dp0.\config\cfg.ini B91 .\.project
call %~dp0.\show_info "Remove B91 File Links Completed!" 4
)

if exist %Project_Path_B92% (
call %~dp0.\show_info "Remove B92 File Links" 3
call %~dp0.\tool rm_links %Project_Path_B92% %~dp0.\config\cfg.ini B92 .\.project
call %~dp0.\show_info "Remove B92 File Links Completed!" 4
)

if exist %Project_Path_TL7518% (
call %~dp0.\show_info "Remove TL7518 File Links" 3
call %~dp0.\tool rm_links %Project_Path_TL7518% %~dp0.\config\cfg.ini TL7518 .\.project
call %~dp0.\show_info "Remove TL7518 File Links Completed!" 4
)

if exist %Project_Path_TL751X% (
call %~dp0.\show_info "Remove tl751x File Links" 3
call %~dp0.\tool rm_links %Project_Path_TL751X% %~dp0.\config\cfg.ini tl751x .\.project
call %~dp0.\show_info "Remove tl751x File Links Completed!" 4
)

if exist %Project_Path_TL721X% (
call %~dp0.\show_info "Remove TL721X File Links" 3
call %~dp0.\tool rm_links %Project_Path_TL721X% %~dp0.\config\cfg.ini TL721X .\.project
call %~dp0.\show_info "Remove TL721X File Links Completed!" 4
)

if exist %Project_Path_TL321X% (
call %~dp0.\show_info "Remove TL321X File Links" 3
call %~dp0.\tool rm_links %Project_Path_TL321X% %~dp0.\config\cfg.ini TL321X .\.project
call %~dp0.\show_info "Remove TL321X File Links Completed!" 4
)

if exist %Project_Path_W92% (
call %~dp0.\show_info "Remove W92 File Links" 3
call %~dp0.\tool rm_links %Project_Path_W92% %~dp0.\config\cfg.ini W92 .\.project
call %~dp0.\show_info "Remove W92 File Links Completed!" 4
)

goto :END

:REMOVE_FILES
call %~dp0.\show_info "Remove Files" 1

call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B91
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B91 chip\B91\drivers\driver.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B91 chip\B91\drivers\reg_include\register.h

call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B92
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B92 chip\B92\drivers\driver.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini B92 chip\B92\drivers\reg_include\register.h

call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL7518
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL7518 chip\TL7518\drivers\driver.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL7518 chip\TL7518\drivers\reg_include\register.h

call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini tl751x
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini tl751x chip\tl751x\drivers\driver.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini tl751x chip\tl751x\drivers\reg_include\register.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini tl751x chip\tl751x\drivers\lib\pke\ecdh.c

call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL721X
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL721X chip\TL721X\drivers\driver.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL721X chip\TL721X\drivers\adc.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL721X chip\TL721X\drivers\adc.c
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL721X chip\TL721X\drivers\reg_include\register.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL721X chip\TL721X\drivers\lib\src\pm.c
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL721X chip\TL721X\drivers\lib\include\stimer.h

call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL321X
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL321X chip\TL321X\drivers\driver.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL321X chip\TL321X\drivers\adc.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL321X chip\TL321X\drivers\adc.c
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL321X chip\TL321X\drivers\reg_include\register.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini TL321X chip\TL321X\drivers\lib\src\pm.c

call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini W92
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini W92 chip\W92\drivers\driver.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini W92 chip\W92\drivers\reg_include\register.h
call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini W92 chip\W92\drivers\lib\src\pm.c

call %~dp0.\tool rm_files %Project_Path_Rlease_SDK% %~dp0.\config\cfg.ini Release

call %~dp0.\show_info "Remove Files Completed!" 4
goto :END

:REMOVE_CODE
call %~dp0.\show_info "Remove Code" 1
call %~dp0.\tool rm_code %Project_Path_Rlease_SDK%
call %~dp0.\show_info "Remove Code Completed!" 4
goto :END

:MAIN
echo ------Clear Project BEGIN(%date%  %time%)--------
call :REMOVE_FILES
call :REMOVE_FILE_LINKS
call :REMOVE_CODE
echo ------Clear Project END(%date%  %time%)---------

pause

:END