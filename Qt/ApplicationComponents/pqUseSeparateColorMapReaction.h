/*=========================================================================

   Program: ParaView
   Module:    pqUseSeparateColorMapReaction.h

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2.

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/
#ifndef pqUseSeparateColorMapReaction_h
#define pqUseSeparateColorMapReaction_h

#include "pqPropertyLinks.h" // For Links
#include "pqReaction.h"
#include <QPointer>

class pqDataRepresentation;
class pqDisplayColorWidget;

/**
 * @ingroup Reactions
 * Reaction to toggle the use of separated color map for an array in a representation
 */
class PQAPPLICATIONCOMPONENTS_EXPORT pqUseSeparateColorMapReaction : public pqReaction
{
  Q_OBJECT
  typedef pqReaction Superclass;

public:
  /**
   * if \c track_active_objects is false, then the reaction will not track
   * pqActiveObjects automatically.
   * colorWidget is used to force a representation update
   */
  pqUseSeparateColorMapReaction(
    QAction* parent, pqDisplayColorWidget* colorWidget, bool track_active_objects = true);
  ~pqUseSeparateColorMapReaction() override;

  /**
   * Returns the representation currently being used by the reaction.
   */
  pqDataRepresentation* representation() const;

public Q_SLOTS: // NOLINT(readability-redundant-access-specifiers)
  /**
   * Set the active representation.
   */
  void setRepresentation(pqDataRepresentation*);

protected Q_SLOTS:
  /**
   * Updates the enabled state. Applications need not explicitly call this.
   */
  void updateEnableState() override;

  /**
   * Called when the action is triggered.
   */
  void onTriggered() override;

private:
  Q_DISABLE_COPY(pqUseSeparateColorMapReaction)

  pqPropertyLinks Links;
  QPointer<pqDataRepresentation> CachedRepresentation;
  pqDisplayColorWidget* ColorWidget;
  bool TrackActiveObjects;
  bool BlockSignals;
};

#endif
