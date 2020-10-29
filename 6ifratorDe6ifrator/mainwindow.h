#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QDoubleSpinBox>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_runButton_clicked();

    void on_browseDestButton_clicked();

    void on_browseSourceButton_clicked();

    void on_exitButton_4_clicked();

    void on_shifrsBox_currentIndexChanged(const QString &arg1);

    void on_pathToSourceFIle_textChanged(const QString &arg1);

    void on_outFileName_textChanged(const QString &arg1);

    void on_avalilableOperationsBox_currentIndexChanged(const QString &arg1);

    void on_shift_ValueChanged(double val);
private:
    Ui::MainWindow *ui;

    // Цезарь
    QLabel *shift_descr;
    QDoubleSpinBox *shift;
};
#endif // MAINWINDOW_H
