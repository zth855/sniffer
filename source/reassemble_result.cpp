#include "reassemble_result.h"
#include "ui_reassemble_result.h"

#include "widget.h"
#include "ui_widget.h"

extern int reassemble_packet_length;
extern std::vector<int> total_length;
extern std::vector<int> number_of_same_id_packets;
extern std::vector<int> repeat_ippacket;
extern QString final_reassembled_packet;
extern std::vector<int> ip_header_length;



/*
Obtained individual packet information before merging and
 information about the combined total packet after merging.
*/

reassemble_result::reassemble_result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reassemble_result)
{
    ui->setupUi(this);
    ui->reassemble_packet->setReadOnly(true);
    ui->reassemble_packet->setText(final_reassembled_packet);

    ui->origin_packet->setColumnCount(4);
    ui->origin_packet->setRowCount(number_of_same_id_packets.size());

    QStringList headerLabels;
    headerLabels << "Packet Number" << "Total Length" << "IP Header Length" << "Ethernet Header Length";
    ui->origin_packet->setHorizontalHeaderLabels(headerLabels);

    QHeaderView* header = ui->origin_packet->horizontalHeader();
    header->setDefaultAlignment(Qt::AlignLeft);

    QFont font_header = header->font();
    font_header.setPointSize(12);
    font_header.setBold(true);
    header->setFont(font_header);

    for (int i = 0; i < number_of_same_id_packets.size(); ++i) {
        QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(number_of_same_id_packets[i]));
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(total_length[number_of_same_id_packets[i]]));
        QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(ip_header_length[number_of_same_id_packets[i]]*4));
        QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(14));

        ui->origin_packet->setColumnWidth(0, 155);
        ui->origin_packet->setColumnWidth(1, 155);
        ui->origin_packet->setColumnWidth(2, 190);
        ui->origin_packet->setColumnWidth(3, 260);

        ui->origin_packet->setItem(i, 0, item1);
        ui->origin_packet->setItem(i, 1, item2);
        ui->origin_packet->setItem(i, 2, item3);
        ui->origin_packet->setItem(i, 3, item4);
    }

    QFont font_data = ui->origin_packet->font();

    font_data.setPointSize(14);

    ui->origin_packet->setFont(font_data);


    for(int i = 0; i < repeat_ippacket.size(); i++) {
        qDebug() << repeat_ippacket[i];
    }

    reassembled_packet_length->setGeometry(450, 880, 540, 30);
    QFont font("Ubuntu", 18);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);
    reassembled_packet_length->setFont(font);
    reassembled_packet_length->setPalette(palette);
    reassembled_packet_length->setText(QString::fromStdString("Total Length of Merged Packet: " +std::to_string(reassemble_packet_length)));

    number_of_same_id_packets.clear();
    final_reassembled_packet.clear();
}

reassemble_result::~reassemble_result()
{
    delete ui;
}

