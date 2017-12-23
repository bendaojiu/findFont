#include <QFontDatabase>
#include <QItemSelection>
#include <QKeyEvent>
#include <QDebug>
#include "mainwindow.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    openImageBtn = new QPushButton(tr("打开文件"));
    inputLineEdit = new QLineEdit();
    connect(inputLineEdit, &QLineEdit::textChanged, this, &MainWidget::changeFontText);
    inputLineEdit->setPlaceholderText(tr("此处输入字符"));    // 设置默认为空时显示的灰色字符
    fontListView = new QListView();
    fontListView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // 设置不可编辑
    fontListView->setSelectionMode(QAbstractItemView::SingleSelection); // 设置成单选
    fontListView->installEventFilter(this);
    connect(fontListView, &QListView::pressed, this, &MainWidget::changeFontFamily);

    fontSizeBox = new QSpinBox();   // 调整字体大小的
    fontSizeBox->setMinimum(1);
    fontSizeBox->setMaximum(80);    // 暂时瞎设两值
    fontSizeBox->setValue(20);  // 默认值先是20
    connect(fontSizeBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWidget::changeFontSize);
    fontShowImage = new QLabel();

    m_layout = new QGridLayout(this);
    m_layout->addWidget(openImageBtn, 0, 1, 1, 1);
    m_layout->addWidget(inputLineEdit, 0, 3, 1, 4);
    m_layout->addWidget(fontListView, 1, 0, 7, 3);
    m_layout->addWidget(fontSizeBox, 1, 3, 1, 1);
    m_layout->addWidget(fontShowImage, 2, 3, 6, 4);

    fontModel = new QStringListModel();
    searchFont();

    this->resize(800, 600);
}

MainWidget::~MainWidget()
{

}

bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == fontListView)
    {
        if (event->type() == QEvent::KeyPress)
        {
//            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//            switch (keyEvent->key())
//            {
//            case Qt::Key_Up:
//                if (this->fontListView->currentIndex().row() > 0)
//                {
//                    this->fontListView->setCurrentIndex(this->fontListView->indexAt(QPoint(this->fontListView->currentIndex().row() - 1,
//                                                                                           this->fontListView->currentIndex().column())));
//                }
//                break;
//            }
            changeFontFamily(this->fontListView->currentIndex());
        }
    }
}

//void MainWidget::keyPressEvent(QKeyEvent *event)
//{
//    switch (event->key())
//    {
//    case Qt::Key_Up:
//        if (this->fontListView->currentIndex().row() > 0)
//        {
//            this->fontListView->setCurrentIndex(this->fontListView->indexAt(QPoint(this->fontListView->currentIndex().row() - 1,
//                                                                                   this->fontListView->currentIndex().column())));
//        }
//        break;
//    }
//    changeFontFamily(this->fontListView->currentIndex());
//}

void MainWidget::searchFont()
{
    QFontDatabase fontData;
    this->fontModel->setStringList(fontData.families());
    this->fontListView->setModel(this->fontModel);
    emit this->fontListView->setCurrentIndex(this->fontListView->indexAt(QPoint(0, 0)));    // 设置默认选中第一行
    this->m_font.setFamily(this->fontModel->data(this->fontListView->currentIndex()).toString());   // 初始化字体为第一项
    this->m_font.setPixelSize(this->fontSizeBox->text().toInt());   // 初始化字体大小
}

void MainWidget::changeFontText(const QString &text)
{
    this->fontShowImage->setFont(this->m_font);
    this->fontShowImage->setText(text);
}

void MainWidget::changeFontSize(int i)
{
    this->m_font.setPixelSize(i);
    this->fontShowImage->setFont(this->m_font);
}

void MainWidget::changeFontFamily(const QModelIndex &index)
{
    this->m_font.setFamily(this->fontModel->data(index).toString());
    this->fontShowImage->setFont(this->m_font);
    qDebug() << "改变字体为" << this->m_font.family();
}
