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

	double length() const;
	QString lengthText() const;

private:
	MapLineObject *pLine;
	MapTextObject *pText;
};
}
#endif // MAPRULER_H
