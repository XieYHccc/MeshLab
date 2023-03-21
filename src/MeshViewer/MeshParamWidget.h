#pragma once

#include <QWidget>
#include <QtGui>
#include <QtWidgets>

class MeshParamWidget : public QWidget
{
	Q_OBJECT

public:
	MeshParamWidget(QWidget *parent = 0);
	~MeshParamWidget(void);
private:
	void CreateTabWidget(void);
	void CreateLayout(void);
signals:
	void ShowCurvatureSignal();
	void FindSPSignal(int, int);
	void PrintInfoSignal();

private slots:
	void SendFindSPSignal();

private:
	QTabWidget *twParam;
	QWidget *wParam;
	QScrollArea *saParam;
	QPushButton *pbPrintInfo;
	QPushButton* pbShowSP;
	QPushButton* pbFindMST;
	QPushButton* pbShowCurv;
	QLabel* lShortpath;
	QLabel* lBeginpointidx;
	QLabel* lEndpointidx;
	QLineEdit* leEndpointidx;
	QLineEdit* leBeginpointidx;

};
