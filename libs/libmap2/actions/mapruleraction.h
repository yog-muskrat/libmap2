#ifndef MAPRULERACTION
#define MAPRULERACTION

#include "actions/mapaction.h"

namespace Map2
{
/*!
 * \brief Класс действия по измерению расстояний
 */
class MapRulerAction : public MapAction
{
public:
	explicit MapRulerAction(Map2::MapView *view);
	~MapRulerAction();

	virtual void setEnabled(const bool enabled);
	virtual Map2::MapToolBar::Tools type() { return MapToolBar::Ruler; }
	virtual bool processMouseClickEvent(QMouseEvent *mouseEvent);
	void clear();

private:
	MapRuler * ruler();

	MapRuler *pRuler;
};
}

#endif // MAPRULERACTION
