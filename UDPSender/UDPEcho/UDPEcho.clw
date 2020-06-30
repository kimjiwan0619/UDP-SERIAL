; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUDPEchoDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "UDPEcho.h"

ClassCount=4
Class1=CUDPEchoApp
Class2=CUDPEchoDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CUDPSocket
Resource3=IDD_UDPECHO_DIALOG

[CLS:CUDPEchoApp]
Type=0
HeaderFile=UDPEcho.h
ImplementationFile=UDPEcho.cpp
Filter=N

[CLS:CUDPEchoDlg]
Type=0
HeaderFile=UDPEchoDlg.h
ImplementationFile=UDPEchoDlg.cpp
Filter=D
LastObject=CUDPEchoDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=UDPEchoDlg.h
ImplementationFile=UDPEchoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_UDPECHO_DIALOG]
Type=1
Class=CUDPEchoDlg
ControlCount=2
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BUTTON1,button,1342242816

[CLS:CUDPSocket]
Type=0
HeaderFile=UDPSocket.h
ImplementationFile=UDPSocket.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=CUDPSocket
VirtualFilter=q

