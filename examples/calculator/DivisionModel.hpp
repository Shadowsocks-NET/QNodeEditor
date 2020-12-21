#pragma once

#include "MathOperationDataModel.hpp"

class DivisionModel : public MathOperationDataModel
{
public:

  QString
  caption() const override
  { return QStringLiteral("Division"); }

  QString
  portCaption(PortType portType, PortIndex portIndex) const override;

  QString
  name() const override
  { return QStringLiteral("Division"); }

private:

  void
  compute() override;
};
