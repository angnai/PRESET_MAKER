#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QByteArray>
#include <QMessageBox>
#include <QList>
#include <QDesktopServices>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDirIterator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

#define ALL_DISABLE 0
#define INIT_FRAME  1
#define	SOC_INDEX_ALL_FRAME	2
#define	SOC_INDEX_ALLCH_FRAME	3
#define	SOC_INDEX_CH_FRAME	4
#define	SOC_INDEX_CE_FRAME	5
#define	SOC_INDEX_CHCE_FRAME	6
#define	NAND_INDEX_ALL_FRAME	7
#define	NAND_INDEX_ALLCH_FRAME	8
#define	NAND_INDEX_CH_FRAME	9
#define	NAND_INDEX_CE_FRAME	10
#define	NAND_INDEX_CHCE_FRAME	11
#define SI_FRAME 12
#define PARA_FRAME 13

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Make();
    void Write();
    void Read();
    void DefaultValueOfComboBox();
    void Enable_Frame(int n);
    void Enable_SoC_CB(bool checked);
    void Enable_Nand_CB(bool checked);
    int Get_IndexNum(QString mm);
    void PresetCommand_Init();
    void Search_SerialPort();
    void check_all_x();
    QString Get_PresetCmd(QString str);
    void Set_CmdParameter(int testcnt, QString str);
    void ViewParameter(int testcnt);
    QString ContainString(QString str);

private slots:
    void on_Make_CMD_clicked();

    void on_Sel_CB_currentIndexChanged(const QString &arg1);
    void on_sel_soc_index_select_currentIndexChanged(const QString &arg1);

    void on_Add_CMD_clicked();

    void on_Del_CMD_clicked();

    void on_Up_CMD_clicked();

    void on_Down_CMD_clicked();

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

    void on_Add_CMD_2_clicked();

    void on_Exit_Preset_CMD_clicked();

    void on_MOVE_PRESET_CMD_clicked();

    void on_MOVE_RUN_CMD_clicked();

    void on_Chk_Preset_CMD_clicked();

    void on_Exit_Run_CMD_clicked();

    void on_Run_CMD_clicked();

    void on_log_reflash_CMD_clicked();

    void on_log_parsing_CMD_clicked();

    void on_Chk_Next_CMD_3_clicked();

private:
    QString output1;
    QString output2;

    QString jsonStr;

    QJsonObject title;

    QJsonObject presetlist;

    QJsonObject cmdlist;
    QJsonObject soclist;
    QJsonObject nandlist;
    QJsonObject selindexlist;
    QJsonObject sellist;
    QJsonObject vallist;

    QJsonObject index1list;
    QJsonObject index2list;
    QJsonObject index3list;
    QJsonObject index4list;


    QJsonDocument wrt;
    QJsonDocument rd;

    QFile file;

    QString indexSet[30];
    int indexSetCnt;

    QList<QString> cmdString;
    QList<QString> presetString;
    QList<QString> logPathString;

    int check_si_list;
    int check_si_total;

    int index_soc_ctrl_ds[5];
    int index_soc_re_ds[5];
    int index_soc_dqs_ds[5];
    int index_soc_dq_ds[5];
    int index_soc_dqs_odt[5];
    int index_soc_dq_odt[5];

    int index_nand_ds[5];
    int index_nand_podt[5];
    int index_nand_rodt[5];
    int index_nand_comodt[5];

    int soc_ctrl_ds[50][12];
    int soc_re_ds[50][12];
    int soc_dqs_ds[50][12];
    int soc_dqs_odt[50][12];
    int soc_dq_ds[50][12];
    int soc_dq_odt[50][12];

    int nand_ce0_ds[50][12];
    int nand_ce0_podt[50][12];
    int nand_ce0_rodt[50][12];

    int nand_ce1_ds[50][12];
    int nand_ce1_podt[50][12];
    int nand_ce1_rodt[50][12];

    int nand_ce2_ds[50][12];
    int nand_ce2_podt[50][12];
    int nand_ce2_rodt[50][12];

    int nand_ce3_ds[50][12];
    int nand_ce3_podt[50][12];
    int nand_ce3_rodt[50][12];


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
