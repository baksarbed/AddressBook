#include "addressbook.h"
#include "ui_mainwindow.h"

AddressBook::AddressBook(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *main_layout = new QGridLayout;
    QVBoxLayout *button_layout = new QVBoxLayout;
    QHBoxLayout *button_layout2 = new QHBoxLayout;
    QLabel *address_label = new QLabel(tr("Address:"));
    QLabel *name_label = new QLabel(tr("Name:"));

    main_layout->addWidget(name_label, 0, 0);

    name_line = new QLineEdit;
    main_layout->addWidget(name_line, 0, 1);

    main_layout->addWidget(address_label, 1, 0, Qt::AlignTop);

    address_text = new QTextEdit;
    main_layout->addWidget(address_text, 1, 1);

    add_contact_button = new QPushButton(tr("&Add"));
    add_contact_button->show();

    submit_button = new QPushButton(tr("&Submit"));
    submit_button->hide();

    cancel_button = new QPushButton(tr("&Cancel"));
    cancel_button->hide();

    next_button = new QPushButton(tr("&Next"));
    next_button->setEnabled(false);

    previous_button = new QPushButton(tr("&Previous"));
    previous_button->setEnabled(false);

    name_line->setReadOnly(true);
    address_text->setReadOnly(true);

    connect(add_contact_button, SIGNAL(clicked(bool)), this, SLOT(AddContact()));
    connect(submit_button, SIGNAL(clicked(bool)), this, SLOT(SubmitContact()));
    connect(cancel_button, SIGNAL(clicked(bool)), this, SLOT(Cancel()));
    connect(next_button, SIGNAL(clicked(bool)), this, SLOT(Next()));
    connect(previous_button, SIGNAL(clicked(bool)), this, SLOT(Previous()));

    button_layout->addWidget(add_contact_button, Qt::AlignTop);
    button_layout->addWidget(submit_button);
    button_layout->addWidget(cancel_button);
    button_layout->addStretch();

    button_layout2->addWidget(previous_button);
    button_layout2->addWidget(next_button);

    main_layout->addLayout(button_layout, 1, 2);
    main_layout->addLayout(button_layout2, 2, 1);

    setLayout(main_layout);
    setWindowTitle(tr("Address book"));
}

AddressBook::~AddressBook()
{
    // delete parent;
}

void AddressBook::AddContact()
{
    old_name = name_line->text();
    old_addres = address_text->toPlainText();

    name_line->clear();
    address_text->clear();

    name_line->setReadOnly(false);
    name_line->setFocus(Qt::OtherFocusReason);
    address_text->setReadOnly(false);

    add_contact_button->setEnabled(false);
    next_button->setEnabled(false);
    previous_button->setEnabled(false);
    submit_button->show();
    cancel_button->show();
}

void AddressBook::SubmitContact()
{
    QString name = name_line->text();
    QString address = address_text->toPlainText();
    int number;
    if (name.isEmpty() || address.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
                                 tr("Please enter a name and addres."));
        return;
    }
    if (!contacts.contains(name)) {
        contacts.insert(name,address);
        QMessageBox::information(this, tr("Add successful"),
                                 tr("\"%1\" has beed added to your address book.").arg(name));
        //  return;
    }
    number = contacts.size();
    next_button->setEnabled(number > 1);
    previous_button->setEnabled(number > 1);
    if (contacts.isEmpty()) {
        name_line->clear();
        address_text->clear();
    }
    name_line->setReadOnly(true);
    address_text->setReadOnly(true);
    add_contact_button->setEnabled(true);
    submit_button->hide();
    cancel_button->hide();
}

void AddressBook::Cancel()
{
    name_line->setText(old_name);
    name_line->setReadOnly(true);
    address_text->setText(old_addres);
    address_text->setReadOnly(true);
    add_contact_button->setEnabled(true);
    submit_button->hide();
    cancel_button->hide();
}

void AddressBook::Next()
{
    QString name = name_line->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if (i != contacts.end())
        i++;

    if (i == contacts.end())
        i = contacts.begin();
    name_line->setText(i.key());
    address_text->setText(i.value());
}

void AddressBook::Previous()
{
    QString name = name_line->text();
    QMap <QString, QString>::iterator i = contacts.find(name);
    if (i == contacts.end()) {
        name_line->clear();
        address_text->clear();
        return;
    }
    if (i == contacts.begin())
        i = contacts.end();

    i--;
    name_line->setText(i.key());
    address_text->setText(i.key());
}


