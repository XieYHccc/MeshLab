#include "MeshParamWidget.h"

MeshParamWidget::MeshParamWidget(QWidget *parent)
	: QWidget(parent)
{
	CreateTabWidget();
	CreateLayout();
}

MeshParamWidget::~MeshParamWidget()
{
}

void MeshParamWidget::CreateTabWidget(void)
{
	pbPrintInfo = new QPushButton(tr("Print Mesh Info"));
	connect(pbPrintInfo, SIGNAL(clicked()), SIGNAL(PrintInfoSignal()));
	pbShowSP = new QPushButton(tr("Show"));
	connect(pbShowSP, SIGNAL(clicked()), SLOT(SendFindSPSignal()));
	pbShowCurv = new QPushButton(tr("Show Curvature"));
	connect(pbShowCurv, SIGNAL(clicked()), SIGNAL(ShowCurvatureSignal()));
	pbFindMST = new QPushButton(tr("Find"));
	lShortpath = new QLabel(tr("Find Shortest Path"));
	lBeginpointidx = new QLabel(tr("Begin Point Index:"));
	leBeginpointidx = new QLineEdit();
	lEndpointidx = new QLabel(tr("End Point Index:"));
	leEndpointidx = new QLineEdit();
	QFont fLabel;
	fLabel.setBold(true);
	fLabel.setPointSize(13);
	lShortpath->setFont(fLabel);
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(pbPrintInfo);
	layout->addWidget(pbShowCurv);
	layout->addStretch();
	layout->addWidget(lShortpath);
	layout->addWidget(lBeginpointidx);
	layout->addWidget(leBeginpointidx);
	layout->addWidget(lEndpointidx);
	layout->addWidget(leEndpointidx);
	layout->addWidget(pbShowSP);
	wParam = new QWidget();
	wParam->setLayout(layout);
	saParam = new QScrollArea();
	saParam->setFocusPolicy(Qt::NoFocus);
	saParam->setFrameStyle(QFrame::NoFrame);
	saParam->setWidget(wParam);
	saParam->setWidgetResizable(true);
}

void MeshParamWidget::CreateLayout(void)
{
	twParam = new QTabWidget();
	twParam->addTab(saParam, "Tab");
	QGridLayout *layout = new QGridLayout();
	layout->addWidget(twParam, 0, 0, 1, 1);
	this->setLayout(layout);
}

void MeshParamWidget::SendFindSPSignal()
{
	int sp = leBeginpointidx->text().toInt();
	int ep = leEndpointidx->text().toInt();
	emit FindSPSignal(sp, ep);
}
