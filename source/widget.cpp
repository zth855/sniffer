#include "widget.h"
#include "ui_widget.h"


volatile static int totalSize = 0;

static QString input_src_ip = NULL;
static QString input_dst_ip = NULL;

static bool flag_tcp = 1;
static bool flag_udp = 1;
static bool flag_icmp = 1;
static bool flag_igmp = 1;
static bool flag_ipv6 = 1;
static bool flag_arp = 1;
static bool flag_other = 1;

std::vector<int> total_length;
int reassemble_packet_length;
std::vector<int> repeat_ippacket;

static char *protocol_type;
static std::vector<char*> Protocol_Type;
static std::vector<std::vector<u_char>> Packets;

static std::vector<QString> source_mac;
static std::vector<QString> destination_mac;
static std::vector<int> typeof_ether;

static std::vector<int> ip_version;
std::vector<int> ip_header_length;
static std::vector<int> typeof_service;
static std::vector<int> ip_total_length;
static std::vector<int> ip_id;
static std::vector<int> ip_MF;
static std::vector<int> ip_DF;
static std::vector<unsigned int> iP_fragment_offset;
static std::vector<int> ip_ttl;
static std::vector<int> ip_protocol;

static std::vector<int> ipv6_version;
static std::vector<int> ipv6_traffic_class;
static std::vector<int> ipv6_flow_label;
static std::vector<int> ipv6_payload_length;
static std::vector<int> ipv6_next_header;
static std::vector<int> ipv6_hop_limit;

static std::vector<int> source_port;
static std::vector<int> destination_port;
static std::vector<int> udp_length;
static std::vector<int> udp_checksum;

static std::vector<long long int> sequence_number;
static std::vector<long long int> acknowledge_number;
static std::vector<int> data_offset;
static std::vector<int> Reserved;
static std::vector<char*> flags;
static std::vector<int> window_size;
static std::vector<unsigned int> tcp_checksum;
static std::vector<int> urgent_point;

static std::vector<int> typeof_icmp;
static std::vector<int> codeof_icmp;
static std::vector<int> icmp_checksum;
static std::vector<int> sequence_number_icmp;

static std::vector<int> type_vec;
static std::vector<int> checksum_vec;
static std::vector<QString> group_address_str_vec;

static std::vector<int> typeof_hardware;
static std::vector<int> typeof_protosol;
static std::vector<int> hardware_address_length;
static std::vector<int> protosol_address_length;
static std::vector<int> opcode;
static std::vector<char*> type;

std::vector<int> number_of_same_id_packets;
QString final_reassembled_packet;







//Converting the initial data packets into hexadecimal format for output.
QString formatPacket(const std::vector<u_char> &packet) {
    QString str;
    QTextStream stream(&str);
    int lineNumber = 0;
    for (int i = 0; i < packet.size(); ++i) {
        if(i % 16 == 0) {
            stream << QString::number(lineNumber, 16).rightJustified(4, '0') << ":  ";
            ++lineNumber;
        }
        stream << QString::number(packet[i], 16).rightJustified(2, '0') << "  ";
        if ((i + 1) % 16 == 0) {
            stream << "\n";
        }
    }
    if (packet.size() % 16 != 0) {
        stream << "\n";
    }
    return str;
}



//Calculating the checksum of the IPv4 packet header.
uint16_t compute_ip_checksum(std::vector<u_char>& packet) {
    uint32_t sum = 0;
    uint16_t* ptr = reinterpret_cast<uint16_t*>(&packet[14]);
    int count = (packet[14] & 0x0F) << 2;
    ptr[5] = 0;

    while (count > 1) {
        sum += ntohs(*ptr++);
        count -= 2;
    }

    if (count > 0) {
        sum += *reinterpret_cast<u_char*>(ptr);
    }

    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    uint16_t checksum = ~sum;
    return htons(checksum);
}




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Widget::print_network_traffic);

    timer->start(1000);
    ui->setupUi(this);
    ui->tcp->setChecked(true);
    ui->udp->setChecked(true);
    ui->icmp->setChecked(true);
    ui->igmp->setChecked(true);
    ui->ipv6->setChecked(true);
    ui->arp->setChecked(true);
    ui->other->setChecked(true);

    label_start->setGeometry(50, 240, 340, 30);
    QFont font("Ubuntu", 18);
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);
    label_start->setFont(font);
    label_start->setPalette(palette);
    label_start->hide();

    label_stop->setGeometry(50, 240, 340, 30);
    label_stop->setFont(font);
    label_stop->setPalette(palette);
    label_stop->hide();

    label_wait->setGeometry(50, 240, 340, 30);
    label_wait->setFont(font);
    label_wait->setPalette(palette);
    label_wait->hide();


    QFont font_traffic("Ubuntu", 18);
    label_network_traffic->setGeometry(1400, 240, 340, 30);
    label_network_traffic->setFont(font_traffic);
    label_network_traffic->setPalette(palette);
    label_network_traffic->setText("0 KB/s");


    ui->basic_information->setColumnWidth(0, 120);
    ui->basic_information->setColumnWidth(1, 300);
    ui->basic_information->setColumnWidth(2, 120);
    ui->basic_information->setColumnWidth(3, 120);
    ui->basic_information->setColumnWidth(4, 220);
    ui->basic_information->setColumnWidth(5, 220);
    ui->basic_information->setColumnWidth(6, 200);
    ui->basic_information->setColumnWidth(7, 200);


    connect(ui->basic_information, &QTreeWidget::itemClicked, this, &Widget::onBasicInfoItemClicked);
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    if(pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Couldn't find default device: %s\n", errbuf);
        return;
    }

    for(pcap_if_t *d=alldevs; d; d=d->next)
    {
        ui->choose_device->addItem(d->name);
    }

    pcap_freealldevs(alldevs);
}


Widget::~Widget()
{
    delete ui;
}


//Outputting the information from each vector.
void Widget::onBasicInfoItemClicked(QTreeWidgetItem *item)
{

    std::stringstream ss;

    int row = item->text(0).toInt();

    const std::vector<u_char> &Packet = Packets[row];
    QString str = formatPacket(Packet);

    ui->show_packet->setReadOnly(true);
    ui->show_packet->setText(QString(str));

    QStandardItemModel *model = new QStandardItemModel(ui->specific_information);

    QFont font;
    font.setPointSize(20);
    QFont font0;
    font0.setPointSize(15);
    model->setHorizontalHeaderLabels(QStringList(QStringLiteral("Specific Information")));
    QHeaderView *header = ui->specific_information->header();
    header->setFont(font);

    QStandardItem *item1 = new QStandardItem(QString("Packet %1").arg(item->text(0)));
    QFont font1;
    font1.setPointSize(18);
    item1->setFont(font1);
    model->appendRow(item1);

    QStandardItem *item2_1 = new QStandardItem("Data Link Layer");
    QFont font2_1;
    font2_1.setPointSize(16);
    item2_1->setFont(font2_1);
    item1->appendRow(item2_1);

    QStandardItem *item3_1 = new QStandardItem("Source MAC: "+source_mac[row]);
    item3_1->setFont(font0);
    item2_1->appendRow(item3_1);

    QStandardItem *item3_2 = new QStandardItem("Destination MAC: "+destination_mac[row]);
    item3_2->setFont(font0);
    item2_1->appendRow(item3_2);

    ss << "0x" << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << typeof_ether[row];
    QStandardItem *item3_3 = new QStandardItem(QString::fromStdString("Type pf Ether: "+ss.str()));
    item3_3->setFont(font0);
    item2_1->appendRow(item3_3);

    if(Protocol_Type[row]=="TCP"){
        QStandardItem *item2_2 = new QStandardItem("IPv4 Protocol Header Layer");
        QStandardItem *item2_3 = new QStandardItem("Specific Protocol Header Layer");
        QFont font2_2_3;
        font2_2_3.setPointSize(16);
        item2_2->setFont(font2_2_3);
        item2_3->setFont(font2_2_3);

        item1->appendRow(item2_2);
        item1->appendRow(item2_3);

        QStandardItem *item3_1 = new QStandardItem(QString::fromStdString("IP Version: " +std::to_string(ip_version[row])));
        QStandardItem *item3_2 = new QStandardItem(QString::fromStdString("IP Header Length: " +std::to_string(ip_header_length[row])+" * 4 bytes"));
        QStandardItem *item3_3 = new QStandardItem(QString::fromStdString("Type of Service: " +std::to_string(typeof_service[row])));
        QStandardItem *item3_4 = new QStandardItem(QString::fromStdString("IP Total Length: " +std::to_string(ip_total_length[row])+" bytes"));
        QStandardItem *item3_5 = new QStandardItem(QString::fromStdString("IP ID: " +std::to_string(ip_id[row])));
        QStandardItem *item3_6 = new QStandardItem(QString::fromStdString("MF: " +std::to_string(ip_MF[row])));
        QStandardItem *item3_7 = new QStandardItem(QString::fromStdString("DF: " +std::to_string(ip_DF[row])));
        QStandardItem *item3_8 = new QStandardItem(QString::fromStdString("Fragment Offset: " +std::to_string(iP_fragment_offset[row])));
        QStandardItem *item3_9 = new QStandardItem(QString::fromStdString("TTL: " +std::to_string(ip_ttl[row])));
        QStandardItem *item3_10 = new QStandardItem(QString::fromStdString("IP Protocol: " +std::to_string(ip_protocol[row])));

        QStandardItem *item3_11 = new QStandardItem(QString::fromStdString("Source Port: " +std::to_string(source_port[row])));
        QStandardItem *item3_12 = new QStandardItem(QString::fromStdString("Destination Port: " +std::to_string(destination_port[row])));
        QStandardItem *item3_13 = new QStandardItem(QString::fromStdString("Sequence Number: " +std::to_string(sequence_number[row])));
        QStandardItem *item3_14 = new QStandardItem(QString::fromStdString("Acknowledge Number: " +std::to_string(acknowledge_number[row])));
        QStandardItem *item3_15 = new QStandardItem(QString::fromStdString("Data Offset: " +std::to_string(data_offset[row])));
        QStandardItem *item3_16 = new QStandardItem(QString::fromStdString("Reserved: " +std::to_string(Reserved[row])));
        QStandardItem *item3_17 = new QStandardItem(QString("Flags: ") + QString(flags[row]));
        QStandardItem *item3_18 = new QStandardItem(QString::fromStdString("Window Size: " +std::to_string(window_size[row])));
        QStandardItem *item3_19 = new QStandardItem(QString::fromStdString("Checksum: " +std::to_string(tcp_checksum[row])));
        QStandardItem *item3_20 = new QStandardItem(QString::fromStdString("Urgent Point: " +std::to_string(urgent_point[row])));

        item3_1->setFont(font0);
        item3_2->setFont(font0);
        item3_3->setFont(font0);
        item3_4->setFont(font0);
        item3_5->setFont(font0);
        item3_6->setFont(font0);
        item3_7->setFont(font0);
        item3_8->setFont(font0);
        item3_9->setFont(font0);
        item3_10->setFont(font0);
        item3_11->setFont(font0);
        item3_12->setFont(font0);
        item3_13->setFont(font0);
        item3_14->setFont(font0);
        item3_15->setFont(font0);
        item3_16->setFont(font0);
        item3_17->setFont(font0);
        item3_18->setFont(font0);
        item3_19->setFont(font0);
        item3_20->setFont(font0);

        item2_2->appendRow(item3_1);
        item2_2->appendRow(item3_2);
        item2_2->appendRow(item3_3);
        item2_2->appendRow(item3_4);
        item2_2->appendRow(item3_5);
        item2_2->appendRow(item3_6);
        item2_2->appendRow(item3_7);
        item2_2->appendRow(item3_8);
        item2_2->appendRow(item3_9);
        item2_2->appendRow(item3_10);
        item2_3->appendRow(item3_11);
        item2_3->appendRow(item3_12);
        item2_3->appendRow(item3_13);
        item2_3->appendRow(item3_14);
        item2_3->appendRow(item3_15);
        item2_3->appendRow(item3_16);
        item2_3->appendRow(item3_17);
        item2_3->appendRow(item3_18);
        item2_3->appendRow(item3_19);
        item2_3->appendRow(item3_20);
    }
    else if(Protocol_Type[row]=="UDP"){
        QStandardItem *item2_2 = new QStandardItem("IPv4 Protocol Header Layer");
        QStandardItem *item2_3 = new QStandardItem("Specific Protocol Header Layer");
        QFont font2_2_3;
        font2_2_3.setPointSize(16);
        item2_2->setFont(font2_2_3);
        item2_3->setFont(font2_2_3);

        item1->appendRow(item2_2);
        item1->appendRow(item2_3);


        QStandardItem *item3_1 = new QStandardItem(QString::fromStdString("IP Version: " +std::to_string(ip_version[row])));
        QStandardItem *item3_2 = new QStandardItem(QString::fromStdString("IP Header Length: " +std::to_string(ip_header_length[row])+" * 4 bytes"));
        QStandardItem *item3_3 = new QStandardItem(QString::fromStdString("Type of Service: " +std::to_string(typeof_service[row])));
        QStandardItem *item3_4 = new QStandardItem(QString::fromStdString("IP Total Length: " +std::to_string(ip_total_length[row])+" bytes"));
        QStandardItem *item3_5 = new QStandardItem(QString::fromStdString("IP ID: " +std::to_string(ip_id[row])));
        QStandardItem *item3_6 = new QStandardItem(QString::fromStdString("MF: " +std::to_string(ip_MF[row])));
        QStandardItem *item3_7 = new QStandardItem(QString::fromStdString("DF: " +std::to_string(ip_DF[row])));
        QStandardItem *item3_8 = new QStandardItem(QString::fromStdString("Fragment Offset: " +std::to_string(iP_fragment_offset[row])));
        QStandardItem *item3_9 = new QStandardItem(QString::fromStdString("TTL: " +std::to_string(ip_ttl[row])));
        QStandardItem *item3_10 = new QStandardItem(QString::fromStdString("IP Protocol: " +std::to_string(ip_protocol[row])));

        QStandardItem *item3_11 = new QStandardItem(QString::fromStdString("Source Port: " +std::to_string(source_port[row])));
        QStandardItem *item3_12 = new QStandardItem(QString::fromStdString("Destination Port: " +std::to_string(destination_port[row])));
        QStandardItem *item3_13 = new QStandardItem(QString::fromStdString("UDP Length: " +std::to_string(udp_length[row])));
        QStandardItem *item3_14 = new QStandardItem(QString::fromStdString("UDP Checksum: " +std::to_string(udp_checksum[row])));

        item3_1->setFont(font0);
        item3_2->setFont(font0);
        item3_3->setFont(font0);
        item3_4->setFont(font0);
        item3_5->setFont(font0);
        item3_6->setFont(font0);
        item3_7->setFont(font0);
        item3_8->setFont(font0);
        item3_9->setFont(font0);
        item3_10->setFont(font0);
        item3_11->setFont(font0);
        item3_12->setFont(font0);
        item3_13->setFont(font0);
        item3_14->setFont(font0);

        item2_2->appendRow(item3_1);
        item2_2->appendRow(item3_2);
        item2_2->appendRow(item3_3);
        item2_2->appendRow(item3_4);
        item2_2->appendRow(item3_5);
        item2_2->appendRow(item3_6);
        item2_2->appendRow(item3_7);
        item2_2->appendRow(item3_8);
        item2_2->appendRow(item3_9);
        item2_2->appendRow(item3_10);
        item2_3->appendRow(item3_11);
        item2_3->appendRow(item3_12);
        item2_3->appendRow(item3_13);
        item2_3->appendRow(item3_14);

    }
    else if(Protocol_Type[row]=="ICMP"){
        QStandardItem *item2_2 = new QStandardItem("IPv4 Protocol Header Layer");
        QStandardItem *item2_3 = new QStandardItem("Specific Protocol Header Layer");
        QFont font2_2_3;
        font2_2_3.setPointSize(16);
        item2_2->setFont(font2_2_3);
        item2_3->setFont(font2_2_3);

        item1->appendRow(item2_2);
        item1->appendRow(item2_3);

        QStandardItem *item3_1 = new QStandardItem(QString::fromStdString("IP Version: " +std::to_string(ip_version[row])));
        QStandardItem *item3_2 = new QStandardItem(QString::fromStdString("IP Header Length: " +std::to_string(ip_header_length[row])+" * 4 bytes"));
        QStandardItem *item3_3 = new QStandardItem(QString::fromStdString("Type of Service: " +std::to_string(typeof_service[row])));
        QStandardItem *item3_4 = new QStandardItem(QString::fromStdString("IP Total Length: " +std::to_string(ip_total_length[row])+" bytes"));
        QStandardItem *item3_5 = new QStandardItem(QString::fromStdString("IP ID: " +std::to_string(ip_id[row])));
        QStandardItem *item3_6 = new QStandardItem(QString::fromStdString("MF: " +std::to_string(ip_MF[row])));
        QStandardItem *item3_7 = new QStandardItem(QString::fromStdString("DF: " +std::to_string(ip_DF[row])));
        QStandardItem *item3_8 = new QStandardItem(QString::fromStdString("Fragment Offset: " +std::to_string(iP_fragment_offset[row])));
        QStandardItem *item3_9 = new QStandardItem(QString::fromStdString("TTL: " +std::to_string(ip_ttl[row])));
        QStandardItem *item3_10 = new QStandardItem(QString::fromStdString("IP Protocol: " +std::to_string(ip_protocol[row])));

        QStandardItem *item3_11 = new QStandardItem(QString::fromStdString("Type of ICMP: " +std::to_string(typeof_icmp[row])));
        QStandardItem *item3_12 = new QStandardItem(QString::fromStdString("Code of ICMP: " +std::to_string(codeof_icmp[row])));
        QStandardItem *item3_13 = new QStandardItem(QString::fromStdString("ICMP Checksum: " +std::to_string(icmp_checksum[row])));
        QStandardItem *item3_14 = new QStandardItem(QString::fromStdString("Sequence Number: " +std::to_string(sequence_number_icmp[row])));

        item3_1->setFont(font0);
        item3_2->setFont(font0);
        item3_3->setFont(font0);
        item3_4->setFont(font0);
        item3_5->setFont(font0);
        item3_6->setFont(font0);
        item3_7->setFont(font0);
        item3_8->setFont(font0);
        item3_9->setFont(font0);
        item3_10->setFont(font0);
        item3_11->setFont(font0);
        item3_12->setFont(font0);
        item3_13->setFont(font0);
        item3_14->setFont(font0);

        item2_2->appendRow(item3_1);
        item2_2->appendRow(item3_2);
        item2_2->appendRow(item3_3);
        item2_2->appendRow(item3_4);
        item2_2->appendRow(item3_5);
        item2_2->appendRow(item3_6);
        item2_2->appendRow(item3_7);
        item2_2->appendRow(item3_8);
        item2_2->appendRow(item3_9);
        item2_2->appendRow(item3_10);
        item2_3->appendRow(item3_11);
        item2_3->appendRow(item3_12);
        item2_3->appendRow(item3_13);
        item2_3->appendRow(item3_14);
    }
    else if(Protocol_Type[row]=="IGMP"){
        QStandardItem *item2_2 = new QStandardItem("IPv4 Protocol Header Layer");
        QStandardItem *item2_3 = new QStandardItem("Specific Protocol Header Layer");
        QFont font2_2_3;
        font2_2_3.setPointSize(16);
        item2_2->setFont(font2_2_3);
        item2_3->setFont(font2_2_3);

        item1->appendRow(item2_2);
        item1->appendRow(item2_3);

        QStandardItem *item3_1 = new QStandardItem(QString::fromStdString("IP Version: " +std::to_string(ip_version[row])));
        QStandardItem *item3_2 = new QStandardItem(QString::fromStdString("IP Header Length: " +std::to_string(ip_header_length[row])+" * 4 bytes"));
        QStandardItem *item3_3 = new QStandardItem(QString::fromStdString("Type of Service: " +std::to_string(typeof_service[row])));
        QStandardItem *item3_4 = new QStandardItem(QString::fromStdString("IP Total Length: " +std::to_string(ip_total_length[row])+" bytes"));
        QStandardItem *item3_5 = new QStandardItem(QString::fromStdString("IP ID: " +std::to_string(ip_id[row])));
        QStandardItem *item3_6 = new QStandardItem(QString::fromStdString("MF: " +std::to_string(ip_MF[row])));
        QStandardItem *item3_7 = new QStandardItem(QString::fromStdString("DF: " +std::to_string(ip_DF[row])));
        QStandardItem *item3_8 = new QStandardItem(QString::fromStdString("Fragment Offset: " +std::to_string(iP_fragment_offset[row])));
        QStandardItem *item3_9 = new QStandardItem(QString::fromStdString("TTL: " +std::to_string(ip_ttl[row])));
        QStandardItem *item3_10 = new QStandardItem(QString::fromStdString("IP Protocol: " +std::to_string(ip_protocol[row])));

        std::stringstream ss;
        ss << std::hex << type_vec[row];
        QStandardItem *item3_11 = new QStandardItem(QString::fromStdString("Type of IGMP: 0x" +ss.str()));
        QStandardItem *item3_12 = new QStandardItem(QString::fromStdString("IGMP Checksum: " +std::to_string(checksum_vec[row])));
        QStandardItem *item3_13 = new QStandardItem("Multicast Address: " +group_address_str_vec[row]);

        item3_1->setFont(font0);
        item3_2->setFont(font0);
        item3_3->setFont(font0);
        item3_4->setFont(font0);
        item3_5->setFont(font0);
        item3_6->setFont(font0);
        item3_7->setFont(font0);
        item3_8->setFont(font0);
        item3_9->setFont(font0);
        item3_10->setFont(font0);
        item3_11->setFont(font0);
        item3_12->setFont(font0);
        item3_13->setFont(font0);

        item2_2->appendRow(item3_1);
        item2_2->appendRow(item3_2);
        item2_2->appendRow(item3_3);
        item2_2->appendRow(item3_4);
        item2_2->appendRow(item3_5);
        item2_2->appendRow(item3_6);
        item2_2->appendRow(item3_7);
        item2_2->appendRow(item3_8);
        item2_2->appendRow(item3_9);
        item2_2->appendRow(item3_10);
        item2_3->appendRow(item3_11);
        item2_3->appendRow(item3_12);
        item2_3->appendRow(item3_13);
    }
    if(Protocol_Type[row]=="IPv6"){
        QStandardItem *item2_2 = new QStandardItem("IPv6 Protocol Header Layer");

        QFont font2_2;
        font2_2.setPointSize(16);
        item2_2->setFont(font2_2);


        item1->appendRow(item2_2);

        QStandardItem *item3_1 = new QStandardItem(QString::fromStdString("IPv6 Version: " +std::to_string(ipv6_version[row])));
        QStandardItem *item3_2 = new QStandardItem(QString::fromStdString("Traffic Class: " +std::to_string(ipv6_traffic_class[row])));
        QStandardItem *item3_3 = new QStandardItem(QString::fromStdString("Flow Label: " +std::to_string(ipv6_flow_label[row])));
        QStandardItem *item3_4 = new QStandardItem(QString::fromStdString("Payload Length: " +std::to_string(ipv6_payload_length[row])));
        QStandardItem *item3_5 = new QStandardItem(QString::fromStdString("Next Header: " +std::to_string(ipv6_next_header[row])));
        QStandardItem *item3_6 = new QStandardItem(QString::fromStdString("Hop Limit: " +std::to_string(ipv6_hop_limit[row])));

        item3_1->setFont(font0);
        item3_2->setFont(font0);
        item3_3->setFont(font0);
        item3_4->setFont(font0);
        item3_5->setFont(font0);
        item3_6->setFont(font0);

        item2_2->appendRow(item3_1);
        item2_2->appendRow(item3_2);
        item2_2->appendRow(item3_3);
        item2_2->appendRow(item3_4);
        item2_2->appendRow(item3_5);
        item2_2->appendRow(item3_6);
    }
    else if(Protocol_Type[row]=="ARP"){
        QStandardItem *item2_2 = new QStandardItem("ARP Protocol Header");
        QFont font2_2;
        font2_2.setPointSize(16);
        item2_2->setFont(font2_2);

        item1->appendRow(item2_2);

        QStandardItem *item3_1 = new QStandardItem(QString::fromStdString("Type of Hardware: " +std::to_string(typeof_hardware[row])));
        QStandardItem *item3_2 = new QStandardItem(QString::fromStdString("Type of Protosol: " +std::to_string(typeof_protosol[row])));
        QStandardItem *item3_3 = new QStandardItem(QString::fromStdString("Hardware Address Length: " +std::to_string(hardware_address_length[row])));
        QStandardItem *item3_4 = new QStandardItem(QString::fromStdString("Protosol Address Length: " +std::to_string(protosol_address_length[row])));
        QStandardItem *item3_5 = new QStandardItem(QString::fromStdString("Opcode: " +std::to_string(opcode[row])));
        QStandardItem *item3_6 = new QStandardItem(QString("Type: ") + QString(type[row]));

        item3_1->setFont(font0);
        item3_2->setFont(font0);
        item3_3->setFont(font0);
        item3_4->setFont(font0);
        item3_5->setFont(font0);
        item3_6->setFont(font0);


        item2_2->appendRow(item3_1);
        item2_2->appendRow(item3_2);
        item2_2->appendRow(item3_3);
        item2_2->appendRow(item3_4);
        item2_2->appendRow(item3_5);
        item2_2->appendRow(item3_6);
    }
    else if(Protocol_Type[row]=="OTHER"){

    }

    ui->specific_information->setModel(model);
    ui->specific_information->expandAll();

}


//Outputting basic information of each protocol packet.
void Widget::onAddPacketInfo(int number, const QString &timeInfo, int length, const QString &protocolType, const QString &srcMac, const QString &dstMac, const QString &srcIp, const QString &dstIp)
{
    if(protocolType!="OTHER"){
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->basic_information);
        if(protocolType=="TCP"){
            for (int i = 0; i < ui->basic_information->columnCount(); ++i) {
                QColor color(255, 228, 196);
                item->setBackground(i, QBrush(color));
            }
        }
        if(protocolType=="UDP"){
            for (int i = 0; i < ui->basic_information->columnCount(); ++i) {
                QColor color(230, 230, 250);
                item->setBackground(i, QBrush(color));
            }
        }
        if(protocolType=="ARP"){
            for (int i = 0; i < ui->basic_information->columnCount(); ++i) {
                QColor color(135, 206, 250);
                item->setBackground(i, QBrush(color));
            }
        }
        if(protocolType=="ICMP"){
            for (int i = 0; i < ui->basic_information->columnCount(); ++i) {
                QColor color(205, 155, 155);
                item->setBackground(i, QBrush(color));
            }
        }
        if(protocolType=="IGMP"){
            for (int i = 0; i < ui->basic_information->columnCount(); ++i) {
                QColor color(193, 255, 193);
                item->setBackground(i, QBrush(color));
            }
        }
        if(protocolType=="TCP"){
            for (int i = 0; i < ui->basic_information->columnCount(); ++i) {
                QColor color(255, 228, 196);
                item->setBackground(i, QBrush(color));
            }
        }
        if(protocolType=="IPv6"){
            for (int i = 0; i < ui->basic_information->columnCount(); ++i) {
                QColor color(255, 228, 255);
                item->setBackground(i, QBrush(color));
            }
        }
        item->setText(0, QString::number(number));
        item->setText(1, timeInfo);
        item->setText(2, QString::number(length));
        item->setText(3, protocolType);
        item->setText(4, srcMac);
        item->setText(5, dstMac);
        item->setText(6, srcIp);
        item->setText(7, dstIp);

        QFont font;
        font.setPointSize(16);
        item->setFont(0, font);
        item->setFont(1, font);
        item->setFont(2, font);
        item->setFont(3, font);
        item->setFont(4, font);
        item->setFont(5, font);
        item->setFont(6, font);
        item->setFont(7, font);

    }

    else{
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->basic_information);
        item->setText(0, QString::number(number));
        item->setText(1, timeInfo);
        item->setText(2, "?");
        item->setText(3, protocolType);
        item->setText(4, srcMac);
        item->setText(5, dstMac);
        item->setText(6, "?");
        item->setText(7, "?");

        QFont font;
        font.setPointSize(16);
        item->setFont(0, font);
        item->setFont(1, font);
        item->setFont(2, font);
        item->setFont(3, font);
        item->setFont(4, font);
        item->setFont(5, font);
        item->setFont(6, font);
        item->setFont(7, font);
    }
}


//Packet capture function that internally passes packet information to a global variable.
void PacketCaptureThread:: packet_handler(u_char *user_data, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    totalSize += pkthdr->len;

    static int number = 0;
    QString timeStr = NULL;
    int length;
    QString protocolType = NULL;
    QString srcMac = NULL;
    QString dstMac = NULL;
    QString srcIp = NULL;
    QString dstIp = NULL;

    PacketCaptureThread *thread = reinterpret_cast<PacketCaptureThread*>(user_data);
    char src_ip[INET_ADDRSTRLEN];
    char dst_ip[INET_ADDRSTRLEN];
    struct ether_header *eth_header;
    struct ip* ip_packet = NULL;
    eth_header = (struct ether_header *) packet;


    struct arp_header {
        unsigned short arp_hardware_type;
        unsigned short arp_protocol_type;
        unsigned char arp_hardware_len;
        unsigned char arp_protocol_len;
        unsigned short arp_opcode;
        unsigned char arp_sender_mac[6];
        unsigned char arp_sender_ip[4];
        unsigned char arp_target_mac[6];
        unsigned char arp_target_ip[4];
    };

    struct igmp_header {
        uint8_t type;
        uint8_t max_resp_time;
        uint16_t checksum;
        uint32_t group_address;
    } __attribute__((packed));

    switch (ntohs(eth_header->ether_type)) {
    case ETHERTYPE_IP:
    {
        ip_packet = (struct ip *)(packet + ETHER_HDR_LEN);
        switch (ip_packet->ip_p) {
        case IPPROTO_TCP:
            if(!flag_tcp) return;
            break;
        case IPPROTO_UDP:
            if(!flag_udp) return;
            break;
        case IPPROTO_ICMP:
            if(!flag_icmp) return;
            break;
        case IPPROTO_IGMP:
            if(!flag_igmp) return;
            break;
        default:
            if(!flag_other) return;
            if(input_src_ip!=NULL||input_dst_ip!=NULL) return;
        }

    }
        break;
    case ETHERTYPE_IPV6:
        if(!flag_ipv6) return;
        break;
    case ETHERTYPE_ARP:
    {
        if(!flag_arp) return;
    }
        break;
    default:
        if(!flag_other) return;
        if(input_src_ip!=NULL||input_dst_ip!=NULL) return;
    }

    switch (ntohs(eth_header->ether_type)) {
    case ETHERTYPE_IP:
    {
        ip_packet = (struct ip *)(packet + ETHER_HDR_LEN);
        inet_ntop(AF_INET, &(ip_packet->ip_src), src_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ip_packet->ip_dst), dst_ip, INET_ADDRSTRLEN);
        srcIp = QString::fromUtf8(src_ip);
        dstIp = QString::fromUtf8(dst_ip);

        if(input_src_ip!=NULL&&input_src_ip!=srcIp) return;
        if(input_dst_ip!=NULL&&input_dst_ip!=dstIp) return;

        ip_version.push_back(ip_packet->ip_v);
        ip_header_length.push_back(ip_packet->ip_hl);
        typeof_service.push_back(ip_packet->ip_tos);
        ip_total_length.push_back(ntohs(ip_packet->ip_len));
        ip_id.push_back(ip_packet->ip_id);
        ip_MF.push_back((ntohs(ip_packet->ip_off) >> 13) & 0x1);
        ip_DF.push_back(((ntohs(ip_packet->ip_off) >> 13) & 0x2) >> 1);
        iP_fragment_offset.push_back(ntohs(ip_packet->ip_off) & 0x1FFF);
        ip_ttl.push_back(ip_packet->ip_ttl);
        ip_protocol.push_back(ip_packet->ip_p);

        ipv6_version.push_back(-1);
        ipv6_traffic_class.push_back(-1);
        ipv6_flow_label.push_back(-1);
        ipv6_payload_length.push_back(-1);
        ipv6_next_header.push_back(-1);
        ipv6_hop_limit.push_back(-1);

        switch (ip_packet->ip_p) {
        case IPPROTO_TCP:
            protocol_type = "TCP";
            break;
        case IPPROTO_UDP:
            protocol_type = "UDP";
            break;
        case IPPROTO_ICMP:
            protocol_type = "ICMP";
            break;
        case IPPROTO_IGMP:
            protocol_type = "IGMP";
            break;
        default:
            protocol_type = "OTHER";
            ip_version.push_back(-1);
            ip_header_length.push_back(-1);
            typeof_service.push_back(-1);
            ip_total_length.push_back(-1);
            ip_id.push_back(-1);
            ip_MF.push_back(-1);
            ip_DF.push_back(-1);
            iP_fragment_offset.push_back(-1);
            ip_ttl.push_back(-1);
            ip_protocol.push_back(-1);
        }

    }
        break;
    case ETHERTYPE_IPV6:
    {
        protocol_type = "IPv6";
        struct ip6_hdr *ip6_packet;
        ip6_packet = (struct ip6_hdr *)(packet + ETHER_HDR_LEN);
        char src_ip6[INET6_ADDRSTRLEN], dst_ip6[INET6_ADDRSTRLEN];

        inet_ntop(AF_INET6, &(ip6_packet->ip6_src), src_ip6, INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &(ip6_packet->ip6_dst), dst_ip6, INET6_ADDRSTRLEN);
        srcIp = QString::fromUtf8(src_ip6);
        dstIp = QString::fromUtf8(dst_ip6);

        int version = (ip6_packet->ip6_vfc & 0xf0) >> 4;

        int traffic_class = ((ip6_packet->ip6_vfc & 0x0F) << 4) | ((ip6_packet->ip6_flow & 0xF000) >> 12);


        int flow_label = ntohl(ip6_packet->ip6_flow) & 0x000fffff;

        int payload_length = ntohs(ip6_packet->ip6_plen);

        int next_header = ip6_packet->ip6_nxt;

        int hop_limit = ip6_packet->ip6_hops;


        if(input_src_ip!=NULL&&input_src_ip!=srcIp) return;
        if(input_dst_ip!=NULL&&input_dst_ip!=dstIp) return;

        ipv6_version.push_back(version);
        ipv6_traffic_class.push_back(traffic_class);
        ipv6_flow_label.push_back(flow_label);
        ipv6_payload_length.push_back(payload_length);
        ipv6_next_header.push_back(next_header);
        ipv6_hop_limit.push_back(hop_limit);

        ip_version.push_back(-1);
        ip_header_length.push_back(-1);
        typeof_service.push_back(-1);
        ip_total_length.push_back(-1);
        ip_id.push_back(-1);
        ip_MF.push_back(-1);
        ip_DF.push_back(-1);
        iP_fragment_offset.push_back(-1);
        ip_ttl.push_back(-1);
        ip_protocol.push_back(-1);
    }
        break;
    case ETHERTYPE_ARP:
    {
        protocol_type = "ARP";

        struct ether_arp *arp_header = (struct ether_arp *)(packet + ETHER_HDR_LEN);

        char src_ip[INET_ADDRSTRLEN];
        char dst_ip[INET_ADDRSTRLEN];

        inet_ntop(AF_INET, arp_header->arp_spa, src_ip, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, arp_header->arp_tpa, dst_ip, INET_ADDRSTRLEN);

        srcIp = src_ip;
        dstIp = dst_ip;

        if(input_src_ip!=NULL&&input_src_ip!=srcIp) return;
        if(input_dst_ip!=NULL&&input_dst_ip!=dstIp) return;


        char src_mac[ETH_ALEN*3];
        char dst_mac[ETH_ALEN*3];

        snprintf(src_mac, sizeof(src_mac), "%02x:%02x:%02x:%02x:%02x:%02x",
                 arp_header->arp_sha[0],
                arp_header->arp_sha[1],
                arp_header->arp_sha[2],
                arp_header->arp_sha[3],
                arp_header->arp_sha[4],
                arp_header->arp_sha[5]);

        snprintf(dst_mac, sizeof(dst_mac), "%02x:%02x:%02x:%02x:%02x:%02x",
                 arp_header->arp_tha[0],
                arp_header->arp_tha[1],
                arp_header->arp_tha[2],
                arp_header->arp_tha[3],
                arp_header->arp_tha[4],
                arp_header->arp_tha[5]);

        srcMac = src_mac;
        dstMac = dst_mac;

        length = ETHER_HDR_LEN + sizeof(struct ether_arp);

        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];
        time (&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
        timeStr = buffer;

        ip_version.push_back(-1);
        ip_header_length.push_back(-1);
        typeof_service.push_back(-1);
        ip_total_length.push_back(-1);
        ip_id.push_back(-1);
        ip_MF.push_back(-1);
        ip_DF.push_back(-1);
        iP_fragment_offset.push_back(-1);
        ip_ttl.push_back(-1);
        ip_protocol.push_back(-1);

        ipv6_version.push_back(-1);
        ipv6_traffic_class.push_back(-1);
        ipv6_flow_label.push_back(-1);
        ipv6_payload_length.push_back(-1);
        ipv6_next_header.push_back(-1);
        ipv6_hop_limit.push_back(-1);
    }
        break;
    default:
        protocol_type = "OTHER";
        ip_version.push_back(-1);
        ip_header_length.push_back(-1);
        typeof_service.push_back(-1);
        ip_total_length.push_back(-1);
        ip_id.push_back(-1);
        ip_MF.push_back(-1);
        ip_DF.push_back(-1);
        iP_fragment_offset.push_back(-1);
        ip_ttl.push_back(-1);
        ip_protocol.push_back(-1);

        ipv6_version.push_back(-1);
        ipv6_traffic_class.push_back(-1);
        ipv6_flow_label.push_back(-1);
        ipv6_payload_length.push_back(-1);
        ipv6_next_header.push_back(-1);
        ipv6_hop_limit.push_back(-1);
    }

    Protocol_Type.push_back(protocol_type);

    time_t rawTime = pkthdr->ts.tv_sec;
    char *timeCStr = ctime(&rawTime);
    timeStr = QString::fromLocal8Bit(timeCStr).trimmed();
    length = pkthdr->len;
    protocolType = QString::fromUtf8(protocol_type);
    const char *srcMacStr = ether_ntoa((struct ether_addr*)eth_header->ether_shost);
    srcMac = QString::fromUtf8(srcMacStr);
    const char *dstMacStr = ether_ntoa((struct ether_addr*)eth_header->ether_dhost);
    dstMac = QString::fromUtf8(dstMacStr);

    source_mac.push_back(srcMac);
    destination_mac.push_back(dstMac);
    typeof_ether.push_back(ntohs(eth_header->ether_type));

    if(protocol_type=="UDP"){
        struct udphdr* udp_header = (struct udphdr*)(packet + ETHER_HDR_LEN + ip_packet->ip_hl * 4);
        source_port.push_back(ntohs(udp_header->uh_sport));
        destination_port.push_back(ntohs(udp_header->uh_dport));
        udp_length.push_back(ntohs(udp_header->uh_ulen));
        udp_checksum.push_back(ntohs(udp_header->uh_sum));


        sequence_number.push_back(-1);
        acknowledge_number.push_back(-1);
        data_offset.push_back(-1);
        Reserved.push_back(-1);
        flags.push_back("null");
        window_size.push_back(-1);
        tcp_checksum.push_back(-1);
        urgent_point.push_back(-1);

        typeof_icmp.push_back(-1);
        codeof_icmp.push_back(-1);
        icmp_checksum.push_back(-1);
        sequence_number_icmp.push_back(-1);

        type_vec.push_back(-1);
        checksum_vec.push_back(-1);
        group_address_str_vec.push_back("null");

        typeof_hardware.push_back(-1);
        typeof_protosol.push_back(-1);
        hardware_address_length.push_back(-1);
        protosol_address_length.push_back(-1);
        opcode.push_back(-1);
        type.push_back("NULL");
    }
    else if(protocol_type=="TCP"){
        struct tcphdr *tcp_header = (struct tcphdr*)(packet + ETHER_HDR_LEN + ip_packet->ip_hl * 4);
        source_port.push_back(ntohs(tcp_header->th_sport));
        destination_port.push_back(ntohs(tcp_header->th_dport));
        sequence_number.push_back(ntohl(tcp_header->th_seq));
        acknowledge_number.push_back(ntohl(tcp_header->th_ack));
        data_offset.push_back(tcp_header->th_off);
        Reserved.push_back(tcp_header->th_x2);
        if(tcp_header->th_flags & TH_FIN) flags.push_back("FIN ");
        if(tcp_header->th_flags & TH_SYN) flags.push_back("SYN ");
        if(tcp_header->th_flags & TH_RST) flags.push_back("RST ");
        if(tcp_header->th_flags & TH_PUSH) flags.push_back("PUSH ");
        if(tcp_header->th_flags & TH_ACK) flags.push_back("ACK ");
        if(tcp_header->th_flags & TH_URG) flags.push_back("URG ");
        window_size.push_back(ntohs(tcp_header->th_win));
        tcp_checksum.push_back(ntohs(tcp_header->th_sum));
        urgent_point.push_back(ntohs(tcp_header->th_urp));


        udp_length.push_back(-1);
        udp_checksum.push_back(-1);

        typeof_icmp.push_back(-1);
        codeof_icmp.push_back(-1);
        icmp_checksum.push_back(-1);
        sequence_number_icmp.push_back(-1);

        type_vec.push_back(-1);
        checksum_vec.push_back(-1);
        group_address_str_vec.push_back("null");

        typeof_hardware.push_back(-1);
        typeof_protosol.push_back(-1);
        hardware_address_length.push_back(-1);
        protosol_address_length.push_back(-1);
        opcode.push_back(-1);
        type.push_back("NULL");
    }
    else if(protocol_type=="ICMP"){
        struct icmphdr *icmp_header = (struct icmphdr*)(packet + ETHER_HDR_LEN + ip_packet->ip_hl * 4);
        typeof_icmp.push_back(icmp_header->type);
        codeof_icmp.push_back(icmp_header->code);
        icmp_checksum.push_back(ntohs(icmp_header->checksum));

        if(icmp_header->type == ICMP_ECHO || icmp_header->type == ICMP_ECHOREPLY){
            sequence_number_icmp.push_back(ntohs(icmp_header->un.echo.sequence));
        }


        source_port.push_back(-1);
        destination_port.push_back(-1);
        sequence_number.push_back(-1);
        acknowledge_number.push_back(-1);
        data_offset.push_back(-1);
        Reserved.push_back(-1);
        flags.push_back("null");
        window_size.push_back(-1);
        tcp_checksum.push_back(-1);
        urgent_point.push_back(-1);

        udp_length.push_back(-1);
        udp_checksum.push_back(-1);

        type_vec.push_back(-1);
        checksum_vec.push_back(-1);
        group_address_str_vec.push_back("null");


        typeof_hardware.push_back(-1);
        typeof_protosol.push_back(-1);
        hardware_address_length.push_back(-1);
        protosol_address_length.push_back(-1);
        opcode.push_back(-1);
        type.push_back("NULL");
    }

    else if(protocol_type=="IGMP"){
        struct igmp_header* igmp_header;
        igmp_header = (struct igmp_header*)(packet + ETHER_HDR_LEN + ip_packet->ip_hl * 4);;

        type_vec.push_back(igmp_header->type);
        checksum_vec.push_back(ntohs(igmp_header->checksum));
        uint32_t group_address = ntohl(igmp_header->group_address);
        std::stringstream sstream;
        sstream << ((group_address >> 24) & 0xFF) << '.'
                << ((group_address >> 16) & 0xFF) << '.'
                << ((group_address >> 8) & 0xFF) << '.'
                << (group_address & 0xFF);
        QString qstr = QString::fromStdString(sstream.str());
        group_address_str_vec.push_back(qstr);


        source_port.push_back(-1);
        destination_port.push_back(-1);
        sequence_number.push_back(-1);
        acknowledge_number.push_back(-1);
        data_offset.push_back(-1);
        Reserved.push_back(-1);
        flags.push_back("null");
        window_size.push_back(-1);
        tcp_checksum.push_back(-1);
        urgent_point.push_back(-1);

        udp_length.push_back(-1);
        udp_checksum.push_back(-1);

        typeof_icmp.push_back(-1);
        codeof_icmp.push_back(-1);
        icmp_checksum.push_back(-1);
        sequence_number_icmp.push_back(-1);

        typeof_hardware.push_back(-1);
        typeof_protosol.push_back(-1);
        hardware_address_length.push_back(-1);
        protosol_address_length.push_back(-1);
        opcode.push_back(-1);
        type.push_back("NULL");

    }
    else if(protocol_type=="IPv6"){
        source_port.push_back(-1);
        destination_port.push_back(-1);
        sequence_number.push_back(-1);
        acknowledge_number.push_back(-1);
        data_offset.push_back(-1);
        Reserved.push_back(-1);
        flags.push_back("null");
        window_size.push_back(-1);
        tcp_checksum.push_back(-1);
        urgent_point.push_back(-1);

        udp_length.push_back(-1);
        udp_checksum.push_back(-1);

        typeof_icmp.push_back(-1);
        codeof_icmp.push_back(-1);
        icmp_checksum.push_back(-1);
        sequence_number_icmp.push_back(-1);

        type_vec.push_back(-1);
        checksum_vec.push_back(-1);
        group_address_str_vec.push_back("null");

        typeof_hardware.push_back(-1);
        typeof_protosol.push_back(-1);
        hardware_address_length.push_back(-1);
        protosol_address_length.push_back(-1);
        opcode.push_back(-1);
        type.push_back("NULL");
    }

    else if(protocol_type=="ARP"){
        struct arp_header *arp_header = (struct arp_header*)(packet + ETHER_HDR_LEN);
        typeof_hardware.push_back(ntohs(arp_header->arp_hardware_type));
        typeof_protosol.push_back(ntohs(arp_header->arp_protocol_type));
        hardware_address_length.push_back(arp_header->arp_hardware_len);
        protosol_address_length.push_back(arp_header->arp_protocol_len);
        opcode.push_back(ntohs(arp_header->arp_opcode));

        if(ntohs(arp_header->arp_opcode) == ARPOP_REQUEST) type.push_back("Request");
        else if(ntohs(arp_header->arp_opcode) == ARPOP_REPLY) type.push_back("Reply");
        else type.push_back("Unknown");


        source_port.push_back(-1);
        destination_port.push_back(-1);
        sequence_number.push_back(-1);
        acknowledge_number.push_back(-1);
        data_offset.push_back(-1);
        Reserved.push_back(-1);
        flags.push_back("null");
        window_size.push_back(-1);
        tcp_checksum.push_back(-1);
        urgent_point.push_back(-1);

        udp_length.push_back(-1);
        udp_checksum.push_back(-1);

        typeof_icmp.push_back(-1);
        codeof_icmp.push_back(-1);
        icmp_checksum.push_back(-1);
        sequence_number_icmp.push_back(-1);

        type_vec.push_back(-1);
        checksum_vec.push_back(-1);
        group_address_str_vec.push_back("null");

    }
    else if(protocol_type=="OTHER"){
        source_port.push_back(-1);
        destination_port.push_back(-1);
        sequence_number.push_back(-1);
        acknowledge_number.push_back(-1);
        data_offset.push_back(-1);
        Reserved.push_back(-1);
        flags.push_back("null");
        window_size.push_back(-1);
        tcp_checksum.push_back(-1);
        urgent_point.push_back(-1);

        udp_length.push_back(-1);
        udp_checksum.push_back(-1);

        typeof_icmp.push_back(-1);
        codeof_icmp.push_back(-1);
        icmp_checksum.push_back(-1);
        sequence_number_icmp.push_back(-1);

        type_vec.push_back(-1);
        checksum_vec.push_back(-1);
        group_address_str_vec.push_back("null");

        typeof_hardware.push_back(-1);
        typeof_protosol.push_back(-1);
        hardware_address_length.push_back(-1);
        protosol_address_length.push_back(-1);
        opcode.push_back(-1);
        type.push_back("NULL");

        srcIp="UNKONWN";
        dstIp="UNKONWN";
    }

    Packets.push_back(std::vector<u_char>(packet, packet + pkthdr->len));

    total_length.push_back(length);

    emit thread->addPacketInfo(number++, timeStr, length, protocolType, srcMac, dstMac, srcIp, dstIp);
}



//Packet capture thread started.
void Widget::on_capture_start_clicked()
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    QString dev = ui->choose_device->currentText();

    handle = pcap_open_live(dev.toStdString().c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        QMessageBox::warning(this, "Error", "Couldn't open device: " + QString(errbuf));
        return;
    }

    thread = new PacketCaptureThread(handle, this);
    connect(thread, &PacketCaptureThread::addPacketInfo, this, &Widget::onAddPacketInfo);
    thread->start();

    label_stop->hide();
    label_start->show();
}



//Packet capture thread stopped.
void Widget::on_capture_stop_clicked() {
    if (thread != nullptr) {
        label_start->hide();
        label_wait->show();
        QApplication::processEvents();
        thread->stop();
        pcap_close(thread->getHandle());
        thread->wait();
        delete thread;
        thread = nullptr;

        label_wait->hide();
        label_stop->show();
    }
}



//Saving the packet capture results to a file.
void Widget::on_result_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "/home",
                                                    tr("Text Files (*.txt)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    QTreeWidgetItemIterator it(ui->basic_information);
    QString str;
    int row=0;
    while (*it) {
        for(int i = 0; i < (*it)->columnCount(); ++i) {
            out << (*it)->text(i);
            if(i < (*it)->columnCount() - 1)
                out << ", ";
        }
        out << "\n";
        const std::vector<u_char> &Packet = Packets[row];
        str = formatPacket(Packet);
        out << str;
        ++it;
        ++row;
    }
}



//Packet reassembly function.
void Widget::on_packet_reassemble_clicked()
{
    int current_number;
    int last_number = Protocol_Type.size();;
    QTreeWidgetItem* currentItem = ui->basic_information->currentItem();
    if (currentItem != nullptr) {
        current_number = currentItem->text(0).toInt();
    } else {
        QMessageBox::warning(this, "Error", "No item selected. ");
        return;
    }

    int target_id = ip_id[current_number];
    std::vector<u_char> reassembled_packet;

    if(Protocol_Type[current_number]=="OTHER" ||Protocol_Type[current_number]=="ARP" ||Protocol_Type[current_number]=="IPv6"){
        QMessageBox::warning(this, "Error", "Non-IP type protocol header. ");
        return;
    }

    if(ip_DF[current_number]==1){
        QMessageBox::warning(this, "Error", "DF=1, the message cannot be fragmented. ");
        return;
    }

    for (int j = 0; j < last_number; ++j) {
        if (ip_id[j] == target_id) {
            bool flag=true;
            for(int i=0;i<j;i++){
                if(ip_id[i]==target_id&&iP_fragment_offset[j]==iP_fragment_offset[i]){
                    flag = false;
                    repeat_ippacket.push_back(j);
                }
            }
            if(flag) number_of_same_id_packets.push_back(j);
        }
    }
    std::sort(number_of_same_id_packets.begin(), number_of_same_id_packets.end(), [&](int a, int b){
        return iP_fragment_offset[a] < iP_fragment_offset[b];
    });



    for (int j = 0; j < number_of_same_id_packets.size(); ++j) {
        if (j == 0) {
            reassembled_packet.insert(reassembled_packet.end(), Packets[number_of_same_id_packets[j]].begin(), Packets[number_of_same_id_packets[j]].end());
        } else {
            reassembled_packet.insert(reassembled_packet.end(), Packets[number_of_same_id_packets[j]].begin() + ip_header_length[number_of_same_id_packets[j]]*4+14, Packets[number_of_same_id_packets[j]].end());
        }
    }

    uint16_t total_length = htons(reassembled_packet.size() - 14);
    std::memcpy(&reassembled_packet[2 + 14], &total_length, sizeof(total_length));

    reassembled_packet[6 + 14] &= ~(1 << 5);
    uint16_t checksum = compute_ip_checksum(reassembled_packet);
    std::memcpy(&reassembled_packet[24], &checksum, sizeof(checksum));

    final_reassembled_packet = formatPacket(reassembled_packet);

    reassemble_packet_length = reassembled_packet.size();

    reassemble_result *newwidget =new reassemble_result;
    newwidget->show();
}


//Filtering and determining various types of packets.
void Widget::on_tcp_clicked(bool checked)
{
    if(checked) flag_tcp=1;
    else flag_tcp=0;
}


void Widget::on_udp_clicked(bool checked)
{
    if(checked) flag_udp=1;
    else flag_udp=0;
}


void Widget::on_icmp_clicked(bool checked)
{
    if(checked) flag_icmp=1;
    else flag_icmp=0;
}


void Widget::on_igmp_clicked(bool checked)
{
    if(checked) flag_igmp=1;
    else flag_igmp=0;
}


void Widget::on_ipv6_clicked(bool checked)
{
    if(checked) flag_ipv6=1;
    else flag_ipv6=0;
}


void Widget::on_arp_clicked(bool checked)
{
    if(checked) flag_arp=1;
    else flag_arp=0;
}


void Widget::on_other_clicked(bool checked)
{
    if(checked) flag_other=1;
    else flag_other=0;
}


//Outputting real-time network traffic.
void Widget::print_network_traffic(){
    double kbs = totalSize / 1024.0;
    label_network_traffic->setText(QString("%1 KB/s").arg(kbs));
    totalSize = 0;
}


//Exit.
void Widget::on_exit_clicked()
{
    QApplication::quit();
}


//Filtering packets with different source IP and destination IP addresses.
void Widget::on_packet_filter_clicked()
{
    input_src_ip = ui->src_ip->text();
    input_dst_ip = ui->dst_ip->text();

    if(input_src_ip!=NULL){
        for (int i=0; i<ui->basic_information->topLevelItemCount(); ) {
            QTreeWidgetItem* item = ui->basic_information->topLevelItem(i);
            if(item->text(6) != input_src_ip) {
                delete ui->basic_information->takeTopLevelItem(i);
            } else {
                ++i;
            }
        }
    }

    if(input_dst_ip!=NULL){
        for (int i=0; i<ui->basic_information->topLevelItemCount(); ) {
            QTreeWidgetItem* item = ui->basic_information->topLevelItem(i);
            if(item->text(7) != input_dst_ip) {
                delete ui->basic_information->takeTopLevelItem(i);
            } else {
                ++i;
            }
        }
    }
}


