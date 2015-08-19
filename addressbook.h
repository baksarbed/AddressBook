#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>


class AddressBook : public QWidget
{
    Q_OBJECT

public:
    explicit AddressBook(QWidget *parent = 0);
    ~AddressBook();

public slots:
    void AddContact();
    void SubmitContact();
    void Cancel();
    void Next();
    void Previous();

private:
    QLineEdit *name_line;
    QTextEdit *address_text;
    QPushButton *add_contact_button;
    QPushButton *submit_button;
    QPushButton *cancel_button;
    QPushButton *next_button;
    QPushButton *previous_button;
    QMap<QString, QString> contacts;
    QString old_name;
    QString old_addres;

};

#endif // ADDRESSBOOK_H
