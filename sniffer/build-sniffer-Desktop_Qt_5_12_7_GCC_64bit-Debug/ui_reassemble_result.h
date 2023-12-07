/********************************************************************************
** Form generated from reading UI file 'reassemble_result.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REASSEMBLE_RESULT_H
#define UI_REASSEMBLE_RESULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reassemble_result
{
public:
    QTextEdit *reassemble_packet;
    QTableWidget *origin_packet;
    QLabel *label;

    void setupUi(QWidget *reassemble_result)
    {
        if (reassemble_result->objectName().isEmpty())
            reassemble_result->setObjectName(QString::fromUtf8("reassemble_result"));
        reassemble_result->resize(920, 937);
        reassemble_packet = new QTextEdit(reassemble_result);
        reassemble_packet->setObjectName(QString::fromUtf8("reassemble_packet"));
        reassemble_packet->setGeometry(QRect(80, 350, 760, 500));
        reassemble_packet->setStyleSheet(QString::fromUtf8("QTextEdit { font-size: 20px; color: black; }"));
        origin_packet = new QTableWidget(reassemble_result);
        origin_packet->setObjectName(QString::fromUtf8("origin_packet"));
        origin_packet->setGeometry(QRect(80, 20, 760, 241));
        label = new QLabel(reassemble_result);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 300, 311, 31));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);

        retranslateUi(reassemble_result);

        QMetaObject::connectSlotsByName(reassemble_result);
    } // setupUi

    void retranslateUi(QWidget *reassemble_result)
    {
        reassemble_result->setWindowTitle(QApplication::translate("reassemble_result", "REASSEMBLED", nullptr));
        label->setText(QApplication::translate("reassemble_result", "reassembled packet : ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class reassemble_result: public Ui_reassemble_result {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REASSEMBLE_RESULT_H
