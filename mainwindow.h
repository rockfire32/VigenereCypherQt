#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>

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
    void on_button_encrypt_clicked();
    void on_button_decrypt_clicked();

private:
    QString text, key;
    Ui::MainWindow *ui;

    void mod(QString &text, QString &key);
    void encrypt(QString &text, QString &key);
    void decrypt(QString &text, QString &key);

    bool is_en(const QChar &c);

    const uint8_t  EN_SIZE = 26;
    const uint8_t  RU_SIZE = 32;

    const uint16_t RU_FIRST_SYMBOL = 0x410;
    const uint16_t EN_FIRST_SYMBOL = 0x41;

    const uint16_t EN_LAST_SYMBOL  = 0x5A;
};
#endif // MAINWINDOW_H
