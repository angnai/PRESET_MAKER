#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    output1 = "preset.ini";
    output2 = "TestCmd.ini";

    jsonStr = "info.json";
    if(QFile::exists(QApplication::applicationDirPath()+"/"+jsonStr) == false)
        Make();

    Read();

    DefaultValueOfComboBox();
    Enable_Frame(ALL_DISABLE);
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    Enable_SoC_CB(false);
    Enable_Nand_CB(false);

    //ui->Main_frame->hide();
    ui->Preset_frame->hide();
    ui->Run_frame->hide();
    ui->Check_frame->hide();

    Search_SerialPort();
    PresetCommand_Init();


    indexSetCnt = 0;
}

MainWindow::~MainWindow()
{
    index1list["soc_dqs_ds"] = ui->set_soc_ds_dqs_1->currentText();
    index1list["soc_dqs_odt"] = ui->set_soc_odt_dqs_1->currentText();
    index1list["soc_dq_ds"] = ui->set_soc_ds_dq_1->currentText();
    index1list["soc_dq_odt"] = ui->set_soc_odt_dq_1->currentText();
    index1list["soc_re_ds"] = ui->set_soc_ds_re_1->currentText();
    index1list["soc_ctrl_ds"] = ui->set_soc_ds_ctrl_1->currentText();
    index1list["nand_ds"] = ui->set_nand_ds_1->currentText();
    index1list["nand_podt"] = ui->set_nand_odt_podt_1->currentText();
    index1list["nand_rodt"] = ui->set_nand_odt_rodt_1->currentText();
    title["index1"] = index1list;

    index2list["soc_dqs_ds"] = ui->set_soc_ds_dqs_2->currentText();
    index2list["soc_dqs_odt"] = ui->set_soc_odt_dqs_2->currentText();
    index2list["soc_dq_ds"] = ui->set_soc_ds_dq_2->currentText();
    index2list["soc_dq_odt"] = ui->set_soc_odt_dq_2->currentText();
    index2list["soc_re_ds"] = ui->set_soc_ds_re_2->currentText();
    index2list["soc_ctrl_ds"] = ui->set_soc_ds_ctrl_2->currentText();
    index2list["nand_ds"] = ui->set_nand_ds_2->currentText();
    index2list["nand_podt"] = ui->set_nand_odt_podt_2->currentText();
    index2list["nand_rodt"] = ui->set_nand_odt_rodt_2->currentText();
    title["index2"] = index2list;

    index3list["soc_dqs_ds"] = ui->set_soc_ds_dqs_3->currentText();
    index3list["soc_dqs_odt"] = ui->set_soc_odt_dqs_3->currentText();
    index3list["soc_dq_ds"] = ui->set_soc_ds_dq_3->currentText();
    index3list["soc_dq_odt"] = ui->set_soc_odt_dq_3->currentText();
    index3list["soc_re_ds"] = ui->set_soc_ds_re_3->currentText();
    index3list["soc_ctrl_ds"] = ui->set_soc_ds_ctrl_3->currentText();
    index3list["nand_ds"] = ui->set_nand_ds_3->currentText();
    index3list["nand_podt"] = ui->set_nand_odt_podt_3->currentText();
    index3list["nand_rodt"] = ui->set_nand_odt_rodt_3->currentText();
    title["index3"] = index3list;

    index4list["soc_dqs_ds"] = ui->set_soc_ds_dqs_4->currentText();
    index4list["soc_dqs_odt"] = ui->set_soc_odt_dqs_4->currentText();
    index4list["soc_dq_ds"] = ui->set_soc_ds_dq_4->currentText();
    index4list["soc_dq_odt"] = ui->set_soc_odt_dq_4->currentText();
    index4list["soc_re_ds"] = ui->set_soc_ds_re_4->currentText();
    index4list["soc_ctrl_ds"] = ui->set_soc_ds_ctrl_4->currentText();
    index4list["nand_ds"] = ui->set_nand_ds_4->currentText();
    index4list["nand_podt"] = ui->set_nand_odt_podt_4->currentText();
    index4list["nand_rodt"] = ui->set_nand_odt_rodt_4->currentText();
    title["index4"] = index4list;

    cmdlist["val"] = ui->Sel_CB->currentText();
    title["cmd_list"] = cmdlist;

    sellist["val"] = ui->sel_soc_index_select->currentText();
    title["sel_list"] = sellist;

    vallist["init_start"] = ui->init_start_txt->text();
    vallist["init_end"] = ui->init_end_txt->text();
    vallist["init_freq"] = ui->init_freq_txt->text();

    vallist["all_index"] = ui->all_index_txt->text();
    vallist["all_index_2"] = ui->all_index_txt_2->text();

    vallist["all_ch_ce0_2"] = ui->all_ch_ce0_txt_2->text();
    vallist["all_ch_ce1_2"] = ui->all_ch_ce1_txt_2->text();
    vallist["all_ch_ce2_2"] = ui->all_ch_ce2_txt_2->text();
    vallist["all_ch_ce3_2"] = ui->all_ch_ce3_txt_2->text();

    vallist["ce_ce_2"] = ui->ce_ce_txt_2->text();
    vallist["ce_index_2"] = ui->ce_index_txt_2->text();

    vallist["ch_ch_2"] = ui->ch_ch_txt_2->text();
    vallist["ch_ce0_2"] = ui->ch_ce0_txt_2->text();
    vallist["ch_ce1_2"] = ui->ch_ce1_txt_2->text();
    vallist["ch_ce2_2"] = ui->ch_ce2_txt_2->text();
    vallist["ch_ce3_2"] = ui->ch_ce3_txt_2->text();

    vallist["ch_ce_ch"] = ui->ch_ce_ch_txt->text();
    vallist["ch_ce_index"] = ui->ch_ce_index_txt->text();
    vallist["ch_ce_ch_2"] = ui->ch_ce_ch_txt_2->text();
    vallist["ch_ce_ce_2"] = ui->ch_ce_ce_txt_2->text();
    vallist["ch_ce_index_2"] = ui->ch_ce_index_txt_2->text();

    vallist["si_ch0"] = ui->si_ch0_txt->text();
    vallist["si_ch1"] = ui->si_ch1_txt->text();
    vallist["si_ch2"] = ui->si_ch2_txt->text();
    vallist["si_ch3"] = ui->si_ch3_txt->text();
    vallist["si_ch4"] = ui->si_ch4_txt->text();
    vallist["si_ch5"] = ui->si_ch5_txt->text();
    vallist["si_ch6"] = ui->si_ch6_txt->text();
    vallist["si_ch7"] = ui->si_ch7_txt->text();
    vallist["si_ch8"] = ui->si_ch8_txt->text();
    vallist["si_ch9"] = ui->si_ch9_txt->text();
    vallist["si_ch10"] = ui->si_ch10_txt->text();
    vallist["si_ch11"] = ui->si_ch11_txt->text();
    vallist["si_freq"] = ui->si_freq_txt->text();

    vallist["para_test_cnt"] = ui->para_test_cnt_txt->text();
    vallist["para_random"] = ui->para_random_txt->text();
    vallist["para_pattern"] = ui->para_pattern_txt->text();
    vallist["para_diff"] = ui->para_diff_txt->text();

    vallist["vref_mode"] = ui->vref_mode_txt->text();
    vallist["vref_channel"] = ui->vref_channel_txt->text();
    vallist["vref_mV"] = ui->vref_mV_txt->text();
    title["val_list"] = vallist;

    Write();

    delete ui;
}

void MainWindow::Search_SerialPort()
{
    int cnt;
    cnt = ui->port_CB->count();
    for(int i=0;i<cnt;i++){
        ui->port_CB->removeItem(0);
    }

    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        ui->port_CB->addItem(port.portName());
    }

}

void MainWindow::PresetCommand_Init()
{

    cmdString.empty();
    cmdString.append("power_on");
    cmdString.append("n init ");
    cmdString.append("n si ");
    cmdString.append("n get_window all");
    cmdString.append("n get_para");
    cmdString.append("n si_para ");
    cmdString.append("power_off");
    cmdString.append("add_index_val ");
    //cmdString.append("n set_ds_to_soc ");
    //cmdString.append("n set_ds_to_nand ");
    //cmdString.append("n set_odt_to_soc ");
    //cmdString.append("n set_odt_to_nand ");
    cmdString.append("n sel_index_to_soc ");
    cmdString.append("n sel_index_to_nand ");
    cmdString.append("n set_vref ");
    cmdString.append("n get_vref ");


    presetString.empty();
    presetString.append("power_on");
    presetString.append("init");
    presetString.append("si");
    presetString.append("get_window");
    presetString.append("get_para");
    presetString.append("si_para");
    presetString.append("power_off");
    presetString.append("add_index_val");
    //presetString.append("soc_ds");
    //presetString.append("nand_ds");
    //presetString.append("soc_odt");
    //presetString.append("nand_odt");
    presetString.append("soc_index");
    presetString.append("nand_index");
    presetString.append("set_vref");
    presetString.append("get_vref");

}

void MainWindow::Make()
{
    int i,cnt;
    QJsonArray jsonarr;

    file.setFileName(QApplication::applicationDirPath()+"/"+jsonStr);
    file.open(QIODevice::ReadWrite|QIODevice::Truncate);
    file.close();

    presetlist["list"] = "";
    title["preset_list"] = presetlist;

    cnt = jsonarr.count();
    for(i=0;i<cnt;i++) jsonarr.removeLast();
    jsonarr.append("x");
    jsonarr.append("50");
    jsonarr.append("35");
    jsonarr.append("25");
    jsonarr.append("18");
    soclist["ds"] = jsonarr;

    cnt = jsonarr.count();
    for(i=0;i<cnt;i++) jsonarr.removeLast();
    jsonarr.append("x");
    jsonarr.append("NONE");
    jsonarr.append("150");
    jsonarr.append("100");
    jsonarr.append("75");
    jsonarr.append("50");
    jsonarr.append("30");
    soclist["odt"] = jsonarr;
    title["soc_list"] = soclist;

    cnt = jsonarr.count();
    for(i=0;i<cnt;i++) jsonarr.removeLast();
    jsonarr.append("x");
    jsonarr.append("UNDER");
    jsonarr.append("NORMAL");
    jsonarr.append("OVER");
    nandlist["ds"] = jsonarr;

    cnt = jsonarr.count();
    for(i=0;i<cnt;i++) jsonarr.removeLast();
    jsonarr.append("x");
    jsonarr.append("NONE");
    jsonarr.append("150");
    jsonarr.append("100");
    jsonarr.append("75");
    jsonarr.append("50");
    nandlist["odt"] = jsonarr;
    title["nand_list"] = nandlist;

    cnt = jsonarr.count();
    for(i=0;i<cnt;i++) jsonarr.removeLast();
    jsonarr.append("power_on");
    jsonarr.append("add_index_val");
    jsonarr.append("sel_index_to_soc");
    jsonarr.append("sel_index_to_nand");
    jsonarr.append("init");
    jsonarr.append("si");
    jsonarr.append("get_window");
    jsonarr.append("get_para");
    jsonarr.append("si_para");
    jsonarr.append("set_vref");
    jsonarr.append("get_vref");
    jsonarr.append("power_off");
    cmdlist["list"] = jsonarr;
    cmdlist["val"] = "power_on";
    title["cmd_list"] = cmdlist;

    cnt = jsonarr.count();
    for(i=0;i<cnt;i++) jsonarr.removeLast();
    jsonarr.append("all");
    jsonarr.append("all_ch");
    jsonarr.append("ch");
    jsonarr.append("ce");
    jsonarr.append("ch_ce");
    sellist["list"] = jsonarr;
    sellist["val"] = "all";
    title["sel_list"] = sellist;

    vallist["init_start"] = "0";
    vallist["init_end"] = "11";
    vallist["init_freq"] = "600";

    vallist["all_index"] = "1";
    vallist["all_index_2"] = "1";

    vallist["all_ch_ce0_2"] = "1";
    vallist["all_ch_ce1_2"] = "1";
    vallist["all_ch_ce2_2"] = "1";
    vallist["all_ch_ce3_2"] = "1";

    vallist["ch_ch_2"] = "0";
    vallist["ch_ce0_2"] = "1";
    vallist["ch_ce1_2"] = "1";
    vallist["ch_ce2_2"] = "1";
    vallist["ch_ce3_2"] = "1";

    vallist["ce_ce_2"] = "0";
    vallist["ce_index_2"] = "1";

    vallist["ch_ce_ch"] = "0";
    vallist["ch_ce_index"] = "1";
    vallist["ch_ce_ch_2"] = "0";
    vallist["ch_ce_ce_2"] = "0";
    vallist["ch_ce_index_2"] = "1";

    vallist["si_ch0"] = "33";
    vallist["si_ch1"] = "33";
    vallist["si_ch2"] = "33";
    vallist["si_ch3"] = "33";
    vallist["si_ch4"] = "33";
    vallist["si_ch5"] = "33";
    vallist["si_ch6"] = "33";
    vallist["si_ch7"] = "33";
    vallist["si_ch8"] = "ff";
    vallist["si_ch9"] = "ff";
    vallist["si_ch10"] = "ff";
    vallist["si_ch11"] = "ff";
    vallist["si_freq"] = "600";

    vallist["para_test_cnt"] = "10";
    vallist["para_random"] = "0";
    vallist["para_pattern"] = "504065060";
    vallist["para_diff"] = "3";

    vallist["vref_mode"] = "all";
    vallist["vref_channel"] = "all";
    vallist["vref_mV"] = "600";
    title["val_list"] = vallist;


    Write();

}

void MainWindow::Write()
{
    file.setFileName(QApplication::applicationDirPath()+"/"+jsonStr);
    file.open(QIODevice::ReadWrite|QIODevice::Truncate);
    wrt.setObject(title);
    file.write(wrt.toJson());
    file.close();
}

void MainWindow::Read()
{
    file.setFileName(QApplication::applicationDirPath()+"/"+jsonStr);
    file.open(QIODevice::ReadOnly);

    QByteArray load_data;
    load_data = file.readAll();
    rd = QJsonDocument::fromJson(load_data);
    file.close();

    presetlist = rd.object()["preset_list"].toObject();
    soclist = rd.object()["soc_list"].toObject();
    nandlist = rd.object()["nand_list"].toObject();
    index1list = rd.object()["index1"].toObject();
    index2list = rd.object()["index2"].toObject();
    index3list = rd.object()["index3"].toObject();
    index4list = rd.object()["index4"].toObject();

    cmdlist = rd.object()["cmd_list"].toObject();
    vallist = rd.object()["val_list"].toObject();
    sellist = rd.object()["sel_list"].toObject();


    title["preset_list"] = presetlist;
    title["soc_list"] = soclist;
    title["nand_list"] = nandlist;
    title["cmd_list"] = cmdlist;
    title["cmd_list"] = cmdlist;
    title["val_list"] = vallist;
    title["sel_list"] = sellist;
}

void MainWindow::DefaultValueOfComboBox()
{
    int i,cnt;
    QJsonArray jsonarr;
    QString jsonval;

    jsonarr = soclist["ds"].toArray();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->set_soc_ds_dqs_1->addItem(jsonarr[0].toString());
        ui->set_soc_ds_dqs_2->addItem(jsonarr[0].toString());
        ui->set_soc_ds_dqs_3->addItem(jsonarr[0].toString());
        ui->set_soc_ds_dqs_4->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }
    jsonarr = soclist["ds"].toArray();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->set_soc_ds_dq_1->addItem(jsonarr[0].toString());
        ui->set_soc_ds_dq_2->addItem(jsonarr[0].toString());
        ui->set_soc_ds_dq_3->addItem(jsonarr[0].toString());
        ui->set_soc_ds_dq_4->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }
    jsonarr = soclist["odt"].toArray();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->set_soc_odt_dqs_1->addItem(jsonarr[0].toString());
        ui->set_soc_odt_dqs_2->addItem(jsonarr[0].toString());
        ui->set_soc_odt_dqs_3->addItem(jsonarr[0].toString());
        ui->set_soc_odt_dqs_4->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }
    jsonarr = soclist["odt"].toArray();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->set_soc_odt_dq_1->addItem(jsonarr[0].toString());
        ui->set_soc_odt_dq_2->addItem(jsonarr[0].toString());
        ui->set_soc_odt_dq_3->addItem(jsonarr[0].toString());
        ui->set_soc_odt_dq_4->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }
    jsonarr = soclist["ds"].toArray();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->set_soc_ds_re_1->addItem(jsonarr[0].toString());
        ui->set_soc_ds_re_2->addItem(jsonarr[0].toString());
        ui->set_soc_ds_re_3->addItem(jsonarr[0].toString());
        ui->set_soc_ds_re_4->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }
    jsonarr = soclist["ds"].toArray();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->set_soc_ds_ctrl_1->addItem(jsonarr[0].toString());
        ui->set_soc_ds_ctrl_2->addItem(jsonarr[0].toString());
        ui->set_soc_ds_ctrl_3->addItem(jsonarr[0].toString());
        ui->set_soc_ds_ctrl_4->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }

    jsonarr = nandlist["ds"].toArray();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->set_nand_ds_1->addItem(jsonarr[0].toString());
        ui->set_nand_ds_2->addItem(jsonarr[0].toString());
        ui->set_nand_ds_3->addItem(jsonarr[0].toString());
        ui->set_nand_ds_4->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }
    jsonarr = nandlist["odt"].toArray();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->set_nand_odt_podt_1->addItem(jsonarr[0].toString());
        ui->set_nand_odt_podt_2->addItem(jsonarr[0].toString());
        ui->set_nand_odt_podt_3->addItem(jsonarr[0].toString());
        ui->set_nand_odt_podt_4->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }
    jsonarr = nandlist["odt"].toArray();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->set_nand_odt_rodt_1->addItem(jsonarr[0].toString());
        ui->set_nand_odt_rodt_2->addItem(jsonarr[0].toString());
        ui->set_nand_odt_rodt_3->addItem(jsonarr[0].toString());
        ui->set_nand_odt_rodt_4->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }

    jsonval =	index1list["soc_dqs_ds"].toString();
    ui->set_soc_ds_dqs_1->setCurrentText(jsonval);
    jsonval =	index1list["soc_dqs_odt"].toString();
    ui->set_soc_odt_dqs_1->setCurrentText(jsonval);
    jsonval =	index1list["soc_dq_ds"].toString();
    ui->set_soc_ds_dq_1->setCurrentText(jsonval);
    jsonval =	index1list["soc_dq_odt"].toString();
    ui->set_soc_odt_dq_1->setCurrentText(jsonval);
    jsonval =	index1list["soc_re_ds"].toString();
    ui->set_soc_ds_re_1->setCurrentText(jsonval);
    jsonval =	index1list["soc_ctrl_ds"].toString();
    ui->set_soc_ds_ctrl_1->setCurrentText(jsonval);
    jsonval =	index1list["nand_ds"].toString();
    ui->set_nand_ds_1->setCurrentText(jsonval);
    jsonval =	index1list["nand_podt"].toString();
    ui->set_nand_odt_podt_1->setCurrentText(jsonval);
    jsonval =	index1list["nand_rodt"].toString();
    ui->set_nand_odt_rodt_1->setCurrentText(jsonval);

    jsonval =	index2list["soc_dqs_ds"].toString();
    ui->set_soc_ds_dqs_2->setCurrentText(jsonval);
    jsonval =	index2list["soc_dqs_odt"].toString();
    ui->set_soc_odt_dqs_2->setCurrentText(jsonval);
    jsonval =	index2list["soc_dq_ds"].toString();
    ui->set_soc_ds_dq_2->setCurrentText(jsonval);
    jsonval =	index2list["soc_dq_odt"].toString();
    ui->set_soc_odt_dq_2->setCurrentText(jsonval);
    jsonval =	index2list["soc_re_ds"].toString();
    ui->set_soc_ds_re_2->setCurrentText(jsonval);
    jsonval =	index2list["soc_ctrl_ds"].toString();
    ui->set_soc_ds_ctrl_2->setCurrentText(jsonval);
    jsonval =	index2list["nand_ds"].toString();
    ui->set_nand_ds_2->setCurrentText(jsonval);
    jsonval =	index2list["nand_podt"].toString();
    ui->set_nand_odt_podt_2->setCurrentText(jsonval);
    jsonval =	index2list["nand_rodt"].toString();
    ui->set_nand_odt_rodt_2->setCurrentText(jsonval);

    jsonval =	index3list["soc_dqs_ds"].toString();
    ui->set_soc_ds_dqs_3->setCurrentText(jsonval);
    jsonval =	index3list["soc_dqs_odt"].toString();
    ui->set_soc_odt_dqs_3->setCurrentText(jsonval);
    jsonval =	index3list["soc_dq_ds"].toString();
    ui->set_soc_ds_dq_3->setCurrentText(jsonval);
    jsonval =	index3list["soc_dq_odt"].toString();
    ui->set_soc_odt_dq_3->setCurrentText(jsonval);
    jsonval =	index3list["soc_re_ds"].toString();
    ui->set_soc_ds_re_3->setCurrentText(jsonval);
    jsonval =	index3list["soc_ctrl_ds"].toString();
    ui->set_soc_ds_ctrl_3->setCurrentText(jsonval);
    jsonval =	index3list["nand_ds"].toString();
    ui->set_nand_ds_3->setCurrentText(jsonval);
    jsonval =	index3list["nand_podt"].toString();
    ui->set_nand_odt_podt_3->setCurrentText(jsonval);
    jsonval =	index3list["nand_rodt"].toString();
    ui->set_nand_odt_rodt_3->setCurrentText(jsonval);

    jsonval =	index4list["soc_dqs_ds"].toString();
    ui->set_soc_ds_dqs_4->setCurrentText(jsonval);
    jsonval =	index4list["soc_dqs_odt"].toString();
    ui->set_soc_odt_dqs_4->setCurrentText(jsonval);
    jsonval =	index4list["soc_dq_ds"].toString();
    ui->set_soc_ds_dq_4->setCurrentText(jsonval);
    jsonval =	index4list["soc_dq_odt"].toString();
    ui->set_soc_odt_dq_4->setCurrentText(jsonval);
    jsonval =	index4list["soc_re_ds"].toString();
    ui->set_soc_ds_re_4->setCurrentText(jsonval);
    jsonval =	index4list["soc_ctrl_ds"].toString();
    ui->set_soc_ds_ctrl_4->setCurrentText(jsonval);
    jsonval =	index4list["nand_ds"].toString();
    ui->set_nand_ds_4->setCurrentText(jsonval);
    jsonval =	index4list["nand_podt"].toString();
    ui->set_nand_odt_podt_4->setCurrentText(jsonval);
    jsonval =	index4list["nand_rodt"].toString();
    ui->set_nand_odt_rodt_4->setCurrentText(jsonval);


    jsonarr = cmdlist["list"].toArray();
    jsonval =	cmdlist["val"].toString();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->Sel_CB->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }
    ui->Sel_CB->setCurrentText(jsonval);


    jsonarr = sellist["list"].toArray();
    jsonval = sellist["val"].toString();
    cnt = jsonarr.count();
    for(i=0;i<cnt;i++){
        ui->sel_soc_index_select->addItem(jsonarr[0].toString());
        jsonarr.removeFirst();
    }
    ui->sel_soc_index_select->setCurrentText(jsonval);


    ui->init_start_txt->setText(vallist["init_start"].toString());
    ui->init_end_txt->setText(vallist["init_end"].toString());
    ui->init_freq_txt->setText(vallist["init_freq"].toString());

    ui->all_index_txt->setText(vallist["all_index"].toString());
    ui->all_index_txt_2->setText(vallist["all_index_2"].toString());

    ui->all_ch_ce0_txt_2->setText(vallist["all_ch_ce0_2"].toString());
    ui->all_ch_ce1_txt_2->setText(vallist["all_ch_ce1_2"].toString());
    ui->all_ch_ce2_txt_2->setText(vallist["all_ch_ce2_2"].toString());
    ui->all_ch_ce3_txt_2->setText(vallist["all_ch_ce3_2"].toString());

    ui->ce_ce_txt_2->setText(vallist["ce_ce_2"].toString());
    ui->ce_index_txt_2->setText(vallist["ce_index_2"].toString());

    ui->ch_ch_txt_2->setText(vallist["ch_ch_2"].toString());
    ui->ch_ce0_txt_2->setText(vallist["ch_ce0_2"].toString());
    ui->ch_ce1_txt_2->setText(vallist["ch_ce1_2"].toString());
    ui->ch_ce2_txt_2->setText(vallist["ch_ce2_2"].toString());
    ui->ch_ce3_txt_2->setText(vallist["ch_ce3_2"].toString());

    ui->ch_ce_ch_txt->setText(vallist["ch_ce_ch"].toString());
    ui->ch_ce_index_txt->setText(vallist["ch_ce_index"].toString());
    ui->ch_ce_ch_txt_2->setText(vallist["ch_ce_ch_2"].toString());
    ui->ch_ce_ce_txt_2->setText(vallist["ch_ce_ce_2"].toString());
    ui->ch_ce_index_txt_2->setText(vallist["ch_ce_index_2"].toString());

    ui->si_ch0_txt->setText(vallist["si_ch0"].toString());
    ui->si_ch1_txt->setText(vallist["si_ch1"].toString());
    ui->si_ch2_txt->setText(vallist["si_ch2"].toString());
    ui->si_ch3_txt->setText(vallist["si_ch3"].toString());
    ui->si_ch4_txt->setText(vallist["si_ch4"].toString());
    ui->si_ch5_txt->setText(vallist["si_ch5"].toString());
    ui->si_ch6_txt->setText(vallist["si_ch6"].toString());
    ui->si_ch7_txt->setText(vallist["si_ch7"].toString());
    ui->si_ch8_txt->setText(vallist["si_ch8"].toString());
    ui->si_ch9_txt->setText(vallist["si_ch9"].toString());
    ui->si_ch10_txt->setText(vallist["si_ch10"].toString());
    ui->si_ch11_txt->setText(vallist["si_ch11"].toString());
    ui->si_freq_txt->setText(vallist["si_freq"].toString());

    ui->para_test_cnt_txt->setText(vallist["para_test_cnt"].toString());
    ui->para_random_txt->setText(vallist["para_random"].toString());
    ui->para_pattern_txt->setText(vallist["para_pattern"].toString());
    ui->para_diff_txt->setText(vallist["para_diff"].toString());

    ui->vref_mode_txt->setText(vallist["vref_mode"].toString());
    ui->vref_channel_txt->setText(vallist["vref_channel"].toString());
    ui->vref_mV_txt->setText(vallist["vref_mV"].toString());

    ui->parser_CB->addItem("ch");
    ui->parser_CB->addItem("lun");
}

void MainWindow::Enable_Frame(int n)
{
    ui->init_frame->setVisible(false);

    ui->sel_index_frame->setVisible(false);

    ui->sel_soc_index_all_frame->setVisible(false);
    ui->sel_nand_index_all_frame->setVisible(false);

    ui->sel_nand_index_all_ch_frame->setVisible(false);

    ui->sel_nand_index_ch_frame->setVisible(false);

    ui->sel_nand_index_ce_frame->setVisible(false);

    ui->sel_soc_index_ch_ce_frame->setVisible(false);
    ui->sel_nand_index_ch_ce_frame->setVisible(false);


    ui->si_frame->setVisible(false);
    ui->si_para_frame->setVisible(false);
    ui->vref_frame->setVisible(false);

    switch(n){
    case INIT_FRAME  :
        ui->init_frame->setVisible(true);
        break;
    case SOC_INDEX_ALL_FRAME :
        ui->sel_index_frame->setVisible(true);
        ui->sel_soc_index_all_frame->setVisible(true);
        break;
    case SOC_INDEX_CHCE_FRAME :
        ui->sel_index_frame->setVisible(true);
        ui->sel_soc_index_ch_ce_frame->setVisible(true);
        break;
    case NAND_INDEX_ALL_FRAME :
        ui->sel_index_frame->setVisible(true);
        ui->sel_nand_index_all_frame->setVisible(true);
        break;
    case NAND_INDEX_ALLCH_FRAME :
        ui->sel_index_frame->setVisible(true);
        ui->sel_nand_index_all_ch_frame->setVisible(true);
        break;
    case NAND_INDEX_CH_FRAME :
        ui->sel_index_frame->setVisible(true);
        ui->sel_nand_index_ch_frame->setVisible(true);
        break;
    case NAND_INDEX_CE_FRAME :
        ui->sel_index_frame->setVisible(true);
        ui->sel_nand_index_ce_frame->setVisible(true);
        break;
    case NAND_INDEX_CHCE_FRAME :
        ui->sel_index_frame->setVisible(true);
        ui->sel_nand_index_ch_ce_frame->setVisible(true);
        break;
    case SI_FRAME :
        ui->si_frame->setVisible(true);
        break;
    case PARA_FRAME :
        ui->si_para_frame->setVisible(true);
        break;
    case VREF_FRAME :
        ui->vref_frame->setVisible(true);
        break;
    default:
        break;
    }
}

void MainWindow::on_Sel_CB_currentIndexChanged(const QString &arg1)
{
    static QString backVal = "";

    if(backVal == arg1){
        return;
    }
    backVal = arg1;

    if(arg1 == "power_on") {
        Enable_Frame(ALL_DISABLE);
    }
    else if(arg1 == "sel_index_to_soc") {
        int cnt;
        cnt = ui->sel_soc_index_select->count();
        for(int i=0;i<cnt;i++){
            ui->sel_soc_index_select->removeItem(0);
        }
        ui->sel_soc_index_select->addItem("all");
        ui->sel_soc_index_select->addItem("ch");


        Enable_Frame(SOC_INDEX_ALL_FRAME);
    }
    else if(arg1 == "sel_index_to_nand") {
        int cnt;
        cnt = ui->sel_soc_index_select->count();
        for(int i=0;i<cnt;i++){
            ui->sel_soc_index_select->removeItem(0);
        }
        ui->sel_soc_index_select->addItem("all");
        ui->sel_soc_index_select->addItem("all_ch");
        ui->sel_soc_index_select->addItem("ch");
        ui->sel_soc_index_select->addItem("ce");
        ui->sel_soc_index_select->addItem("ch_ce");


        Enable_Frame(NAND_INDEX_ALL_FRAME);
    }
    else if(arg1 == "init") {
        Enable_Frame(INIT_FRAME);
    }
    else if(arg1 == "si") {
        Enable_Frame(SI_FRAME);
    }
    else if(arg1 == "get_window") {
        Enable_Frame(ALL_DISABLE);
    }
    else if(arg1 == "get_para") {
        Enable_Frame(ALL_DISABLE);
    }
    else if(arg1 == "si_para"){
        Enable_Frame(PARA_FRAME);
    }
    else if(arg1 == "power_off") {
        Enable_Frame(ALL_DISABLE);
    }
    else if(arg1 == "add_index_val"){
        Enable_Frame(ALL_DISABLE);
    }
    else if(arg1 == "set_vref") {
        Enable_Frame(VREF_FRAME);
    }
    else if(arg1 == "get_vref"){
        Enable_Frame(ALL_DISABLE);
    }
}

void MainWindow::on_sel_soc_index_select_currentIndexChanged(const QString &arg1)
{
    static QString backVal = "";

    if(backVal == arg1){
        return;
    }
    backVal = arg1;

    if(ui->Sel_CB->currentText() == "sel_index_to_soc") {
        if(arg1 == "all"){
            Enable_Frame(SOC_INDEX_ALL_FRAME);
        }
        else if(arg1 == "ch"){
            Enable_Frame(SOC_INDEX_CHCE_FRAME);
        }
    }
    else if(ui->Sel_CB->currentText() == "sel_index_to_nand") {
        if(arg1 == "all"){
            Enable_Frame(NAND_INDEX_ALL_FRAME);
        }
        else if(arg1 == "all_ch"){
            Enable_Frame(NAND_INDEX_ALLCH_FRAME);
        }
        else if(arg1 == "ch"){
            Enable_Frame(NAND_INDEX_CH_FRAME);
        }
        else if(arg1 == "ce"){
            Enable_Frame(NAND_INDEX_CE_FRAME);
        }
        else if(arg1 == "ch_ce"){
            Enable_Frame(NAND_INDEX_CHCE_FRAME);
        }
    }
    ui->sel_soc_index_select->setFocus();
}

void MainWindow::Enable_SoC_CB(bool checked)
{
    if(checked == true){
        ui->set_soc_ds_dqs_1->setEnabled(true);
        ui->set_soc_ds_dq_1->setEnabled(true);
        ui->set_soc_odt_dqs_1->setEnabled(true);
        ui->set_soc_odt_dq_1->setEnabled(true);
        ui->set_soc_ds_re_1->setEnabled(true);
        ui->set_soc_ds_ctrl_1->setEnabled(true);
        ui->set_soc_ds_dqs_2->setEnabled(true);
        ui->set_soc_ds_dq_2->setEnabled(true);
        ui->set_soc_odt_dqs_2->setEnabled(true);
        ui->set_soc_odt_dq_2->setEnabled(true);
        ui->set_soc_ds_re_2->setEnabled(true);
        ui->set_soc_ds_ctrl_2->setEnabled(true);
        ui->set_soc_ds_dqs_3->setEnabled(true);
        ui->set_soc_ds_dq_3->setEnabled(true);
        ui->set_soc_odt_dqs_3->setEnabled(true);
        ui->set_soc_odt_dq_3->setEnabled(true);
        ui->set_soc_ds_re_3->setEnabled(true);
        ui->set_soc_ds_ctrl_3->setEnabled(true);
        ui->set_soc_ds_dqs_4->setEnabled(true);
        ui->set_soc_ds_dq_4->setEnabled(true);
        ui->set_soc_odt_dqs_4->setEnabled(true);
        ui->set_soc_odt_dq_4->setEnabled(true);
        ui->set_soc_ds_re_4->setEnabled(true);
        ui->set_soc_ds_ctrl_4->setEnabled(true);
    }
    else{
        ui->set_soc_ds_dqs_1->setEnabled(false);
        ui->set_soc_ds_dq_1->setEnabled(false);
        ui->set_soc_odt_dqs_1->setEnabled(false);
        ui->set_soc_odt_dq_1->setEnabled(false);
        ui->set_soc_ds_re_1->setEnabled(false);
        ui->set_soc_ds_ctrl_1->setEnabled(false);
        ui->set_soc_ds_dqs_2->setEnabled(false);
        ui->set_soc_ds_dq_2->setEnabled(false);
        ui->set_soc_odt_dqs_2->setEnabled(false);
        ui->set_soc_odt_dq_2->setEnabled(false);
        ui->set_soc_ds_re_2->setEnabled(false);
        ui->set_soc_ds_ctrl_2->setEnabled(false);
        ui->set_soc_ds_dqs_3->setEnabled(false);
        ui->set_soc_ds_dq_3->setEnabled(false);
        ui->set_soc_odt_dqs_3->setEnabled(false);
        ui->set_soc_odt_dq_3->setEnabled(false);
        ui->set_soc_ds_re_3->setEnabled(false);
        ui->set_soc_ds_ctrl_3->setEnabled(false);
        ui->set_soc_ds_dqs_4->setEnabled(false);
        ui->set_soc_ds_dq_4->setEnabled(false);
        ui->set_soc_odt_dqs_4->setEnabled(false);
        ui->set_soc_odt_dq_4->setEnabled(false);
        ui->set_soc_ds_re_4->setEnabled(false);
        ui->set_soc_ds_ctrl_4->setEnabled(false);
    }
}

void MainWindow::Enable_Nand_CB(bool checked)
{
    if(checked == true){
        ui->set_nand_ds_1->setEnabled(true);
        ui->set_nand_odt_podt_1->setEnabled(true);
        ui->set_nand_odt_rodt_1->setEnabled(true);
        ui->set_nand_ds_2->setEnabled(true);
        ui->set_nand_odt_podt_2->setEnabled(true);
        ui->set_nand_odt_rodt_2->setEnabled(true);
        ui->set_nand_ds_3->setEnabled(true);
        ui->set_nand_odt_podt_3->setEnabled(true);
        ui->set_nand_odt_rodt_3->setEnabled(true);
        ui->set_nand_ds_4->setEnabled(true);
        ui->set_nand_odt_podt_4->setEnabled(true);
        ui->set_nand_odt_rodt_4->setEnabled(true);
    }
    else{
        ui->set_nand_ds_1->setEnabled(false);
        ui->set_nand_odt_podt_1->setEnabled(false);
        ui->set_nand_odt_rodt_1->setEnabled(false);
        ui->set_nand_ds_2->setEnabled(false);
        ui->set_nand_odt_podt_2->setEnabled(false);
        ui->set_nand_odt_rodt_2->setEnabled(false);
        ui->set_nand_ds_3->setEnabled(false);
        ui->set_nand_odt_podt_3->setEnabled(false);
        ui->set_nand_odt_rodt_3->setEnabled(false);
        ui->set_nand_ds_4->setEnabled(false);
        ui->set_nand_odt_podt_4->setEnabled(false);
        ui->set_nand_odt_rodt_4->setEnabled(false);
    }

}

void MainWindow::on_checkBox_toggled(bool checked)
{
    Enable_SoC_CB(checked);
}

void MainWindow::on_checkBox_2_toggled(bool checked)
{
    Enable_Nand_CB(checked);
}

int MainWindow::Get_IndexNum(QString mm)
{
    int ret = -1;

    return ret;
}

void MainWindow::on_Make_CMD_clicked()
{

    QStringList m1;
    QStringList m2;

    QString n1;
    QString n2;
    QString presetData;
    QString testData;
    int n,i,j;
    int cmdcnt[20] = {0,};

    QMessageBox mm;
    presetData = "[" + ui->test_name_txt->text() + "]\n";
    presetData += "preset_list = ";
    for (i = 0; i < ui->Preset_List->count(); i++) {
        m2 = ui->Preset_List->item(i)->text().split(" ");

        for(j=0; j<cmdString.count();j++){
            m1 = cmdString.at(j).split(" ");

            if(m1[0] == 'n') n1 = m1[1];
            else             n1 = m1[0];

            if(m2[0] == 'n') n2 = m2[1];
            else             n2 = m2[0];

            if(n1 == n2) break;
        }

        if(j != cmdString.count()){
            n = j;

            cmdcnt[n]++;

            if(m2[0] == "add_index_val"){
                QString str;
                QStringList strArr;
                int cnt;
                strArr = indexSet[m2[1].toInt()].split(';');
                str = "";
                cnt = 0;
                foreach(QString n10, strArr){
                    if(n10 == "") break;

                    if((cnt%4) == 0) presetData += "soc_ds" + QString::number(((cmdcnt[n]*4)-3)+(cnt/4)) + ",";
                    else if((cnt%4) == 1) presetData += "soc_odt" + QString::number(((cmdcnt[n]*4)-3)+(cnt/4)) + ",";
                    else if((cnt%4) == 2) presetData += "nand_ds" + QString::number(((cmdcnt[n]*4)-3)+(cnt/4)) + ",";
                    else if((cnt%4) == 3) presetData += "nand_odt" + QString::number(((cmdcnt[n]*4)-3)+(cnt/4)) + ",";

                    if((cnt%4) == 0) testData += "[soc_ds" + QString::number(((cmdcnt[n]*4)-3)+(cnt/4)) + "]\n";
                    else if((cnt%4) == 1) testData += "[soc_odt" + QString::number(((cmdcnt[n]*4)-3)+(cnt/4)) + "]\n";
                    else if((cnt%4) == 2) testData += "[nand_ds" + QString::number(((cmdcnt[n]*4)-3)+(cnt/4)) + "]\n";
                    else if((cnt%4) == 3) testData += "[nand_odt" + QString::number(((cmdcnt[n]*4)-3)+(cnt/4)) + "]\n";
                    testData += "Cmd = " +  n10 + "\n\n";

                    cnt ++;
                }
            }
            else{
                presetData += presetString[n] + QString::number(cmdcnt[n]) + ",";
                testData += "[" + presetString[n] + QString::number(cmdcnt[n]) + "]\n";
                testData += "Cmd = " +  ui->Preset_List->item(i)->text() + "\n\n";
            }
        }

    }

    presetData.remove(presetData.length()-1,1);


    file.setFileName(QApplication::applicationDirPath()+"/"+output1);
    file.open(QIODevice::ReadWrite|QIODevice::Truncate);
    file.write(presetData.toUtf8());
    file.close();

    file.setFileName(QApplication::applicationDirPath()+"/"+output2);
    file.open(QIODevice::ReadWrite|QIODevice::Truncate);
    file.write(testData.toUtf8());
    file.close();

    mm.setText("Create success!");
    mm.exec();

    QDesktopServices::openUrl(QUrl("file:///"+QApplication::applicationDirPath(), QUrl::TolerantMode));

}

void MainWindow::on_Add_CMD_clicked()
{

    QString str;
    bool ok;

    str = ui->Sel_CB->currentText();

    if(str == "power_on"){
        str = "power_on";
    }
    else if(str == "init"){
        str = "n init ";
        str += ui->init_start_txt->text() + " ";
        str += ui->init_end_txt->text() + " ";
        str += ui->init_freq_txt->text();
    }
    else if(str == "si"){
        str = "n si ";
        str += QString::number(ui->si_ch0_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch1_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch2_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch3_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch4_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch5_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch6_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch7_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch8_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch9_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch10_txt->text().toUInt(&ok,16)) + " ";
        str += QString::number(ui->si_ch11_txt->text().toUInt(&ok,16)) + " ";

        str += ui->si_freq_txt->text();
    }
    else if(str == "get_window"){
        str = "n get_window all";
    }
    else if(str == "get_para"){
        str = "n get_para";
    }
    else if(str == "si_para"){
        str = "n si_para ";
        str += ui->para_test_cnt_txt->text() + " ";
        str += ui->para_random_txt->text() + " ";
        str += ui->para_pattern_txt->text() + " ";
        str += ui->para_diff_txt->text();
    }
    else if(str == "poweroff"){
        str = "power_off";
    }
    else if(str == "add_index_val"){
        if(indexSetCnt >= 30){
            QMessageBox mm;
            mm.setText("index_val overflow");
            mm.exec();
            return;
        }

        indexSet[indexSetCnt] = "";

        str = "n set_ds_to_soc 1 ";
        str += QString::number(ui->set_soc_ds_dqs_1->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_dq_1->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_re_1->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_ctrl_1->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_odt_to_soc 1 ";
        str += QString::number(ui->set_soc_odt_dqs_1->currentIndex()) + " ";
        str += QString::number(ui->set_soc_odt_dq_1->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_ds_to_nand 1 ";
        str += QString::number(ui->set_nand_ds_1->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_odt_to_nand 1 0 ";
        str += QString::number(ui->set_nand_odt_podt_1->currentIndex()) + " ";
        str += QString::number(ui->set_nand_odt_rodt_1->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;


        str = "n set_ds_to_soc 2 ";
        str += QString::number(ui->set_soc_ds_dqs_2->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_dq_2->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_re_2->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_ctrl_2->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_odt_to_soc 2 ";
        str += QString::number(ui->set_soc_odt_dqs_2->currentIndex()) + " ";
        str += QString::number(ui->set_soc_odt_dq_2->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_ds_to_nand 2 ";
        str += QString::number(ui->set_nand_ds_2->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_odt_to_nand 2 0 ";
        str += QString::number(ui->set_nand_odt_podt_2->currentIndex()) + " ";
        str += QString::number(ui->set_nand_odt_rodt_2->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;


        str = "n set_ds_to_soc 3 ";
        str += QString::number(ui->set_soc_ds_dqs_3->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_dq_3->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_re_3->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_ctrl_3->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_odt_to_soc 3 ";
        str += QString::number(ui->set_soc_odt_dqs_3->currentIndex()) + " ";
        str += QString::number(ui->set_soc_odt_dq_3->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_ds_to_nand 3 ";
        str += QString::number(ui->set_nand_ds_3->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_odt_to_nand 3 0 ";
        str += QString::number(ui->set_nand_odt_podt_3->currentIndex()) + " ";
        str += QString::number(ui->set_nand_odt_rodt_3->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;


        str = "n set_ds_to_soc 4 ";
        str += QString::number(ui->set_soc_ds_dqs_4->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_dq_4->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_re_4->currentIndex()) + " ";
        str += QString::number(ui->set_soc_ds_ctrl_4->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_odt_to_soc 4 ";
        str += QString::number(ui->set_soc_odt_dqs_4->currentIndex()) + " ";
        str += QString::number(ui->set_soc_odt_dq_4->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_ds_to_nand 4 ";
        str += QString::number(ui->set_nand_ds_4->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;
        str = "n set_odt_to_nand 4 0 ";
        str += QString::number(ui->set_nand_odt_podt_4->currentIndex()) + " ";
        str += QString::number(ui->set_nand_odt_rodt_4->currentIndex()) + ";";
        indexSet[indexSetCnt] += str;


        str = "add_index_val " + QString::number(indexSetCnt);
        indexSetCnt++;

    }
    else if(str == "sel_index_to_soc"){
        if(ui->sel_soc_index_select->currentText() == "all"){
            str = "n sel_index_to_soc all ";
            str += ui->all_index_txt->text();
        }
        else if(ui->sel_soc_index_select->currentText() == "ch"){
            str = "n sel_index_to_soc ";
            str += ui->ch_ce_ch_txt->text() + " ";
            str += ui->ch_ce_index_txt->text();
        }
    }
    else if(str == "sel_index_to_nand"){
        if(ui->sel_soc_index_select->currentText() == "all"){
            str = "n sel_index_to_nand all ";
            str += ui->all_index_txt_2->text();
        }
        else if(ui->sel_soc_index_select->currentText() == "all_ch"){
            str = "n sel_index_to_nand all_ch ";
            str += ui->all_ch_ce0_txt_2->text() + " ";
            str += ui->all_ch_ce1_txt_2->text() + " ";
            str += ui->all_ch_ce2_txt_2->text() + " ";
            str += ui->all_ch_ce3_txt_2->text();
        }
        else if(ui->sel_soc_index_select->currentText() == "ch"){
            str = "n sel_index_to_nand ch ";
            str += ui->ch_ch_txt_2->text() + " ";
            str += ui->ch_ce0_txt_2->text() + " ";
            str += ui->ch_ce1_txt_2->text() + " ";
            str += ui->ch_ce2_txt_2->text() + " ";
            str += ui->ch_ce3_txt_2->text();
        }
        else if(ui->sel_soc_index_select->currentText() == "ce"){
            str = "n sel_index_to_nand ce ";
            str += ui->ce_ce_txt_2->text() + " ";
            str += ui->ce_index_txt_2->text();
        }
        else if(ui->sel_soc_index_select->currentText() == "ch_ce"){
            str = "n sel_index_to_nand ";
            str += ui->ch_ce_ch_txt_2->text() + " ";
            str += ui->ch_ce_ce_txt_2->text() + " ";
            str += ui->ch_ce_index_txt_2->text();
        }
    }
    else if(str == "set_vref"){
        str = "n set_vref ";
        str += ui->vref_mode_txt->text() + " ";
        str += ui->vref_channel_txt->text() + " ";
        str += ui->vref_mV_txt->text() + " ";
    }
    else if(str == "get_vref"){
        str = "n get_vref";
    }

    ui->Preset_List->addItem(str);
}

void MainWindow::check_all_x()
{
    ui->LB_SOC_CTRL_DS_0->setText("x");
    ui->LB_SOC_CTRL_DS_1->setText("x");
    ui->LB_SOC_CTRL_DS_12->setText("x");
    ui->LB_SOC_CTRL_DS_3->setText("x");
    ui->LB_SOC_CTRL_DS_4->setText("x");
    ui->LB_SOC_CTRL_DS_5->setText("x");
    ui->LB_SOC_CTRL_DS_6->setText("x");
    ui->LB_SOC_CTRL_DS_7->setText("x");
    ui->LB_SOC_CTRL_DS_8->setText("x");
    ui->LB_SOC_CTRL_DS_9->setText("x");
    ui->LB_SOC_CTRL_DS_10->setText("x");
    ui->LB_SOC_CTRL_DS_11->setText("x");

    ui->LB_SOC_RE_DS_0->setText("x");
    ui->LB_SOC_RE_DS_1->setText("x");
    ui->LB_SOC_RE_DS_12->setText("x");
    ui->LB_SOC_RE_DS_3->setText("x");
    ui->LB_SOC_RE_DS_4->setText("x");
    ui->LB_SOC_RE_DS_5->setText("x");
    ui->LB_SOC_RE_DS_6->setText("x");
    ui->LB_SOC_RE_DS_7->setText("x");
    ui->LB_SOC_RE_DS_8->setText("x");
    ui->LB_SOC_RE_DS_9->setText("x");
    ui->LB_SOC_RE_DS_10->setText("x");
    ui->LB_SOC_RE_DS_11->setText("x");

    ui->LB_SOC_DQS_DS_0->setText("x");
    ui->LB_SOC_DQS_DS_1->setText("x");
    ui->LB_SOC_DQS_DS_12->setText("x");
    ui->LB_SOC_DQS_DS_3->setText("x");
    ui->LB_SOC_DQS_DS_4->setText("x");
    ui->LB_SOC_DQS_DS_5->setText("x");
    ui->LB_SOC_DQS_DS_6->setText("x");
    ui->LB_SOC_DQS_DS_7->setText("x");
    ui->LB_SOC_DQS_DS_8->setText("x");
    ui->LB_SOC_DQS_DS_9->setText("x");
    ui->LB_SOC_DQS_DS_10->setText("x");
    ui->LB_SOC_DQS_DS_11->setText("x");

    ui->LB_SOC_DQS_ODT_0->setText("x");
    ui->LB_SOC_DQS_ODT_1->setText("x");
    ui->LB_SOC_DQS_ODT_12->setText("x");
    ui->LB_SOC_DQS_ODT_3->setText("x");
    ui->LB_SOC_DQS_ODT_4->setText("x");
    ui->LB_SOC_DQS_ODT_5->setText("x");
    ui->LB_SOC_DQS_ODT_6->setText("x");
    ui->LB_SOC_DQS_ODT_7->setText("x");
    ui->LB_SOC_DQS_ODT_8->setText("x");
    ui->LB_SOC_DQS_ODT_9->setText("x");
    ui->LB_SOC_DQS_ODT_10->setText("x");
    ui->LB_SOC_DQS_ODT_11->setText("x");

    ui->LB_SOC_DQ_DS_0->setText("x");
    ui->LB_SOC_DQ_DS_1->setText("x");
    ui->LB_SOC_DQ_DS_12->setText("x");
    ui->LB_SOC_DQ_DS_3->setText("x");
    ui->LB_SOC_DQ_DS_4->setText("x");
    ui->LB_SOC_DQ_DS_5->setText("x");
    ui->LB_SOC_DQ_DS_6->setText("x");
    ui->LB_SOC_DQ_DS_7->setText("x");
    ui->LB_SOC_DQ_DS_8->setText("x");
    ui->LB_SOC_DQ_DS_9->setText("x");
    ui->LB_SOC_DQ_DS_10->setText("x");
    ui->LB_SOC_DQ_DS_11->setText("x");

    ui->LB_SOC_DQ_ODT_0->setText("x");
    ui->LB_SOC_DQ_ODT_1->setText("x");
    ui->LB_SOC_DQ_ODT_12->setText("x");
    ui->LB_SOC_DQ_ODT_3->setText("x");
    ui->LB_SOC_DQ_ODT_4->setText("x");
    ui->LB_SOC_DQ_ODT_5->setText("x");
    ui->LB_SOC_DQ_ODT_6->setText("x");
    ui->LB_SOC_DQ_ODT_7->setText("x");
    ui->LB_SOC_DQ_ODT_8->setText("x");
    ui->LB_SOC_DQ_ODT_9->setText("x");
    ui->LB_SOC_DQ_ODT_10->setText("x");
    ui->LB_SOC_DQ_ODT_11->setText("x");

    ui->LB_NAND_CE0_DS_0->setText("x");
    ui->LB_NAND_CE0_DS_1->setText("x");
    ui->LB_NAND_CE0_DS_12->setText("x");
    ui->LB_NAND_CE0_DS_3->setText("x");
    ui->LB_NAND_CE0_DS_4->setText("x");
    ui->LB_NAND_CE0_DS_5->setText("x");
    ui->LB_NAND_CE0_DS_6->setText("x");
    ui->LB_NAND_CE0_DS_7->setText("x");
    ui->LB_NAND_CE0_DS_8->setText("x");
    ui->LB_NAND_CE0_DS_9->setText("x");
    ui->LB_NAND_CE0_DS_10->setText("x");
    ui->LB_NAND_CE0_DS_11->setText("x");

    ui->LB_NAND_CE0_PODT_0->setText("x");
    ui->LB_NAND_CE0_PODT_1->setText("x");
    ui->LB_NAND_CE0_PODT_12->setText("x");
    ui->LB_NAND_CE0_PODT_3->setText("x");
    ui->LB_NAND_CE0_PODT_4->setText("x");
    ui->LB_NAND_CE0_PODT_5->setText("x");
    ui->LB_NAND_CE0_PODT_6->setText("x");
    ui->LB_NAND_CE0_PODT_7->setText("x");
    ui->LB_NAND_CE0_PODT_8->setText("x");
    ui->LB_NAND_CE0_PODT_9->setText("x");
    ui->LB_NAND_CE0_PODT_10->setText("x");
    ui->LB_NAND_CE0_PODT_11->setText("x");

    ui->LB_NAND_CE0_RODT_0->setText("x");
    ui->LB_NAND_CE0_RODT_1->setText("x");
    ui->LB_NAND_CE0_RODT_12->setText("x");
    ui->LB_NAND_CE0_RODT_3->setText("x");
    ui->LB_NAND_CE0_RODT_4->setText("x");
    ui->LB_NAND_CE0_RODT_5->setText("x");
    ui->LB_NAND_CE0_RODT_6->setText("x");
    ui->LB_NAND_CE0_RODT_7->setText("x");
    ui->LB_NAND_CE0_RODT_8->setText("x");
    ui->LB_NAND_CE0_RODT_9->setText("x");
    ui->LB_NAND_CE0_RODT_10->setText("x");
    ui->LB_NAND_CE0_RODT_11->setText("x");

    ui->LB_NAND_CE1_DS_0->setText("x");
    ui->LB_NAND_CE1_DS_1->setText("x");
    ui->LB_NAND_CE1_DS_12->setText("x");
    ui->LB_NAND_CE1_DS_3->setText("x");
    ui->LB_NAND_CE1_DS_4->setText("x");
    ui->LB_NAND_CE1_DS_5->setText("x");
    ui->LB_NAND_CE1_DS_6->setText("x");
    ui->LB_NAND_CE1_DS_7->setText("x");
    ui->LB_NAND_CE1_DS_8->setText("x");
    ui->LB_NAND_CE1_DS_9->setText("x");
    ui->LB_NAND_CE1_DS_10->setText("x");
    ui->LB_NAND_CE1_DS_11->setText("x");

    ui->LB_NAND_CE1_PODT_0->setText("x");
    ui->LB_NAND_CE1_PODT_1->setText("x");
    ui->LB_NAND_CE1_PODT_12->setText("x");
    ui->LB_NAND_CE1_PODT_3->setText("x");
    ui->LB_NAND_CE1_PODT_4->setText("x");
    ui->LB_NAND_CE1_PODT_5->setText("x");
    ui->LB_NAND_CE1_PODT_6->setText("x");
    ui->LB_NAND_CE1_PODT_7->setText("x");
    ui->LB_NAND_CE1_PODT_8->setText("x");
    ui->LB_NAND_CE1_PODT_9->setText("x");
    ui->LB_NAND_CE1_PODT_10->setText("x");
    ui->LB_NAND_CE1_PODT_11->setText("x");

    ui->LB_NAND_CE1_RODT_0->setText("x");
    ui->LB_NAND_CE1_RODT_1->setText("x");
    ui->LB_NAND_CE1_RODT_12->setText("x");
    ui->LB_NAND_CE1_RODT_3->setText("x");
    ui->LB_NAND_CE1_RODT_4->setText("x");
    ui->LB_NAND_CE1_RODT_5->setText("x");
    ui->LB_NAND_CE1_RODT_6->setText("x");
    ui->LB_NAND_CE1_RODT_7->setText("x");
    ui->LB_NAND_CE1_RODT_8->setText("x");
    ui->LB_NAND_CE1_RODT_9->setText("x");
    ui->LB_NAND_CE1_RODT_10->setText("x");
    ui->LB_NAND_CE1_RODT_11->setText("x");

    ui->LB_NAND_CE2_DS_0->setText("x");
    ui->LB_NAND_CE2_DS_1->setText("x");
    ui->LB_NAND_CE2_DS_12->setText("x");
    ui->LB_NAND_CE2_DS_3->setText("x");
    ui->LB_NAND_CE2_DS_4->setText("x");
    ui->LB_NAND_CE2_DS_5->setText("x");
    ui->LB_NAND_CE2_DS_6->setText("x");
    ui->LB_NAND_CE2_DS_7->setText("x");
    ui->LB_NAND_CE2_DS_8->setText("x");
    ui->LB_NAND_CE2_DS_9->setText("x");
    ui->LB_NAND_CE2_DS_10->setText("x");
    ui->LB_NAND_CE2_DS_11->setText("x");

    ui->LB_NAND_CE2_PODT_0->setText("x");
    ui->LB_NAND_CE2_PODT_1->setText("x");
    ui->LB_NAND_CE2_PODT_12->setText("x");
    ui->LB_NAND_CE2_PODT_3->setText("x");
    ui->LB_NAND_CE2_PODT_4->setText("x");
    ui->LB_NAND_CE2_PODT_5->setText("x");
    ui->LB_NAND_CE2_PODT_6->setText("x");
    ui->LB_NAND_CE2_PODT_7->setText("x");
    ui->LB_NAND_CE2_PODT_8->setText("x");
    ui->LB_NAND_CE2_PODT_9->setText("x");
    ui->LB_NAND_CE2_PODT_10->setText("x");
    ui->LB_NAND_CE2_PODT_11->setText("x");

    ui->LB_NAND_CE2_RODT_0->setText("x");
    ui->LB_NAND_CE2_RODT_1->setText("x");
    ui->LB_NAND_CE2_RODT_12->setText("x");
    ui->LB_NAND_CE2_RODT_3->setText("x");
    ui->LB_NAND_CE2_RODT_4->setText("x");
    ui->LB_NAND_CE2_RODT_5->setText("x");
    ui->LB_NAND_CE2_RODT_6->setText("x");
    ui->LB_NAND_CE2_RODT_7->setText("x");
    ui->LB_NAND_CE2_RODT_8->setText("x");
    ui->LB_NAND_CE2_RODT_9->setText("x");
    ui->LB_NAND_CE2_RODT_10->setText("x");
    ui->LB_NAND_CE2_RODT_11->setText("x");

    ui->LB_NAND_CE3_DS_0->setText("x");
    ui->LB_NAND_CE3_DS_1->setText("x");
    ui->LB_NAND_CE3_DS_12->setText("x");
    ui->LB_NAND_CE3_DS_3->setText("x");
    ui->LB_NAND_CE3_DS_4->setText("x");
    ui->LB_NAND_CE3_DS_5->setText("x");
    ui->LB_NAND_CE3_DS_6->setText("x");
    ui->LB_NAND_CE3_DS_7->setText("x");
    ui->LB_NAND_CE3_DS_8->setText("x");
    ui->LB_NAND_CE3_DS_9->setText("x");
    ui->LB_NAND_CE3_DS_10->setText("x");
    ui->LB_NAND_CE3_DS_11->setText("x");

    ui->LB_NAND_CE3_PODT_0->setText("x");
    ui->LB_NAND_CE3_PODT_1->setText("x");
    ui->LB_NAND_CE3_PODT_12->setText("x");
    ui->LB_NAND_CE3_PODT_3->setText("x");
    ui->LB_NAND_CE3_PODT_4->setText("x");
    ui->LB_NAND_CE3_PODT_5->setText("x");
    ui->LB_NAND_CE3_PODT_6->setText("x");
    ui->LB_NAND_CE3_PODT_7->setText("x");
    ui->LB_NAND_CE3_PODT_8->setText("x");
    ui->LB_NAND_CE3_PODT_9->setText("x");
    ui->LB_NAND_CE3_PODT_10->setText("x");
    ui->LB_NAND_CE3_PODT_11->setText("x");

    ui->LB_NAND_CE3_RODT_0->setText("x");
    ui->LB_NAND_CE3_RODT_1->setText("x");
    ui->LB_NAND_CE3_RODT_12->setText("x");
    ui->LB_NAND_CE3_RODT_3->setText("x");
    ui->LB_NAND_CE3_RODT_4->setText("x");
    ui->LB_NAND_CE3_RODT_5->setText("x");
    ui->LB_NAND_CE3_RODT_6->setText("x");
    ui->LB_NAND_CE3_RODT_7->setText("x");
    ui->LB_NAND_CE3_RODT_8->setText("x");
    ui->LB_NAND_CE3_RODT_9->setText("x");
    ui->LB_NAND_CE3_RODT_10->setText("x");
    ui->LB_NAND_CE3_RODT_11->setText("x");

}

void MainWindow::on_Del_CMD_clicked()
{
    delete ui->Preset_List->currentItem();
}

void MainWindow::on_Up_CMD_clicked()
{
    QListWidgetItem *current = ui->Preset_List->currentItem();
    int currIndex = ui->Preset_List->row(current);

    QListWidgetItem *prev = ui->Preset_List->item(ui->Preset_List->row(current) - 1);
    int prevIndex = ui->Preset_List->row(prev);

    QListWidgetItem *temp = ui->Preset_List->takeItem(prevIndex);
    ui->Preset_List->insertItem(prevIndex, current);
    ui->Preset_List->insertItem(currIndex, temp);
}

void MainWindow::on_Down_CMD_clicked()
{
    QListWidgetItem *current = ui->Preset_List->currentItem();
    int currIndex = ui->Preset_List->row(current);

    QListWidgetItem *next = ui->Preset_List->item(ui->Preset_List->row(current) + 1);
    int nextIndex = ui->Preset_List->row(next);

    QListWidgetItem *temp = ui->Preset_List->takeItem(nextIndex);
    ui->Preset_List->insertItem(currIndex, temp);
    ui->Preset_List->insertItem(nextIndex, current);

}

void MainWindow::on_Add_CMD_2_clicked()
{
    // ui->Preset_List->currentItem()->text()
    QString str;
    QStringList strArr;


    str = ui->Preset_List->currentItem()->text();
    strArr = str.split(' ');


    if(strArr[0] == "add_index_val"){
        strArr = indexSet[0].split(';');

        str = "";
        foreach(QString n, strArr)
            str += n + "\r\n";

        QMessageBox mm;
        mm.setText(str);
        mm.exec();
    }
}

void MainWindow::on_Exit_Preset_CMD_clicked()
{
    Search_SerialPort();

    ui->Preset_frame->hide();
    ui->Main_frame->show();
    //ui->Run_frame->show();
}

void MainWindow::on_MOVE_PRESET_CMD_clicked()
{
    ui->Main_frame->hide();
    ui->Preset_frame->show();
}

void MainWindow::on_MOVE_RUN_CMD_clicked()
{
    ui->run_preset_txt->setText(ui->test_name_txt->text());
    ui->Main_frame->hide();
    ui->Run_frame->show();
}

void MainWindow::on_Chk_Preset_CMD_clicked()
{
    QDesktopServices::openUrl(QUrl("file:///"+QApplication::applicationDirPath()+"/"+output1, QUrl::TolerantMode));
}

void MainWindow::on_Exit_Run_CMD_clicked()
{
    ui->Run_frame->hide();
    ui->Main_frame->show();
    //ui->Preset_frame->show();
}

QString MainWindow::Get_PresetCmd(QString str)
{
    QByteArray arr;
    QString fileStr;
    QString retStr;
    QStringList listStr;
    int startPos;

    file.setFileName(QApplication::applicationDirPath()+"/"+output2);
    file.open(QIODevice::ReadWrite);
    arr = file.readAll();
    file.close();

    fileStr = QString(arr);
    startPos = fileStr.indexOf(str);
    if(startPos == -1){
        return "error1";
    }
    fileStr = fileStr.right(fileStr.length() - startPos);


    startPos = fileStr.indexOf("Cmd");
    if(startPos == -1){
        return "error2";
    }
    fileStr = fileStr.right(fileStr.length() - startPos - 6);


    listStr = fileStr.split(" ");
    if(listStr.count() < 2){
        return "error3";
    }

    retStr = fileStr;

    return retStr;
}

void MainWindow::Set_CmdParameter(int testcnt, QString str)
{
    QStringList listStr;

    listStr = str.split(" ");
    if(listStr[1] == "set_ds_to_soc"){
        index_soc_dqs_ds[listStr[2].toInt()] = listStr[3].toInt();
        index_soc_dq_ds[listStr[2].toInt()] = listStr[4].toInt();
        index_soc_re_ds[listStr[2].toInt()] = listStr[5].toInt();
        index_soc_ctrl_ds[listStr[2].toInt()] = listStr[6].toInt();
    }
    else if(listStr[1] == "set_odt_to_soc"){
        index_soc_dqs_odt[listStr[2].toInt()] = listStr[3].toInt();
        index_soc_dq_odt[listStr[2].toInt()] = listStr[4].toInt();
    }
    else if(listStr[1] == "set_ds_to_nand"){
        index_nand_ds[listStr[2].toInt()] = listStr[3].toInt();
    }
    else if(listStr[1] == "set_odt_to_nand"){
        index_nand_comodt[listStr[2].toInt()] = listStr[3].toInt();
        index_nand_podt[listStr[2].toInt()] = listStr[4].toInt();
        index_nand_rodt[listStr[2].toInt()] = listStr[5].toInt();
    }
    else if(listStr[1] == "sel_index_to_soc"){
        if(listStr[2] == "all"){
            for(int i=0;i<12;i++){
                soc_ctrl_ds[testcnt][i] = index_soc_ctrl_ds[listStr[3].toInt()];
                soc_re_ds[testcnt][i] = index_soc_re_ds[listStr[3].toInt()];
                soc_dqs_ds[testcnt][i] = index_soc_dqs_ds[listStr[3].toInt()];
                soc_dqs_odt[testcnt][i] = index_soc_dqs_odt[listStr[3].toInt()];
                soc_dq_ds[testcnt][i] = index_soc_dq_ds[listStr[3].toInt()];
                soc_dq_odt[testcnt][i] = index_soc_dq_odt[listStr[3].toInt()];
            }
        }
        else{
            soc_ctrl_ds[testcnt][2] = index_soc_ctrl_ds[listStr[3].toInt()];
            soc_re_ds[testcnt][2] = index_soc_re_ds[listStr[3].toInt()];
            soc_dqs_ds[testcnt][2] = index_soc_dqs_ds[listStr[3].toInt()];
            soc_dqs_odt[testcnt][2] = index_soc_dqs_odt[listStr[3].toInt()];
            soc_dq_ds[testcnt][2] = index_soc_dq_ds[listStr[3].toInt()];
            soc_dq_odt[testcnt][2] = index_soc_dq_odt[listStr[3].toInt()];
        }

    }
    else if(listStr[1] == "sel_index_to_nand"){
        if(listStr[2] == "all"){
            for(int i=0;i<12;i++){
                nand_ce0_ds[testcnt][i] = index_nand_ds[listStr[3].toInt()];
                nand_ce0_podt[testcnt][i] = index_nand_podt[listStr[3].toInt()];
                nand_ce0_rodt[testcnt][i] = index_nand_rodt[listStr[3].toInt()];

                nand_ce1_ds[testcnt][i] = index_nand_ds[listStr[3].toInt()];
                nand_ce1_podt[testcnt][i] = index_nand_podt[listStr[3].toInt()];
                nand_ce1_rodt[testcnt][i] = index_nand_rodt[listStr[3].toInt()];

                nand_ce2_ds[testcnt][i] = index_nand_ds[listStr[3].toInt()];
                nand_ce2_podt[testcnt][i] = index_nand_podt[listStr[3].toInt()];
                nand_ce2_rodt[testcnt][i] = index_nand_rodt[listStr[3].toInt()];

                nand_ce3_ds[testcnt][i] = index_nand_ds[listStr[3].toInt()];
                nand_ce3_podt[testcnt][i] = index_nand_podt[listStr[3].toInt()];
                nand_ce3_rodt[testcnt][i] = index_nand_rodt[listStr[3].toInt()];
            }
        }
        else if(listStr[2] == "all_ch"){
            for(int i=0;i<12;i++){
                nand_ce0_ds[testcnt][i] = index_nand_ds[listStr[3].toInt()];
                nand_ce0_podt[testcnt][i] = index_nand_podt[listStr[3].toInt()];
                nand_ce0_rodt[testcnt][i] = index_nand_rodt[listStr[3].toInt()];

                nand_ce1_ds[testcnt][i] = index_nand_ds[listStr[4].toInt()];
                nand_ce1_podt[testcnt][i] = index_nand_podt[listStr[4].toInt()];
                nand_ce1_rodt[testcnt][i] = index_nand_rodt[listStr[4].toInt()];

                nand_ce2_ds[testcnt][i] = index_nand_ds[listStr[5].toInt()];
                nand_ce2_podt[testcnt][i] = index_nand_podt[listStr[5].toInt()];
                nand_ce2_rodt[testcnt][i] = index_nand_rodt[listStr[5].toInt()];

                nand_ce3_ds[testcnt][i] = index_nand_ds[listStr[6].toInt()];
                nand_ce3_podt[testcnt][i] = index_nand_podt[listStr[6].toInt()];
                nand_ce3_rodt[testcnt][i] = index_nand_rodt[listStr[6].toInt()];
            }
        }
        else if(listStr[2] == "ch"){
            nand_ce0_ds[testcnt][listStr[3].toInt()] = index_nand_ds[listStr[4].toInt()];
            nand_ce0_podt[testcnt][listStr[3].toInt()] = index_nand_podt[listStr[4].toInt()];
            nand_ce0_rodt[testcnt][listStr[3].toInt()] = index_nand_rodt[listStr[4].toInt()];

            nand_ce1_ds[testcnt][listStr[3].toInt()] = index_nand_ds[listStr[5].toInt()];
            nand_ce1_podt[testcnt][listStr[3].toInt()] = index_nand_podt[listStr[5].toInt()];
            nand_ce1_rodt[testcnt][listStr[3].toInt()] = index_nand_rodt[listStr[5].toInt()];

            nand_ce2_ds[testcnt][listStr[3].toInt()] = index_nand_ds[listStr[6].toInt()];
            nand_ce2_podt[testcnt][listStr[3].toInt()] = index_nand_podt[listStr[6].toInt()];
            nand_ce2_rodt[testcnt][listStr[3].toInt()] = index_nand_rodt[listStr[6].toInt()];

            nand_ce3_ds[testcnt][listStr[3].toInt()] = index_nand_ds[listStr[7].toInt()];
            nand_ce3_podt[testcnt][listStr[3].toInt()] = index_nand_podt[listStr[7].toInt()];
            nand_ce3_rodt[testcnt][listStr[3].toInt()] = index_nand_rodt[listStr[7].toInt()];
        }
        else if(listStr[2] == "ce"){
            for(int i=0;i<12;i++){
                if(listStr[3].toInt() == 0){
                    nand_ce0_ds[testcnt][i] = index_nand_ds[listStr[4].toInt()];
                    nand_ce0_podt[testcnt][i] = index_nand_podt[listStr[4].toInt()];
                    nand_ce0_rodt[testcnt][i] = index_nand_rodt[listStr[4].toInt()];
                }
                else if(listStr[3].toInt() == 1){
                    nand_ce1_ds[testcnt][i] = index_nand_ds[listStr[4].toInt()];
                    nand_ce1_podt[testcnt][i] = index_nand_podt[listStr[4].toInt()];
                    nand_ce1_rodt[testcnt][i] = index_nand_rodt[listStr[4].toInt()];
                }
                else if(listStr[3].toInt() == 2){
                    nand_ce2_ds[testcnt][i] = index_nand_ds[listStr[4].toInt()];
                    nand_ce2_podt[testcnt][i] = index_nand_podt[listStr[4].toInt()];
                    nand_ce2_rodt[testcnt][i] = index_nand_rodt[listStr[4].toInt()];
                }
                else if(listStr[3].toInt() == 3){
                    nand_ce3_ds[testcnt][i] = index_nand_ds[listStr[4].toInt()];
                    nand_ce3_podt[testcnt][i] = index_nand_podt[listStr[4].toInt()];
                    nand_ce3_rodt[testcnt][i] = index_nand_rodt[listStr[4].toInt()];
                }
            }
        }
    }
}

void MainWindow::ViewParameter(int testcnt)
{
    QStringList strlist_soc_ds;
    QStringList strlist_soc_odt;
    QStringList strlist_nand_ds;
    QStringList strlist_nand_odt;

    strlist_soc_ds.empty();
    strlist_soc_ds.append("50");
    strlist_soc_ds.append("35");
    strlist_soc_ds.append("25");
    strlist_soc_ds.append("18");

    strlist_soc_odt.empty();
    strlist_soc_odt.append("NONE");
    strlist_soc_odt.append("150");
    strlist_soc_odt.append("100");
    strlist_soc_odt.append("75");
    strlist_soc_odt.append("50");
    strlist_soc_odt.append("30");

    strlist_nand_ds.empty();
    strlist_nand_ds.append("UNDER");
    strlist_nand_ds.append("NORMAL");
    strlist_nand_ds.append("OVER");

    strlist_nand_odt.empty();
    strlist_nand_odt.append("NONE");
    strlist_nand_odt.append("150");
    strlist_nand_odt.append("100");
    strlist_nand_odt.append("75");
    strlist_nand_odt.append("50");

    ui->LB_SOC_CTRL_DS_0->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][0]-1]);
    ui->LB_SOC_CTRL_DS_1->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][1]-1]);
    ui->LB_SOC_CTRL_DS_12->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][2]-1]);
    ui->LB_SOC_CTRL_DS_3->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][3]-1]);
    ui->LB_SOC_CTRL_DS_4->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][4]-1]);
    ui->LB_SOC_CTRL_DS_5->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][5]-1]);
    ui->LB_SOC_CTRL_DS_6->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][6]-1]);
    ui->LB_SOC_CTRL_DS_7->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][7]-1]);
    ui->LB_SOC_CTRL_DS_8->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][8]-1]);
    ui->LB_SOC_CTRL_DS_9->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][9]-1]);
    ui->LB_SOC_CTRL_DS_10->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][10]-1]);
    ui->LB_SOC_CTRL_DS_11->setText(strlist_soc_ds[soc_ctrl_ds[testcnt][11]-1]);
    ui->LB_SOC_RE_DS_0->setText(strlist_soc_ds[soc_re_ds[testcnt][0]-1]);
    ui->LB_SOC_RE_DS_1->setText(strlist_soc_ds[soc_re_ds[testcnt][1]-1]);
    ui->LB_SOC_RE_DS_12->setText(strlist_soc_ds[soc_re_ds[testcnt][2]-1]);
    ui->LB_SOC_RE_DS_3->setText(strlist_soc_ds[soc_re_ds[testcnt][3]-1]);
    ui->LB_SOC_RE_DS_4->setText(strlist_soc_ds[soc_re_ds[testcnt][4]-1]);
    ui->LB_SOC_RE_DS_5->setText(strlist_soc_ds[soc_re_ds[testcnt][5]-1]);
    ui->LB_SOC_RE_DS_6->setText(strlist_soc_ds[soc_re_ds[testcnt][6]-1]);
    ui->LB_SOC_RE_DS_7->setText(strlist_soc_ds[soc_re_ds[testcnt][7]-1]);
    ui->LB_SOC_RE_DS_8->setText(strlist_soc_ds[soc_re_ds[testcnt][8]-1]);
    ui->LB_SOC_RE_DS_9->setText(strlist_soc_ds[soc_re_ds[testcnt][9]-1]);
    ui->LB_SOC_RE_DS_10->setText(strlist_soc_ds[soc_re_ds[testcnt][10]-1]);
    ui->LB_SOC_RE_DS_11->setText(strlist_soc_ds[soc_re_ds[testcnt][11]-1]);
    ui->LB_SOC_DQS_DS_0->setText(strlist_soc_ds[soc_dqs_ds[testcnt][0]-1]);
    ui->LB_SOC_DQS_DS_1->setText(strlist_soc_ds[soc_dqs_ds[testcnt][1]-1]);
    ui->LB_SOC_DQS_DS_12->setText(strlist_soc_ds[soc_dqs_ds[testcnt][2]-1]);
    ui->LB_SOC_DQS_DS_3->setText(strlist_soc_ds[soc_dqs_ds[testcnt][3]-1]);
    ui->LB_SOC_DQS_DS_4->setText(strlist_soc_ds[soc_dqs_ds[testcnt][4]-1]);
    ui->LB_SOC_DQS_DS_5->setText(strlist_soc_ds[soc_dqs_ds[testcnt][5]-1]);
    ui->LB_SOC_DQS_DS_6->setText(strlist_soc_ds[soc_dqs_ds[testcnt][6]-1]);
    ui->LB_SOC_DQS_DS_7->setText(strlist_soc_ds[soc_dqs_ds[testcnt][7]-1]);
    ui->LB_SOC_DQS_DS_8->setText(strlist_soc_ds[soc_dqs_ds[testcnt][8]-1]);
    ui->LB_SOC_DQS_DS_9->setText(strlist_soc_ds[soc_dqs_ds[testcnt][9]-1]);
    ui->LB_SOC_DQS_DS_10->setText(strlist_soc_ds[soc_dqs_ds[testcnt][10]-1]);
    ui->LB_SOC_DQS_DS_11->setText(strlist_soc_ds[soc_dqs_ds[testcnt][11]-1]);
    ui->LB_SOC_DQS_ODT_0->setText(strlist_soc_odt[soc_dqs_odt[testcnt][0]-1]);
    ui->LB_SOC_DQS_ODT_1->setText(strlist_soc_odt[soc_dqs_odt[testcnt][1]-1]);
    ui->LB_SOC_DQS_ODT_12->setText(strlist_soc_odt[soc_dqs_odt[testcnt][2]-1]);
    ui->LB_SOC_DQS_ODT_3->setText(strlist_soc_odt[soc_dqs_odt[testcnt][3]-1]);
    ui->LB_SOC_DQS_ODT_4->setText(strlist_soc_odt[soc_dqs_odt[testcnt][4]-1]);
    ui->LB_SOC_DQS_ODT_5->setText(strlist_soc_odt[soc_dqs_odt[testcnt][5]-1]);
    ui->LB_SOC_DQS_ODT_6->setText(strlist_soc_odt[soc_dqs_odt[testcnt][6]-1]);
    ui->LB_SOC_DQS_ODT_7->setText(strlist_soc_odt[soc_dqs_odt[testcnt][7]-1]);
    ui->LB_SOC_DQS_ODT_8->setText(strlist_soc_odt[soc_dqs_odt[testcnt][8]-1]);
    ui->LB_SOC_DQS_ODT_9->setText(strlist_soc_odt[soc_dqs_odt[testcnt][9]-1]);
    ui->LB_SOC_DQS_ODT_10->setText(strlist_soc_odt[soc_dqs_odt[testcnt][10]-1]);
    ui->LB_SOC_DQS_ODT_11->setText(strlist_soc_odt[soc_dqs_odt[testcnt][11]-1]);
    ui->LB_SOC_DQ_DS_0->setText(strlist_soc_ds[soc_dq_ds[testcnt][0]-1]);
    ui->LB_SOC_DQ_DS_1->setText(strlist_soc_ds[soc_dq_ds[testcnt][1]-1]);
    ui->LB_SOC_DQ_DS_12->setText(strlist_soc_ds[soc_dq_ds[testcnt][2]-1]);
    ui->LB_SOC_DQ_DS_3->setText(strlist_soc_ds[soc_dq_ds[testcnt][3]-1]);
    ui->LB_SOC_DQ_DS_4->setText(strlist_soc_ds[soc_dq_ds[testcnt][4]-1]);
    ui->LB_SOC_DQ_DS_5->setText(strlist_soc_ds[soc_dq_ds[testcnt][5]-1]);
    ui->LB_SOC_DQ_DS_6->setText(strlist_soc_ds[soc_dq_ds[testcnt][6]-1]);
    ui->LB_SOC_DQ_DS_7->setText(strlist_soc_ds[soc_dq_ds[testcnt][7]-1]);
    ui->LB_SOC_DQ_DS_8->setText(strlist_soc_ds[soc_dq_ds[testcnt][8]-1]);
    ui->LB_SOC_DQ_DS_9->setText(strlist_soc_ds[soc_dq_ds[testcnt][9]-1]);
    ui->LB_SOC_DQ_DS_10->setText(strlist_soc_ds[soc_dq_ds[testcnt][10]-1]);
    ui->LB_SOC_DQ_DS_11->setText(strlist_soc_ds[soc_dq_ds[testcnt][11]-1]);
    ui->LB_SOC_DQ_ODT_0->setText(strlist_soc_odt[soc_dq_odt[testcnt][0]-1]);
    ui->LB_SOC_DQ_ODT_1->setText(strlist_soc_odt[soc_dq_odt[testcnt][1]-1]);
    ui->LB_SOC_DQ_ODT_12->setText(strlist_soc_odt[soc_dq_odt[testcnt][2]-1]);
    ui->LB_SOC_DQ_ODT_3->setText(strlist_soc_odt[soc_dq_odt[testcnt][3]-1]);
    ui->LB_SOC_DQ_ODT_4->setText(strlist_soc_odt[soc_dq_odt[testcnt][4]-1]);
    ui->LB_SOC_DQ_ODT_5->setText(strlist_soc_odt[soc_dq_odt[testcnt][5]-1]);
    ui->LB_SOC_DQ_ODT_6->setText(strlist_soc_odt[soc_dq_odt[testcnt][6]-1]);
    ui->LB_SOC_DQ_ODT_7->setText(strlist_soc_odt[soc_dq_odt[testcnt][7]-1]);
    ui->LB_SOC_DQ_ODT_8->setText(strlist_soc_odt[soc_dq_odt[testcnt][8]-1]);
    ui->LB_SOC_DQ_ODT_9->setText(strlist_soc_odt[soc_dq_odt[testcnt][9]-1]);
    ui->LB_SOC_DQ_ODT_10->setText(strlist_soc_odt[soc_dq_odt[testcnt][10]-1]);
    ui->LB_SOC_DQ_ODT_11->setText(strlist_soc_odt[soc_dq_odt[testcnt][11]-1]);
    ui->LB_NAND_CE0_DS_0->setText(strlist_nand_ds[nand_ce0_ds[testcnt][0]-1]);
    ui->LB_NAND_CE0_DS_1->setText(strlist_nand_ds[nand_ce0_ds[testcnt][1]-1]);
    ui->LB_NAND_CE0_DS_12->setText(strlist_nand_ds[nand_ce0_ds[testcnt][2]-1]);
    ui->LB_NAND_CE0_DS_3->setText(strlist_nand_ds[nand_ce0_ds[testcnt][3]-1]);
    ui->LB_NAND_CE0_DS_4->setText(strlist_nand_ds[nand_ce0_ds[testcnt][4]-1]);
    ui->LB_NAND_CE0_DS_5->setText(strlist_nand_ds[nand_ce0_ds[testcnt][5]-1]);
    ui->LB_NAND_CE0_DS_6->setText(strlist_nand_ds[nand_ce0_ds[testcnt][6]-1]);
    ui->LB_NAND_CE0_DS_7->setText(strlist_nand_ds[nand_ce0_ds[testcnt][7]-1]);
    ui->LB_NAND_CE0_DS_8->setText(strlist_nand_ds[nand_ce0_ds[testcnt][8]-1]);
    ui->LB_NAND_CE0_DS_9->setText(strlist_nand_ds[nand_ce0_ds[testcnt][9]-1]);
    ui->LB_NAND_CE0_DS_10->setText(strlist_nand_ds[nand_ce0_ds[testcnt][10]-1]);
    ui->LB_NAND_CE0_DS_11->setText(strlist_nand_ds[nand_ce0_ds[testcnt][11]-1]);
    ui->LB_NAND_CE0_PODT_0->setText(strlist_nand_odt[nand_ce0_podt[testcnt][0]-1]);
    ui->LB_NAND_CE0_PODT_1->setText(strlist_nand_odt[nand_ce0_podt[testcnt][1]-1]);
    ui->LB_NAND_CE0_PODT_12->setText(strlist_nand_odt[nand_ce0_podt[testcnt][2]-1]);
    ui->LB_NAND_CE0_PODT_3->setText(strlist_nand_odt[nand_ce0_podt[testcnt][3]-1]);
    ui->LB_NAND_CE0_PODT_4->setText(strlist_nand_odt[nand_ce0_podt[testcnt][4]-1]);
    ui->LB_NAND_CE0_PODT_5->setText(strlist_nand_odt[nand_ce0_podt[testcnt][5]-1]);
    ui->LB_NAND_CE0_PODT_6->setText(strlist_nand_odt[nand_ce0_podt[testcnt][6]-1]);
    ui->LB_NAND_CE0_PODT_7->setText(strlist_nand_odt[nand_ce0_podt[testcnt][7]-1]);
    ui->LB_NAND_CE0_PODT_8->setText(strlist_nand_odt[nand_ce0_podt[testcnt][8]-1]);
    ui->LB_NAND_CE0_PODT_9->setText(strlist_nand_odt[nand_ce0_podt[testcnt][9]-1]);
    ui->LB_NAND_CE0_PODT_10->setText(strlist_nand_odt[nand_ce0_podt[testcnt][10]-1]);
    ui->LB_NAND_CE0_PODT_11->setText(strlist_nand_odt[nand_ce0_podt[testcnt][11]-1]);
    ui->LB_NAND_CE0_RODT_0->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][0]-1]);
    ui->LB_NAND_CE0_RODT_1->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][1]-1]);
    ui->LB_NAND_CE0_RODT_12->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][2]-1]);
    ui->LB_NAND_CE0_RODT_3->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][3]-1]);
    ui->LB_NAND_CE0_RODT_4->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][4]-1]);
    ui->LB_NAND_CE0_RODT_5->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][5]-1]);
    ui->LB_NAND_CE0_RODT_6->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][6]-1]);
    ui->LB_NAND_CE0_RODT_7->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][7]-1]);
    ui->LB_NAND_CE0_RODT_8->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][8]-1]);
    ui->LB_NAND_CE0_RODT_9->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][9]-1]);
    ui->LB_NAND_CE0_RODT_10->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][10]-1]);
    ui->LB_NAND_CE0_RODT_11->setText(strlist_nand_odt[nand_ce0_rodt[testcnt][11]-1]);
    ui->LB_NAND_CE1_DS_0->setText(strlist_nand_ds[nand_ce1_ds[testcnt][0]-1]);
    ui->LB_NAND_CE1_DS_1->setText(strlist_nand_ds[nand_ce1_ds[testcnt][1]-1]);
    ui->LB_NAND_CE1_DS_12->setText(strlist_nand_ds[nand_ce1_ds[testcnt][2]-1]);
    ui->LB_NAND_CE1_DS_3->setText(strlist_nand_ds[nand_ce1_ds[testcnt][3]-1]);
    ui->LB_NAND_CE1_DS_4->setText(strlist_nand_ds[nand_ce1_ds[testcnt][4]-1]);
    ui->LB_NAND_CE1_DS_5->setText(strlist_nand_ds[nand_ce1_ds[testcnt][5]-1]);
    ui->LB_NAND_CE1_DS_6->setText(strlist_nand_ds[nand_ce1_ds[testcnt][6]-1]);
    ui->LB_NAND_CE1_DS_7->setText(strlist_nand_ds[nand_ce1_ds[testcnt][7]-1]);
    ui->LB_NAND_CE1_DS_8->setText(strlist_nand_ds[nand_ce1_ds[testcnt][8]-1]);
    ui->LB_NAND_CE1_DS_9->setText(strlist_nand_ds[nand_ce1_ds[testcnt][9]-1]);
    ui->LB_NAND_CE1_DS_10->setText(strlist_nand_ds[nand_ce1_ds[testcnt][10]-1]);
    ui->LB_NAND_CE1_DS_11->setText(strlist_nand_ds[nand_ce1_ds[testcnt][11]-1]);
    ui->LB_NAND_CE1_PODT_0->setText(strlist_nand_odt[nand_ce1_podt[testcnt][0]-1]);
    ui->LB_NAND_CE1_PODT_1->setText(strlist_nand_odt[nand_ce1_podt[testcnt][1]-1]);
    ui->LB_NAND_CE1_PODT_12->setText(strlist_nand_odt[nand_ce1_podt[testcnt][2]-1]);
    ui->LB_NAND_CE1_PODT_3->setText(strlist_nand_odt[nand_ce1_podt[testcnt][3]-1]);
    ui->LB_NAND_CE1_PODT_4->setText(strlist_nand_odt[nand_ce1_podt[testcnt][4]-1]);
    ui->LB_NAND_CE1_PODT_5->setText(strlist_nand_odt[nand_ce1_podt[testcnt][5]-1]);
    ui->LB_NAND_CE1_PODT_6->setText(strlist_nand_odt[nand_ce1_podt[testcnt][6]-1]);
    ui->LB_NAND_CE1_PODT_7->setText(strlist_nand_odt[nand_ce1_podt[testcnt][7]-1]);
    ui->LB_NAND_CE1_PODT_8->setText(strlist_nand_odt[nand_ce1_podt[testcnt][8]-1]);
    ui->LB_NAND_CE1_PODT_9->setText(strlist_nand_odt[nand_ce1_podt[testcnt][9]-1]);
    ui->LB_NAND_CE1_PODT_10->setText(strlist_nand_odt[nand_ce1_podt[testcnt][10]-1]);
    ui->LB_NAND_CE1_PODT_11->setText(strlist_nand_odt[nand_ce1_podt[testcnt][11]-1]);
    ui->LB_NAND_CE1_RODT_0->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][0]-1]);
    ui->LB_NAND_CE1_RODT_1->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][1]-1]);
    ui->LB_NAND_CE1_RODT_12->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][2]-1]);
    ui->LB_NAND_CE1_RODT_3->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][3]-1]);
    ui->LB_NAND_CE1_RODT_4->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][4]-1]);
    ui->LB_NAND_CE1_RODT_5->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][5]-1]);
    ui->LB_NAND_CE1_RODT_6->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][6]-1]);
    ui->LB_NAND_CE1_RODT_7->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][7]-1]);
    ui->LB_NAND_CE1_RODT_8->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][8]-1]);
    ui->LB_NAND_CE1_RODT_9->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][9]-1]);
    ui->LB_NAND_CE1_RODT_10->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][10]-1]);
    ui->LB_NAND_CE1_RODT_11->setText(strlist_nand_odt[nand_ce1_rodt[testcnt][11]-1]);
    ui->LB_NAND_CE2_DS_0->setText(strlist_nand_ds[nand_ce2_ds[testcnt][0]-1]);
    ui->LB_NAND_CE2_DS_1->setText(strlist_nand_ds[nand_ce2_ds[testcnt][1]-1]);
    ui->LB_NAND_CE2_DS_12->setText(strlist_nand_ds[nand_ce2_ds[testcnt][2]-1]);
    ui->LB_NAND_CE2_DS_3->setText(strlist_nand_ds[nand_ce2_ds[testcnt][3]-1]);
    ui->LB_NAND_CE2_DS_4->setText(strlist_nand_ds[nand_ce2_ds[testcnt][4]-1]);
    ui->LB_NAND_CE2_DS_5->setText(strlist_nand_ds[nand_ce2_ds[testcnt][5]-1]);
    ui->LB_NAND_CE2_DS_6->setText(strlist_nand_ds[nand_ce2_ds[testcnt][6]-1]);
    ui->LB_NAND_CE2_DS_7->setText(strlist_nand_ds[nand_ce2_ds[testcnt][7]-1]);
    ui->LB_NAND_CE2_DS_8->setText(strlist_nand_ds[nand_ce2_ds[testcnt][8]-1]);
    ui->LB_NAND_CE2_DS_9->setText(strlist_nand_ds[nand_ce2_ds[testcnt][9]-1]);
    ui->LB_NAND_CE2_DS_10->setText(strlist_nand_ds[nand_ce2_ds[testcnt][10]-1]);
    ui->LB_NAND_CE2_DS_11->setText(strlist_nand_ds[nand_ce2_ds[testcnt][11]-1]);
    ui->LB_NAND_CE2_PODT_0->setText(strlist_nand_odt[nand_ce2_podt[testcnt][0]-1]);
    ui->LB_NAND_CE2_PODT_1->setText(strlist_nand_odt[nand_ce2_podt[testcnt][1]-1]);
    ui->LB_NAND_CE2_PODT_12->setText(strlist_nand_odt[nand_ce2_podt[testcnt][2]-1]);
    ui->LB_NAND_CE2_PODT_3->setText(strlist_nand_odt[nand_ce2_podt[testcnt][3]-1]);
    ui->LB_NAND_CE2_PODT_4->setText(strlist_nand_odt[nand_ce2_podt[testcnt][4]-1]);
    ui->LB_NAND_CE2_PODT_5->setText(strlist_nand_odt[nand_ce2_podt[testcnt][5]-1]);
    ui->LB_NAND_CE2_PODT_6->setText(strlist_nand_odt[nand_ce2_podt[testcnt][6]-1]);
    ui->LB_NAND_CE2_PODT_7->setText(strlist_nand_odt[nand_ce2_podt[testcnt][7]-1]);
    ui->LB_NAND_CE2_PODT_8->setText(strlist_nand_odt[nand_ce2_podt[testcnt][8]-1]);
    ui->LB_NAND_CE2_PODT_9->setText(strlist_nand_odt[nand_ce2_podt[testcnt][9]-1]);
    ui->LB_NAND_CE2_PODT_10->setText(strlist_nand_odt[nand_ce2_podt[testcnt][10]-1]);
    ui->LB_NAND_CE2_PODT_11->setText(strlist_nand_odt[nand_ce2_podt[testcnt][11]-1]);
    ui->LB_NAND_CE2_RODT_0->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][0]-1]);
    ui->LB_NAND_CE2_RODT_1->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][1]-1]);
    ui->LB_NAND_CE2_RODT_12->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][2]-1]);
    ui->LB_NAND_CE2_RODT_3->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][3]-1]);
    ui->LB_NAND_CE2_RODT_4->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][4]-1]);
    ui->LB_NAND_CE2_RODT_5->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][5]-1]);
    ui->LB_NAND_CE2_RODT_6->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][6]-1]);
    ui->LB_NAND_CE2_RODT_7->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][7]-1]);
    ui->LB_NAND_CE2_RODT_8->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][8]-1]);
    ui->LB_NAND_CE2_RODT_9->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][9]-1]);
    ui->LB_NAND_CE2_RODT_10->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][10]-1]);
    ui->LB_NAND_CE2_RODT_11->setText(strlist_nand_odt[nand_ce2_rodt[testcnt][11]-1]);
    ui->LB_NAND_CE3_DS_0->setText(strlist_nand_ds[nand_ce3_ds[testcnt][0]-1]);
    ui->LB_NAND_CE3_DS_1->setText(strlist_nand_ds[nand_ce3_ds[testcnt][1]-1]);
    ui->LB_NAND_CE3_DS_12->setText(strlist_nand_ds[nand_ce3_ds[testcnt][2]-1]);
    ui->LB_NAND_CE3_DS_3->setText(strlist_nand_ds[nand_ce3_ds[testcnt][3]-1]);
    ui->LB_NAND_CE3_DS_4->setText(strlist_nand_ds[nand_ce3_ds[testcnt][4]-1]);
    ui->LB_NAND_CE3_DS_5->setText(strlist_nand_ds[nand_ce3_ds[testcnt][5]-1]);
    ui->LB_NAND_CE3_DS_6->setText(strlist_nand_ds[nand_ce3_ds[testcnt][6]-1]);
    ui->LB_NAND_CE3_DS_7->setText(strlist_nand_ds[nand_ce3_ds[testcnt][7]-1]);
    ui->LB_NAND_CE3_DS_8->setText(strlist_nand_ds[nand_ce3_ds[testcnt][8]-1]);
    ui->LB_NAND_CE3_DS_9->setText(strlist_nand_ds[nand_ce3_ds[testcnt][9]-1]);
    ui->LB_NAND_CE3_DS_10->setText(strlist_nand_ds[nand_ce3_ds[testcnt][10]-1]);
    ui->LB_NAND_CE3_DS_11->setText(strlist_nand_ds[nand_ce3_ds[testcnt][11]-1]);
    ui->LB_NAND_CE3_PODT_0->setText(strlist_nand_odt[nand_ce3_podt[testcnt][0]-1]);
    ui->LB_NAND_CE3_PODT_1->setText(strlist_nand_odt[nand_ce3_podt[testcnt][1]-1]);
    ui->LB_NAND_CE3_PODT_12->setText(strlist_nand_odt[nand_ce3_podt[testcnt][2]-1]);
    ui->LB_NAND_CE3_PODT_3->setText(strlist_nand_odt[nand_ce3_podt[testcnt][3]-1]);
    ui->LB_NAND_CE3_PODT_4->setText(strlist_nand_odt[nand_ce3_podt[testcnt][4]-1]);
    ui->LB_NAND_CE3_PODT_5->setText(strlist_nand_odt[nand_ce3_podt[testcnt][5]-1]);
    ui->LB_NAND_CE3_PODT_6->setText(strlist_nand_odt[nand_ce3_podt[testcnt][6]-1]);
    ui->LB_NAND_CE3_PODT_7->setText(strlist_nand_odt[nand_ce3_podt[testcnt][7]-1]);
    ui->LB_NAND_CE3_PODT_8->setText(strlist_nand_odt[nand_ce3_podt[testcnt][8]-1]);
    ui->LB_NAND_CE3_PODT_9->setText(strlist_nand_odt[nand_ce3_podt[testcnt][9]-1]);
    ui->LB_NAND_CE3_PODT_10->setText(strlist_nand_odt[nand_ce3_podt[testcnt][10]-1]);
    ui->LB_NAND_CE3_PODT_11->setText(strlist_nand_odt[nand_ce3_podt[testcnt][11]-1]);
    ui->LB_NAND_CE3_RODT_0->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][0]-1]);
    ui->LB_NAND_CE3_RODT_1->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][1]-1]);
    ui->LB_NAND_CE3_RODT_12->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][2]-1]);
    ui->LB_NAND_CE3_RODT_3->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][3]-1]);
    ui->LB_NAND_CE3_RODT_4->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][4]-1]);
    ui->LB_NAND_CE3_RODT_5->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][5]-1]);
    ui->LB_NAND_CE3_RODT_6->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][6]-1]);
    ui->LB_NAND_CE3_RODT_7->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][7]-1]);
    ui->LB_NAND_CE3_RODT_8->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][8]-1]);
    ui->LB_NAND_CE3_RODT_9->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][9]-1]);
    ui->LB_NAND_CE3_RODT_10->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][10]-1]);
    ui->LB_NAND_CE3_RODT_11->setText(strlist_nand_odt[nand_ce3_rodt[testcnt][11]-1]);

}

QString MainWindow::ContainString(QString str)
{
    str.remove("0");
    str.remove("1");
    str.remove("2");
    str.remove("3");
    str.remove("4");
    str.remove("5");
    str.remove("6");
    str.remove("7");
    str.remove("8");
    str.remove("9");

    return str;
}

void MainWindow::on_Run_CMD_clicked()
{
#if 1
    QString path;
    path = QApplication::applicationDirPath()+"/"+"bist.py";
    path.replace("/","\\");
    QString cmd_qt = QString("python3 \"" + path +"\" -D %2 -P %3 -T %4").arg(ui->port_CB->currentText()).arg(ui->run_preset_txt->text()).arg(ui->run_text_txt->text());

    const char* cmd = cmd_qt.toUtf8();
    system(cmd);
#else
    QByteArray arr;
    QString str;
    QStringList parser_strList;
    QMessageBox mm;

    //if(QFile::exists(QApplication::applicationDirPath()+"/"+output1) == false){
    if(QFile::exists("D:\\OneDrive - FADU Inc\\work\\98_ETC\\Test\\Test_QT_PresetMake\\build-PRESET_MAKER-Desktop_Qt_5_9_5_MinGW_32bit-Release\\release\\"+output1) == false){

        mm.setText("File not found");
        mm.exec();
        return;
    }

    //file.setFileName(QApplication::applicationDirPath()+"/"+output1);
    file.setFileName("D:\\OneDrive - FADU Inc\\work\\98_ETC\\Test\\Test_QT_PresetMake\\build-PRESET_MAKER-Desktop_Qt_5_9_5_MinGW_32bit-Release\\release\\"+output1);

    file.open(QIODevice::ReadWrite);

    arr = file.readAll();
    file.close();

    str = QString(arr);
    parser_strList.empty();
    parser_strList = str.split(" = ");
    if(parser_strList.count() < 2){
        check_si_list = 0;
        check_si_total = 0;
        check_all_x();
    }
    else{

        str = parser_strList[1];

        parser_strList.empty();
        parser_strList = str.split(",");

        check_si_list = 0;
        check_si_total = 0;
        foreach(QString n, parser_strList){
            if(n.contains("si_para")) {
                continue;
            }
            else if(n.contains("si")) {
                check_si_total++;
                check_si_list = 1;
            }
            else{
                QString strn;

                strn = Get_PresetCmd(strn);
                Set_CmdParameter(check_si_total, strn);
            }
        }
    }
    if(check_si_total == 0)
    {
        check_all_x();
    }
    else{
        ViewParameter(check_si_list-1);
    }

    ui->si_test_txt->setText("SI Test (" + QString::number(check_si_list) + "/" + QString::number(check_si_total) + ")");
    ui->Check_frame->show();
    ui->Run_frame->hide();
#endif
}

void MainWindow::on_log_reflash_CMD_clicked()
{
    QStringList strFilters;
    int cnt;

    logPathString.empty();
    cnt = ui->log_list->count();
    for(int i=0;i<cnt;i++){
        delete ui->log_list->item(0);
    }

    strFilters += "*.log";

    QDirIterator iterDir(QApplication::applicationDirPath(), strFilters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    while (iterDir.hasNext())
    {
        iterDir.next();

        ui->log_list->addItem(iterDir.fileName());
        logPathString.append(iterDir.filePath());
    }
}

void MainWindow::on_log_parsing_CMD_clicked()
{
    QString path;
    QString path2;

    path = QApplication::applicationDirPath()+"/"+"bist_parser.py";
    path.replace("/","\\");

    path2 = logPathString[ui->log_list->currentRow()];
    path2.replace("/","\\");

    QString cmd_qt = QString("python3 \"" + path +"\" %2 %3 \"%4\" %5").arg(ui->parser_ch_txt->text()).arg(ui->parser_tap_txt->text()).arg(path2).arg(ui->parser_CB->currentText());

    const char* cmd = cmd_qt.toUtf8();
    system(cmd);
}

void MainWindow::on_Chk_Next_CMD_3_clicked()
{
    ui->Run_frame->show();
    ui->Check_frame->hide();
}

void MainWindow::on_si_ch0_txt_returnPressed()
{
    ui->si_ch1_txt->setFocus();
}

void MainWindow::on_si_ch1_txt_returnPressed()
{
    ui->si_ch2_txt->setFocus();
}
