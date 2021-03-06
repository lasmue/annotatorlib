#ifndef MONGODBPLUGIN_H
#define MONGODBPLUGIN_H

#include <AnnotatorLib/Storage/StoragePlugin.h>

class MongoDBPlugin : public AnnotatorLib::Storage::StoragePlugin {
 public:
  MongoDBPlugin();

  virtual const std::string name() { return "mongodb"; }
  virtual const std::string description() { return "MongoDB Storage"; }

  virtual bool hasLoader();
  virtual bool hasSaver();
  virtual bool hasStorage();

  virtual shared_ptr<AnnotatorLib::Storage::AbstractLoader> createLoader();
  virtual shared_ptr<AnnotatorLib::Storage::AbstractSaver> createSaver();
  virtual shared_ptr<AnnotatorLib::Storage::AbstractStorage> createStorage();
};

#endif  // MONGODBPLUGIN_H
