#pragma once

#include <QtWidgets/QLineEdit>

#include <nodes/NodeDataModel>

#include "TextData.hpp"

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class TextSourceDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  TextSourceDataModel();

public:

  QString
  caption() const override
  { return QString("Text Source"); }

  bool
  captionVisible() const override
  { return false; }

  static QString
  Name()
  { return QString("TextSourceDataModel"); }

  QString
  name() const override
  { return TextSourceDataModel::Name(); }

public:

  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData>, int) override
  {}

  QWidget *
  embeddedWidget() override;

private Q_SLOTS:

  void
  onTextEdited(QString const &string);

private:
  QString _text;
  QLineEdit * _lineEdit;
};
