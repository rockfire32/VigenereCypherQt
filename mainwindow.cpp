#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_encrypt_clicked()
{
    text = ui->text_line->text();
    key  = ui->key_line->text();

    mod(text, key);
    encrypt(text, key);

    ui->text_line->setText(text);
    ui->key_line->setText(key);
}

void MainWindow::on_button_decrypt_clicked()
{
    text = ui->text_line->text();
    key  = ui->key_line->text();

    mod(text, key);
    decrypt(text, key);

    ui->text_line->setText(text);
    ui->key_line->setText(key);
}

//   --- Уравниваем длины ключа и текста ---
void MainWindow::mod(QString &text, QString &key)
{
    if ( text.size() > key.size() )
    {
        for ( int i = 0; i < key.size(); ++i )
        {
            if ( key.size() == i ) {
                i = 0;
            }

            if ( text.size() == key.size() ) {
                break;
            }

            key.append(key.at(i));
        }
    }
    else if ( text.size() < key.size() ) {
        key.resize(text.size());
    }

    text = text.toUpper();
    key  = key.toUpper();
}

void MainWindow::encrypt(QString &text, QString &key)
{
    int language_length = EN_SIZE;
    uint16_t first_symbol = EN_FIRST_SYMBOL;
    QString encrypted;

    if ( !is_en(text[0]) )
    {
        first_symbol = RU_FIRST_SYMBOL;
        language_length = RU_SIZE;
    }

    for ( int i = 0; i < text.size(); i++ ) {
        encrypted.append((( text[i].unicode() + key[i].unicode() ) % language_length) + first_symbol );
    }

    text = encrypted;
}

void MainWindow::decrypt(QString &text, QString &key)
{
    int language_length = EN_SIZE;
    uint16_t first_symbol = EN_FIRST_SYMBOL;
    QString decrypted;

    if ( !is_en(text[0]) )
    {
        first_symbol = RU_FIRST_SYMBOL;
        language_length = RU_SIZE;
    }

    for ( int i = 0; i < text.size(); i++ ) {
        decrypted.append((( text[i].unicode() + language_length - key[i].unicode() ) % language_length + first_symbol ));
    }

    text = decrypted;
}

bool MainWindow::is_en(const QChar &c)
{
    if ( c.unicode() >= EN_FIRST_SYMBOL && c.unicode() <= EN_LAST_SYMBOL ) {
        return true;
    }

    return false;
}
