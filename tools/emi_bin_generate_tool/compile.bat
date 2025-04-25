set ANDESRISCV_ECLIPSE_BUILD=AndeSight -console -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild --launcher.suppressErrors
set workspace=%~dp0.\~workspace\
set ADNES_PATH=%~1\ide
set project_path=%~2
set project_name=%~3
set build_configuration_name=%~4

cd /d %ADNES_PATH%\
%ANDESRISCV_ECLIPSE_BUILD% -data %workspace% -import %project_path% -cleanBuild %project_name%/%build_configuration_name%
cd /d %~dp0
