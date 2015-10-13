#ifndef MAPRULER_H
#define MAPRULER_H

#include "structs.h"

class MapLayer;
class MapLineObject;
class MapTextObject;

class MapRuler
{
public:
	MapRuler(MapLayer *layer);
	~MapRuler();

	void clear();
	void addPoint(const CoordPlane &coord);

	double length() const;
	QString lengthText() const;

private:
	MapLineObject *pLine;
	MapTextObject *pText;
};

#endif // MAPRULER_H
