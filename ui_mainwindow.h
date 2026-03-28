/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_15;
    QLabel *logo_1;
    QPushButton *employes_2;
    QLineEdit *purple_3;
    QPushButton *reservations_2;
    QPushButton *evenement_2;
    QPushButton *pushButton_logout;
    QPushButton *chambres_2;
    QPushButton *clients_2;
    QLineEdit *purple_4;
    QLabel *dashboard_2;
    QLineEdit *arrierePlan_7;
    QLineEdit *purple_6;
    QPushButton *evenement_3;
    QLabel *labelDeadline;
    QTableView *tableViewPickUp;
    QDateTimeEdit *dateTimeEditDeadline;
    QLabel *labelDateDebut;
    QTableView *tableViewDistribution;
    QGroupBox *groupBoxTimers;
    QHBoxLayout *horizontalLayoutTimers_2;
    QLabel *labelTimerDistribution;
    QLabel *labelTimerPickUp;
    QGroupBox *groupBoxDistribution;
    QFormLayout *formLayoutDistribution_2;
    QLabel *labelIdDistribution;
    QLineEdit *lineEditIdDistribution;
    QLabel *labelIdCentreRegional;
    QLineEdit *lineEditIdCentreRegional;
    QLabel *labelEtat;
    QComboBox *comboBoxEtat;
    QGroupBox *groupBoxPickUp;
    QFormLayout *formLayoutPickUp_2;
    QLabel *labelIdDistributionPickUp;
    QLineEdit *lineEditIdDistributionPickUp;
    QLabel *labelMatiere;
    QComboBox *comboBoxMatiere;
    QLabel *labelIdEpreuve;
    QLineEdit *lineEditIdEpreuvePickUp;
    QDateTimeEdit *dateTimeEditFin;
    QLabel *labelDateFin;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonCreateDistribution;
    QPushButton *pushButtonUpdateDistribution;
    QPushButton *pushButtonDeleteDistribution;
    QPushButton *pushButtonCreatePickUp;
    QPushButton *pushButtonUpdatePickUp;
    QPushButton *pushButtonDeletePickUp;
    QPushButton *pushButtonExportDistribution;
    QPushButton *pushButtonExportPickUp;
    QDateTimeEdit *dateTimeEditDebut;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1334, 738);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(-10, -30, 1311, 711));
        tab = new QWidget();
        tab->setObjectName("tab");
        label_15 = new QLabel(tab);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(150, 30, 231, 41));
        label_15->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 237, 255);\n"
"font: 87 13pt \"Segoe UI Black\";\n"
"\n"
""));
        label_15->setFrameShape(QFrame::Shape::NoFrame);
        label_15->setFrameShadow(QFrame::Shadow::Plain);
        label_15->setLineWidth(1);
        logo_1 = new QLabel(tab);
        logo_1->setObjectName("logo_1");
        logo_1->setGeometry(QRect(1150, 30, 41, 41));
        logo_1->setPixmap(QPixmap(QString::fromUtf8("../../../OneDrive/Documents/logo-design.png")));
        logo_1->setScaledContents(true);
        employes_2 = new QPushButton(tab);
        employes_2->setObjectName("employes_2");
        employes_2->setGeometry(QRect(0, 190, 171, 41));
        employes_2->setStyleSheet(QString::fromUtf8(""));
        purple_3 = new QLineEdit(tab);
        purple_3->setObjectName("purple_3");
        purple_3->setGeometry(QRect(210, 120, 1081, 561));
        purple_3->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #D3CDBC; /* Neutral beige/gray */\n"
"    color: #1F1F1F; /* Dark ink/black for text */\n"
"    font-family: \"Segoe UI\", \"Arial\", sans-serif;\n"
"}\n"
"\n"
"QLabel {\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    color: #1F1F1F;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #1F1F1F;\n"
"    color: #D3CDBC;\n"
"    border: 2px solid #1F1F1F;\n"
"    border-radius: 5px;\n"
"    padding: 5px 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #3B3B3B;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background-color: #F5F2EB;\n"
"    border: 1px solid #1F1F1F;\n"
"    border-radius: 3px;\n"
"    padding: 3px;\n"
"}\n"
"\n"
"QFrame {\n"
"    border: 1px solid #1F1F1F;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QComboBox {\n"
"    background-color: #F5F2EB;\n"
"    border: 1px solid #1F1F1F;\n"
"    border-radius: 3px;\n"
"    padding: 2px;\n"
"}"));
        reservations_2 = new QPushButton(tab);
        reservations_2->setObjectName("reservations_2");
        reservations_2->setGeometry(QRect(0, 290, 171, 41));
        reservations_2->setStyleSheet(QString::fromUtf8(""));
        evenement_2 = new QPushButton(tab);
        evenement_2->setObjectName("evenement_2");
        evenement_2->setGeometry(QRect(0, 390, 171, 41));
        evenement_2->setStyleSheet(QString::fromUtf8(""));
        pushButton_logout = new QPushButton(tab);
        pushButton_logout->setObjectName("pushButton_logout");
        pushButton_logout->setGeometry(QRect(0, 550, 171, 41));
        pushButton_logout->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Segoe UI\";\n"
"color: rgb(255, 0, 0);\n"
""));
        chambres_2 = new QPushButton(tab);
        chambres_2->setObjectName("chambres_2");
        chambres_2->setGeometry(QRect(0, 340, 171, 41));
        chambres_2->setStyleSheet(QString::fromUtf8(""));
        clients_2 = new QPushButton(tab);
        clients_2->setObjectName("clients_2");
        clients_2->setGeometry(QRect(0, 240, 171, 41));
        clients_2->setStyleSheet(QString::fromUtf8(""));
        purple_4 = new QLineEdit(tab);
        purple_4->setObjectName("purple_4");
        purple_4->setGeometry(QRect(0, -10, 171, 741));
        purple_4->setAcceptDrops(false);
        purple_4->setStyleSheet(QString::fromUtf8("background-color: rgb(5, 41, 47)\n"
";"));
        dashboard_2 = new QLabel(tab);
        dashboard_2->setObjectName("dashboard_2");
        dashboard_2->setGeometry(QRect(10, 40, 161, 41));
        dashboard_2->setStyleSheet(QString::fromUtf8("color: rgb(232, 231, 244);\n"
"font: 87 16pt \"Segoe UI Black\";\n"
"\n"
""));
        arrierePlan_7 = new QLineEdit(tab);
        arrierePlan_7->setObjectName("arrierePlan_7");
        arrierePlan_7->setGeometry(QRect(-10, -50, 1291, 991));
        arrierePlan_7->setStyleSheet(QString::fromUtf8("background-color: rgb( 250,  250, 255);"));
        purple_6 = new QLineEdit(tab);
        purple_6->setObjectName("purple_6");
        purple_6->setGeometry(QRect(0, 0, 1271, 101));
        purple_6->setAcceptDrops(false);
        purple_6->setStyleSheet(QString::fromUtf8("background-color: rgb(5, 41, 47)\n"
";"));
        evenement_3 = new QPushButton(tab);
        evenement_3->setObjectName("evenement_3");
        evenement_3->setGeometry(QRect(0, 440, 171, 41));
        evenement_3->setStyleSheet(QString::fromUtf8(""));
        labelDeadline = new QLabel(tab);
        labelDeadline->setObjectName("labelDeadline");
        labelDeadline->setGeometry(QRect(240, 470, 986, 16));
        tableViewPickUp = new QTableView(tab);
        tableViewPickUp->setObjectName("tableViewPickUp");
        tableViewPickUp->setGeometry(QRect(240, 580, 981, 61));
        dateTimeEditDeadline = new QDateTimeEdit(tab);
        dateTimeEditDeadline->setObjectName("dateTimeEditDeadline");
        dateTimeEditDeadline->setGeometry(QRect(240, 490, 986, 28));
        dateTimeEditDeadline->setCalendarPopup(true);
        labelDateDebut = new QLabel(tab);
        labelDateDebut->setObjectName("labelDateDebut");
        labelDateDebut->setGeometry(QRect(240, 250, 986, 16));
        tableViewDistribution = new QTableView(tab);
        tableViewDistribution->setObjectName("tableViewDistribution");
        tableViewDistribution->setGeometry(QRect(240, 520, 981, 51));
        groupBoxTimers = new QGroupBox(tab);
        groupBoxTimers->setObjectName("groupBoxTimers");
        groupBoxTimers->setGeometry(QRect(240, 756, 986, 59));
        horizontalLayoutTimers_2 = new QHBoxLayout(groupBoxTimers);
        horizontalLayoutTimers_2->setObjectName("horizontalLayoutTimers_2");
        labelTimerDistribution = new QLabel(groupBoxTimers);
        labelTimerDistribution->setObjectName("labelTimerDistribution");

        horizontalLayoutTimers_2->addWidget(labelTimerDistribution);

        labelTimerPickUp = new QLabel(groupBoxTimers);
        labelTimerPickUp->setObjectName("labelTimerPickUp");

        horizontalLayoutTimers_2->addWidget(labelTimerPickUp);

        groupBoxDistribution = new QGroupBox(tab);
        groupBoxDistribution->setObjectName("groupBoxDistribution");
        groupBoxDistribution->setGeometry(QRect(260, 140, 941, 101));
        formLayoutDistribution_2 = new QFormLayout(groupBoxDistribution);
        formLayoutDistribution_2->setObjectName("formLayoutDistribution_2");
        labelIdDistribution = new QLabel(groupBoxDistribution);
        labelIdDistribution->setObjectName("labelIdDistribution");

        formLayoutDistribution_2->setWidget(0, QFormLayout::LabelRole, labelIdDistribution);

        lineEditIdDistribution = new QLineEdit(groupBoxDistribution);
        lineEditIdDistribution->setObjectName("lineEditIdDistribution");

        formLayoutDistribution_2->setWidget(0, QFormLayout::FieldRole, lineEditIdDistribution);

        labelIdCentreRegional = new QLabel(groupBoxDistribution);
        labelIdCentreRegional->setObjectName("labelIdCentreRegional");

        formLayoutDistribution_2->setWidget(1, QFormLayout::LabelRole, labelIdCentreRegional);

        lineEditIdCentreRegional = new QLineEdit(groupBoxDistribution);
        lineEditIdCentreRegional->setObjectName("lineEditIdCentreRegional");

        formLayoutDistribution_2->setWidget(1, QFormLayout::FieldRole, lineEditIdCentreRegional);

        labelEtat = new QLabel(groupBoxDistribution);
        labelEtat->setObjectName("labelEtat");

        formLayoutDistribution_2->setWidget(2, QFormLayout::LabelRole, labelEtat);

        comboBoxEtat = new QComboBox(groupBoxDistribution);
        comboBoxEtat->addItem(QString());
        comboBoxEtat->addItem(QString());
        comboBoxEtat->addItem(QString());
        comboBoxEtat->setObjectName("comboBoxEtat");

        formLayoutDistribution_2->setWidget(2, QFormLayout::FieldRole, comboBoxEtat);

        groupBoxPickUp = new QGroupBox(tab);
        groupBoxPickUp->setObjectName("groupBoxPickUp");
        groupBoxPickUp->setGeometry(QRect(245, 350, 981, 111));
        formLayoutPickUp_2 = new QFormLayout(groupBoxPickUp);
        formLayoutPickUp_2->setObjectName("formLayoutPickUp_2");
        labelIdDistributionPickUp = new QLabel(groupBoxPickUp);
        labelIdDistributionPickUp->setObjectName("labelIdDistributionPickUp");

        formLayoutPickUp_2->setWidget(0, QFormLayout::LabelRole, labelIdDistributionPickUp);

        lineEditIdDistributionPickUp = new QLineEdit(groupBoxPickUp);
        lineEditIdDistributionPickUp->setObjectName("lineEditIdDistributionPickUp");

        formLayoutPickUp_2->setWidget(0, QFormLayout::FieldRole, lineEditIdDistributionPickUp);

        labelMatiere = new QLabel(groupBoxPickUp);
        labelMatiere->setObjectName("labelMatiere");

        formLayoutPickUp_2->setWidget(1, QFormLayout::LabelRole, labelMatiere);

        comboBoxMatiere = new QComboBox(groupBoxPickUp);
        comboBoxMatiere->addItem(QString());
        comboBoxMatiere->addItem(QString());
        comboBoxMatiere->addItem(QString());
        comboBoxMatiere->addItem(QString());
        comboBoxMatiere->addItem(QString());
        comboBoxMatiere->addItem(QString());
        comboBoxMatiere->setObjectName("comboBoxMatiere");

        formLayoutPickUp_2->setWidget(1, QFormLayout::FieldRole, comboBoxMatiere);

        labelIdEpreuve = new QLabel(groupBoxPickUp);
        labelIdEpreuve->setObjectName("labelIdEpreuve");

        formLayoutPickUp_2->setWidget(2, QFormLayout::LabelRole, labelIdEpreuve);

        lineEditIdEpreuvePickUp = new QLineEdit(groupBoxPickUp);
        lineEditIdEpreuvePickUp->setObjectName("lineEditIdEpreuvePickUp");

        formLayoutPickUp_2->setWidget(2, QFormLayout::FieldRole, lineEditIdEpreuvePickUp);

        dateTimeEditFin = new QDateTimeEdit(tab);
        dateTimeEditFin->setObjectName("dateTimeEditFin");
        dateTimeEditFin->setGeometry(QRect(240, 320, 986, 28));
        dateTimeEditFin->setCalendarPopup(true);
        labelDateFin = new QLabel(tab);
        labelDateFin->setObjectName("labelDateFin");
        labelDateFin->setGeometry(QRect(240, 300, 986, 16));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(230, 110, 1001, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonCreateDistribution = new QPushButton(layoutWidget);
        pushButtonCreateDistribution->setObjectName("pushButtonCreateDistribution");

        horizontalLayout->addWidget(pushButtonCreateDistribution);

        pushButtonUpdateDistribution = new QPushButton(layoutWidget);
        pushButtonUpdateDistribution->setObjectName("pushButtonUpdateDistribution");

        horizontalLayout->addWidget(pushButtonUpdateDistribution);

        pushButtonDeleteDistribution = new QPushButton(layoutWidget);
        pushButtonDeleteDistribution->setObjectName("pushButtonDeleteDistribution");

        horizontalLayout->addWidget(pushButtonDeleteDistribution);

        pushButtonCreatePickUp = new QPushButton(layoutWidget);
        pushButtonCreatePickUp->setObjectName("pushButtonCreatePickUp");

        horizontalLayout->addWidget(pushButtonCreatePickUp);

        pushButtonUpdatePickUp = new QPushButton(layoutWidget);
        pushButtonUpdatePickUp->setObjectName("pushButtonUpdatePickUp");

        horizontalLayout->addWidget(pushButtonUpdatePickUp);

        pushButtonDeletePickUp = new QPushButton(layoutWidget);
        pushButtonDeletePickUp->setObjectName("pushButtonDeletePickUp");

        horizontalLayout->addWidget(pushButtonDeletePickUp);

        pushButtonExportDistribution = new QPushButton(layoutWidget);
        pushButtonExportDistribution->setObjectName("pushButtonExportDistribution");

        horizontalLayout->addWidget(pushButtonExportDistribution);

        pushButtonExportPickUp = new QPushButton(layoutWidget);
        pushButtonExportPickUp->setObjectName("pushButtonExportPickUp");

        horizontalLayout->addWidget(pushButtonExportPickUp);

        dateTimeEditDebut = new QDateTimeEdit(tab);
        dateTimeEditDebut->setObjectName("dateTimeEditDebut");
        dateTimeEditDebut->setGeometry(QRect(240, 270, 986, 28));
        dateTimeEditDebut->setCalendarPopup(true);
        tabWidget->addTab(tab, QString());
        arrierePlan_7->raise();
        purple_3->raise();
        purple_4->raise();
        label_15->raise();
        logo_1->raise();
        pushButton_logout->raise();
        chambres_2->raise();
        clients_2->raise();
        reservations_2->raise();
        evenement_2->raise();
        employes_2->raise();
        purple_6->raise();
        dashboard_2->raise();
        evenement_3->raise();
        labelDeadline->raise();
        tableViewPickUp->raise();
        dateTimeEditDeadline->raise();
        labelDateDebut->raise();
        tableViewDistribution->raise();
        groupBoxTimers->raise();
        groupBoxDistribution->raise();
        groupBoxPickUp->raise();
        dateTimeEditFin->raise();
        labelDateFin->raise();
        layoutWidget->raise();
        dateTimeEditDebut->raise();
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1334, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(whatsthis)
        tabWidget->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        label_15->setText(QCoreApplication::translate("MainWindow", "distribution", nullptr));
        logo_1->setText(QString());
        employes_2->setText(QCoreApplication::translate("MainWindow", "Epreuves", nullptr));
        reservations_2->setText(QCoreApplication::translate("MainWindow", "centres regionaux", nullptr));
        evenement_2->setText(QCoreApplication::translate("MainWindow", "preparattion epreuves", nullptr));
        pushButton_logout->setText(QCoreApplication::translate("MainWindow", "se deconnecter", nullptr));
        chambres_2->setText(QCoreApplication::translate("MainWindow", "correction epreuve", nullptr));
        clients_2->setText(QCoreApplication::translate("MainWindow", "distrubution", nullptr));
        dashboard_2->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        evenement_3->setText(QCoreApplication::translate("MainWindow", "enseignants", nullptr));
        labelDeadline->setText(QCoreApplication::translate("MainWindow", "Deadline:", nullptr));
        labelDateDebut->setText(QCoreApplication::translate("MainWindow", "Date d\303\251but:", nullptr));
        groupBoxTimers->setTitle(QCoreApplication::translate("MainWindow", "Temps restant", nullptr));
        labelTimerDistribution->setText(QCoreApplication::translate("MainWindow", "Distribution: -", nullptr));
        labelTimerPickUp->setText(QCoreApplication::translate("MainWindow", "Pick-Up: -", nullptr));
        groupBoxDistribution->setTitle(QCoreApplication::translate("MainWindow", "Distribution", nullptr));
        labelIdDistribution->setText(QCoreApplication::translate("MainWindow", "ID Distribution:", nullptr));
        labelIdCentreRegional->setText(QCoreApplication::translate("MainWindow", "ID Centre R\303\251gional:", nullptr));
        labelEtat->setText(QCoreApplication::translate("MainWindow", "\303\211tat:", nullptr));
        comboBoxEtat->setItemText(0, QCoreApplication::translate("MainWindow", "pas encore", nullptr));
        comboBoxEtat->setItemText(1, QCoreApplication::translate("MainWindow", "en cours", nullptr));
        comboBoxEtat->setItemText(2, QCoreApplication::translate("MainWindow", "distribu\303\251e", nullptr));

        groupBoxPickUp->setTitle(QCoreApplication::translate("MainWindow", "Pick-Up", nullptr));
        labelIdDistributionPickUp->setText(QCoreApplication::translate("MainWindow", "ID Distribution:", nullptr));
        labelMatiere->setText(QCoreApplication::translate("MainWindow", "Mati\303\250re:", nullptr));
        comboBoxMatiere->setItemText(0, QCoreApplication::translate("MainWindow", "Arabe", nullptr));
        comboBoxMatiere->setItemText(1, QCoreApplication::translate("MainWindow", "Fran\303\247ais", nullptr));
        comboBoxMatiere->setItemText(2, QCoreApplication::translate("MainWindow", "Anglais", nullptr));
        comboBoxMatiere->setItemText(3, QCoreApplication::translate("MainWindow", "Math\303\251matiques", nullptr));
        comboBoxMatiere->setItemText(4, QCoreApplication::translate("MainWindow", "Physique", nullptr));
        comboBoxMatiere->setItemText(5, QCoreApplication::translate("MainWindow", "SVT", nullptr));

        labelIdEpreuve->setText(QCoreApplication::translate("MainWindow", "ID \303\211preuve:", nullptr));
        labelDateFin->setText(QCoreApplication::translate("MainWindow", "Date fin:", nullptr));
        pushButtonCreateDistribution->setText(QCoreApplication::translate("MainWindow", "Cr\303\251er Distribution", nullptr));
        pushButtonUpdateDistribution->setText(QCoreApplication::translate("MainWindow", "Mettre \303\240 jour Distribution", nullptr));
        pushButtonDeleteDistribution->setText(QCoreApplication::translate("MainWindow", "Supprimer Distribution", nullptr));
        pushButtonCreatePickUp->setText(QCoreApplication::translate("MainWindow", "Cr\303\251er Pick-Up", nullptr));
        pushButtonUpdatePickUp->setText(QCoreApplication::translate("MainWindow", "Mettre \303\240 jour Pick-Up", nullptr));
        pushButtonDeletePickUp->setText(QCoreApplication::translate("MainWindow", "Supprimer Pick-Up", nullptr));
        pushButtonExportDistribution->setText(QCoreApplication::translate("MainWindow", "Exporter Distribution PDF", nullptr));
        pushButtonExportPickUp->setText(QCoreApplication::translate("MainWindow", "Exporter Pick-Up PDF", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "ajout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
