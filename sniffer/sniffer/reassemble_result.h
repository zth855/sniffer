#ifndef REASSEMBLE_RESULT_H
#define REASSEMBLE_RESULT_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QLabel>

namespace Ui {
class reassemble_result;
}

class reassemble_result : public QWidget
{
    Q_OBJECT

public:
    explicit reassemble_result(QWidget *parent = nullptr);
    ~reassemble_result();

private:
    Ui::reassemble_result *ui;

    QLabel* reassembled_packet_length = new QLabel(this);
};

#endif // REASSEMBLE_RESULT_H
