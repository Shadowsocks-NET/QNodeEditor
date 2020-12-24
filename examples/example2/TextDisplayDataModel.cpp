#include "TextDisplayDataModel.hpp"

TextDisplayDataModel::
TextDisplayDataModel()
  : _label(new QLabel("Resulting Text"))
{
  _label->setMargin(3);
}


TextDisplayDataModel::
~TextDisplayDataModel()
{
  if(_label && !_label->parent()){
    _label->deleteLater();
  }
}


unsigned int
TextDisplayDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 1;
      break;

    case PortType::Out:
      result = 0;

    default:
      break;
  }

  return result;
}


NodeDataType
TextDisplayDataModel::
dataType(PortType, PortIndex) const
{
  return TextData().type();
}


std::shared_ptr<NodeData>
TextDisplayDataModel::
outData(PortIndex)
{
  std::shared_ptr<NodeData> ptr;
  return ptr;
}

void TextDisplayDataModel::setInData(std::shared_ptr<QtNodes::NodeData> data, int)
{
  auto textData = std::dynamic_pointer_cast<TextData>(data);

  if (textData)
  {
    _label->setText(textData->text());
  }
  else
  {
    _label->clear();
  }

  _label->adjustSize();
}
