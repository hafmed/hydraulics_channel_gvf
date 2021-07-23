Name "hydraulics-channel-gvf HAFIANE Mohamed"
OutFile "hydraulics-channel-gvf_win64_install_3.0.9.exe"

Icon "hydraulics-channel-gvf.ico"
UninstallIcon "hydraulics-channel-gvf.ico"

DirText "Uninstall previous version if exist and Choose directory for installing of Simulation of Gradually Varied Flow in Channel (hydraulics-channel-gvf) Ver 3.0.9 ; 25-7-2021"

InstallDir "$PROGRAMFILES\hydraulics-channel-gvf"

Section "Install"
  SetOutPath $INSTDIR
  File "C:\Qt6\6.1.1\mingw81_64\bin\libgcc_s_seh-1.dll"
  File "C:\Qt6\6.1.1\mingw81_64\bin\libstdc++-6.dll"
  File "C:\Qt6\6.1.1\mingw81_64\bin\libwinpthread-1.dll"
  File "C:\Qt6\6.1.1\mingw81_64\bin\Qt6Core.dll"
  File "C:\Qt6\6.1.1\mingw81_64\bin\Qt6Gui.dll"
  File "C:\Qt6\6.1.1\mingw81_64\bin\Qt6PrintSupport.dll"
  File "C:\Qt6\6.1.1\mingw81_64\bin\Qt6Widgets.dll"
CreateDirectory $INSTDIR\platforms
SetOutPath $INSTDIR\platforms
  File "C:\Qt6\6.1.1\mingw81_64\plugins\platforms\qwindows.dll"
SetOutPath $INSTDIR 
 File "..\CompilationWin\release\hydraulics-channel-gvf.exe"
 File "hydraulics-channel-gvf.ico"

  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\hydraulics-channel-gvf" "DisplayName" "hydraulics-channel-gvf"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\hydraulics-channel-gvf" "UninstallString" "$INSTDIR\uninstall.exe"
  WriteUninstaller "uninstall.exe"
SectionEnd

Section "Shortcuts"
  CreateDirectory "$SMPROGRAMS\hydraulics-channel-gvf"
  SetOutPath $INSTDIR
  CreateShortCut "$SMPROGRAMS\hydraulics-channel-gvf\hydraulics-channel-gvf.lnk""$INSTDIR\hydraulics-channel-gvf.exe"
  SetOutPath $INSTDIR
  CreateShortCut "$DESKTOP\hydraulics-channel-gvf.lnk""$INSTDIR\hydraulics-channel-gvf.exe"
  CreateShortCut "$QUICKLAUNCH\hydraulics-channel-gvf.lnk""$INSTDIR\hydraulics-channel-gvf.exe"
  CreateShortCut "$SMPROGRAMS\hydraulics-channel-gvf\uninstall_hydraulics-channel-gvf.lnk""$INSTDIR\uninstall.exe"
SectionEnd

UninstallText "Close hydraulics-channel-gvf if running ; This will uninstall hydraulics-channel-gvf from your system"

Section "Uninstall"
DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\hydraulics-channel-gvf"
Delete "$SMPROGRAMS\hydraulics-channel-gvf\hydraulics-channel-gvf.lnk"
Delete "$SMPROGRAMS\hydraulics-channel-gvf\uninstall_hydraulics-channel-gvf.lnk"
RmDir "$SMPROGRAMS\hydraulics-channel-gvf"
Delete "$DESKTOP\hydraulics-channel-gvf.lnk"
Delete "$QUICKLAUNCH\hydraulics-channel-gvf.lnk"
Delete "$INSTDIR\libgcc_s_seh-1.dll"
Delete "$INSTDIR\libstdc++-6.dll"
Delete "$INSTDIR\libwinpthread-1.dll"
Delete "$INSTDIR\Qt6Core.dll"
Delete "$INSTDIR\Qt6Gui.dll"
Delete "$INSTDIR\Qt6PrintSupport.dll"
Delete "$INSTDIR\Qt6Widgets.dll"
Delete "$INSTDIR\platforms\qwindows.dll"
RMDir $INSTDIR\platforms
Delete "$INSTDIR\hydraulics-channel-gvf.exe"
Delete "$INSTDIR\hydraulics-channel-gvf.ico"
Delete "$INSTDIR\uninstall.exe"
RmDir "$INSTDIR"
SectionEnd
