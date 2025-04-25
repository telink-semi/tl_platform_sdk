@echo off
set log_out_path=~log.txt
set para2=%~2
set para1=%~1

goto :MAIN

:SHOW_INFO
if index%para2% equ index1 (
echo [%time:~0,-3%]telink@ ################################################ 
echo [%time:~0,-3%]telink@ ## %para1%
echo [%time:~0,-3%]telink@ ################################################
) else (
if index%para2% equ index2 (
echo [%time:~0,-3%]telink@ ## [ %para1% ] ##
echo [%time:~0,-3%]telink@
) else (
if index%para2% equ index3 (
echo [%time:~0,-3%]telink@
echo [%time:~0,-3%]telink@ ## %para1% 
) else (
if index%para2% equ index4 (
echo [%time:~0,-3%]telink@ %para1% 
echo [%time:~0,-3%]telink@
) else (
echo [%time:~0,-3%]telink@ %para1%
)
)
)
)
goto :END

:MAIN
call :SHOW_INFO
call :SHOW_INFO>>%log_out_path% 

:END