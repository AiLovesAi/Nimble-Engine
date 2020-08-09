!include LogicLib.nsh
!include nsDialogs.nsh
!include MUI2.nsh

# Variables
!define name "Nimble Game Engine"
!define productName "NimbleGameEngine"
!define author "Avery Aaron"
!define version "1.0.0"

!define icon "build\images\icon.ico"
!define logo "build\images\logo.bmp"
!define banner "build\images\banner.bmp"
!define uninstallIcon "build\images\uninstall.ico"

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
!define uninstallerShortcut "NimbleUninstaller.lnk"

!define regKey "Software\${productName}"
!define uninstallerRegKey "Software\Microsoft\Windows\CurrentVersion\Uninstall\${productName}"

# Installation
Unicode true
SetCompressor /SOLID lzma

Name "${name}"
Icon "${icon}"
OutFile "NimbleInstaller.exe"

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

Caption "${name} Installer"
SubCaption 3 " "
SubCaption 4 " "

!insertmacro MUI_PAGE_WELCOME

!insertmacro MUI_PAGE_LICENSE "build\LICENSE.txt"

!insertmacro MUI_PAGE_DIRECTORY

!insertmacro MUI_PAGE_INSTFILES
 
!insertmacro MUI_PAGE_FINISH
 
!insertmacro MUI_LANGUAGE "English"


# Default section
Section "Install"
  WriteRegStr HKLM "${regKey}" "Install_Dir" "$INSTDIR"
  WriteRegStr HKLM "${uninstallerRegKey}" "DisplayName" "${productName}"
  WriteRegStr HKLM "${uninstallerRegKey}" "UninstallString" '"$INSTDIR\${uninstaller}"'
  WriteRegStr HKLM "${uninstallerRegKey}" "Publisher" "${author}"
  WriteRegStr HKLM "${uninstallerRegKey}" "DisplayVersion" "${version}"

  # Remove previously installed files
  RMDir /r "$INSTDIR"

  SetOutPath $INSTDIR
  
  # TODO: Install files

  WriteUninstaller "$INSTDIR\${uninstaller}"
  CreateShortCut "$SMPROGRAMS\${uninstallerShortcut}" "$INSTDIR\${uninstaller}"

SectionEnd

Section "un.Uninstall"

  Delete "$INSTDIR\${uninstaller}"
  Delete "$SMPROGRAMS\${uninstallerShortcut}"

  RMDir $INSTDIR

SectionEnd
