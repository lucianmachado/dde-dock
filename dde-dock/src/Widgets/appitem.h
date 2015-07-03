#ifndef APPITEM_H
#define APPITEM_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QDrag>
#include <QRectF>
#include <QDrag>
#include <QMimeData>
#include <QPixmap>
#include <QImage>
#include <QList>
#include <QMap>
#include <QDebug>
#include "DBus/dbusentryproxyer.h"
#include "DBus/dbusclientmanager.h"
#include "Controller/dockmodedata.h"
#include "abstractdockitem.h"
#include "appicon.h"
#include "appbackground.h"

struct AppItemData {
    QString id;
    QString iconPath;
    QString title;
    QString xidsJsonString;
    QString menuJsonString;
    bool isActived;
    bool currentOpened;
    bool isDocked;
};

class AppItem : public AbstractDockItem
{
    Q_OBJECT
    Q_PROPERTY(QPoint pos READ pos WRITE move)
public:
    AppItem(QWidget *parent = 0);
    ~AppItem();

    void setEntryProxyer(DBusEntryProxyer *entryProxyer);
    void destroyItem(const QString &id);
    QString itemId() const;
    AppItemData itemData() const;

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent * event);
    void leaveEvent(QEvent * event);
    void dragEnterEvent(QDragEnterEvent * event);
    void dragLeaveEvent(QDragLeaveEvent * event);
    void dropEvent(QDropEvent * event);

private slots:
    void slotDockModeChanged(DockConstants::DockMode newMode,DockConstants::DockMode oldMode);
    void reanchorIcon();
    void resizeBackground();
    void dbusDataChanged(const QString &key, const QString &value);
    void setCurrentOpened(uint);

private:
    void resizeResources();
    void initBackground();
    void initClientManager();
    void setActived(bool value);

    void initData();
    void updateIcon();
    void updateTitle();
    void updateState();
    void updateXids();
    void updateMenuJsonString();

private:
    AppItemData m_itemData;
    DockModeData *dockCons = DockModeData::getInstants();
    DBusEntryProxyer *m_entryProxyer = NULL;
    DBusClientManager *m_clientmanager = NULL;
    AppBackground * appBackground = NULL;
    AppIcon * m_appIcon = NULL;

};

#endif // APPITEM_H
