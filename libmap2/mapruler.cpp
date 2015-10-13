#include "mapruler.h"

#include "maplayer.h"
#include "maplineobject.h"
#include "maptextobject.h"

MapRuler::MapRuler(MapLayer *layer)
{
	pLine = new MapLineObject(0, layer);
	pText = new MapTextObject(layer);
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

void MapRuler::addPoint(const CoordPlane &coord)
{
	pLine->addPoint(coord);
	pText->setCoordinate(coord);
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
