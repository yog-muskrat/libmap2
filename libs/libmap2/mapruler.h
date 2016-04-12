#ifndef MAPRULER_H
#define MAPRULER_H

#include "mapstructs.h"

namespace Map2
{

class MapLayer;
class MapLineObject;
class MapTextObject;

class MapRuler
{
public:
	explicit MapRuler(Map2::MapLayer *layer);
	~MapRuler();

	void clear();
	void addPoint(const Map2::CoordPlane &coord);

	void hide() { setVisible(false); }
	void show() { setVisible(true); }
	void setVisible(bool visible);
	bool isVisible() const;

	double length() const;
	QString lengthText() const;

private:
	MapLineObject *pLine;
	MapTextObject *pText;
	bool mVisible;
};
}
#endif // MAPRULER_H
