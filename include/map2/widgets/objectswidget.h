#ifndef OBJECTSWIDGET
#define OBJECTSWIDGET

#include <QSet>
#include <QWidget>
#include <QIdentityProxyModel>

#include "map2/mapstructs.h"

class QTableView;
class QPushButton;
class QLabel;

namespace Map2
{
class MapLayer;
class MapObject;
class HiddenTextProxyModel;

class ObjectsWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ObjectsWidget(QWidget *parent = 0);
	~ObjectsWidget();

public slots:
	void setMapLayer(Map2::MapLayer *layer);

signals:
	void objectEditRequest(Map2::MapObject *obj);
	void objectAddRequest(Map2::Coord coordinate);

private slots:
	void onAdd();
	void onRemove();
	void onEdit();
	void onObjectClicked(const QModelIndex &index);
	void onObjectDoubleClicked(const QModelIndex &index);

private:
	MapLayer *pLayerModel;
	HiddenTextProxyModel *pProxyModel;

	QTableView *pTableView;
	QPushButton *pbAdd;
	QPushButton *pbRemove;
	QPushButton *pbEdit;
	QLabel *pTitle;
};

class HiddenTextProxyModel : public QIdentityProxyModel
{
	Q_OBJECT
public:
	explicit HiddenTextProxyModel(QObject *parent = 0) : QIdentityProxyModel(parent){}
	~HiddenTextProxyModel(){}

	void setColumnTextHidden(int col, bool hidden = true);
	void showAllText();

	virtual QVariant data(const QModelIndex &proxyIndex, int role) const;

private:
	QSet<int> mHiddenTextCols;
};

}
#endif // OBJECTSWIDGET

