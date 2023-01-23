//
// Copyright (c) 2009, Jim Hourihan
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0 
// 
#ifndef __MuQt5__QHBoxLayoutType__h__
#define __MuQt5__QHBoxLayoutType__h__
#include <iostream>
#include <Mu/Class.h>
#include <Mu/MuProcess.h>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include <QtNetwork/QtNetwork>
#include <QtWebEngine/QtWebEngine>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QtQml/QtQml>
#include <QtQuick/QtQuick>
#include <QtQuickWidgets/QtQuickWidgets>
#include <QtSvg/QtSvg>
#include <MuQt5/Bridge.h>

namespace Mu {
class MuQt_QHBoxLayout;

//
//  NOTE: file generated by qt2mu.py
//

class QHBoxLayoutType : public Class
{
  public:

    typedef MuQt_QHBoxLayout MuQtType;
    typedef QHBoxLayout QtType;

    //
    //  Constructors
    //

    QHBoxLayoutType(Context* context, 
           const char* name,
           Class* superClass = 0,
           Class* superClass2 = 0);

    virtual ~QHBoxLayoutType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[13];
};

// Inheritable object

class MuQt_QHBoxLayout : public QHBoxLayout
{
  public:
    virtual ~MuQt_QHBoxLayout();
    MuQt_QHBoxLayout(Pointer muobj, const CallEnvironment*) ;
    MuQt_QHBoxLayout(Pointer muobj, const CallEnvironment*, QWidget * parent) ;
    virtual void addItem(QLayoutItem * item) ;
    virtual int count() const;
    virtual Qt::Orientations expandingDirections() const;
    virtual bool hasHeightForWidth() const;
    virtual int heightForWidth(int w) const;
    virtual void invalidate() ;
    virtual QLayoutItem * itemAt(int index) const;
    virtual QSize maximumSize() const;
    virtual int minimumHeightForWidth(int w) const;
    virtual QSize minimumSize() const;
    virtual void setGeometry(const QRect & r) ;
    virtual QSize sizeHint() const;
    virtual QLayoutItem * takeAt(int index) ;
  public:
    const QHBoxLayoutType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QHBoxLayoutType::cachedInstance(const QHBoxLayoutType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QHBoxLayoutType__h__