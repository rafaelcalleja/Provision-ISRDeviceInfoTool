// SDKDEMO.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "SDKDEMO.h"
#include "SDKDEMODlg.h"
#include "DeviceDlg.h"
#include "ConnectModeDlg.h"
#ifdef _IPTOOL_SEARCH_AND_NOTIFY_SDK_H
#include "IPTool_SearchAndNotifySDK.h"
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDKDEMOApp

BEGIN_MESSAGE_MAP(CSDKDEMOApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSDKDEMOApp ����

CSDKDEMOApp::CSDKDEMOApp():m_lUserID(-1)
{
	// TODO: �ڴ˴����ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSDKDEMOApp ����

CSDKDEMOApp theApp;


void CALLBACK AcceptRegisterProc(LONG lUserID, LONG lRegisterID, LPNET_SDK_DEVICEINFO pDeviceInfo, void *pUser)
{
	CSDKDEMOApp* pThis = (CSDKDEMOApp*)(pUser);
	if (!pThis)
		return;

	pThis->m_lUserID = lUserID;
	memcpy(&(pThis->m_deviceInfo), pDeviceInfo, sizeof(NET_SDK_DEVICEINFO));
}
// CSDKDEMOApp ��ʼ��

BOOL CSDKDEMOApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	
	CoInitialize(NULL);
	//��ʼ��sdk
	NET_SDK_Init();
	NET_SDK_SetConnectTime(4000, 1);
	NET_SDK_SetReconnect();
#ifdef _IPTOOL_SEARCH_AND_NOTIFY_SDK_H
	IPTOOL_SEARCH_AND_NOTIFY_Initial();
#endif
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CConnectModeDlg connectModeDlg;

	//if(IDOK == connectModeDlg.DoModal())
	//{
		//if(CConnectModeDlg::CONNECT_MODE_LOGIN_TO_DEVICE == connectModeDlg.m_connectMode)
	//	{
			while(true)
			{
				CDeviceDlg *deviceDlg = new CDeviceDlg;
				CSDKDEMODlg dlg;
//#define USER_DEVICE_SERACH
#ifdef USER_DEVICE_SERACH
				if (deviceDlg->DoModal() == IDOK)//ȥ��ɨ��Ի���
#else
				if(1)
#endif
				{
#ifdef USER_DEVICE_SERACH
					dlg.SetDeviceInfo(deviceDlg->GetIp(), deviceDlg->GetPort());
#else
					dlg.SetDeviceInfo("213.57.116.4", 6004);
					//dlg.SetDeviceInfo("192.168.61.35", 9008);
#endif
					dlg.DoModal();

					delete deviceDlg;
					break;
				}
				else
				{
					delete deviceDlg;
					break;
				}
				delete deviceDlg;		
			}
	//	}
		/*else
		{
			NET_SDK_SetRegisterPort(connectModeDlg.m_registerPort);
			NET_SDK_SetRegisterCallback(AcceptRegisterProc, this);

			int tryTimes = 0;
			CSDKDEMODlg dlg;
			while(-1 == m_lUserID)
			{
				Sleep(10);
				tryTimes++;

				if(tryTimes > 10000)
				{
					AfxMessageBox("No device register!");
#ifdef _IPTOOL_SEARCH_AND_NOTIFY_SDK_H
					IPTOOL_SEARCH_AND_NOTIFY_Quit();
#endif
					NET_SDK_Cleanup();
					return FALSE;
				}
			}

			dlg.SetDeviceInfo(m_lUserID, &m_deviceInfo);
			dlg.DoModal();
		}*/
	//}
#ifdef _IPTOOL_SEARCH_AND_NOTIFY_SDK_H
	IPTOOL_SEARCH_AND_NOTIFY_Quit();
#endif
	NET_SDK_Cleanup();
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CSDKDEMOApp::ExitInstance()
{
	// TODO: �ڴ�����ר�ô����/����û���
	CoUninitialize();

	return CWinApp::ExitInstance();
}