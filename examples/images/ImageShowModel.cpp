#include "ImageShowModel.hpp"

#include <QtCore/QEvent>
#include <QtCore/QDir>

#include <QtWidgets/QFileDialog>

#include <nodes/DataModelRegistry>

#include "PixmapData.hpp"

ImageShowModel::
ImageShowModel()
  : _label(nullptr)
{
}

unsigned int
ImageShowModel::
nPorts(PortType) const
{
  return 1;
}


bool
ImageShowModel::
eventFilter(QObject *object, QEvent *event)
{
  if (object == _label)
  {
    int w = _label->width();
    int h = _label->height();

    if (event->type() == QEvent::Resize)
    {
      auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);
      if (d)
      {
        Q_EMIT updateLabel(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
      }
    }
  }

  return false;
}


NodeDataType
ImageShowModel::
dataType(PortType, PortIndex) const
{
  return PixmapData().type();
}


std::shared_ptr<NodeData>
ImageShowModel::
outData(PortIndex)
{
  return _nodeData;
}


void
ImageShowModel::
setInData(std::shared_ptr<NodeData> nodeData, PortIndex)
{
  _nodeData = nodeData;

  if (_nodeData)
  {
    auto d = std::dynamic_pointer_cast<PixmapData>(_nodeData);

    int w = _label->width();
    int h = _label->height();

    Q_EMIT updateLabel(d->pixmap().scaled(w, h, Qt::KeepAspectRatio));
  }
  else
  {
    Q_EMIT updateLabel(QPixmap());
  }

  Q_EMIT dataUpdated(0);
}

QWidget* ImageShowModel::embeddedWidget()
{
   if(!_label)
   {
      _label = new QLabel("Image will appear here");
      _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

      QFont f = _label->font();
      f.setBold(true);
      f.setItalic(true);

      _label->setFont(f);
      _label->setFixedSize(200, 200);
      _label->installEventFilter(this);

      connect(this, &ImageShowModel::updateLabel,
              _label, [this](const QPixmap& pix){
                _label->setPixmap(pix);
              });
   }
   return _label;
}
