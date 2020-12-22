#pragma once

#include "MathOperationDataModel.hpp"

class MultiplicationModel : public MathOperationDataModel
{
public:

  QString
  caption() const override
  { return QStringLiteral("Multiplication"); }

  QString
  name() const override
  { return QStringLiteral("Multiplication"); }

private:

  void
  compute() override;
};
