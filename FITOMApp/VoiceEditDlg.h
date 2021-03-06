#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "TestButton.h"
#include "SoundDev.h"
#include "MIDI.h"
#include "GridCtrl.h"

// CVoiceEditDlg ダイアログ

class CVoiceEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVoiceEditDlg)

public:
	CVoiceEditDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CVoiceEditDlg();

	// ダイアログ データ
	enum { IDD = IDD_DLG_VEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	CFITOM* theFitom;
	BOOL bInit;
	BOOL bModified;
	int theDevice;
	int theBank;
	int theProg;
	FMVOICE theVoice;
	CInstCh* pICh;

	struct VoiceItem {
		LPCTSTR caption;
		DWORD edittype;
		int min;
		int max;
		DWORD mask;
		void (CVoiceEditDlg::*pSetter)(int op, int val);
		int (CVoiceEditDlg::*pGetter)(int op);
	};
	int editting_op;
	VoiceItem* editting_item;
	static VoiceItem commonItem[];
	static VoiceItem operatorItem[];
	CListCtrl* lstctls[5];

	void UpdateListCtrl(int op, BOOL bInit=FALSE);
	void UpdateVoiceView();
	LRESULT OnDblclkListParam(LPNMITEMACTIVATE pNMLV, int op);

	//Getter
	int GetAL(int op) { return theVoice.AL; };
	int GetAL1(int op) { return theVoice.AL & 0x1; };
	int GetAL3(int op) { return theVoice.AL & 0x7; };
	int GetAL4(int op) { return theVoice.AL & 0xf; };
	int GetFB(int op) { return theVoice.FB; };
	int GetFB1(int op) { return theVoice.FB & 0x7; };
	int GetFB2(int op) { return theVoice.FB >> 3; };
	int GetNE(int op) { return theVoice.AL >> 3; };
	int GetNFreq(int op) { return theVoice.NFQ; };
	int GetNFreq2(int op) { return (theVoice.NFQ << 3) | (theVoice.FB & 0x7); };
	int GetAMS(int op) { return theVoice.AMS; };
	int GetPMS(int op) { return theVoice.PMS; };
	int GetLFODepth(int op) { int ldep = ((theVoice.LDM << 7) | theVoice.LDL); return (ldep > 8191) ? (ldep - 16384) : ldep; };
	int GetLFOFreq(int op) { return theVoice.LFO; };
	int GetLFOWave(int op) { return theVoice.LWF; };
	int GetLFORate(int op) { return theVoice.LFR; };
	int GetLFODelay(int op) { return theVoice.LFD; };
	int GetAR(int op) { return theVoice.op[op].AR; };
	int GetDR(int op) { return theVoice.op[op].DR; };
	int GetSR(int op) { return theVoice.op[op].SR; };
	int GetSL(int op) { return theVoice.op[op].SL; };
	int GetRR(int op) { return theVoice.op[op].RR; };
	int GetRV(int op) { return theVoice.op[op].REV; };
	int GetTL(int op) { return theVoice.op[op].TL; };
	int GetML(int op) { return theVoice.op[op].MUL; };
	int GetDT1(int op) { return theVoice.op[op].DT1; };
	int GetDT2(int op) { return theVoice.op[op].DT2; };
	int GetPDT(int op) { return ((GetDT2(op) << 7) | (GetDT1(op))) - ((GetDT2(op) & 0x40) ? 8192 : 0); };
	int GetAME(int op) { return theVoice.op[op].AM; };
	int GetVIB(int op) { return theVoice.op[op].VIB; };
	int GetEG(int op) { return theVoice.op[op].EGT; };
	int GetEGS(int op) { return theVoice.op[op].EGS; };
	int GetKSL(int op) { return theVoice.op[op].KSL; };
	int GetKSR(int op) { return theVoice.op[op].KSR; };
	int GetWS(int op) { return theVoice.op[op].WS; };
	int GetFix(int op) { return (1 << theVoice.op[op].DT1) * ((theVoice.op[op].MUL << 4) | theVoice.op[op].DT2); };
	int GetOPLFOFreq(int op) { return theVoice.op[op].SLF; };
	int GetOPLFODepth(int op) { return (theVoice.op[op].SLD > 63) ? (theVoice.op[op].SLD - 128) : theVoice.op[op].SLD; };
	int GetOPLFOWave(int op) { return theVoice.op[op].SLW; };
	int GetOPLFODelay(int op) { return theVoice.op[op].SLY; };
	int GetOPLFORate(int op) { return theVoice.op[op].SLR; };
	//Setter
	void SetAL(int op, int val) { theVoice.AL = val; };
	void SetAL3(int op, int val) { theVoice.AL = val | (GetNE(op) ? 0x8 : 0); };
	void SetROMTN(int op, int val) { theVoice.AL = val ? (val | 64) : 0; };
	void SetFB(int op, int val) { theVoice.FB = val; };
	void SetFB1(int op, int val) { theVoice.FB = (theVoice.FB & 0x78) | (val & 0x7); };
	void SetFB2(int op, int val) { theVoice.FB = (theVoice.FB & 0x47) | ((val & 0x7) << 3); };
	void SetNE(int op, int val) { theVoice.AL = (theVoice.AL & 0x77) | (val ? 8 : 0); };
	void SetNFreq(int op, int val) { theVoice.NFQ = val; };
	void SetNFreq2(int op, int val) { theVoice.NFQ = (val >> 3); theVoice.FB = (val & 0x7); };
	void SetAMS(int op, int val) { theVoice.AMS = val; };
	void SetPMS(int op, int val) { theVoice.PMS = val; };
	void SetLFODepth(int op, int val) { theVoice.LDM = ((val >> 7) & 0x7f); theVoice.LDL = (val & 0x7f); };
	void SetLFOFreq(int op, int val) { theVoice.LFO = val; };
	void SetLFOWave(int op, int val) { theVoice.LWF = val; };
	void SetLFORate(int op, int val) { theVoice.LFR = val; };
	void SetLFODelay(int op, int val) { theVoice.LFD = val; };
	void SetAR(int op, int val) { theVoice.op[op].AR = val; };
	void SetDR(int op, int val) { theVoice.op[op].DR = val; };
	void SetSR(int op, int val) { theVoice.op[op].SR = val; };
	void SetRR(int op, int val) { theVoice.op[op].RR = val; };
	void SetSL(int op, int val) { theVoice.op[op].SL = val; };
	void SetRV(int op, int val) { theVoice.op[op].REV = val; };
	void SetTL(int op, int val) { theVoice.op[op].TL = val; };
	void SetML(int op, int val) { theVoice.op[op].MUL = val; };
	void SetDT1(int op, int val) { theVoice.op[op].DT1 = val; };
	void SetDT2(int op, int val) { theVoice.op[op].DT2 = val; };
	void SetPDT(int op, int val) { theVoice.op[op].DT2 = ((val >> 7) & 0x7f); theVoice.op[op].DT1 = (val & 0x7f); };
	void SetAME(int op, int val) { theVoice.op[op].AM = val; };
	void SetVIB(int op, int val) { theVoice.op[op].VIB = val; };
	void SetEG(int op, int val) { theVoice.op[op].EGT = val; };
	void SetEGS(int op, int val) { theVoice.op[op].EGS = val; };
	void SetKSL(int op, int val) { theVoice.op[op].KSL = val; };
	void SetKSR(int op, int val) { theVoice.op[op].KSR = val; };
	void SetWS(int op, int val) { theVoice.op[op].WS = val; };
	void SetOPLFOFreq(int op, int val) { theVoice.op[op].SLF = val; };
	void SetOPLFODepth(int op, int val) { theVoice.op[op].SLD = (val & 0x7f); };
	void SetOPLFOWave(int op, int val) { theVoice.op[op].SLW = val; };
	void SetOPLFODelay(int op, int val) { theVoice.op[op].SLY = val; };
	void SetOPLFORate(int op, int val) { theVoice.op[op].SLR = val; };

	DECLARE_MESSAGE_MAP()
public:
	void SetDevice(int dev);
	void SetBank(int bank);
	void SetProg(int prog);
	CListCtrl lstCommon;
	CListCtrl lstOper1;
	CListCtrl lstOper2;
	CListCtrl lstOper3;
	CListCtrl lstOper4;
	afx_msg void OnTestButtonDown();
	afx_msg void OnTestButtonUp();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CEdit edtName;
	afx_msg void OnBnClickedButtonPick();
	afx_msg void OnUpdateEditName();
	CEdit edtDevice;
	CEdit edtBank;
	CEdit edtProg;
	CTestButton btnTest;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	CSpinButtonCtrl spnVelocity;
	CSpinButtonCtrl spnNote;
	afx_msg void OnDblclkListCparam(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListOpparam1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListOpparam2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListOpparam3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListOpparam4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditInplace();
	afx_msg void OnKillfocusEditInplace();
	afx_msg void OnDeltaposSpinInplace(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnClickedButtonBank();
	CEdit edtInplace;
	CSpinButtonCtrl spnInplace;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();
};
