#pragma once
#include "CProcessInfo.h"
#include "CLiveProgram.h"
#include "CUserManager.h"
#include "CDataShowView.h"
#include "CDataControl.h"
#include "CLiveManager.h"
#include "CSoundManager.h"
// CInteracteLiveDlg 对话框

/*
 * 互动直播对话框
 */
class CInteracteLiveDlg : public CDialogEx, public CLocalDataControl, public CPicControlCallback, public ILiveListener, public IChatroomGetListListener, public ISoundCallback
{
	DECLARE_DYNAMIC(CInteracteLiveDlg)

public:
	CInteracteLiveDlg(CUserManager* pUserManager, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInteracteLiveDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	/**
	 * 查询聊天室列表回调
	 */
	virtual int chatroomQueryAllListOK(list<ChatroomInfo>& listData);
	/*
	 * 获取直播列表
	 */
	void getLiveList();

	afx_msg LRESULT OnRecvLiveMsg(WPARAM wParam, LPARAM lParam);

	/*
	 * 刷新列表
	 */
	afx_msg void OnBnClickedButtonLiveBrushList();
	/*
	 * 关闭当前直播
	 */
	afx_msg LRESULT setShowPictures(WPARAM wParam, LPARAM lParam);
	/*
	 * 绘制
	 */
	afx_msg void OnPaint();

	/*
	 * 销毁函数
	 */
	afx_msg void OnDestroy();
	/*
	 * 创建新直播
	 */
	afx_msg void OnBnClickedButtonCreateNewLive();
	/*
	 * 初始化对话框
	 */
	virtual BOOL OnInitDialog();
	
	/*
	 * 查询直播内容
	 */
	CLiveProgram* getLiveProgram(CString strId, CString strName, CString strCreator);

public:
	// picture control 回调函数
	/*
	 * 右键退出回调
	 */
	virtual void liveExit(void* pParam);
	/*
	 * 双击修改配置回调
	 */
	virtual void changeStreamConfig(void* pParam, int upid);
	/*
	 * 关闭当前直播
	 */
	virtual void closeCurrentLive(void* pParam);
	/*
	 * 开启人脸识别
	 */
	virtual void startFaceFeature(void* pParam);
	/*
	 * 停止人脸识别
	 */
	virtual void stopFaceFeature(void* pParam);

public:
	// start回调函数
	virtual int downloadChannelClosed();
	virtual int downloadChannelLeave();
	virtual int downloadNetworkUnnormal();
	virtual int queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum);
	virtual int uploaderAdd(char* upUserId, int upId);
	virtual int uploaderRemove(char* upUserId, int upId);
	virtual int getRealtimeData(int upId, uint8_t* data, int len);
	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen);

	virtual int deleteChannel(char* channelId);
	virtual int stopOK();
	virtual int srcError(char* errString);
public:
	/**
	 * 聊天室成员数变化
	 * @param number
	 */
	virtual void onMembersUpdated(int number);

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfKicked();

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfMuted(int seconds);

	/**
	 * 聊天室已关闭
	 */
	virtual void onClosed();

	/**
	 * 收到消息
	 * @param message
	 */
	virtual void onReceivedMessage(CIMMessage* pMessage);

	/**
	 * 收到私信消息
	 * @param message
	 */
	virtual void onReceivePrivateMessage(CIMMessage* pMessage);

	/**
	 * 房主收到其他用户的连麦申请
	 * @param liveID
	 * @param applyUserID
	 */
	virtual void onApplyBroadcast(string liveID, string applyUserID);

	/**
	 * 申请连麦用户收到的回复
	 * @param liveID
	 * @param result
	 */
	virtual void onApplyResponsed(string liveID, bool bAgree);

public:
	virtual void addUpId();
	virtual void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	virtual int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	virtual void drawPic(YUV_TYPE type, int w, int h, uint8_t* videoData, int videoDataLen);
public:
	virtual void getLocalSoundData(char* pData, int nLength);
	virtual void querySoundData(char** pData, int* nLength);
public:
	CListBox m_liveList;
	CDataShowView* m_pDataShowView;
	CUserManager* m_pUserManager;

	CLiveManager* m_pLiveManager;
	CSoundManager* m_pSoundManager;
	vector<CLiveProgram> mVLivePrograms;
	CLiveProgram* m_pCurrentLive;
	HANDLE m_hSetShowPicThread;
	HANDLE m_hSetShowPicEvent;

	int m_nUpId;

	CStatic m_ShowArea;
	CListCtrl m_liveListListControl;
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_ApplyUploadButton;
	afx_msg void OnBnClickedButtonLiveApplyUpload();
	afx_msg void OnBnClickedButtonLiveExitUpload();
	CButton m_ExitUpload;
};
