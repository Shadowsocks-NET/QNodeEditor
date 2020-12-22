#pragma once

#include "MathOperationDataModel.hpp"

class AdditionModel : public MathOperationDataModel
{
public:

  QString
  caption() const override
  { return QStringLiteral("Addition"); }

  QString
  name() const override
  { return QStringLiteral("Addition"); }

private:

  void
  compute() override;
};
