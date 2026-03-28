#include "colordelegate.h"
#include <QPainter>
#include <QSqlQueryModel>
#include <QApplication>
#include <QDebug>

ColorDelegate::ColorDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QColor backgroundColor = Qt::white;
    QAbstractItemModel *model = const_cast<QAbstractItemModel*>(index.model());
    int colCount = model->columnCount();

    try {
        // Identification du type de tableau
        bool isPickUpTable = false;
        bool isDistributionTable = false;

        // Méthode robuste pour identifier le tableau
        if (model->columnCount() == 5) {
            QString header0 = model->headerData(0, Qt::Horizontal).toString();
            QString header1 = model->headerData(1, Qt::Horizontal).toString();

            if (header0.contains("Distribution", Qt::CaseInsensitive) &&
                header1.contains("Matière", Qt::CaseInsensitive)) {
                isPickUpTable = true;
            }
        }
        else if (model->columnCount() == 6) {
            isDistributionTable = true;
        }

        if (isPickUpTable) {
            // Debug: Afficher la structure du modèle
            qDebug() << "PickUp Table Structure:";
            for (int i = 0; i < model->columnCount(); ++i) {
                qDebug() << "Col" << i << ":" << model->headerData(i, Qt::Horizontal).toString();
            }

            // Trouver la colonne Temps restant dynamiquement
            int tempsRestantCol = -1;
            for (int i = 0; i < model->columnCount(); ++i) {
                QString header = model->headerData(i, Qt::Horizontal).toString();
                if (header.contains("Temps", Qt::CaseInsensitive) ||
                    header.contains("Restant", Qt::CaseInsensitive)) {
                    tempsRestantCol = i;
                    break;
                }
            }

            if (tempsRestantCol >= 0) {
                QString tempsRestant = model->data(model->index(index.row(), tempsRestantCol)).toString();
                qDebug() << "Temps restant value:" << tempsRestant;

                if (tempsRestant.contains("Expire", Qt::CaseInsensitive)) {
                    backgroundColor = QColor(255, 200, 200); // Rouge
                    qDebug() << "Applying RED (expired)";
                }
                else if (tempsRestant.contains("minutes")) {
                    QStringList parts = tempsRestant.split(" ");
                    if (!parts.isEmpty()) {
                        bool ok;
                        int minutes = parts.first().toInt(&ok);
                        if (ok && minutes >0) {
                            backgroundColor = QColor(255, 255, 200); // Jaune
                            qDebug() << "Applying YELLOW (" << minutes << "minutes)";
                        }
                    }
                }
            }
        }
        else if (isDistributionTable) {
            // ... (garder votre code existant pour les distributions)

            if (colCount == 6) { // Distribution table
                QString etat = index.siblingAtColumn(2).data().toString();
                QString tempsRestant = index.siblingAtColumn(5).data().toString();

                if (etat == "distribuee") {
                    backgroundColor = QColor(200, 255, 200); // Vert clair
                } else if (tempsRestant == "En retard") {
                    backgroundColor = QColor(255, 200, 200); // Rouge clair
                } else if (etat == "en cours") {
                    backgroundColor = QColor(255, 255, 200); // Jaune clair
                }
            }
        }
    }
    catch (...) {
        qDebug() << "Error in ColorDelegate";
    }

    painter->fillRect(option.rect, backgroundColor);
    QStyledItemDelegate::paint(painter, option, index);
}



/*
#include "colordelegate.h"
#include <QPainter>
#include <QSqlQueryModel>
#include <QApplication>
#include <QDebug>

ColorDelegate::ColorDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QColor backgroundColor = Qt::white;

    const QAbstractItemModel *model = index.model();
    int colCount = model->columnCount();

    if (colCount == 6) { // Distribution table
        QString etat = index.siblingAtColumn(2).data().toString();
        QString tempsRestant = index.siblingAtColumn(5).data().toString();

        if (etat == "distribuée") {
            backgroundColor = QColor(200, 255, 200); // Vert clair
        } else if (tempsRestant == "En retard") {
            backgroundColor = QColor(255, 200, 200); // Rouge clair
        } else if (etat == "en cours") {
            backgroundColor = QColor(255, 255, 200); // Jaune clair
        }

    } else if (colCount == 5) { // Pick-Up table
        QString tempsRestant = index.siblingAtColumn(4).data().toString();
        qDebug() << "[Pick-Up] Temps restant:" << tempsRestant;

        if (tempsRestant == "Expiré") {
            backgroundColor = QColor(255, 200, 200); // Rouge pour expiré
        } else if (tempsRestant.contains("minutes")) {
            QString minutesStr = tempsRestant.split(" ").first();
            bool ok;
            int minutes = minutesStr.toInt(&ok);
            if (ok && minutes < 10) {
                backgroundColor = QColor(255, 255, 200); // Jaune pour proche expiration
            }
        }
    }

    // Dessiner l'arrière-plan coloré
    painter->fillRect(option.rect, backgroundColor);

    // Dessiner le texte
    QStyledItemDelegate::paint(painter, option, index);
}
*/
