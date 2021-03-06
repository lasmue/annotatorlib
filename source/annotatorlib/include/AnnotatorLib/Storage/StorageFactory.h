// Copyright 2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_STORAGEFACTORY_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_STORAGEFACTORY_H

/************************************************************
 StorageFactory class header
 ************************************************************/

#include <list>
#include <map>
#include <string>

#include <AnnotatorLib/annotatorlib_api.h>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/Storage/AbstractLoader.h>
#include <AnnotatorLib/Storage/AbstractSaver.h>
#include <AnnotatorLib/Storage/AbstractStorage.h>
#include <AnnotatorLib/Storage/StoragePlugin.h>

namespace AnnotatorLib {
namespace Storage {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API StorageFactory {
 public:
  shared_ptr<AnnotatorLib::Storage::AbstractLoader> createLoader(
      std::string type);

  std::list<std::string> availableLoader();

  shared_ptr<AnnotatorLib::Storage::AbstractSaver> createSaver(
      std::string type);

  std::list<std::string> availableSaver();

  /**
 * @brief createStorage
 * @param type
 * @return
 */
  shared_ptr<AbstractStorage> createStorage(std::string type);

  std::list<std::string> availableStorages();

  /**
   * @brief loadPlugins
   * @param dir the path to plugins
   */
  void loadPlugins(std::string dir);

  /**
   * @brief instance
   * @return singleton for StorageFactory
   */
  static StorageFactory* instance();

  ~StorageFactory();

 protected:
  void addAvailableLoader(StoragePlugin* plugin);
  void addAvailableSaver(StoragePlugin* plugin);
  void addAvailableStorage(StoragePlugin* plugin);

 private:
  StorageFactory() {}

  std::list<std::string> _availableLoader{"json", "xml"};
  std::list<std::string> _availableSaver{"json", "xml"};
  std::list<std::string> _availableStorages{"json", "xml"};

  std::map<std::string, std::shared_ptr<StoragePlugin>> plugins;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of StorageFactory class header
 ************************************************************/

#endif
