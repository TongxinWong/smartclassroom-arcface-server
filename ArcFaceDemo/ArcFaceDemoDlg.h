
// ArcFaceDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ArcFaceEngine.h"

#include <memory>
#include <string>
#include <queue>
#include <ctime>

//����GDI+
#include <GdiPlus.h>
#include "afxwin.h"
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

struct Active_FaceInfo
{
	int faceID;
	int faceStatus;
	ASF_SingleFaceInfo faceInfo;
	CString StudentID;
	CString videoShowString;
	time_t begin;							//���������뻭��ʱ��ʱ��
};

//struct faceData
//{
//	ASF_SingleFaceInfo faceInfo;
//	int faceID;
//};

// CArcFaceDemoDlg �Ի���
class CArcFaceDemoDlg : public CDialogEx
{
	// ����
public:
	CArcFaceDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CArcFaceDemoDlg();
	// �Ի�������
	enum { IDD = IDD_ARCFACEDEMO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnRegister();
	afx_msg void OnBnClickedBtnRecognition();
	afx_msg void OnBnClickedBtnCompare();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnCamera();
	afx_msg void OnEnChangeEditThreshold();

	void EditOut(CString str, bool add_endl);
	void IplDrawToHDC(BOOL isVideoMode, IplImage* rgbImage, CRect& showRect, UINT ID);
	void IplDrawToHDC(BOOL isVideoMode, IplImage* rgbImage, CString videoShowString, CRect& showRect, UINT ID);

private:
	void LoadThumbnailImages();
	CString SelectFolder();
	BOOL TerminateLoadThread();
	BOOL ClearRegisterImages();
	BOOL CalculateShowPositon(IplImage*curSelectImage, Gdiplus::Rect& showRect);
	MRESULT StaticImageFaceOp(IplImage* image);
	void ClearShowWindow();
public:
	CListCtrl m_ImageListCtrl;
	CImageList m_IconImageList;
	CEdit m_editLog;

	CString m_folderPath;
	std::vector<ASF_FaceFeature> m_featuresVec;
	std::vector<CString> m_studentIDsVec;				//ѧ��ѧ����Ϣ

	BOOL m_bLoadIconThreadRunning;
	DWORD m_dwLoadIconThreadID;
	HANDLE m_hLoadIconThread;

	BOOL m_bClearFeatureThreadRunning;
	DWORD m_dwClearFeatureThreadID;
	HANDLE m_hClearFeatureThread;

	BOOL m_bFDThreadRunning;
	DWORD m_dwFDThreadID;
	HANDLE m_hFDThread;

	BOOL m_bFRThreadRunning;
	DWORD m_dwFRThreadID;
	HANDLE m_hFRThread;

	ArcFaceEngine m_imageFaceEngine;
	ArcFaceEngine m_videoFaceEngine;

	IplImage* m_curStaticImage;					//��ǰѡ�е�ͼƬ
	ASF_FaceFeature m_curStaticImageFeature;	//��ǰͼƬ����������
	BOOL m_curStaticImageFRSucceed;
	Gdiplus::Rect m_curFaceShowRect;
	Gdiplus::Rect m_curImageShowRect;

	CString m_curStaticShowAgeGenderString;

	CString m_curStaticShowCmpString;

	IplImage* m_curVideoImage;
	IplImage* m_curIrVideoImage;
	ASF_SingleFaceInfo m_curFaceInfo;
	int m_curFaceID;							//��ǰ�����faceID
	bool m_dataValid;
	bool m_irDataValid;

	bool m_videoOpened;
	CString m_strEditThreshold;

	Gdiplus::PointF m_curStringShowPosition;	//��ǰ�ַ�����ʾ��λ��
	CString m_curVideoShowString;
	CString m_curIRVideoShowString;
	CFont* m_Font;

	Active_FaceInfo m_faceList[256];			//��ǰ�����е�����״̬
	std::queue<int> m_FRList;					//���ȼ��ߵĶ���
	std::queue<int> m_FRSecList;				//���ȼ��͵Ķ��� ֮ǰʶ��ʧ�ܵ���������

	std::vector<int> m_befFaceSet;				//֮ǰ����������
	std::vector<int> m_curFaceSet;				//���ڵ���������
	std::vector<int> m_curFaceDrawn;			//������Ҫ���Ƶ�����

	time_t m_postTime;								//��ʱ��
private:
	CRect m_windowViewRect;						//չʾ�ؼ��ĳߴ�
	BOOL bFullScreen;
	CRect rectFullScreen;
	WINDOWPLACEMENT m_struOldWndpl;				//�ṹ�а������йش�������Ļ��λ�õ���Ϣ
	WINDOWPLACEMENT m_struOldWndpPic;			//PICTURE�ؼ�����Ļ��λ�õ���Ϣ

public:
	afx_msg void OnClose();
	afx_msg void OnStnClickedStaticView();
};
