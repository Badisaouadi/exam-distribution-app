#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QSerialPort>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateTimers();
    void on_pushButtonCreateDistribution_clicked();
    void on_pushButtonUpdateDistribution_clicked();
    void on_pushButtonDeleteDistribution_clicked();
    void on_pushButtonCreatePickUp_clicked();
    void on_pushButtonUpdatePickUp_clicked();
    void on_pushButtonDeletePickUp_clicked();
    void verifierRetards();
    void on_pushButtonExportDistribution_clicked();
    void on_pushButtonExportPickUp_clicked();


private:
    void setupUI();
    void resetPickUpForm();
    void resetDistributionForm();
    bool validateEtat(const QString& etat) const;
    void refreshDistributionTable();
    void setupMatiereComboBox();
    void refreshPickUpTable();
    void loadInitialData();
    bool validatePickUpInputs(int idDistribution, const QString& matiere, int idEpreuve, const QDateTime& deadline);
    bool validateDistributionInputs(int id, int idCentre, const QString& etat, const QDateTime& debut, const QDateTime& fin);
    QSerialPort *arduino;
    void setupArduino();

    Ui::MainWindow *ui;
    QTimer *m_timer;
    QSortFilterProxyModel *m_distProxyModel;
    QSortFilterProxyModel *m_pickupProxyModel;
    void afficherNotification(int idDistribution, const QString& centre);
    QTimer *m_notificationTimer;
    void afficherNotificationPickUp(int idDistribution, const QString& matiere);
    void exportToPdf(QAbstractItemModel* model, const QString& title, const QString& fileName);

};

#endif // MAINWINDOW_H
