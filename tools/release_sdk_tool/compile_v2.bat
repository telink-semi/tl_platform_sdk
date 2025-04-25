set ANDESRISCV_ECLIPSE_BUILD=TelinkIoTStudioc.exe -console -nosplash --launcher.suppressErrors -application org.eclipse.cdt.managedbuilder.core.headlessbuild
set workspace=%~dp0~workspace_v2\
set ADNES_PATH=%~1
set project_path=%~2
set project_name=%~3
set build_configuration_name=%~4

REM if exist %workspace% del /s /q /f %workspace%

cd /d %ADNES_PATH%\
REM echo %ADNES_PATH%
REM echo %project_path%
call "%ADNES_PATH%"\%ANDESRISCV_ECLIPSE_BUILD% -data %workspace% -import %project_path% -cleanBuild %project_name%/%build_configuration_name%
cd /d %~dp0
