#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "distribution.h"
#include "pick_up.h"
#include "colordelegate.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSystemTrayIcon>
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QScrollBar>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_timer(new QTimer(this)),
    m_distProxyModel(new QSortFilterProxyModel(this)),
    m_pickupProxyModel(new QSortFilterProxyModel(this)),
    arduino(nullptr)
{
    ui->setupUi(this);
    setupArduino();

    arduino->setPortName("COM3"); // Doit correspondre au COMPIM dans Proteus
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->open(QIODevice::ReadWrite);

    setupMatiereComboBox();
    // Initialisation des tables avec délégation de couleur
    ui->tableViewDistribution->setModel(m_distProxyModel);
    ui->tableViewPickUp->setModel(m_pickupProxyModel);
    ui->tableViewDistribution->setItemDelegate(new ColorDelegate(this));
    ui->tableViewPickUp->setItemDelegate(new ColorDelegate(this));

    // Désactiver l'alternance des couleurs par défaut
    ui->tableViewDistribution->setAlternatingRowColors(false);
    ui->tableViewPickUp->setAlternatingRowColors(false);

    // Configuration du timer pour les mises à jour en temps réel
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateTimers);
    m_timer->start(1000); // Mise à jour chaque seconde

    // Valeurs par défaut pour les champs
    ui->dateTimeEditDebut->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEditFin->setDateTime(QDateTime::currentDateTime().addDays(1));
    ui->dateTimeEditDeadline->setDateTime(QDateTime::currentDateTime().addDays(1));
    ui->comboBoxEtat->setCurrentText("pas encore");
    m_notificationTimer = new QTimer(this);
    connect(m_notificationTimer, &QTimer::timeout, this, &MainWindow::verifierRetards);
    m_notificationTimer->start(1000);

    // Premier chargement des données
    loadInitialData();
    ui->tableViewPickUp->setItemDelegate(new ColorDelegate(this));

}

void MainWindow::verifierRetards() {
    auto retards = Distribution::getDistributionsEnRetard();

    for(const auto& retard : retards) {
        // Appeler avec les deux paramètres attendus
        afficherNotification(retard.first, retard.second);
    }

    auto retardsPickUp = PickUp::getPickUpsEnRetard();
    for(const auto& retard : retardsPickUp) {
        afficherNotificationPickUp(retard.first, retard.second);
    }
}

void MainWindow::afficherNotificationPickUp(int idDistribution, const QString& matiere)
{
    static QSet<int> notifiedPickUps;

    if (notifiedPickUps.contains(idDistribution))
        return;

    notifiedPickUps.insert(idDistribution);
    if (arduino && arduino->isOpen()) {
        arduino->write("ALERT\n"); // Le '\n' est important pour Serial.readStringUntil()
        arduino->flush();
    }

    QString message = QString("Le pick-up pour la matière %1 (Distribution #%2) est en retard!\n"
                              "La deadline est dépassée.")
                          .arg(matiere)
                          .arg(idDistribution);

    QMessageBox msgBox;
    msgBox.setWindowTitle("ALERTE - Pick-Up en retard");
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

/*void MainWindow::afficherNotification(int idDistribution, const QString& centre)
{
    // Vérifier si on a déjà notifié pour cette distribution
    static QSet<int> notifiedDistributions;

    if (notifiedDistributions.contains(idDistribution))
        return;

    notifiedDistributions.insert(idDistribution);

    QString message = QString("La distribution #%1 pour le centre %2 est en retard!\n"
                              "La date limite est dépassée sans distribution.")
                          .arg(idDistribution)
                          .arg(centre);

    QMessageBox msgBox;
    msgBox.setWindowTitle("ALERTE - Distribution en retard");
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}*/
void MainWindow::loadInitialData()
{
    // Distribution
    Distribution dist(0, 0, "", QDateTime(), QDateTime(), this);
    QSqlQueryModel *distModel = dist.afficher();
    m_distProxyModel->setSourceModel(distModel);
    ui->tableViewDistribution->setModel(m_distProxyModel);
    ui->tableViewDistribution->setItemDelegate(new ColorDelegate(this));


    // Pick-Up
    PickUp pickup(0, "", 0, QDateTime(), this);
    QSqlQueryModel *pickupModel = pickup.afficher();

    // Debug: Vérifier la structure du modèle
    qDebug() << "PickUp Model Column Count:" << pickupModel->columnCount();
    for (int i = 0; i < pickupModel->columnCount(); ++i) {
        qDebug() << "Col" << i << ":" << pickupModel->headerData(i, Qt::Horizontal).toString();
    }

    m_pickupProxyModel->setSourceModel(pickupModel);
    m_pickupProxyModel->setDynamicSortFilter(false);

    // Forcer les en-têtes exacts
    pickupModel->setHeaderData(0, Qt::Horizontal, "ID Distribution");
    pickupModel->setHeaderData(1, Qt::Horizontal, "Matière");
    pickupModel->setHeaderData(2, Qt::Horizontal, "ID Épreuve");
    pickupModel->setHeaderData(3, Qt::Horizontal, "Deadline");
    pickupModel->setHeaderData(4, Qt::Horizontal, "Temps restant");

    ui->tableViewPickUp->setModel(m_pickupProxyModel);

    // Appliquer le délégué une seule fois
    static bool delegateSet = false;
    if (!delegateSet) {
        ui->tableViewPickUp->setItemDelegate(new ColorDelegate(this));
        delegateSet = true;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTimers()
{


        // Timer pour la Distribution sélectionnée
        QModelIndex distIndex = ui->tableViewDistribution->currentIndex();
        if (distIndex.isValid()) {
            QModelIndex sourceIndex = m_distProxyModel->mapToSource(distIndex);
            QSqlQueryModel *distModel = qobject_cast<QSqlQueryModel*>(m_distProxyModel->sourceModel());

            if (distModel) {
                QDateTime fin = distModel->data(distModel->index(sourceIndex.row(), 4)).toDateTime();
                QString etat = distModel->data(distModel->index(sourceIndex.row(), 2)).toString();
                QDateTime now = QDateTime::currentDateTime();

                if (fin.isValid()) {
                    if (now >= fin && etat != "distribuée") {
                        // Afficher notification si le temps est écoulé et pas encore distribué
                        QString centre = distModel->data(distModel->index(sourceIndex.row(), 1)).toString();
                        int id = distModel->data(distModel->index(sourceIndex.row(), 0)).toInt();
                        afficherNotification(id, centre);
                    }

                    if (now < fin) {
                        qint64 secs = now.secsTo(fin);
                        ui->labelTimerDistribution->setText(
                            QString("Distribution: %1j %2h %3m %4s")
                                .arg(secs / 86400)
                                .arg((secs % 86400) / 3600)
                                .arg((secs % 3600) / 60)
                                .arg(secs % 60));
                        ui->labelTimerDistribution->setStyleSheet("");
                    } else {
                        ui->labelTimerDistribution->setText("Distribution: Délai dépassé!");
                        ui->labelTimerDistribution->setStyleSheet("color: red;");
                    }
                }
            }
        }
        // ... reste du code pour les pick-ups ...


        QModelIndex pickUpIndex = ui->tableViewPickUp->currentIndex();
        if (pickUpIndex.isValid()) {
            QModelIndex sourceIndex = m_pickupProxyModel->mapToSource(pickUpIndex);
            QSqlQueryModel *pickupModel = qobject_cast<QSqlQueryModel*>(m_pickupProxyModel->sourceModel());

            if (pickupModel) {
                QDateTime deadline = pickupModel->data(pickupModel->index(sourceIndex.row(), 3)).toDateTime();
                QDateTime now = QDateTime::currentDateTime();

                if (deadline.isValid() && now >= deadline) {
                    QString matiere = pickupModel->data(pickupModel->index(sourceIndex.row(), 1)).toString();
                    int idDist = pickupModel->data(pickupModel->index(sourceIndex.row(), 0)).toInt();
                    afficherNotificationPickUp(idDist, matiere);
                }

                QString tempsRestant = pickupModel->data(pickupModel->index(sourceIndex.row(), 4)).toString();
                ui->labelTimerPickUp->setText("Pick-Up: " + tempsRestant);
            }
        }
}
void MainWindow::refreshDistributionTable(){
    // Sauvegarde de l'état actuel
    int scrollPos = ui->tableViewDistribution->verticalScrollBar()->value();
    QModelIndex currentIndex = ui->tableViewDistribution->currentIndex();

    // Désactiver temporairement les mises à jour
    ui->tableViewDistribution->setUpdatesEnabled(false);

    // Création du nouveau modèle
    Distribution dist(0, 0, "", QDateTime(), QDateTime(), this);
    QSqlQueryModel *newModel = dist.afficher();

    if (newModel->lastError().isValid()) {
        qDebug() << "Erreur Distribution:" << newModel->lastError();
        QMessageBox::critical(this, "Erreur", "Impossible de rafraîchir les distributions");
        delete newModel;
        ui->tableViewDistribution->setUpdatesEnabled(true);
        return;
    }

    // Remplacer le modèle source
    QSqlQueryModel *oldModel = qobject_cast<QSqlQueryModel*>(m_distProxyModel->sourceModel());
    m_distProxyModel->setSourceModel(newModel);
    if (oldModel) oldModel->deleteLater();

    // Restaurer l'état
    if (currentIndex.isValid() && currentIndex.row() < newModel->rowCount()) {
        ui->tableViewDistribution->setCurrentIndex(m_distProxyModel->index(currentIndex.row(), 0));
    }
    ui->tableViewDistribution->verticalScrollBar()->setValue(scrollPos);

    // Réactiver les mises à jour et ajuster les colonnes
    ui->tableViewDistribution->setUpdatesEnabled(true);
    ui->tableViewDistribution->resizeColumnsToContents();
}


void MainWindow::refreshPickUpTable()
{
    PickUp pickup(0, "", 0, QDateTime(), this);
    QSqlQueryModel *newModel = pickup.afficher();

    if(newModel->lastError().isValid()) {
        qDebug() << "Erreur rafraîchissement pick-up:" << newModel->lastError();
        return;
    }

    // Sauvegarde de la sélection et position de défilement
    QModelIndex currentIndex = ui->tableViewPickUp->currentIndex();
    int scrollPos = ui->tableViewPickUp->verticalScrollBar()->value();

    // Remplacement du modèle
    QSqlQueryModel *oldModel = qobject_cast<QSqlQueryModel*>(m_pickupProxyModel->sourceModel());
    m_pickupProxyModel->setSourceModel(newModel);
    if(oldModel) oldModel->deleteLater();

    // Restauration de la sélection
    if(currentIndex.isValid()) {
        QModelIndex newIndex = m_pickupProxyModel->mapFromSource(
            newModel->index(currentIndex.row(), currentIndex.column()));
        ui->tableViewPickUp->setCurrentIndex(newIndex);
    }
    ui->tableViewPickUp->verticalScrollBar()->setValue(scrollPos);
    ui->tableViewPickUp->resizeColumnsToContents();
}
bool MainWindow::validateEtat(const QString& etat) const
{
    return Distribution::etatValide(etat);
}

void MainWindow::setupMatiereComboBox()
{
    ui->comboBoxMatiere->clear();
    ui->comboBoxMatiere->addItem("Arabe");
    ui->comboBoxMatiere->addItem("Français");
    ui->comboBoxMatiere->addItem("Anglais");
    ui->comboBoxMatiere->addItem("Mathématiques");
    ui->comboBoxMatiere->addItem("Physique");
    ui->comboBoxMatiere->addItem("SVT");
    ui->comboBoxMatiere->setCurrentIndex(0); // Sélection par défaut
}

void MainWindow::on_pushButtonCreateDistribution_clicked()
{
    int id = ui->lineEditIdDistribution->text().toInt();
    int idCentre = ui->lineEditIdCentreRegional->text().toInt();
    QString etat = ui->comboBoxEtat->currentText();
    QDateTime debut = ui->dateTimeEditDebut->dateTime();
    QDateTime fin = ui->dateTimeEditFin->dateTime();

    // Validation
    if(id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID Distribution doit être positif");
        return;
    }
    if(idCentre <= 0) {
        QMessageBox::warning(this, "Erreur", "ID Centre doit être positif");
        return;
    }
    if(!validateEtat(etat)) {
        QMessageBox::warning(this, "Erreur", "État invalide");
        return;
    }
    if(debut >= fin) {
        QMessageBox::warning(this, "Erreur", "Date fin doit être après date début");
        return;
    }

    Distribution dist(id, idCentre, etat, debut, fin, this);
    if(!dist.ajouter()) {
        QMessageBox::critical(this, "Erreur", "Échec création distribution:\n" + dist.getLastError());
        return;
    }

    QMessageBox::information(this, "Succès", "Distribution créée avec succès");
    refreshDistributionTable();
}


void MainWindow::on_pushButtonUpdateDistribution_clicked()
{
    int id = ui->lineEditIdDistribution->text().toInt();
    QString etat = ui->comboBoxEtat->currentText();
    QDateTime debut = ui->dateTimeEditDebut->dateTime();
    QDateTime fin = ui->dateTimeEditFin->dateTime();

    if (id <= 0 || !validateEtat(etat) || !debut.isValid() || !fin.isValid() || debut >= fin) {
        QMessageBox::warning(this, "Erreur",
                             "Veuillez spécifier des valeurs valides\n"
                             "La date de début doit être avant la date de fin");
        return;
    }

    Distribution dist(id, 0, etat, debut, fin, this);
    if (dist.mettreAJour(id, etat, debut, fin)) {
        QMessageBox::information(this, "Succès", "Distribution mise à jour avec succès");
        refreshDistributionTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la mise à jour");
    }
}

void MainWindow::on_pushButtonDeleteDistribution_clicked()
{
    int id = ui->lineEditIdDistribution->text().toInt();

    if (id <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez spécifier un ID valide");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cette distribution?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Distribution dist(0, 0, "", QDateTime(), QDateTime(), this);
        if (dist.supprimer(id)) {
            QMessageBox::information(this, "Succès", "Distribution supprimée avec succès");
            refreshDistributionTable();
            // Réinitialisation du formulaire
            ui->lineEditIdDistribution->clear();
            ui->dateTimeEditDebut->setDateTime(QDateTime::currentDateTime());
            ui->dateTimeEditFin->setDateTime(QDateTime::currentDateTime().addDays(1));
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression");
        }
    }
}

void MainWindow::on_pushButtonCreatePickUp_clicked()
{
    int idDistribution = ui->lineEditIdDistributionPickUp->text().toInt();
    QString matiere = ui->comboBoxMatiere->currentText(); // Changé ici
    int idEpreuve = ui->lineEditIdEpreuvePickUp->text().toInt();
    QDateTime deadline = ui->dateTimeEditDeadline->dateTime();

    // Validation
    if(idDistribution <= 0) {
        QMessageBox::warning(this, "Erreur", "ID Distribution doit être positif");
        return;
    }
    if(matiere.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "La matière ne peut pas être vide");
        return;
    }
    if(idEpreuve <= 0) {
        QMessageBox::warning(this, "Erreur", "ID Épreuve doit être positif");
        return;
    }
    if(!deadline.isValid() || deadline < QDateTime::currentDateTime()) {
        QMessageBox::warning(this, "Erreur", "Deadline invalide");
        return;
    }

    PickUp pickup(idDistribution, matiere, idEpreuve, deadline, this);
    if(!pickup.ajouter()) {
        QMessageBox::critical(this, "Erreur", "Échec création pick-up:\n" + pickup.getLastError());
        return;
    }

    QMessageBox::information(this, "Succès", "Pick-up créé avec succès");
    refreshPickUpTable();
    resetPickUpForm();
}

void MainWindow::on_pushButtonUpdatePickUp_clicked()
{
    int idDistribution = ui->lineEditIdDistributionPickUp->text().toInt();
    QString matiere = ui->comboBoxMatiere->currentText(); // Changé ici
    int idEpreuve = ui->lineEditIdEpreuvePickUp->text().toInt();
    QDateTime deadline = ui->dateTimeEditDeadline->dateTime();

    // Validation identique à la création
    if(idDistribution <= 0 || matiere.isEmpty() || idEpreuve <= 0 || !deadline.isValid()) {
        QMessageBox::warning(this, "Erreur", "Données invalides");
        return;
    }

    PickUp pickup(0, "", 0, QDateTime(), this);
    if(!pickup.mettreAJour(idDistribution, matiere, idEpreuve, deadline)) {
        QMessageBox::critical(this, "Erreur", "Échec mise à jour:\n" + pickup.getLastError());
        return;
    }

    QMessageBox::information(this, "Succès", "Pick-up mis à jour");
    refreshPickUpTable();
}


void MainWindow::on_pushButtonDeletePickUp_clicked()
{
    int idDistribution = ui->lineEditIdDistributionPickUp->text().toInt();
    int idEpreuve = ui->lineEditIdEpreuvePickUp->text().toInt();

    if(idDistribution <= 0 || idEpreuve <= 0) {
        QMessageBox::warning(this, "Erreur", "IDs invalides");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
                                                              "Voulez-vous vraiment supprimer ce pick-up?",
                                                              QMessageBox::Yes|QMessageBox::No);

    if(reply != QMessageBox::Yes) return;

    PickUp pickup(0, "", 0, QDateTime(), this);
    if(!pickup.supprimer(idDistribution, idEpreuve)) {
        QMessageBox::critical(this, "Erreur", "Échec suppression:\n" + pickup.getLastError());
        return;
    }

    QMessageBox::information(this, "Succès", "Pick-up supprimé");
    refreshPickUpTable();
    resetPickUpForm();
}

void MainWindow::resetPickUpForm()
{
    ui->lineEditIdDistributionPickUp->clear();
    ui->comboBoxMatiere->setCurrentIndex(0); // Réinitialisation
    ui->lineEditIdEpreuvePickUp->clear();
    ui->dateTimeEditDeadline->setDateTime(QDateTime::currentDateTime().addDays(1));
}


void MainWindow::exportToPdf(QAbstractItemModel* model, const QString& title, const QString& fileName) {
    // Demander à l'utilisateur où sauvegarder le fichier
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Enregistrer le PDF",
                                                    QDir::homePath() + "/" + fileName,
                                                    "Fichiers PDF (*.pdf)");
    if (filePath.isEmpty()) return;

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(filePath);

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'écrire dans le fichier");
        return;
    }

    // Création du document HTML
    QString html;
    html += "<html><body>";
    html += "<h1 align='center'>" + title + "</h1>";
    html += "<table border='1' cellspacing='0' cellpadding='5' width='100%'>";

    // En-têtes
    html += "<tr>";
    for (int col = 0; col < model->columnCount(); ++col) {
        html += "<th>" + model->headerData(col, Qt::Horizontal).toString() + "</th>";
    }
    html += "</tr>";

    // Données
    for (int row = 0; row < model->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            html += "<td>" + model->index(row, col).data().toString() + "</td>";
        }
        html += "</tr>";
    }

    html += "</table>";
    html += "<p align='right'>Généré le " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm") + "</p>";
    html += "</body></html>";

    // Utilisation de QTextDocument pour un meilleur rendu
    QTextDocument document;
    document.setHtml(html);
    document.drawContents(&painter);

    painter.end();

    QMessageBox::information(this, "Succès", "Export PDF terminé avec succès");
}
void MainWindow::on_pushButtonExportDistribution_clicked() {
    exportToPdf(m_distProxyModel->sourceModel(), "Liste des Distributions", "distributions.pdf");
}

void MainWindow::on_pushButtonExportPickUp_clicked() {
    exportToPdf(m_pickupProxyModel->sourceModel(), "Liste des Pick-Ups", "pickups.pdf");
}

void MainWindow::setupArduino() {
    arduino = new QSerialPort(this);
    arduino->setPortName("COM3"); // Même port que COMPIM
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);

    if (!arduino->open(QIODevice::ReadWrite)) {
        qDebug() << "Erreur : Port COM3 inaccessible";
    }
}

// Modifiez la fonction afficherNotification pour déclencher le buzzer
void MainWindow::afficherNotification(int idDistribution, const QString& centre) {
    static QSet<int> notifiedDistributions;

    if (notifiedDistributions.contains(idDistribution))
        return;

    notifiedDistributions.insert(idDistribution);

    // Envoyer la commande à Arduino
    if (arduino && arduino->isOpen()) {
        qDebug() << "Envoi de ALERT à l'Arduino";
        arduino->write("ALERT\n");
        arduino->flush();
    }
    QString message = QString("La distribution #%1 pour le centre %2 est en retard!\n"
                              "La date limite est dépassée sans distribution.")
                          .arg(idDistribution)
                          .arg(centre);

    QMessageBox msgBox;
    msgBox.setWindowTitle("ALERTE - Distribution en retard");
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}
