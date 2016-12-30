// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Storage_StorageFactory_BODY

/************************************************************
 LoaderFactory class body
 ************************************************************/

#include <memory>

// include associated header file
#include "AnnotatorLib/Storage/JSONStorage.h"
#include "AnnotatorLib/Storage/MySQLStorage.h"
#include "AnnotatorLib/Storage/SQLiteStorage.h"
#include "AnnotatorLib/Storage/StorageFactory.h"
#include "AnnotatorLib/Storage/XMLStorage.h"

// Derived includes directives

namespace AnnotatorLib {
namespace Storage {

// static attributes (if any)

shared_ptr<AbstractStorage> StorageFactory::createStorage(std::string type) {
  if ("xml" == type) return createStorage(AnnotatorLib::StorageType::XML);
  if ("json" == type) return createStorage(AnnotatorLib::StorageType::JSON);
  if ("mysql" == type) return createStorage(AnnotatorLib::StorageType::MYSQL);
  if ("sqlite" == type) return createStorage(AnnotatorLib::StorageType::SQLITE);
  return createStorage(AnnotatorLib::StorageType::UNKNOWN);
}

shared_ptr<AbstractStorage> StorageFactory::createStorage(
    AnnotatorLib::StorageType type) {
  switch (type) {
    case StorageType::XML:
      return std::make_shared<XMLStorage>();
    case StorageType::JSON:
      return std::make_shared<JSONStorage>();
    case StorageType::MYSQL:
      return std::make_shared<MySQLStorage>();
    case StorageType::SQLITE:
      return std::make_shared<SQLiteStorage>();
    default:
      return nullptr;
  }
}

}  // of namespace Storage
}  // of namespace AnnotatorLib

/************************************************************
 End of LoaderFactory class body
 ************************************************************/
