#include "mapruler.h"

#include "maplayer.h"
#include "objects/maplineobject.h"
#include "objects/maptextobject.h"

using namespace Map2;

MapRuler::MapRuler(Map2::MapLayer *layer)
{
	pLine = new MapLineObject("", QList<Coord>(), layer);
	pText = new MapTextObject("", Coord(), 4, QColor(Qt::black), layer);
}

MapRuler::~MapRuler()
{
	pLine->mapLayer()->removeObject( pLine );
	pText->mapLayer()->removeObject( pText );
}

void MapRuler::clear()
{
	pLine->clear();
	pText->setText("");
}

void MapRuler::addPoint(const Map2::CoordPlane &coord)
{
	pLine->addPoint(coord);
	pText->setCoordinatePlane(coord);
	pText->setText( pLine->lengthText() );
}

double MapRuler::length() const
{
	return pLine->length();
}

QString MapRuler::lengthText() const
{
	return pLine->lengthText();
}
