#ifndef INTERVALSLIDER_H
#define INTERVALSLIDER_H

#include "controlelement.h"
#include <QSlider>
#include <QLabel>

class RangeSliderHandle;

class RangeSlider: public QSlider
{
  Q_OBJECT
public:
  /** Constructor */
  RangeSlider(QWidget *parent = 0);

  /** Store the alternate handle for this slider*/
  RangeSliderHandle *alt_handle;

  /** Overridden mouse release event */
  void mouseReleaseEvent(QMouseEvent *event);

  /** Returns the slider value for the alternate handle */
  int alt_value();

  /** Convenience function for setting the value of the alternate handle */
  void alt_setValue(int value);

  /** Resets the alternate handle to the right side of the slider */
  void Reset();

  /** Used to update the position of the alternate handle through the use of an event filter */
  void alt_update();
signals:
  /** Constructor */
  void alt_valueChanged(int);
};

class RangeEventFilter : public QObject
{
public:
  RangeEventFilter(RangeSlider *_grandParent)
  {grandParent = _grandParent;};

protected:
  /*
  * overloaded functions for object that inherit from this class
  */
  bool eventFilter(QObject* obj, QEvent* event);

private:
  /** Store the SuperSlider that this event filter is used within. */
  RangeSlider *grandParent;
};

class RangeSliderHandle: public QLabel
{
  Q_OBJECT
public:
  RangeSliderHandle(RangeSlider *parent = 0);

  /** An overloaded mousePressevent so that we can start grabbing the cursor and using it's position for the value */
  void mousePressEvent(QMouseEvent *event);

  /** Returns the value of this handle with respect to the slider */
  int value();

  /** Maps mouse coordinates to slider values */
  int mapValue();

  /** Store the parent as a slider so that you don't have to keep casting it  */
  RangeSlider *parent;

  /** Store a bool to determine if the alternate handle has been activated  */
  bool handleActivated;

private:
  /** Store the filter for installation on the qguiapp */
  RangeEventFilter *filter;

  public slots:
    /** Sets the value of the handle with respect to the slider */
    void setValue(double value);
};

class IntervalSlider : public ControlElement
{
public:
    IntervalSlider(QWidget *parent,const QString labeltext);
    ~IntervalSlider();
    virtual bool init(QSqlQuery* query);
    virtual void init();
    virtual void reset();
private:
    RangeSlider *slider;
};

#endif // INTERVALSLIDER_H
