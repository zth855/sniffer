#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QThread>
#include <QLabel>
#include <QMessageBox>
#include <QTreeWidget>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTimer>
#include <signal.h>
#include <pcap.h>
#include <stdio.h>
#include <time.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <netinet/ether.h>
#include <netinet/ip6.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netpacket/packet.h>
#include <sstream>
#include <iomanip>
#include <atomic>
#include <cstring>

#include "reassemble_result.h"
#include "ui_reassemble_result.h"



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class PacketCaptureThread : public QThread
{
    Q_OBJECT


public:
    PacketCaptureThread(pcap_t *handle, QObject *parent = nullptr)
        : QThread(parent), m_handle(handle) {}

    void stop() { stopFlag.store(true); }

    pcap_t* getHandle() const { return m_handle; }


signals:
    void addPacketInfo(int number, const QString &timeInfo, int length, const QString &protocolType, const QString &srcMac, const QString &dstMac, const QString &srcIp, const QString &dstIp);


protected:
    void run() override {
        while (!stopFlag.load()) {
            pcap_loop(m_handle, 1, packet_handler, reinterpret_cast<u_char*>(this));
        }
    }

    static void packet_handler(u_char *user_data, const struct pcap_pkthdr *pkthdr, const u_char *packet);


private:
    pcap_t *m_handle;

    std::atomic<bool> stopFlag { false };

};
//Created a new packet capture thread.




class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    ~Widget();

    void onAddPacketInfo(int number, const QString &timeInfo, int length, const QString &protocolType, const QString &srcMac, const QString &dstMac, const QString &srcIp, const QString &dstIp);

    void onBasicInfoItemClicked(QTreeWidgetItem *item);



private slots:
    void on_capture_start_clicked();

    void on_capture_stop_clicked();

    void on_result_save_clicked();

    void on_packet_reassemble_clicked();

    void on_tcp_clicked(bool checked);

    void on_icmp_clicked(bool checked);

    void on_igmp_clicked(bool checked);

    void on_ipv6_clicked(bool checked);

    void on_arp_clicked(bool checked);

    void on_other_clicked(bool checked);

    void on_udp_clicked(bool checked);

    void on_exit_clicked();

    void on_packet_filter_clicked();


public slots:
    void print_network_traffic();


private:
    Ui::Widget *ui;

    PacketCaptureThread *thread = nullptr;

    QLabel *label_start = new QLabel("Packet capturing......", this);

    QLabel *label_stop = new QLabel("Capture stopped!", this);

    QLabel *label_wait = new QLabel("Waiting......", this);

    QLabel* label_network_traffic= new QLabel(this);

};

#endif // WIDGET_H
