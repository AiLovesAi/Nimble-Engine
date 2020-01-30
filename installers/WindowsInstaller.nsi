; ######################################################
; #             NIMBLE GAME ENGINE INSTALLER           #
; #                  Windows Version                   #
; #         Created by Avery Aaron on 1/29/20.         #
; # Copyright © 2020 Avery Aaron. All rights reserved. #
; ######################################################


!define PRODUCT_NAME "Nimble Example"


!include "LogicLib.nsh"

Name "${PRODUCT_NAME}"
OutFile "${PRODUCT_NAME} Installer.exe"
InstallDir "$PROGRAMFILES\Steam\SteamApps\common\Nimble Example"

SetCompressor /FINAL /SOLID lzma
SetCompressorDictSize 64

RequestExecutionLevel user

Section "Install"
  
  SetSilent silent
  
  CreateDirectory "$INSTDIR"
  SetOutPath "$INSTDIR"
  SetOverwrite try
  
  WriteUninstaller "$INSTDIR\Uninstall ${PRODUCT_NAME}.exe"
  
  SetAutoClose true 
  
SectionEnd

Section "un.Uninstall"
  
  SetSilent silent
  
  MessageBox MB_YESNO "You are about to uninstall ${PRODUCT_NAME}, including all files in $INSTDIR. Continue?" IDYES NoAbortCancel
    Abort
  NoAbortCancel:
  
  StrCmpS "$INSTDIR" "$PROGRAMFILES" AbortProtectFiles 0
  StrCmpS "$INSTDIR" "$DESKTOP" AbortProtectFiles 0
  StrCmpS "$INSTDIR" "$SYSDIR" AbortProtectFiles 0
  StrCmpS "$INSTDIR" "$WINDIR" AbortProtectFiles 0
  StrCmpS "$INSTDIR" "$TEMP" AbortProtectFiles 0
  StrCmpS "$INSTDIR" "$STARTMENU" AbortProtectFiles 0
  StrCmpS "$INSTDIR" "$SMSTARTUP" AbortProtectFiles 0
  StrCmpS "$INSTDIR" "$DOCUMENTS" AbortProtectFiles 0
  StrCmpS "$INSTDIR" "$APPDATA" AbortProtectFiles 0
  StrCmpS "$INSTDIR" "$CDBURN_AREA" AbortProtectFiles 0
  StrCmpS "$INSTDIR" "$PROGRAMFILES\Steam\SteamApps\common" AbortProtectFiles 0
  RMDir /R /REBOOTOK "$INSTDIR"
  Goto NoAbortProtectFiles
  AbortProtectFiles:
  MessageBox MB_ICONSTOP "${PRODUCT_NAME} is installed under an important folder. Please move the files into their own directory and try again."
  Abort
  NoAbortProtectFiles:
  
  SetAutoClose true
  
SectionEnd
