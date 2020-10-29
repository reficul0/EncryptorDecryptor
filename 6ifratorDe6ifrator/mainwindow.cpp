#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <memory>
#include <experimental/filesystem>

#include "operations.h"
#include "shifrs.h"
#include "cesar_encryptor.h"
#include "cesar_decryptor.h"


#include <QFileDialog>
#include <QString>
#include <QGraphicsScene>
#include <QMessageBox>

template<typename StringT>
bool is_correct_file_name(StringT const &path)
{
    return path.size();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , shift_descr(nullptr)
    , shift(nullptr)
{
    ui->setupUi(this);
    ui->complitionInfo->setHidden(true);

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    for(auto &operation : operations)
        ui->avalilableOperationsBox->addItem( QString::fromUtf8(operation.second.c_str()) );

    for(auto &shifr : shifrs)
        ui->shifrsBox->addItem( QString::fromUtf8(shifr.second.c_str()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runButton_clicked()
{
    ui->complitionInfo->setHidden(true);

    auto source = ui->pathToSourceFIle->text().toStdString();
    auto dest =ui->outFileName->text().toStdString();
    if(!is_correct_file_name(source) || !is_correct_file_name(dest))
        return;

    auto operation = ui->avalilableOperationsBox->currentText().toStdString();

    try
    {
        if(operation == operations[Operations::Shifr])
        {
            std::unique_ptr<Encryptor> encryptor;
            if(ui->shifrsBox->currentText().toStdString() == shifrs[Shifrs::Cesar])
                encryptor = std::make_unique<CesarEncryptor>(shift->value());

            if(encryptor)
            {
                encryptor->encrypt(source, dest);
                ui->complitionInfo->setHidden(false);
            }
        }
        else if(operation == operations[Operations::Deshifr])
        {
            std::unique_ptr<Decryptor> decryptor;
            if(ui->shifrsBox->currentText().toStdString() == shifrs[Shifrs::Cesar])
                decryptor = std::make_unique<CesarDecryptor>(shift->value());

            if(decryptor)
            {
                decryptor->decrypt(source, dest);
                ui->complitionInfo->setHidden(false);
            }
        }
    } catch(std::ios::failure e)
    {
        QMessageBox messageBox;
        messageBox.critical(this,"Ошибка", QString::fromUtf8(e.what()) );
        messageBox.setFixedSize(500,500);
        messageBox.show();
    }
}

void MainWindow::on_browseDestButton_clicked()
{
    auto prew_path = ui->outFileName->text().toStdString();
    std::experimental::filesystem::path prew_dest(prew_path);
    std::experimental::filesystem::path prew_directory(
        prew_path.size()
            ? prew_dest.parent_path().string()
            : QDir::homePath().toStdString()
    );

    QString path = QFileDialog::getOpenFileName(
        this,
        "Укажите исходный файл",
        QString::fromUtf8(prew_directory.string().c_str()),
        "Все файлы (*.*)"
    );

    if(is_correct_file_name(path))
        ui->outFileName->setText(path);
}

void MainWindow::on_browseSourceButton_clicked()
{
    auto prew_path = ui->pathToSourceFIle->text().toStdString();
    std::experimental::filesystem::path prew_dest(prew_path);
    std::experimental::filesystem::path prew_directory(
        prew_path.size()
            ? prew_dest.parent_path().string()
            : QDir::homePath().toStdString()
    );

    QString path = QFileDialog::getOpenFileName(
        this,
        "Укажите исходный файл",
        QString::fromUtf8(prew_directory.string().c_str()),
        "Все файлы (*.*)"
    );

    if(is_correct_file_name(path))
        ui->pathToSourceFIle->setText(path);
}

void MainWindow::on_shifrsBox_currentIndexChanged(const QString &encryption_name)
{
    ui->complitionInfo->setHidden(true);

    if(shift_descr)
        shift_descr->hide();
    if(shift)
        shift->hide();

    if(encryption_name.toStdString() == shifrs[Shifrs::Cesar])
    {
        if(!shift_descr)
        {
            shift_descr = new QLabel("Смещение");
            shift_descr->setStyleSheet(R"(
                                 color: white;
                                 font-family: Rockwell;
                                 font-style: normal;
                                 font-weight: normal;
                                 font-size: 15px;
                                 line-height: 56px;
                                 )");
            ui->encryptionSettingsLayuot->addWidget(shift_descr);
        }
        if(!shift)
        {
            shift = new QDoubleSpinBox();
            shift->setMinimum(1);
            shift->setStyleSheet(R"(position: absolute;
                                  width: 778px;
                                  height: 85px;
                                  left: 338px;
                                  top: 301px;

                                  background: #B0B7F8;
                                  color : white;
                                  border-radius: 10px;

                                  border: 1px solid gray;
                                  padding-left: 30px;

                                  font-family: Rockwell;
                                  font-style: normal;
                                  font-weight: normal;
                                  font-size: 15px;
                                  line-height: 56px;)");
            shift->setDecimals(0);
            ui->encryptionSettingsLayuot->addWidget(shift);
        }

        shift_descr->show();
        QObject::connect(shift, SIGNAL(valueChanged(double)), this, SLOT(on_shift_ValueChanged(double)));
        shift->show();
    }
}

void MainWindow::on_exitButton_4_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pathToSourceFIle_textChanged(const QString &arg1)
{
    ui->complitionInfo->setHidden(true);
}

void MainWindow::on_outFileName_textChanged(const QString &arg1)
{
    ui->complitionInfo->setHidden(true);
}

void MainWindow::on_avalilableOperationsBox_currentIndexChanged(const QString &arg1)
{
    ui->complitionInfo->setHidden(true);
}

void MainWindow::on_shift_ValueChanged(double val)
{
    ui->complitionInfo->setHidden(true);
}
