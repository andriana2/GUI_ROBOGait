#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H
#include <QObject>
#include <QStringListModel>
#include <vector>
#include <string>
#include <QQmlContext>


class StringHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringListModel* model READ model NOTIFY modelChanged)

public:
    explicit StringHandler(QObject *parent = nullptr) : QObject(parent), m_model(new QStringListModel(this)) {}

    QStringListModel *model() const{
        return m_model;
    }

    Q_INVOKABLE void loadData() {
        QStringList list;
        const std::vector<std::string> data = {"Mapa 1", "Mapa 2", "Mapa 3"};
        for (const std::string &str : data) {
            qDebug() << "Loading: " << QString::fromStdString(str);  // Depuración
            list.append(QString::fromStdString(str));
        }
        m_model->setStringList(list);
        emit modelChanged();  // Notificar a QML
    }

signals:
    void modelChanged();

private:
    QStringListModel *m_model;
};

#endif // STRINGHANDLER_H
