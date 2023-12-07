/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QComboBox *choose_device;
    QLabel *label;
    QPushButton *capture_start;
    QTreeWidget *basic_information;
    QTreeView *specific_information;
    QPushButton *capture_stop;
    QTextEdit *show_packet;
    QPushButton *result_save;
    QPushButton *packet_reassemble;
    QCheckBox *tcp;
    QCheckBox *udp;
    QCheckBox *icmp;
    QCheckBox *arp;
    QCheckBox *other;
    QLineEdit *src_ip;
    QLineEdit *dst_ip;
    QPushButton *packet_filter;
    QPushButton *exit;
    QLabel *label_2;
    QLabel *label_3;
    QCheckBox *igmp;
    QCheckBox *ipv6;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1600, 1300);
        Widget->setMinimumSize(QSize(1600, 1300));
        Widget->setMaximumSize(QSize(1600, 1300));
        QFont font;
        font.setFamily(QString::fromUtf8("URW Gothic L"));
        Widget->setFont(font);
        choose_device = new QComboBox(Widget);
        choose_device->setObjectName(QString::fromUtf8("choose_device"));
        choose_device->setGeometry(QRect(360, 30, 200, 50));
        choose_device->setMinimumSize(QSize(200, 50));
        choose_device->setMaximumSize(QSize(200, 50));
        choose_device->setStyleSheet(QString::fromUtf8("QComboBox, QAbstractItemView { font-size: 22px; }"));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 30, 400, 50));
        label->setMinimumSize(QSize(200, 50));
        label->setMaximumSize(QSize(400, 50));
        QFont font1;
        font1.setFamily(QString::fromUtf8("mry_KacstQurn"));
        font1.setPointSize(20);
        label->setFont(font1);
        capture_start = new QPushButton(Widget);
        capture_start->setObjectName(QString::fromUtf8("capture_start"));
        capture_start->setGeometry(QRect(200, 110, 150, 60));
        capture_start->setMinimumSize(QSize(150, 60));
        capture_start->setMaximumSize(QSize(150, 60));
        QFont font2;
        font2.setFamily(QString::fromUtf8("URW Gothic L"));
        font2.setPointSize(18);
        font2.setBold(true);
        font2.setWeight(75);
        capture_start->setFont(font2);
        capture_start->setStyleSheet(QString::fromUtf8(""));
        basic_information = new QTreeWidget(Widget);
        QFont font3;
        font3.setPointSize(18);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(7, Qt::AlignLeading|Qt::AlignVCenter);
        __qtreewidgetitem->setFont(7, font3);
        __qtreewidgetitem->setTextAlignment(6, Qt::AlignLeading|Qt::AlignVCenter);
        __qtreewidgetitem->setFont(6, font3);
        __qtreewidgetitem->setTextAlignment(5, Qt::AlignLeading|Qt::AlignVCenter);
        __qtreewidgetitem->setFont(5, font3);
        __qtreewidgetitem->setTextAlignment(4, Qt::AlignLeading|Qt::AlignVCenter);
        __qtreewidgetitem->setFont(4, font3);
        __qtreewidgetitem->setTextAlignment(3, Qt::AlignLeading|Qt::AlignVCenter);
        __qtreewidgetitem->setFont(3, font3);
        __qtreewidgetitem->setTextAlignment(2, Qt::AlignLeading|Qt::AlignVCenter);
        __qtreewidgetitem->setFont(2, font3);
        __qtreewidgetitem->setTextAlignment(1, Qt::AlignLeading|Qt::AlignVCenter);
        __qtreewidgetitem->setFont(1, font3);
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignLeading|Qt::AlignVCenter);
        __qtreewidgetitem->setFont(0, font3);
        basic_information->setHeaderItem(__qtreewidgetitem);
        basic_information->setObjectName(QString::fromUtf8("basic_information"));
        basic_information->setGeometry(QRect(50, 290, 1500, 500));
        basic_information->setMinimumSize(QSize(1500, 200));
        basic_information->setMaximumSize(QSize(1500, 500));
        basic_information->setStyleSheet(QString::fromUtf8(""));
        specific_information = new QTreeView(Widget);
        specific_information->setObjectName(QString::fromUtf8("specific_information"));
        specific_information->setGeometry(QRect(50, 830, 700, 441));
        specific_information->setMinimumSize(QSize(700, 200));
        specific_information->setMaximumSize(QSize(700, 500));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Ubuntu"));
        specific_information->setFont(font4);
        specific_information->setStyleSheet(QString::fromUtf8(""));
        capture_stop = new QPushButton(Widget);
        capture_stop->setObjectName(QString::fromUtf8("capture_stop"));
        capture_stop->setGeometry(QRect(410, 110, 150, 60));
        capture_stop->setMinimumSize(QSize(150, 60));
        capture_stop->setMaximumSize(QSize(150, 60));
        capture_stop->setFont(font2);
        show_packet = new QTextEdit(Widget);
        show_packet->setObjectName(QString::fromUtf8("show_packet"));
        show_packet->setGeometry(QRect(850, 830, 700, 441));
        show_packet->setMinimumSize(QSize(700, 200));
        show_packet->setMaximumSize(QSize(700, 500));
        show_packet->setStyleSheet(QString::fromUtf8("QTextEdit { font-size: 20px; color: black; }"));
        result_save = new QPushButton(Widget);
        result_save->setObjectName(QString::fromUtf8("result_save"));
        result_save->setGeometry(QRect(1040, 110, 150, 60));
        result_save->setMinimumSize(QSize(150, 60));
        result_save->setMaximumSize(QSize(150, 60));
        result_save->setFont(font2);
        packet_reassemble = new QPushButton(Widget);
        packet_reassemble->setObjectName(QString::fromUtf8("packet_reassemble"));
        packet_reassemble->setGeometry(QRect(830, 110, 150, 60));
        packet_reassemble->setMinimumSize(QSize(150, 60));
        packet_reassemble->setMaximumSize(QSize(150, 60));
        packet_reassemble->setFont(font2);
        tcp = new QCheckBox(Widget);
        tcp->setObjectName(QString::fromUtf8("tcp"));
        tcp->setGeometry(QRect(650, 40, 100, 30));
        tcp->setMinimumSize(QSize(100, 30));
        tcp->setMaximumSize(QSize(100, 30));
        tcp->setStyleSheet(QString::fromUtf8("QCheckBox::indicator { width: 30px; height: 30px; }\n"
"QCheckBox { font-size: 20px; color: black; font-weight: bold; font-family: \"Arial\"; }\n"
""));
        tcp->setIconSize(QSize(50, 50));
        udp = new QCheckBox(Widget);
        udp->setObjectName(QString::fromUtf8("udp"));
        udp->setGeometry(QRect(770, 40, 100, 30));
        udp->setMinimumSize(QSize(100, 30));
        udp->setMaximumSize(QSize(100, 30));
        udp->setStyleSheet(QString::fromUtf8("QCheckBox::indicator { width: 30px; height: 30px; }\n"
"QCheckBox { font-size: 20px; color: black; font-weight: bold; font-family: \"Arial\"; }\n"
""));
        icmp = new QCheckBox(Widget);
        icmp->setObjectName(QString::fromUtf8("icmp"));
        icmp->setGeometry(QRect(890, 40, 100, 30));
        icmp->setMinimumSize(QSize(100, 30));
        icmp->setMaximumSize(QSize(100, 30));
        icmp->setStyleSheet(QString::fromUtf8("QCheckBox::indicator { width: 30px; height: 30px; }\n"
"QCheckBox { font-size: 20px; color: black; font-weight: bold; font-family: \"Arial\"; }\n"
""));
        arp = new QCheckBox(Widget);
        arp->setObjectName(QString::fromUtf8("arp"));
        arp->setGeometry(QRect(1250, 40, 100, 30));
        arp->setMinimumSize(QSize(100, 30));
        arp->setMaximumSize(QSize(100, 30));
        arp->setStyleSheet(QString::fromUtf8("QCheckBox::indicator { width: 30px; height: 30px; }\n"
"QCheckBox { font-size: 20px; color: black; font-weight: bold; font-family: \"Arial\"; }\n"
""));
        other = new QCheckBox(Widget);
        other->setObjectName(QString::fromUtf8("other"));
        other->setGeometry(QRect(1370, 40, 120, 30));
        other->setMinimumSize(QSize(120, 30));
        other->setMaximumSize(QSize(120, 30));
        other->setStyleSheet(QString::fromUtf8("QCheckBox::indicator { width: 30px; height: 30px; }\n"
"QCheckBox { font-size: 20px; color: black; font-weight: bold; font-family: \"Arial\"; }\n"
""));
        src_ip = new QLineEdit(Widget);
        src_ip->setObjectName(QString::fromUtf8("src_ip"));
        src_ip->setGeometry(QRect(440, 200, 301, 61));
        src_ip->setStyleSheet(QString::fromUtf8("QLineEdit { font-size: 24px; }"));
        dst_ip = new QLineEdit(Widget);
        dst_ip->setObjectName(QString::fromUtf8("dst_ip"));
        dst_ip->setGeometry(QRect(1050, 200, 301, 61));
        dst_ip->setStyleSheet(QString::fromUtf8("QLineEdit { font-size: 24px; }"));
        packet_filter = new QPushButton(Widget);
        packet_filter->setObjectName(QString::fromUtf8("packet_filter"));
        packet_filter->setGeometry(QRect(620, 110, 150, 60));
        packet_filter->setMinimumSize(QSize(150, 60));
        packet_filter->setMaximumSize(QSize(150, 60));
        packet_filter->setFont(font2);
        exit = new QPushButton(Widget);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(1250, 110, 150, 60));
        exit->setMinimumSize(QSize(150, 60));
        exit->setMaximumSize(QSize(150, 60));
        exit->setFont(font2);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(240, 200, 261, 50));
        label_2->setMinimumSize(QSize(200, 50));
        label_2->setMaximumSize(QSize(400, 50));
        QFont font5;
        font5.setFamily(QString::fromUtf8("KacstQurn"));
        font5.setPointSize(19);
        label_2->setFont(font5);
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(800, 200, 261, 50));
        label_3->setMinimumSize(QSize(200, 50));
        label_3->setMaximumSize(QSize(400, 50));
        label_3->setFont(font5);
        igmp = new QCheckBox(Widget);
        igmp->setObjectName(QString::fromUtf8("igmp"));
        igmp->setGeometry(QRect(1010, 40, 120, 30));
        igmp->setMinimumSize(QSize(120, 30));
        igmp->setMaximumSize(QSize(120, 30));
        igmp->setStyleSheet(QString::fromUtf8("QCheckBox::indicator { width: 30px; height: 30px; }\n"
"QCheckBox { font-size: 20px; color: black; font-weight: bold; font-family: \"Arial\"; }\n"
""));
        ipv6 = new QCheckBox(Widget);
        ipv6->setObjectName(QString::fromUtf8("ipv6"));
        ipv6->setGeometry(QRect(1130, 40, 120, 30));
        ipv6->setMinimumSize(QSize(120, 30));
        ipv6->setMaximumSize(QSize(120, 30));
        ipv6->setStyleSheet(QString::fromUtf8("QCheckBox::indicator { width: 30px; height: 30px; }\n"
"QCheckBox { font-size: 20px; color: black; font-weight: bold; font-family: \"Arial\"; }\n"
""));
        specific_information->raise();
        choose_device->raise();
        label->raise();
        capture_start->raise();
        basic_information->raise();
        capture_stop->raise();
        show_packet->raise();
        result_save->raise();
        packet_reassemble->raise();
        tcp->raise();
        udp->raise();
        icmp->raise();
        arp->raise();
        other->raise();
        src_ip->raise();
        dst_ip->raise();
        packet_filter->raise();
        exit->raise();
        label_2->raise();
        label_3->raise();
        igmp->raise();
        ipv6->raise();

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "SNIFFER", nullptr));
        label->setText(QApplication::translate("Widget", "Select Network Card :", nullptr));
        capture_start->setText(QApplication::translate("Widget", "Start", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = basic_information->headerItem();
        ___qtreewidgetitem->setText(7, QApplication::translate("Widget", "Destination IP", nullptr));
        ___qtreewidgetitem->setText(6, QApplication::translate("Widget", "Source IP", nullptr));
        ___qtreewidgetitem->setText(5, QApplication::translate("Widget", "Destination MAC", nullptr));
        ___qtreewidgetitem->setText(4, QApplication::translate("Widget", "Source MAC", nullptr));
        ___qtreewidgetitem->setText(3, QApplication::translate("Widget", "Protocol", nullptr));
        ___qtreewidgetitem->setText(2, QApplication::translate("Widget", "Length", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("Widget", "Time", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("Widget", "Number", nullptr));
        capture_stop->setText(QApplication::translate("Widget", "Stop", nullptr));
        result_save->setText(QApplication::translate("Widget", "Save", nullptr));
        packet_reassemble->setText(QApplication::translate("Widget", "Reassemble", nullptr));
        tcp->setText(QApplication::translate("Widget", "TCP", nullptr));
        udp->setText(QApplication::translate("Widget", "UDP", nullptr));
        icmp->setText(QApplication::translate("Widget", "ICMP", nullptr));
        arp->setText(QApplication::translate("Widget", "ARP", nullptr));
        other->setText(QApplication::translate("Widget", "OTHER", nullptr));
        packet_filter->setText(QApplication::translate("Widget", "Filter", nullptr));
        exit->setText(QApplication::translate("Widget", "Exit", nullptr));
        label_2->setText(QApplication::translate("Widget", "Set Source IP :", nullptr));
        label_3->setText(QApplication::translate("Widget", "Set Destination IP :", nullptr));
        igmp->setText(QApplication::translate("Widget", "IGMP", nullptr));
        ipv6->setText(QApplication::translate("Widget", "IPV6", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
