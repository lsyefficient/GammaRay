/*
  toolfactory.h

  This file is part of Endoscope, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2010-2011 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ENDOSCOPE_TOOLFACTORY_H
#define ENDOSCOPE_TOOLFACTORY_H

#include <QtPlugin>
#include <QtCore/QStringList>
#include <QMetaType>

namespace Endoscope {

class ProbeInterface;

/**
 * Abstract interface for probe tools.
 */
class ToolFactory
{
  public:
    virtual inline ~ToolFactory() {}

    /** Human readable name of this tool. */
    virtual QString name() const = 0;

    /**
     * Class names of types this tool can handle.
     * The tool will only be activated if an object of one of these types is seen in the probed application.
     */
    virtual QStringList supportedTypes() const = 0;

    /**
     * Create an instance of this tool.
     * @param probeIface The probe interface allowing access to the object models.
     * @param parentWidget The parent widget for the visual elements of this tool.
     */
    virtual QWidget* createInstance( ProbeInterface *probeIface, QWidget *parentWidget ) = 0;
};

template <typename Type, typename Tool>
class StandardToolFactory : public ToolFactory
{
  public:
    virtual inline QStringList supportedTypes() const { return QStringList( Type::staticMetaObject.className() ); }
    virtual inline QWidget* createInstance( ProbeInterface *probe, QWidget *parentWidget ) { return new Tool( probe, parentWidget ); }
};

}

Q_DECLARE_INTERFACE(Endoscope::ToolFactory, "com.kdab.Endoscope.ToolFactory/1.0")
Q_DECLARE_METATYPE(Endoscope::ToolFactory*)

#endif
