#pragma once
#define DWORD_PTR unsigned long
#define LONG_PTR unsigned long
#include <atlbase.h>
#include <afxpriv.h>
#include <WbemIdl.h>
#pragma comment(lib,"WbemUuid.lib")

class CWmiInfo
{
public:
	CWmiInfo(void);
	~CWmiInfo(void);

public:
	HRESULT InitWmi();    //��ʼ��WMI
	HRESULT ReleaseWmi(); //�ͷ�

		
	BOOL GetSingleItemInfo(CString,CString,CString&);
	BOOL GetGroupItemInfo(CString,CString[],int,CString&);

private:
	void VariantToString(const LPVARIANT,CString &) const;//��Variant���͵ı���ת��ΪCString
private:
	IEnumWbemClassObject* m_pEnumClsObj;
	IWbemClassObject* m_pWbemClsObj;
	IWbemServices* m_pWbemSvc;
	IWbemLocator* m_pWbemLoc;
};
/*
��һ������ΪҪ��ѯ��������"Win32_Processor"��ʾCPU��,
�ڶ���������ʾҪ�����ĳ�Ա,��"Caption"��ʾ��ѯCPU������
������������ʾ����ֵ.�ʿ�����������
CString strRetValue;
GetSingleItemInfo(_T("Win32_Processor"),_T("Caption"),strRetValue);
һ�����óɹ��󼴿ɴ�strRetValue�����ж�ȡ��CPU������GetGroupItemInfo ������GetSingleItemInfo����,��ͬ����GetSingleItemInfoһ��ֻ�ܲ�һ�����Ա��GetGroupItemInfoһ�ο��Բ�ѯһ����Ķ����Ա.GetGroupItemInfo�ĵ�����������ʾҪ��ѯ�����Ա�ĸ���,��:�ڶ�������CString����Ĵ�С�����������ã�CString strRetValue;CString [] strClassMem = {_T("Caption"),_T("CurrentClockSpeed"),_T("DeviceID"),_T("Manufacturer"),_T("Manufacturer")};GetGroupItemInfo(_T("Win32_Processor"),strClassMem,5,strRetValue);*/
/*
Win32_Processor, // CPU ������
Win32_PhysicalMemory, // �����ڴ���
Win32_Keyboard, // ����
Win32_PointingDevice, // �������豸��������ꡣ
Win32_FloppyDrive, // ����������
Win32_DiskDrive, // Ӳ��������
Win32_CDROMDrive, // ����������
Win32_BaseBoard, // ����
Win32_BIOS, // BIOS оƬ
Win32_ParallelPort, // ����
Win32_SerialPort, // ����
Win32_SerialPortConfiguration, // ��������
Win32_SoundDevice, // ��ý�����ã�һ��ָ������
Win32_SystemSlot, // ������ (ISA & PCI & AGP)
Win32_USBController, // USB ������
Win32_NetworkAdapter, // ����������
Win32_NetworkAdapterConfiguration, // ��������������
Win32_Printer, // ��ӡ��
Win32_PrinterConfiguration, // ��ӡ������
Win32_PrintJob, // ��ӡ������
Win32_TCPIPPrinterPort, // ��ӡ���˿�
Win32_POTSModem, // MODEM
Win32_POTSModemToSerialPort, // MODEM �˿�
Win32_DesktopMonitor, // ��ʾ��
Win32_DisplayConfiguration, // �Կ�
Win32_DisplayControllerConfiguration, // �Կ�����
Win32_VideoController, // �Կ�ϸ�ڡ�
Win32_VideoSettings, // �Կ�֧�ֵ���ʾģʽ��

// ����ϵͳ
Win32_TimeZone, // ʱ��
Win32_SystemDriver, // ��������
Win32_DiskPartition, // ���̷���
Win32_LogicalDisk, // �߼�����
Win32_LogicalDiskToPartition, // �߼��������ڷ�����ʼĩλ�á�
Win32_LogicalMemoryConfiguration, // �߼��ڴ�����
Win32_PageFile, // ϵͳҳ�ļ���Ϣ
Win32_PageFileSetting, // ҳ�ļ�����
Win32_BootConfiguration, // ϵͳ��������
Win32_ComputerSystem, // �������Ϣ��Ҫ
Win32_OperatingSystem, // ����ϵͳ��Ϣ
Win32_StartupCommand, // ϵͳ�Զ���������
Win32_Service, // ϵͳ��װ�ķ���
Win32_Group, // ϵͳ������
Win32_GroupUser, // ϵͳ���ʺ�
Win32_UserAccount, // �û��ʺ�
Win32_Process, // ϵͳ����
Win32_Thread, // ϵͳ�߳�
Win32_Share, // ����
Win32_NetworkClient, // �Ѱ�װ������ͻ���
Win32_NetworkProtocol, // �Ѱ�װ������Э��*/