#
# NimbleInstaller.nsi
# Nimble Game Engine
#
# Created by Avery Aaron on 2020-08-09.
# Copyright (C) 2020 Avery Aaron <business.a3ology@gmail.com>
#

!include LogicLib.nsh
!include nsDialogs.nsh
!include MUI2.nsh

# Variables
!define name "Nimble Game Engine"
!define productName "NimbleGameEngine"
!define author "Avery Aaron"
!define version "1.0.5"

!define icon "..\..\assets\images\icon.ico"
!define logo "..\..\assets\images\logo.bmp"
!define banner "..\..\assets\images\banner.bmp"
!define uninstallIcon "..\..\assets\images\uninstall.ico"

!define MUI_ICON "${icon}"
!define MUI_UNICON "${uninstallIcon}"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "${banner}"
!define MUI_HEADERIMAGE_UNBITMAP "${banner}"
!define MUI_HEADERIMAGE_RIGHT
!define MUI_WELCOMEFINISHPAGE_BITMAP "${logo}"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "${logo}"

!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

!define installer "NimbleInstaller.exe"
!define uninstaller "NimbleUninstaller.exe"
!define exe "${productName}.exe"
!define exePath "..\..\products\${exe}"
!define shortcut "${productName}.lnk"
!define uninstallerShortcut "NimbleUninstaller.lnk"

!define regKey "Software\${productName}"
!define uninstallerRegKey "Software\Microsoft\Windows\CurrentVersion\Uninstall\${productName}"

# Installation
Unicode true
SetCompressor /SOLID lzma

Name "${name}"
BrandingText "${name} Installer v${version}"
Icon "${icon}"
OutFile "..\products\NimbleInstaller.exe"

InstallDir "$PROGRAMFILES64\Nimble"
RequestExecutionLevel Admin
InstallDirRegKey HKLM "${regKey}" ""
CRCCheck on
SilentInstall normal
SilentUnInstall normal
XPStyle on
ShowInstDetails show
AutoCloseWindow false
WindowIcon off

!define MUI_WELCOMEPAGE_TITLE "${name} Installer"
!define MUI_WELCOMEPAGE_TEXT "Welcome to the ${name} Installer.$\r$\n$\r$\n\
This setup tool will guide you through the installation process. Please do not close the window until installation is complete to prevent an unfinished installation or file corruption.$\r$\n$\r$\n\
Click Next to get started."
!insertmacro MUI_PAGE_WELCOME

!define MUI_LICENSEPAGE_TEXT_BOTTOM "Once you have finished reading the license, click Next to continue."
!define MUI_LICENSEPAGE_BUTTON "Next"
!insertmacro MUI_PAGE_LICENSE "..\..\assets\InstallerLicense.txt"

!define MUI_COMPONENTSPAGE_NODESC
Var SMDir
!insertmacro MUI_PAGE_COMPONENTS

!define MUI_STARTMENUPAGE_DEFAULTFOLDER "${name}"
!insertmacro MUI_PAGE_STARTMENU 0 $SMDir

!define MUI_DIRECTORYPAGE_TEXT_TOP "${name} will be installed to the following folder. You may change this now by clicking Browse and selecting a different folder. Click Install to start the installation."
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_INSTFILESPAGE_FINISHHEADER_TEXT "Installation Complete"
!define MUI_INSTFILESPAGE_FINISHHEADER_SUBTEXT "The installation has been completed. Click Next to continue."
!define MUI_INSTFILESPAGE_ABORTHEADER_TEXT "Installation Aborted"
!define MUI_INSTFILESPAGE_ABORTHEADER_SUBTEXT "The installation is incomplete and may have corrupt files. You will need to reinstall the program."
!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_TITLE "${name} Installation Completed"
!define MUI_FINISHPAGE_TEXT "${name} is now installed.\r\n\r\n\
Click Finish to close the setup tool."
!define MUI_FINISHPAGE_RUN "$INSTDIR\${exe}"
!define MUI_FINISHPAGE_RUN_TEXT "Run program on exit"
!define MUI_FINISHPAGE_LINK "Open Wiki"
!define MUI_FINISHPAGE_LINK_LOCATION "https://a3ology.github.io/Nimble-Game-Engine/"
!define MUI_FINISHPAGE_LINK_COLOR "2222aa"
!insertmacro MUI_PAGE_FINISH


!define MUI_UNWELCOMEPAGE_TITLE "${name} Uninstaller"
!define MUI_UNWELCOMEPAGE_TEXT "Welcome to the ${name} Uninstaller.$\r$\n$\r$\n\
This uninstallation tool will guide you through the uninstallation process. Please do not close the window until uninstallation is complete to prevent left over files or file corruption.$\r$\n$\r$\n\
Click Next to get started."
!insertmacro MUI_UNPAGE_WELCOME

!define MUI_UNCONFIRMPAGE_TEXT_TOP "You are about to uninstall ${name} from this location. You may now click Browse and select a different folder to change that. Click Uninstall to uninstall the program."
!insertmacro MUI_UNPAGE_CONFIRM

!define MUI_UNINSTFILESPAGE_FINISHHEADER_TEXT "Uninstallation Complete"
!define MUI_UNINSTFILESPAGE_FINISHHEADER_SUBTEXT "The uninstallation has been completed. Click Next to continue."
!define MUI_UNINSTFILESPAGE_ABORTHEADER_TEXT "Uninstallation Aborted"
!define MUI_UNINSTFILESPAGE_ABORTHEADER_SUBTEXT "The uninstallation is incomplete and may have left or corrupted files. You will need to try again."
!insertmacro MUI_UNPAGE_INSTFILES

!define MUI_FINISHPAGE_TITLE "${name} Uninstallation Completed"
!define MUI_FINISHPAGE_TEXT "${name} has been uninstalled.$\r$\n$\r$\n\
Click Finish to close the uninstallation tool."
!insertmacro MUI_UNPAGE_FINISH


!insertmacro MUI_LANGUAGE "English"


Section -StartMenu
SetShellVarContext all
!insertmacro MUI_STARTMENU_WRITE_BEGIN 0
CreateDirectory "$SMPrograms\$SMDir"
CreateShortCut "$SMPROGRAMS\$SMDir\${shortcut}" "$INSTDIR\${exe}"
# TODO: Shortcuts for each program

CreateShortCut "$SMPROGRAMS\$SMDir\${uninstallerShortcut}" "$INSTDIR\${uninstaller}"
!insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section "Desktop Shortcut"
SetShellVarContext all
CreateShortCut "$DESKTOP\${shortcut}" "$INSTDIR\${exe}"
SectionEnd

# Default section
Section
  WriteRegStr HKLM "${regKey}" "Install_Dir" "$INSTDIR"
  WriteRegStr HKLM "${uninstallerRegKey}" "DisplayName" "${productName}"
  WriteRegStr HKLM "${uninstallerRegKey}" "UninstallString" '"$INSTDIR\${uninstaller}"'
  WriteRegStr HKLM "${uninstallerRegKey}" "Publisher" "${author}"
  WriteRegStr HKLM "${uninstallerRegKey}" "DisplayVersion" "${version}"

  # Remove previously installed files
  RMDir /r "$INSTDIR"

  SetOutPath $INSTDIR
  
  # TODO: Install files
  File "${exePath}"

  WriteUninstaller "$INSTDIR\${uninstaller}"

SectionEnd

Section "un.Uninstall"
  SetShellVarContext all
  WriteRegStr HKLM "${regKey}" "Install_Dir" ""
  WriteRegStr HKLM "${uninstallerRegKey}" "DisplayName" ""
  WriteRegStr HKLM "${uninstallerRegKey}" "UninstallString" ""
  WriteRegStr HKLM "${uninstallerRegKey}" "Publisher" ""
  WriteRegStr HKLM "${uninstallerRegKey}" "DisplayVersion" ""
  
  Delete "$INSTDIR\${exe}"
  !insertmacro MUI_STARTMENU_GETFOLDER 0 $SMDir
  Delete "$SMPROGRAMS\$SMDir\${shortcut}"
  Delete "$SMPROGRAMS\$SMDir\${uninstallerShortcut}"
  Delete "$DESKTOP\${shortcut}"
  RMDir "$SMPROGRAMS\$SMDir"

  Delete "$INSTDIR\${uninstaller}"

  RMDir "$INSTDIR"

SectionEnd

# NimnbleInstaller.nsi
