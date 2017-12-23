#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListView>
#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QFont>
#include <QStringListModel>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

    QStringListModel *fontModel;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void searchFont();  // 查找字体并生成model，显示在QListView中

    QPushButton *openImageBtn;
    QLineEdit *inputLineEdit;
    QListView *fontListView;
    QSpinBox *fontSizeBox;
    QLabel *fontShowImage;
    QGridLayout *m_layout;
    QFont m_font;   // 当前字体


private slots:
    void changeFontText(const QString &text);   // 改变先是内容，来自inputLineEdit
    void changeFontSize(int i);  // 改变字体大小，来自fontSizeBox
    void changeFontFamily(const QModelIndex &index);  // 改变字体
};

#endif // MAINWINDOW_H
