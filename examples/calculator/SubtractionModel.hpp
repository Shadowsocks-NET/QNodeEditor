#pragma once

#include "MathOperationDataModel.hpp"

class SubtractionModel : public MathOperationDataModel
{
public:

  QString
  caption() const override
  { return QStringLiteral("Subtraction"); }

  virtual bool
  portCaptionVisible(PortType, PortIndex) const override
  { return true; }

  virtual QString
  portCaption(PortType portType, PortIndex portIndex) const override;

  QString
  name() const override
  { return QStringLiteral("Subtraction"); }

private:

  void
  compute() override;
};
