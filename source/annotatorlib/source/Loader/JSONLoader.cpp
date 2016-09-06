// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#define Annotator_AnnotatorLib_Loader_JSONLoader_BODY

/************************************************************
 JSONLoader class body
 ************************************************************/

// include associated header file
#include <AnnotatorLib/Loader/JSONLoader.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

// Derived includes directives

namespace AnnotatorLib {
namespace Loader {

void JSONLoader::setPath(std::string path) { this->path = path; }

StorageType JSONLoader::getType() { return AnnotatorLib::StorageType::JSON; }

void JSONLoader::loadSession(Session *session) {
  QFile file(QString::fromStdString(this->path));
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());

    QJsonObject json = document.object();
    loadAttributes(json, session);
    loadClasses(json, session);
    loadObjects(json, session);
    loadFrames(json, session);
    loadAnnotations(json, session);
    // loadAnnotationsNextPrevious(json, session);
  }
  file.close();
}

void JSONLoader::loadAttributes(QJsonObject &json, Session *session) {
  QJsonArray attributes = json.value("attributes").toArray();
  for (QJsonValue value : attributes) {
    QJsonObject attribute = value.toObject();
    unsigned long id = attribute["id"].toString().toLong();
    QString name = attribute["name"].toString();
    QString type = attribute["type"].toString();

    // TODO: default value
    AnnotatorLib::AttributeType t =
        AnnotatorLib::AttributeTypeFromString(type.toStdString());
    AnnotatorLib::Attribute *a =
        new AnnotatorLib::Attribute(id, t, name.toStdString());
    AnnotatorLib::AttributeValue *av;
    switch (t) {
      case AnnotatorLib::AttributeType::STRING:
        av = new AnnotatorLib::AttributeValue(
            attribute["default"].toString().toStdString());
        break;
      case AnnotatorLib::AttributeType::INTEGER:
        av = new AnnotatorLib::AttributeValue(
            attribute["default"].toString().toLong());
        break;
      case AnnotatorLib::AttributeType::FLOAT:
        av = new AnnotatorLib::AttributeValue(
            attribute["default"].toString().toDouble());
        break;
      case AnnotatorLib::AttributeType::BOOLEAN:
        av = new AnnotatorLib::AttributeValue(attribute["default"].toBool());
        break;
      default:
        av = new AnnotatorLib::AttributeValue(
            attribute["default"].toString().toStdString());
    };
    a->setDefaultValue(av);
    session->addAttribute(a);
  }
}

void JSONLoader::loadClasses(QJsonObject &json, Session *session) {
  QJsonArray classes = json.value("classes").toArray();
  for (QJsonValue value : classes) {
    QJsonObject object = value.toObject();
    unsigned long id = object["id"].toString().toLong();
    QString name = object["name"].toString();
    AnnotatorLib::Class *c = new AnnotatorLib::Class(id, name.toStdString());

    session->addClass(c);
  }
}

void JSONLoader::loadObjects(QJsonObject &json, Session *session) {
  QJsonArray objects = json.value("objects").toArray();
  for (QJsonValue value : objects) {
    QJsonObject object = value.toObject();
    unsigned long id = object["id"].toString().toLong();
    QString name = object["name"].toString();
    AnnotatorLib::Object *o = new AnnotatorLib::Object(id);
    o->setName(name.toStdString());

    if (object.contains("class"))
      o->setClass(session->getClass(name.toStdString()));

    QJsonArray attributes = object.value("attributes").toArray();
    for (QJsonValue attribute : attributes) {
      unsigned long atid = attribute.toString().toLong();
      AnnotatorLib::Attribute *at = session->getAttribute(atid);
      if (at != nullptr) o->addAttribute(at);
    }
    session->addObject(o);
  }
}

void JSONLoader::loadFrames(QJsonObject &json, Session *session) {
  QJsonArray frames = json.value("frames").toArray();
  for (QJsonValue value : frames) {
    QJsonObject frame = value.toObject();
    unsigned long nmb = frame["number"].toString().toLong();
    AnnotatorLib::Frame *f = new AnnotatorLib::Frame(nmb);
    session->addFrame(f);
  }
}

void JSONLoader::loadAnnotations(QJsonObject &json, Session *session) {
  QJsonArray annotations = json.value("annotations").toArray();
  for (QJsonValue value : annotations) {
    QJsonObject annotation = value.toObject();
    unsigned long id = annotation["id"].toString().toLong();
    unsigned long object = annotation["object"].toString().toLong();
    unsigned long frame = annotation["frame"].toString().toLong();

    float x = annotation["x"].toString().toFloat();
    float y = annotation["y"].toString().toFloat();
    float width = annotation["width"].toString().toFloat();
    float height = annotation["height"].toString().toFloat();
    AnnotatorLib::AnnotationType type = AnnotatorLib::AnnotationTypeFromString(
        annotation["type"].toString().toStdString());

    AnnotatorLib::Object *o = session->getObject(object);
    AnnotatorLib::Frame *f = session->getFrame(frame);

    if (o != nullptr && f != nullptr) {
      AnnotatorLib::Annotation *a =
          new AnnotatorLib::Annotation(id, f, o, type);
      a->setPosition(x, y, width, height);
      // add attributes
      QJsonArray attributes = annotation.value("attributes").toArray();
      for (QJsonValue attribute : attributes) {
        unsigned long atid = attribute.toString().toLong();
        AnnotatorLib::Attribute *at = session->getAttribute(atid);
        if (at != nullptr) a->addAttribute(at);
      }
      session->addAnnotation(a);
    }
  }
}

// NOTE: Not needed anymore. Since objects take care for the correct order
// (based on frame-number)!
// void JSONLoader::loadAnnotationsNextPrevious(QJsonObject &json, Session
// *session)
//{
//    QJsonArray annotations = json.value("annotations").toArray();
//    for(QJsonValue value: annotations){
//        QJsonObject annotation = value.toObject();
//        unsigned long id = annotation["id"].toString().toLong();
//        AnnotatorLib::Annotation * a = session->getAnnotation(id);

//        if(annotation.contains("previous")){
//            unsigned long previousId =
//            annotation["previous"].toString().toLong();
//            a->setPrevious(session->getAnnotation(previousId));
//        }

//        if(annotation.contains("next")){
//            unsigned long nextId = annotation["next"].toString().toLong();
//            a->setNext(session->getAnnotation(nextId));
//        }
//    }
//}

// static attributes (if any)

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of JSONLoader class body
 ************************************************************/
