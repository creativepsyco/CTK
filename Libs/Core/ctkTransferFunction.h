/*=========================================================================

  Library:   ctk

  Copyright (c) Kitware Inc. 
  All rights reserved.
  Distributed under a BSD License. See LICENSE.txt file.

  This software is distributed "AS IS" WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the above copyright notice for more information.

=========================================================================*/

#ifndef __ctkTransferFunction_h
#define __ctkTransferFunction_h

/// Qt includes
#include <QObject>
#include <QtGlobal>
#include <QSharedPointer>
#include <QVariant>

/// CTK includes
#include "CTKCoreExport.h"

/// assumes the mapping is linear by default, if not, then subclasses must be 
/// used
//-----------------------------------------------------------------------------
struct ctkControlPoint
{
  virtual ~ctkControlPoint(){}
  // QColor or qreal.
  QVariant Value;
  qreal    Pos;
};

//-----------------------------------------------------------------------------
struct ctkBezierControlPoint : public ctkControlPoint
{
  qreal P1;
  QVariant ValueP1;
  qreal P2;
  QVariant ValueP2;
};

//-----------------------------------------------------------------------------
class CTK_CORE_EXPORT ctkTransferFunction: public QObject
{
  Q_OBJECT
public:
  ctkTransferFunction(QObject* parent = 0);
  virtual ~ctkTransferFunction();
  
  virtual ctkControlPoint* controlPoint(int index)const =0;
  inline QVariant value(int index)const;
  virtual QVariant value(qreal pos)const =0;
  
  virtual int count()const = 0;
  inline void range(qreal rangeValues[2])const;
  virtual void range(qreal& minRange, qreal& maxRange)const=0;
  virtual QVariant minValue()const = 0;
  virtual QVariant maxValue()const = 0;
  ///
  virtual int insertControlPoint(const ctkControlPoint& cp) = 0;

  /// 
  /// be careful with it, as changing the value might require
  /// more changes to ctkControlPoint.
  virtual void setControlPointPos(int index, qreal pos)=0;
  /// 
  /// be careful with it, as changing the value might require
  /// more changes to ctkControlPoint.
  virtual void setControlPointValue(int index, const QVariant& value)=0;

signals:
  void changed();
};

//-----------------------------------------------------------------------------
QVariant ctkTransferFunction::value(int index)const
{
  QSharedPointer<ctkControlPoint> cp(this->controlPoint(index));
  return cp->Value;
}

//-----------------------------------------------------------------------------
void ctkTransferFunction::range(qreal rangeValues[2])const
{
  this->range(rangeValues[0], rangeValues[1]);
}

#endif